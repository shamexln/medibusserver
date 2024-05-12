#pragma once

#include <S31/Sdc/Private/Discovery/WS-Discovery/Scopes.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/EnumClass.h>
#include <Framework/Utils/Public/QName.h>

#include <string>
#include <string_view>

namespace S31::Sdc::Impl
{

/**
 * @brief Class to build a client WS-Discovery Probe query to search DPWS devices.
 *
 * @ingroup S31SdcWsDiscovery
 */
class S31_CORE_EXPIMP Probe
{
    public:
        /**
         * @brief MatchBy rules for WS-Discovery scopes.
         * @details
         * Specified in <a href="http://docs.oasis-open.org/ws-dd/discovery/1.1/os/wsdd-discovery-1.1-spec-os.html#_Toc234231830">section 5.1 of WS-Discovery</a>.
         */
        enum class ScopeMatchBy
        {
            // REQ_REF(3762, "The CLIENT shall not request http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/rfc3986
            //                scope matching in WS-Discovery Probe messages.");
            // Rfc3986,
            Uuid,
            Ldap,
            Strcmp0,
            None
        };

        Probe& addDiscoveryType(const DFL::QName& type);
        Probe& add(const WSDiscoveryScope& anyUri);
        Probe& add(const WSDiscoveryScopes& anyUris);
        Probe& matchesBy(ScopeMatchBy matchRule);

        const char* matchByString() const;
        std::string typesString() const;
        std::string scopesString() const;
        bool isMatchByNone() const;

    private:
        std::string m_types;
        std::string m_scopes;
        ScopeMatchBy m_matchBy = ScopeMatchBy::Strcmp0;
};

DFL_ENUM_CLASS_STREAM_OPERATOR(Probe::ScopeMatchBy, (Uuid)(Ldap)(Strcmp0)(None))


}
