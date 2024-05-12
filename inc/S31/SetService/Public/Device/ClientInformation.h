#pragma once

#include <S31/Nomenclature/Public/Credentials.h>
#include <S31/Nomenclature/Public/Roles.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/Oids.h>

#include <cstdint>

namespace S31::SetService
{
/**
 * @brief Holds certificate information of the client eg: distinguished name, Roles
 *
 * @ingroup S31SetServiceDevice
 */
class S31_CORE_EXPIMP ClientInformation
{
    public:
        /**
         * @brief Default constructor
         */
        ClientInformation() = default;

        /**
         * @brief Constructor to set the distinguished name and the roles derived from the certificate
         * @param credentials credentials information of the client
         * @param ip client IP address
         * @param port client port number
         */
        explicit ClientInformation(S31::Nomenclature::Credentials credentials,
                                   std::string ip,
                                   std::uint16_t port);

        /**
         * @brief Check the given role.
         * @details To be used on product side when invoking a set operation that requires
         * the invoking client having a certain role.
         */
        S31::Nomenclature::Credentials::RoleAllowedResult isRoleAllowed(const DFL::Oid& role) const;

        /**
         * @brief Debug string representation containing roles from certificate.
         * @details Should be used for human readable messages (e.g., logs) only.
         */
        std::string rolesDebugString() const;

        /**
         * @brief Getter for distinguishedName
         * @returns distinguished name of the client
         */
        DFL::Crypto::DistinguishedName distinguishedName() const;

        /**
         * @brief Getter for the client IP address.
         */
        const std::string& ipAddress() const;

        /**
         * @brief Getter for the client port number.
         */
        std::uint16_t portNumber() const;

        /**
         * @brief Getter for the client certificate.
         */
        const DFL::Crypto::Certificate& certificate() const;

    private:
        S31::Nomenclature::Credentials m_credentials;
        std::string m_ipAddress;
        std::uint16_t m_port = 0;
};

}
