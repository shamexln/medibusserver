#pragma once

#include <S31/SetService/Public/Common/InvocationReport.h>
#include <S31/SetService/Public/Common/TransactionId.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Model/MdibVersion.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::SetService
{
class DeviceTransaction;

/**
 * @brief Functions for asynchronous invocation state changes.
 *
 * @details
 * When calling functions to modify the invocation state, keep in mind, that
 * only specific transitions are allowed as specified in Biceps figure 13 (section 7.4.3).
 *
 * When an instance of this class is returned from \ref SynchronousDeviceTransaction, the current
 * invocation state is \ref S31::SetService::InvocationState::Waiting "Waiting". Thus, only
 * \ref S31::SetService::InvocationState::Started "Started" or
 * \ref S31::SetService::InvocationState::Failed "Failed" are allowed initially.
 *
 * After the Started has been sent,
 * \ref S31::SetService::InvocationState::Finished "Finished",
 * \ref S31::SetService::InvocationState::FinishedWithModification "Finished with modification",
 * \ref S31::SetService::InvocationState::Cancelled "Cancelled",
 * \ref S31::SetService::InvocationState::CancelledManually "Cancelled manually" and
 * \ref S31::SetService::InvocationState::Failed "Failed" are allowed.
 *
 * @ingroup S31SetServiceDevice
 */
class S31_CORE_EXPIMP AsynchronousDeviceTransaction
{
    public:
        explicit AsynchronousDeviceTransaction(DFL::NotNull<std::shared_ptr<DeviceTransaction>> transaction);

        TransactionId transactionId() const;
        void started();

        /**
         * @name Set final invocation state.
         * @{
         */
        void finished(const DFL::Mdib::MdibVersion& mdibVersion, const boost::optional<OperationTarget>& target = boost::none);
        void finishedWithModification(const DFL::Mdib::MdibVersion& mdibVersion, const boost::optional<OperationTarget>& target = boost::none);
        void failed(const DFL::Locale::Utf8& errorMessage);
        void failed(const ErrorMessage& errorMessage);
        void failed(const ErrorMessages& errorMessages);
        void cancelled(const ErrorMessages& errorMessages);
        void cancelledManually(const ErrorMessages& errorMessages);
        /**
         * @}
         */
    private:
        DFL::NotNull<std::shared_ptr<DeviceTransaction>> m_deviceTransaction;
};

}
