#pragma once

#include <S31/Sdc/Public/Common/CoreConfiguration.h>
#include <S31/Nomenclature/Test/Public/CertHelper.h>

namespace S31::Utils::Test
{

/**
 * @brief Adds the Dräger Test Root (and staging root) to the configuration.
 */
inline void addTestRootCas(S31::CoreConfiguration& configuration)
{
    configuration.provideRootCasFunction(CertHelper::makeProvideFunction(CertHelper::rootCasWithTestRoots()));
}

/**
 * @brief Adds valid certificate chain, key, whitelist to the given configuration.
 */
inline void useTestCertificateWithAllRolesAndWildcardWhitelist(S31::CoreConfiguration& configuration, const std::string& commonName)
{
    const auto& privateKey = CertHelper::generatePrivateKey(commonName);
    configuration.provideCertificateChainFunction(CertHelper::makeProvideFunction(CertHelper::leafCertWithAllRoles(commonName, privateKey)));
    configuration.providePrivateKeyFunction(CertHelper::makeProvideFunction(privateKey));
    configuration.whitelistCheckFunction(CertHelper::makeCheckFunctionWithWildcardOnly());
}

/**
 * @brief Adds valid certificate chain, key, whitelist to the given configuration.
 */
inline void useTestCertificateWithAllRolesAndTestWhitelist(S31::CoreConfiguration& configuration, const std::string& commonName)
{
    const auto& privateKey = CertHelper::generatePrivateKey(commonName);
    configuration.provideCertificateChainFunction(CertHelper::makeProvideFunction(CertHelper::leafCertWithAllRoles(commonName, privateKey)));
    configuration.providePrivateKeyFunction(CertHelper::makeProvideFunction(privateKey));
    configuration.whitelistCheckFunction(CertHelper::makeCheckFunctionWithTestWhitelist());
}

}
