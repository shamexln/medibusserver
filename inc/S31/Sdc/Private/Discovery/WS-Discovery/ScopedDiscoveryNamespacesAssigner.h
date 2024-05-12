#pragma once

#include <S31/S31CoreExImp.h>

#include <S31/Gsoap/S31Only/NamespacesAssigner.h>

namespace S31::Sdc::Impl
{

/**
 * @brief XML namespaces needed in WS-Discovery messages
 * @ingroup S31SdcCommon
 */
constexpr const struct Namespace DiscoveryNamespaces[] = {
    { "SOAP-ENV", "http://www.w3.org/2003/05/soap-envelope", "http://schemas.xmlsoap.org/soap/envelope/", nullptr },
    { "wsa5", "http://www.w3.org/2005/08/addressing", "http://www.w3.org/*/addressing", nullptr },
    { "wsd11", "http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01", nullptr, nullptr },
    { nullptr, nullptr, nullptr, nullptr }
};

/**
 * @brief Assigns WS-Discovery related namespaces to a soap handle.
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP ScopedDiscoveryNamespacesAssigner: public S31::Gsoap::NamespacesAssigner
{
    public:
        explicit ScopedDiscoveryNamespacesAssigner(soap* soapHandle);
        explicit ScopedDiscoveryNamespacesAssigner(DFL::NotNull<struct soap*> soapHandle);
};

inline ScopedDiscoveryNamespacesAssigner::ScopedDiscoveryNamespacesAssigner(soap* soapHandle):
    S31::Gsoap::NamespacesAssigner(soapHandle, DiscoveryNamespaces)
{
}

inline ScopedDiscoveryNamespacesAssigner::ScopedDiscoveryNamespacesAssigner(DFL::NotNull<soap*> soapHandle):
    ScopedDiscoveryNamespacesAssigner(soapHandle.get())
{
}

}
