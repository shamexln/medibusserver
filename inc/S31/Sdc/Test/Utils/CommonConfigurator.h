#pragma once

#include <S31/Sdc/Public/Common/CoreConfiguration.h>
#include <S31/Sdc/Test/Utils/s31core_it_utils_exp_imp.h>

#include <Framework/Crypto/Public/DistinguishedName.h>

namespace S31::Sdc::Test
{

/**
 * @brief Configuration generator for device and client side.
 */
class S31_CORE_IT_UTIL_EXPIMP CommonConfigurator
{
    public:
        /// @brief Construct configuration generator with a default common name and whitelist
        CommonConfigurator();

        /// @brief Specify a common name for the certificate.
        CommonConfigurator& commonName(const DFL::Crypto::CommonName& certificateCommonName);

        /// @brief Specify a whitelist for the configuration.
        CommonConfigurator& whitelist(const S31::Nomenclature::Whitelist& whitelist);

        /// @brief Create a configuration with a certificate supporting all roles.
        CoreConfiguration create() const;

        /// @brief Create a configuration with a certificate supporting only specified.
        CoreConfiguration createWithRoles(const DFL::Oids& extendedKeyUsage) const;

        /**
         * @brief Provides the certificate common name used by the default configuration.
         */
        static const DFL::Crypto::CommonName& defaultCertificateCommonName();

        /**
         * @brief Creates a certificate distinguished name based on the given common name.
         */
        static DFL::Crypto::DistinguishedName distinguishedName(const DFL::Crypto::CommonName& commonName);

        /**
         * @brief Creates the distinguished name string representation in LDAP format for a given common name.
         */
        static std::string distinguishedNameInRfc4514(const DFL::Crypto::CommonName& commonName);

        /**
         * @brief Provides a default configuration with valid certificate and random port numbers suitable for most
         *        test cases.
         */
        static CoreConfiguration defaultConfiguration();

        /**
         * @brief Provides a default configuration with crypto store usage
         */
        static CoreConfiguration defaultConfigurationWithCryptoStoreUsage();

        /**
         * @brief Provides a configuration with defined certificate common name and white list.
         * @details Port numbers are configured to be assigned randomly.
         */
        static CoreConfiguration certificateConfiguration(const DFL::Crypto::CommonName& certificateCommonName,
                                                          const S31::Nomenclature::Whitelist& whitelist);

        /**
         * @brief Provides a configuration with supplied extended key usage roles
         */
        static CoreConfiguration extendedKeyUsageConfiguration(const DFL::Oids& extendedKeyUsage);

    private:
        DFL::Crypto::CommonName m_commonName;
        S31::Nomenclature::Whitelist m_whitelist;
};

}
