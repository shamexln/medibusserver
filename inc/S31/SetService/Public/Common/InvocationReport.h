#pragma once

#include <S31/SetService/Public/Common/InvocationError.h>
#include <S31/SetService/Public/Common/InvocationState.h>
#include <S31/SetService/Public/Common/TransactionId.h>

#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>
#include <Framework/Mdib/Public/Model/LocalizedTexts.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <boost/optional/optional.hpp>

#include <utility>

namespace S31::SetService
{

/**
 * @brief Error message that is described in different languages by a @ref DFL::Mdib::LocalizedText.
 * @ingroup S31SetService
 */
using ErrorMessage = DFL::Mdib::LocalizedText;

/**
 * @brief Error messages that are described by a sequence of @ref ErrorMessage objects.
 * @ingroup S31SetService
 */
using ErrorMessages = DFL::Mdib::LocalizedTexts;

/**
 * @brief Source that invoked the operation as @ref DFL::Mdib::InstanceIdentifier.
 * @ingroup S31SetService
 */
using InvocationSource = DFL::Mdib::InstanceIdentifier;

namespace Impl
{
struct InvocationInfoExtensionsTag {};
struct SetResponseExtensionsTag {};
struct OperationTargetTag {};
}

/**
 * @brief Strong typedef for extensions for InvocationInfo
 * @ingroup S31SetService
 */
using InvocationInfoExtensions = DFL::StrongTypedef<DFL::Mdib::ExtensionTypes, Impl::InvocationInfoExtensionsTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

/**
 * @brief Strong typedef for extensions for AbstractSetResponse
 * @ingroup S31SetService
 */
using SetResponseExtensions = DFL::StrongTypedef<DFL::Mdib::ExtensionTypes, Impl::SetResponseExtensionsTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

/**
 * @brief Strong typedef for the operation target in an operation invoked report.
 * @details
 * From BICEPS:
 *  >> An OPTIONAL HANDLE reference that provides a link to the CONTAINMENT TREE ENTRY affected by the transaction.
 *
 * From BICEPS:
 *  >> To identify which state of a multi-state is changed or created, OperationInvokedReport SHALL include
 *  >> msg:OperationInvokedReportPart/@@OperationTarget. This ATTRIBUTE defines the multi-state that is
 *  >> created or updated.
 * @ingroup S31SetService
 */
using OperationTarget = DFL::StrongTypedef<DFL::Mdib::Handle, Impl::OperationTargetTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

/**
 * @brief Transaction metadata that is produced by a device and consumed by a client as part of a set invocation.
 * @ingroup S31SetService
 */
class InvocationReport
{
    public:
        InvocationReport(TransactionId transactionId,
                         InvocationState invocationState,
                         boost::optional<InvocationError> invocationError,
                         ErrorMessages errorMessages,
                         const InvocationSource& invocationSource, // NOLINT(modernize-pass-by-value)
                         boost::optional<OperationTarget> operationTarget,
                         InvocationInfoExtensions invocationInfoExtension = InvocationInfoExtensions(),
                         SetResponseExtensions setResponseExtensions = SetResponseExtensions());

        /**
         * @brief Retrieves the transaction identifier.
         */
        TransactionId transactionId() const;

        /**
         * @brief Gets the invocation state that is conveyed by the invocation report.
         */
        InvocationState invocationState() const;

        /**
         * @brief Gets the invocation error if @ref InvocationReport::invocationState() returns an error state.
         */
        const boost::optional<InvocationError>& invocationError() const;

        /**
         * @brief Returns error messages if existing.
         */
        const ErrorMessages& errorMessages() const;

        /**
         * @brief Returns the source that invoked the operation.
         */
        const InvocationSource& invocationSource() const;

        /**
         * @brief Returns the operation target.
         */
        const boost::optional<OperationTarget>& operationTarget() const;

        /**
         * @brief Returns extensions used by InvocationInfo
         */
        const InvocationInfoExtensions& invocationInfoExtensions() const;

        /**
         * @brief Returns SetResponse extensions
         */
        const SetResponseExtensions& setResponseExtensions() const;

    private:
        TransactionId m_transactionId;
        InvocationState m_invocationState;
        boost::optional<InvocationError> m_invocationError;
        ErrorMessages m_errorMessages;
        InvocationSource m_invocationSource;
        boost::optional<OperationTarget> m_operationTarget;
        InvocationInfoExtensions m_invocationInfoExtensions;
        SetResponseExtensions m_setResponseExtensions;

};

/**
 * @brief Sequence of @ref InvocationReport.
 * @ingroup S31SetService
 */
using InvocationReports = std::vector<InvocationReport>;

inline InvocationReport::InvocationReport(TransactionId transactionId,
                                          InvocationState invocationState,
                                          boost::optional<InvocationError> invocationError,
                                          ErrorMessages errorMessages,
                                          const InvocationSource& invocationSource, // NOLINT(modernize-pass-by-value)
                                          boost::optional<OperationTarget> operationTarget,
                                          InvocationInfoExtensions invocationInfoExtensions,
                                          SetResponseExtensions setResponseExtensions) :
        m_transactionId(transactionId),
        m_invocationState(invocationState),
        m_invocationError(invocationError),
        m_errorMessages(std::move(errorMessages)),
        m_invocationSource(invocationSource),
        m_operationTarget(std::move(operationTarget)),
        m_invocationInfoExtensions(std::move(invocationInfoExtensions)),
        m_setResponseExtensions(std::move(setResponseExtensions))
{
}

inline TransactionId InvocationReport::transactionId() const
{
    return m_transactionId;
}

inline InvocationState InvocationReport::invocationState() const
{
    return m_invocationState;
}

inline const boost::optional<InvocationError>& InvocationReport::invocationError() const
{
    return m_invocationError;
}

inline const ErrorMessages& InvocationReport::errorMessages() const
{
    return m_errorMessages;
}

inline const InvocationSource& InvocationReport::invocationSource() const
{
    return m_invocationSource;
}

inline const boost::optional<OperationTarget>& InvocationReport::operationTarget() const
{
    return m_operationTarget;
}

inline const InvocationInfoExtensions& InvocationReport::invocationInfoExtensions() const
{
    return m_invocationInfoExtensions;
}

inline const SetResponseExtensions& InvocationReport::setResponseExtensions() const
{
    return m_setResponseExtensions;
}

}
