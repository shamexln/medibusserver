#pragma once

#include <S31/Sdc/Private/Common/ErrorDefinitions.h>
#include <S31/Sdc/Public/Common/ErrorDefinitions.h>

#include <Framework/Format/Public/OptionalIo.h>

namespace S31::Sdc::Impl
{

/**
 * Checks whether the error detail is a SSL error or not.
 * @ingroup S31SdcClient
 */
template <typename T_Error1, typename... T_Errors>
inline bool isOneOfAndContainsSslError(const S31::Utils::Error& error, typename std::enable_if<sizeof...(T_Errors) == 0>::type* = nullptr)
{
    if (auto typedErr = error.is<T_Error1>())
    {
        if (typedErr->wrappedError.has_value())
        {
            try
            {
                if(typedErr->wrappedError.type() == typeid(Errors::Ssl))
                {
                    return true;
                }
            }
            catch (std::bad_any_cast&)
            {
            }
        }
    }
    return false;
}

/**
 * Checks whether the error detail is a SSL error or not.
 * @ingroup S31SdcClient
 */
template <typename T_Error1, typename T_Error2, typename... T_Errors>
inline bool isOneOfAndContainsSslError(const S31::Utils::Error& error)
{
    if (isOneOfAndContainsSslError<T_Error1>(error))
    {
        return true;
    }
    return isOneOfAndContainsSslError<T_Error2, T_Errors...>(error);
}

/**
 * Make a public error from a private error.
 * @param error An error that is private or public.
 * @returns An error that is a public error. The error message is preserved.
 * @ingroup S31SdcClient
 */
inline S31::Utils::Error mapToPublicError(const S31::Utils::Error& error)
{
    if (isOneOfAndContainsSslError<
            Errors::WSSubscribeError,
            Errors::WSUnsubscribeError,
            Errors::WSRenewError,
            Errors::WSGetStatusError>(error)
        || error.isOneOf<Errors::Ssl,
                         Errors::PeerNotWhitelisted,
                         Errors::PeerMissingSDCRoles,
                         Errors::PeerMissingCertificate>())
    {
        return Utils::makeError(Sdc::Errors::SslFailure{}, error.message());
    }
    if (auto e = error.is<Errors::Http>())
    {
        auto mappedError = Utils::makeError(Sdc::Errors::CommunicationFailure{}, error.message());
        mappedError.messageStream() << "(" << e->httpStatusCode << ")";
        return mappedError;
    }
    if (error.isOneOf<
            Errors::WSSubscriptionEndError,
            Errors::WSSubscribeError,
            Errors::WSUnsubscribeError,
            Errors::WSRenewError,
            Errors::WSGetStatusError,
            Errors::SubscriptionUnexpectlyEnded,
            Errors::MissingPhysicalAddress,
            Errors::InvalidHostedServiceConfiguration,
            Errors::ResolveXAddrs,
            Errors::GetDeviceMetadataProcessing,
            Errors::SubscriptionCanceledByDevice,
            Errors::Tcp,
            Errors::GsoapEof,
            Errors::GsoapClientFault,
            Errors::GsoapServerFault,
            Errors::PayloadTooLarge
            >())
    {
        return Utils::makeError(Sdc::Errors::CommunicationFailure{}, error.message());
    }
    if (error.isOneOf<
             Errors::IncomingDataNotUnderstood,
             Errors::WrongReportSequence,
             Errors::StateDescriptorVersionMismatch,
             Errors::LocationContextMismatch,
             Errors::UnknownMustUnderstandExtension
             >())
    {
        return Utils::makeError(S31::Sdc::Errors::DataInvalid{}, error.message());
    }
    if (error.isOneOf<Sdc::Impl::Errors::MdibSequenceChanged>())
    {
        return Utils::makeError(Sdc::Errors::MdibSequenceChanged{}, error.message());
    }
    if (error.isOneOf<
             Sdc::Errors::UserDisconnected,
             Sdc::Errors::Shutdown
             >())
    {
        return error;
    }

    return Utils::makeError(Sdc::Errors::Generic{}, error.message());
}

}
