#pragma once

#include <S31/SetService/Public/Common/InvocationReport.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Model/Component/Mds.h>
#include <Framework/Mdib/Public/Model/Handle.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Represents a report part that can be used for OperationInvokedReport messages.
 * @ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP OperationInvokedReportPart
{
    public:
        /**
         * @brief Constructor that accepts the \ref SetService::InvocationReport "invocation report".
         */
        OperationInvokedReportPart(const S31::SetService::InvocationReport& invocationReport, // NOLINT(modernize-pass-by-value)
                                   DFL::Mdib::Handle operationHandle);

        /**
         * @brief Retrieves the transaction identifier.
         */
        S31::SetService::TransactionId transactionId() const;

        /**
         * @brief Gets the invocation state that is conveyed by the invocation report.
         */
        S31::SetService::InvocationState invocationState() const;

        /**
         * @brief Gets the invocation error if \ref SetService::InvocationReport::invocationState() returns an error state.
         */
        const boost::optional<S31::SetService::InvocationError>& invocationError() const;

        /**
         * @brief Returns error messages if existing.
         */
        const S31::SetService::ErrorMessages& errorMessages() const;

        /**
         * @brief Returns the source that invoked the operation.
         */
        const S31::SetService::InvocationSource& invocationSource() const;

        /**
         * @brief Returns extensions used by the \ref SetService::InvocationReport InvocationInfo.
         */
        const S31::SetService::InvocationInfoExtensions& invocationInfoExtensions() const;

        /**
         * @brief Returns the operation handle of the invoked report.
         */
        const DFL::Mdib::Handle& operationHandle() const;

        /**
         * @brief Returns the operation target handle.
         */
        const boost::optional<S31::SetService::OperationTarget>& targetHandle() const;

        /**
         * @brief If set, this function returns the source MDS.
         * @details If no source MDS is returned, then the MDIB is required to possess one MDS only.
         */
        const boost::optional<DFL::Mdib::MdsHandle>& sourceMdsHandle() const;

    private:
        S31::SetService::InvocationReport m_invocationReport;
        DFL::Mdib::Handle m_operationHandle;
        boost::optional<DFL::Mdib::MdsHandle> m_sourceMdsHandle;
};

}
