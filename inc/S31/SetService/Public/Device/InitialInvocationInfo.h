#pragma once

#include <S31/SetService/Public/Common/InvocationError.h>
#include <S31/SetService/Public/Common/InvocationReport.h>
#include <S31/SetService/Public/Common/InvocationState.h>
#include <S31/SetService/Public/Common/TransactionId.h>

#include <Framework/Mdib/Public/Model/MdibVersion.h>

#include <boost/optional/optional.hpp>

#include <utility>

namespace S31::SetService
{

/**
 * @brief Invocation information that is used to derive abstract set response payload.
 * @details Note that data in abstract set response and an invocation report are
 * slightly different: the operation target can be found only in the report.
 * @ingroup S31SetServiceDevice
 */
class InitialInvocationInfo
{
    public:
        /**
         * @brief Constructor.
         * @details Depending on state/error not all parameters carry meaning.
         */
        InitialInvocationInfo(TransactionId transactionId,
                              InvocationState invocationState,
                              const boost::optional<InvocationError>& invocationError,
                              ErrorMessages errorMessages,
                              const DFL::Mdib::MdibVersion& mdibVersion, // NOLINT(modernize-pass-by-value)
                              DFL::Mdib::ExtensionTypes extensions = DFL::Mdib::ExtensionTypes{});

        /**
         * @brief Retrieves the transaction identifier.
         */
        TransactionId transactionId() const;

        /**
         * @brief Gets the invocation state that is conveyed by the invocation report.
         */
        InvocationState invocationState() const;

        /**
         * @brief Gets the invocation error if @ref InitialInvocationInfo::invocationState() returns an error state.
         */
        boost::optional<InvocationError> invocationError() const;

        /**
         * @brief Returns error messages if existing.
         */
        const ErrorMessages& errorMessages() const;

        /**
         * @brief Returns the assigned MDIB version.
         */
        const DFL::Mdib::MdibVersion& mdibVersion() const;

        /**
         * @brief Returns InvocationInfo extensions if they exist.
         */
        const DFL::Mdib::ExtensionTypes& extensions() const;


    private:
        TransactionId m_transactionId;
        InvocationState m_invocationState;
        boost::optional<InvocationError> m_invocationError;
        ErrorMessages m_errorMessages;
        DFL::Mdib::MdibVersion m_mdibVersion;
        DFL::Mdib::ExtensionTypes m_extensions;
};

inline InitialInvocationInfo::InitialInvocationInfo(TransactionId transactionId,
                                                    InvocationState invocationState,
                                                    const boost::optional<InvocationError>& invocationError,
                                                    ErrorMessages errorMessages,
                                                    const DFL::Mdib::MdibVersion& mdibVersion, // NOLINT(modernize-pass-by-value)
                                                    DFL::Mdib::ExtensionTypes extensions) :
        m_transactionId(transactionId),
        m_invocationState(invocationState),
        m_invocationError(invocationError),
        m_errorMessages(std::move(errorMessages)),
        m_mdibVersion(mdibVersion),
        m_extensions(std::move(extensions))
{
}

inline TransactionId InitialInvocationInfo::transactionId() const
{
    return m_transactionId;
}

inline InvocationState InitialInvocationInfo::invocationState() const
{
    return m_invocationState;
}

inline boost::optional<InvocationError> InitialInvocationInfo::invocationError() const
{
    return m_invocationError;
}

inline const ErrorMessages& InitialInvocationInfo::errorMessages() const
{
    return m_errorMessages;
}

inline const DFL::Mdib::MdibVersion& InitialInvocationInfo::mdibVersion() const
{
    return m_mdibVersion;
}

inline const DFL::Mdib::ExtensionTypes& InitialInvocationInfo::extensions() const
{
    return m_extensions;
}

}
