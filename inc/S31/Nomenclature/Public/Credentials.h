#pragma once

#include <S31/Nomenclature/Public/CryptoFunctions.h>
#include <S31/Nomenclature/Public/Whitelist.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/Utf8.h>
#include <Framework/Utils/Public/Oids.h>
#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Crypto/Public/Certificates.h>
#include <Framework/Crypto/Public/DistinguishedName.h>

#include <string>

namespace S31::Nomenclature
{
namespace Impl
{
struct PeerCertificateTag;
struct RootCertificateTag;
}

/**
 * @brief Strong type for the leaf @ref DFL::Crypto::Certificate "Certificate" of a communication peer.
 * @ingroup S31Nomenclature
 */
using PeerCertificate = DFL::StrongTypedef<DFL::Crypto::Certificate, Impl::PeerCertificateTag>;

/**
 * @brief Strong type for the root @ref DFL::Crypto::Certificate "Certificate" of a communication peer.
 * @ingroup S31Nomenclature
 */
using RootCertificate = DFL::StrongTypedef<DFL::Crypto::Certificate, Impl::RootCertificateTag>;

/**
 * @brief Provides access to credentials of a communication peer.
 * @details
 * In this class all credential handling is aggregated.
 * @ingroup S31Nomenclature
 */
class S31_CORE_EXPIMP Credentials
{
    public:
        /**
         * @brief Default constructor without any credentials.
         */
        Credentials() = default;

        /**
         * @brief Constructor with all required data.
         */
        Credentials(PeerCertificate peerCertificate,
                    WhiteListingState whitelistCheck,
                    ProvideRoleAuthorizationListFunction provideRoleAuthorizationList,
                    RootCertificate rootCertificate);

        /**
         * @brief Checks if either SDC device or SDC client.
         */
        [[nodiscard]] bool isSdcParticipant() const;

        /**
         * @brief Result of a isRoleAllowed() call.
         * @details If role is not allowed then a message containing the reason is returned.
         */
        struct [[nodiscard]] RoleAllowedResult
        {
            explicit operator bool() const noexcept
            {
                return isAllowed;
            }
            bool operator==(bool rhs) const
            {
                return (isAllowed == rhs);
            }
            bool operator!=(bool rhs) const
            {
                return (isAllowed != rhs);
            }

            bool isAllowed{};
            DFL::Locale::Utf8 notAllowedReason;
        };

        /**
         * @brief Checks if a specific role is allowed depending on all credential information.
         * @details
         * Instead of just checking the extended key usage, this function
         * may also cross-check the root with additional restriction like
         * the Role Authorization List (RAL).
         */
        RoleAllowedResult isRoleAllowed(const DFL::Oid& role) const noexcept;

        /**
         * @brief Checks that all specified roles are allowed depending on all credential information.
         * @details
         * Instead of just checking the extended key usage, this function
         * may also cross-check the root with additional restriction like
         * the Role Authorization List (RAL).
         */
        RoleAllowedResult areAllRolesAllowed(const DFL::Oids& roles) const noexcept;

        /**
         * @brief Returns all roles associated with these Credentials.
         * @details
         * These roles come from the peer certificate. They are not filtered by
         * whitelist or role authorization list - i.e. if a role is listed
         * here then this does not imply (in some cases) that the peer is trusted
         * or authorized for the role functionlity (e.g. remote control releated roles).
         * @see isRoleAllowed() @see areAllRolesAllowed().
         */
        [[nodiscard]] DFL::Oids allRoles() const noexcept;

        /**
         * @brief \ref DFL::Crypto::DistinguishedName associated with these Credentials
         */
        [[nodiscard]] DFL::Crypto::DistinguishedName distinguishedName() const noexcept;

        /**
         * @brief DEPRECATED: Common name in UTF-8 format.
         * @deprecated Use \ref rawCommonName() or \ref sanitizedCommonName().
         */
        [[nodiscard]] std::string commonName() const;

        /**
         * @brief UTF-8 string with common name.
         * @details
         * Attention: This might contain all kinds of unicode code points.
         */
        [[nodiscard]] DFL::Locale::Utf8 rawCommonName() const;

        /**
         * @brief Special characters (e.g., non-printable ASCII) are hex-encoded.
         * @details
         * In a common name of a certificate the whole range of UTF-8 code
         * points is allowed. To make sure that any postprocessing software
         * (e.g., of log files) has no issue "special" characters are replaced.
         * The function uses encoding according RFC 4514 as this exists in DFL.
         */
        [[nodiscard]] std::string sanitizedCommonName() const;

        /**
         * @brief Debug string representation containing roles from certificate.
         * @details Should be used for human readable messages (e.g., logs) only.
         * Not all roles from the certificate are allowed to be used.
         * This might depend on other certificate information like which root signed the
         * certificate chain etc.
         */
        [[nodiscard]] std::string rolesDebugString() const;

        /**
         * @brief The certificate from the peer.
         */
        [[nodiscard]] const DFL::Crypto::Certificate& peerCertificate() const noexcept;

        /**
         * @brief The @ref WhiteListingState for the peer.
         */
        [[nodiscard]] WhiteListingState whiteListingState() const noexcept;

    private:
        DFL::Crypto::Certificate m_peerCertificate;
        WhiteListingState m_whitelistCheck = WhiteListingState::NotWhitelisted;
        ProvideRoleAuthorizationListFunction m_provideRoleAuthorizationList;
        DFL::Crypto::Certificates m_rootCertificate;
};

}
