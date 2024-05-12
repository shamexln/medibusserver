#pragma once

#include <Framework/Utils/Public/StrongTypedef.h>
#include <S31/SetService/Public/Common/InvocationReport.h>
#include <S31/SetService/Public/Common/OperationHandle.h>

#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/MdibVersion.h>

#include <utility>

namespace S31::SetService
{

/**
 * @brief @ref InvocationReport that is used for client report notifications.
 * @ingroup S31SetService
 */
class ClientInvocationReport: public InvocationReport
{
    public:
        ClientInvocationReport(const DFL::Mdib::MdibVersion& mdibVersion, // NOLINT(modernize-pass-by-value)
                               OperationHandle operationHandle,
                               const boost::optional<OperationTarget>& targetHandle,
                               TransactionId transactionId,
                               InvocationState invocationState,
                               boost::optional<InvocationError> invocationError,
                               const ErrorMessages& errorMessages,
                               const InvocationSource& invocationSource,
                               const InvocationInfoExtensions& invocationInfoExtension = InvocationInfoExtensions(),
                               const SetResponseExtensions& setResponseExtensions = SetResponseExtensions());

        /**
         * @brief Retrieves the @ref DFL::Mdib::MdibVersion "MDIB version" this report is assigned to.
         * @details When a client receives a successful final report, the MDIB version can be used to connect the
         * report with the MDIB snapshot where the requested operation invocation has been applied.
         */
        const DFL::Mdib::MdibVersion& mdibVersion() const;

        /**
         * @brief Untyped operation handle that relates to this report.
         * @details A client should know in advance to which strong-typed object an invocation report belongs
         * by means of the connected transaction identifier. The operation handle might only be interesting in cases
         * where a client tracks invocation reports from other SDC participants.
         */
        const DFL::Mdib::Handle& operationHandle() const;

        /**
         * @brief Untyped handle relating to the target of the operation
         * @deprecated use typesafe variant: operationTarget().
         */
        boost::optional<DFL::Mdib::Handle> targetHandle() const;


    private:
        DFL::Mdib::MdibVersion m_mdibVersion;
        OperationHandle m_operationHandle;
};

namespace Impl
{
    struct ClientSetResponseTag;
}

using ClientSetResponse = ::DFL::StrongTypedef<ClientInvocationReport, Impl::ClientSetResponseTag>;


/**
 * @brief Compares two client invocation reports on equality.
 * @ingroup S31SetService
 */
bool operator==(const ClientInvocationReport& lhs, const ClientInvocationReport& rhs);

/**
 * @brief Compares two client invocation reports on inequality.
 * @ingroup S31SetService
 */
bool operator!=(const ClientInvocationReport& lhs, const ClientInvocationReport& rhs);

/**
 * @brief Sequence of @ref ClientInvocationReport.
 * @ingroup S31SetService
 */
using ClientInvocationReports = std::vector<ClientInvocationReport>;

inline ClientInvocationReport::ClientInvocationReport(const DFL::Mdib::MdibVersion& mdibVersion, // NOLINT(modernize-pass-by-value)
                                                      OperationHandle operationHandle,
                                                      const boost::optional<OperationTarget>& targetHandle,
                                                      TransactionId transactionId,
                                                      InvocationState invocationState,
                                                      boost::optional<InvocationError> invocationError,
                                                      const ErrorMessages& errorMessages,
                                                      const InvocationSource& invocationSource,
                                                      const InvocationInfoExtensions& invocationInfoExtension,
                                                      const SetResponseExtensions& setResponseExtension) :
        InvocationReport(transactionId, invocationState, invocationError, errorMessages, invocationSource, targetHandle, invocationInfoExtension, setResponseExtension),
        m_mdibVersion(mdibVersion),
        m_operationHandle(std::move(operationHandle))
{
}

inline const DFL::Mdib::MdibVersion& ClientInvocationReport::mdibVersion() const
{
    return m_mdibVersion;
}

inline const DFL::Mdib::Handle& ClientInvocationReport::operationHandle() const
{
    return m_operationHandle.get();
}

inline boost::optional<DFL::Mdib::Handle> ClientInvocationReport::targetHandle() const
{
    if (!operationTarget())
    {
        return boost::none;
    }

    return operationTarget()->get();
}

inline bool operator==(const ClientInvocationReport& lhs, const ClientInvocationReport& rhs)
{
    return lhs.transactionId() == rhs.transactionId() &&
            lhs.invocationState() == rhs.invocationState() &&
            lhs.invocationError() == rhs.invocationError() &&
            lhs.errorMessages() == rhs.errorMessages() &&
            lhs.invocationSource() == rhs.invocationSource() &&
            lhs.operationTarget() == rhs.operationTarget() &&
            lhs.invocationInfoExtensions() == rhs.invocationInfoExtensions() &&
            lhs.setResponseExtensions() == rhs.setResponseExtensions() &&
            lhs.mdibVersion() == rhs.mdibVersion() &&
            lhs.operationHandle() == rhs.operationHandle();
}

inline bool operator!=(const ClientInvocationReport& lhs, const ClientInvocationReport& rhs)
{
    return !(lhs == rhs);
}

}
