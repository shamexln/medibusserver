#pragma once

#include <S31/Safety/Public/Context.h>
#include <S31/Safety/Public/DualChannel.h>
#include <S31/SetService/Public/Common/TransactionId.h>
#include <S31/SetService/Public/Device/AsynchronousDeviceTransaction.h>
#include <S31/SetService/Public/Device/ClientInformation.h>
#include <S31/SetService/Public/Device/InitialInvocationInfo.h>

#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Model/MdibVersion.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::SetService
{
class DeviceTransaction;

/**
 * @brief Transaction context for synchronous set response message.
 *
 * @details The callback has to decide, if the remote control request should be handled
 * synchronously or asynchronously. In first case the final invocation state is set by calling
 *  - \ref finished(),
 *  - \ref finishedWithModification() or
 *  - \ref failed().
 *
 *  For asynchronous handling it is possible to get ownership of the transaction by calling \ref waiting().
 *
 * @ingroup S31SetServiceDevice
 */
class S31_CORE_EXPIMP SynchronousDeviceTransaction
{
    public:
        SynchronousDeviceTransaction(DFL::NotNull<std::shared_ptr<DeviceTransaction>> transaction,
                                     const DFL::Mdib::MdibVersion& mdibVersion); // NOLINT(modernize-pass-by-value)

        SynchronousDeviceTransaction(const SynchronousDeviceTransaction&) = default;
        SynchronousDeviceTransaction& operator=(const SynchronousDeviceTransaction&) = default;

        /**
         * @brief Sends initial invocation info report if not already done.
         */
        ~SynchronousDeviceTransaction() noexcept;

        TransactionId transactionId() const;
        Safety::Context safetyContext() const;
        Safety::DualChannel dualChannel() const;

        /**
         * @brief Getter function to get \ref S31::SetService::ClientInformation
         */
        SetService::ClientInformation clientInformation() const;

        /**
         * @brief Access extensions from the BICEPS message %AbstractSet request
         */
        const DFL::Mdib::ExtensionTypes& serviceExtensions() const;

        /**
         * @name Synchronous success
         * The given MDIB version shall be the one when the MDIB was modified.
         *
         * See SDC specification:
         * > R0065: An SDC SERVICE PROVIDER SHALL send any modification that is a result of a
         * > remote-control command within the same MDIB version as the msg:OperationInvokedReport that
         * > indicate the finalization of the execution.
         * @{
         */
        /**
         * @brief Indicates, that the remote control request was applied without modification.
         */
        void finished(const DFL::Mdib::MdibVersion& mdibVersion, const boost::optional<OperationTarget>& target = boost::none);
        /**
         * @brief Indicates, that the remote control request was applied with modification.
         * @details In this case the client has to cross check with the new MDIB what
         * has been applied to the MDIB.
         */
        void finishedWithModification(const DFL::Mdib::MdibVersion& mdibVersion, const boost::optional<OperationTarget>& target = boost::none);
        /**
         * @}
         */

        /**
         * @name Synchronous fail
         * Provide one or more error messages for the SDC client.
         * @{
         */

        /**
         * @brief Fail with non localized error message.
         */
        void failed(const DFL::Locale::Utf8& errorMessage);

        /**
         * @brief Fail with non localized error message.
         */
        void failed(const ErrorMessage& errorMessage);

        /**
         * @brief Fail with localized error messages.
         */
        void failed(const ErrorMessages& errorMessages);

        /**
         * @}
         */

        /**
         * @brief For asynchronous handling of set requests.
         */
        DFL::NotNull<std::shared_ptr<AsynchronousDeviceTransaction>> waiting();

        InitialInvocationInfo initialInvocationInfo() const;


    private:
        /**
         * @brief Trigger sending initial invocation info report.
         */
        void sendInitialInvocationReport();

        bool assignDataNowAllowed();

        InvocationState m_invocationState{InvocationState::Failed};
        boost::optional<InvocationError> m_invocationError{InvocationError::Other};
        ErrorMessages m_errorMessages;
        DFL::Mdib::MdibVersion m_mdibVersion;
        boost::optional<OperationTarget> m_operationTarget;

        DFL::NotNull<std::shared_ptr<DeviceTransaction>> m_transaction;
        bool m_initialDataAssigned = false;
        bool m_initialReportSent = false;
};

}
