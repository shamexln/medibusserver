#pragma once

#include <S31/Safety/Public/Context.h>
#include <S31/Safety/Public/DualChannel.h>
#include <S31/SetService/Public/Common/InvocationError.h>
#include <S31/SetService/Public/Common/InvocationReport.h>
#include <S31/SetService/Public/Common/InvocationState.h>
#include <S31/SetService/Public/Common/TransactionId.h>
#include <S31/SetService/Public/Device/ClientInformation.h>

#include <Framework/Mdib/Public/LocalMdibAccess.h>
#include <Framework/Mdib/Public/Model/ExtensionType.h>
#include <Framework/Mdib/Public/Model/MdibVersion.h>

#include <algorithm>

namespace S31::SetService
{

/**
 * @brief Transaction context on the device side.
 * @details Maintains different transaction information and allows to fire invocation state changes.
 * @ingroup S31SetServiceDevice
 */
class DeviceTransaction
{
    public:
        virtual ~DeviceTransaction() noexcept = default;

        /**
         * @brief Retrieve the transaction identifier.
         */
        virtual TransactionId transactionId() const = 0;

        /**
         * @brief Fire (and forget) an invocation report.
         * @details
         *
         * - This is a non-blocking function that returns immediately.
         * - The latest @ref DFL::Mdib::MdibVersion is appended automatically. If you wish to add a custom @ref DFL::Mdib::MdibVersion,
         *   then use @ref S31::SetService::DeviceTransaction::sendInvocationReport(const DFL::Mdib::MdibVersion&, const InvocationReport&).
         *
         */
        virtual void sendInvocationReport(const InvocationReport& invocationReport) = 0;

        /**
         * @brief Fire (and forget) an invocation report.
         * @details This is a non-blocking function that returns immediately.
         * @param mdibVersion The @ref DFL::Mdib::MdibVersion that is appended to the report. When sending final reports, this version should
         * match the MDIB snapshot in which the requested changes have been applied.
         * @param invocationReport Report to send
         */
        virtual void sendInvocationReport(const DFL::Mdib::MdibVersion& mdibVersion, const InvocationReport& invocationReport) = 0;

        /**
         * @brief Sends a *started* report.
         * @details Shortcut for @ref sendInvocationReport() and @ref started()
         */
        void sendStarted();

        /**
         * @brief Sends a *finished* report.
         */
        void sendFinished(const DFL::Mdib::MdibVersion& mdibVersion, const boost::optional<OperationTarget>& target);

        /**
         * @brief Sends a *finishedWithModification* report.
         */
        void sendFinishedWithModification(const DFL::Mdib::MdibVersion& mdibVersion, const boost::optional<OperationTarget>& target);

        /**
         * @brief Sends a *failed* report.
         * @details Shortcut for @ref sendInvocationReport() and @ref failed()
         * @param errorMessage text describing the error, will be sent out as englisch ('en')
         */
        void sendFailed(const DFL::Locale::Utf8& errorMessage);
        void sendFailed(const ErrorMessages& errorMessages);

        /**
         * @brief Sends a *cancelled* report.
         * @details Shortcut for @ref sendInvocationReport() and @ref cancelled()
         * @param errorMessage text describing the error, will be sent out as english ('en')
         */
        void sendCancelled(const DFL::Locale::Utf8& errorMessage);
        void sendCancelled(const ErrorMessages& errorMessages);

        /**
         * @brief Sends a *cancelledManually* report.
         * @details Shortcut for @ref sendInvocationReport() and @ref cancelledManually()
         * @param errorMessage text describing the error, will be sent out as englisch ('en')
         */
        void sendCancelledManually(const DFL::Locale::Utf8& errorMessage);
        void sendCancelledManually(const ErrorMessages& errorMessages);

        /**
         * @brief The caller of the underlying operation.
         */
        virtual const InvocationSource& invocationSource() const = 0;

        /**
         * @brief Shortcut to create a *started* report based on the device transaction's @ref TransactionId "transaction id" and @ref InvocationSource "invocation source".
         */
        InvocationReport started() const;

        /**
         * @brief Shortcut to create a *failed* report based on the device transaction's @ref TransactionId "transaction id" and @ref InvocationSource "invocation source".
         * @details
         * - The @ref InvocationReport::invocationError() is set to @ref InvocationError::Other
         * - The @c errorMessage argument is passed as english (i.e., en) text.
         */
        InvocationReport failed(const DFL::Locale::Utf8& errorMessage) const;
        InvocationReport failed(const ErrorMessages& errorMessages) const;

        /**
         * @brief Shortcut to create a *cancelled* report based on the device transaction's @ref TransactionId "transaction id" and @ref InvocationSource "invocation source".
         * @details
         * - The @ref InvocationReport::invocationError() is set to @ref InvocationError::Other
         * - The @c errorMessage argument is passed as english (i.e., en) text.
         */
        InvocationReport cancelled(const DFL::Locale::Utf8& errorMessage) const;
        InvocationReport cancelled(const ErrorMessages& errorMessages) const;

        /**
         * @brief Shortcut to create a *cancelled manually* report based on the device transaction's @ref TransactionId "transaction id" and @ref InvocationSource "invocation source".
         * @details
         * - The @ref InvocationReport::invocationError() is set to @ref InvocationError::Other
         * - The @c errorMessage argument is passed as english (i.e., en) text.
         */
        InvocationReport cancelledManually(const DFL::Locale::Utf8& errorMessage) const;
        InvocationReport cancelledManually(const ErrorMessages& errorMessages) const;

        /**
         * @brief getter function to get @ref S31::Safety::Context
         */
        virtual Safety::Context safetyContext() const = 0;

        /**
         * @brief getter function to get @ref S31::Safety::DualChannel
         */
        virtual Safety::DualChannel dualChannel() const = 0;

        /**
         * @brief getter function to get @ref S31::SetService::ClientInformation
         */
        virtual SetService::ClientInformation clientInformation() const = 0;

        /**
         * @brief getter function to get @ref DFL::Mdib::ExtensionTypes from the service request
         */
        virtual const DFL::Mdib::ExtensionTypes& serviceExtensions() const = 0;

    private:
        InvocationReport successfulReport(InvocationState invocationState, const boost::optional<OperationTarget>& target) const;
        InvocationReport unsuccessfulReport(InvocationState invocationState, const DFL::Locale::Utf8& errorMessage) const;
        InvocationReport unsuccessfulReport(InvocationState invocationState, const ErrorMessages& errorMessage) const;
};

inline void DeviceTransaction::sendStarted()
{
    sendInvocationReport(started());
}

inline void DeviceTransaction::sendFinished(const DFL::Mdib::MdibVersion& mdibVersion, const boost::optional<OperationTarget>& target)
{
    sendInvocationReport(mdibVersion, successfulReport(InvocationState::Finished, target));
}

inline void DeviceTransaction::sendFinishedWithModification(const DFL::Mdib::MdibVersion& mdibVersion, const boost::optional<OperationTarget>& target)
{
    sendInvocationReport(mdibVersion, successfulReport(InvocationState::FinishedWithModification, target));
}

inline void DeviceTransaction::sendFailed(const DFL::Locale::Utf8& errorMessage)
{
    sendInvocationReport(failed(errorMessage));
}

inline void DeviceTransaction::sendFailed(const ErrorMessages& errorMessages)
{
    sendInvocationReport(failed(errorMessages));
}

inline void DeviceTransaction::sendCancelled(const DFL::Locale::Utf8& errorMessage)
{
    sendInvocationReport(cancelled({DFL::Mdib::LocalizedText{errorMessage, DFL::Locale::LanguageTag{"en"}}}));
}

inline void DeviceTransaction::sendCancelled(const ErrorMessages& errorMessages)
{
    sendInvocationReport(cancelled(errorMessages));
}

inline void DeviceTransaction::sendCancelledManually(const DFL::Locale::Utf8& errorMessage)
{
    sendInvocationReport(cancelledManually(errorMessage));
}

inline void DeviceTransaction::sendCancelledManually(const ErrorMessages& errorMessages)
{
    sendInvocationReport(cancelledManually(errorMessages));
}

inline InvocationReport DeviceTransaction::started() const
{
    return successfulReport(InvocationState::Started, boost::none);
}

inline InvocationReport DeviceTransaction::failed(const DFL::Locale::Utf8& errorMessage) const
{
    return unsuccessfulReport(InvocationState::Failed, errorMessage);
}

inline InvocationReport DeviceTransaction::failed(const ErrorMessages& errorMessages) const
{
    return unsuccessfulReport(InvocationState::Failed, errorMessages);
}

inline InvocationReport DeviceTransaction::cancelled(const DFL::Locale::Utf8& errorMessage) const
{
    return unsuccessfulReport(InvocationState::Cancelled, errorMessage);
}

inline InvocationReport DeviceTransaction::cancelled(const ErrorMessages& errorMessages) const
{
    return unsuccessfulReport(InvocationState::Cancelled, errorMessages);
}

inline InvocationReport DeviceTransaction::cancelledManually(const DFL::Locale::Utf8& errorMessage) const
{
    return unsuccessfulReport(InvocationState::CancelledManually, errorMessage);
}

inline InvocationReport DeviceTransaction::cancelledManually(const ErrorMessages& errorMessages) const
{
    return unsuccessfulReport(InvocationState::CancelledManually, errorMessages);
}

inline InvocationReport DeviceTransaction::successfulReport(InvocationState invocationState, const boost::optional<OperationTarget>& target) const
{
    return {transactionId(), invocationState, boost::none, ErrorMessages(), invocationSource(), target};
}

inline InvocationReport DeviceTransaction::unsuccessfulReport(InvocationState invocationState, const DFL::Locale::Utf8& errorMessage) const
{
    return unsuccessfulReport(invocationState, ErrorMessages{ErrorMessage(errorMessage, DFL::Locale::LanguageTag(std::string("en")))});
}

inline InvocationReport DeviceTransaction::unsuccessfulReport(InvocationState invocationState, const ErrorMessages& errorMessages) const
{
    return {transactionId(),
            invocationState,
            boost::optional<InvocationError>(InvocationError::Other),
            errorMessages,
            invocationSource(),
            boost::none};
}

}
