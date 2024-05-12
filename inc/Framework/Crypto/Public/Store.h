#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/AttributeTypeAndValue.h>
#include <Framework/Crypto/Public/RootCas.h>

#include <Framework/Utils/Public/Application/Identifier.h>
#include <Framework/Utils/Public/Key.h>
#include <Framework/Utils/Public/Oids.h>

#include <boost/optional/optional.hpp>

#include <string>

namespace DFL::Crypto
{
class CertificateChain;
class Csr;
class Table;
class Whitelist;
class RoleAuthorizationList;

/**
 * @brief Stores the necessary states (key-pair, CSR, certificate, ...) to be
 * able to obtain a signed certificate from a PKI as well as authorization
 * configurations like whitelists, third-party CAs and RALs.
 *
 * The workflow on how to obtain a signed certificate is documented in the
 * library documentation.
 *
 * Since the store persists sensitive data (private keys of the certificates)
 * it is encrypted using @ref DFL::Crypto::Cipher::Symmetric::DeviceSpecific.
 * Please read its documentation to check what encryption method is used on your
 * platform and how to customize it if it is not secure enough for this need.
 *
 * @ref DFL::Crypto::Environment::config is used to configure the path where the
 * store data is saved in.
 *
 * @note There can only be one store per process. If all processes shall be
 * using the same store than ensure that all processes use the same file path.
 * In general access to the file is protected by an interprocess mutex.
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP Store
{
public:
    /**
     * @brief Optional CSR.
     */
    using OptionalCsr = boost::optional<Csr>;
    /**
     * @brief Optional Table.
     */
    using OptionalTable = boost::optional<Table>;
    /**
     * @brief Returns the storage table.
     * @return In case of an error, an empty table will be returned
     */
    static Table table();
    /**
     * @brief Returns the storage table.
     * @param errorMessage If the function returns 'none',
     *                     this string will contain a detailed error message
     * @return In case of an error, 'none' will be returned
     */
    static OptionalTable table(std::string& errorMessage);
    /**
     * @brief Changes the application id in the storage table.
     *
     * @param id
     * @param errorMessage If the function returns false,
     *                     this string will contain a detailed error message
     *
     * @return true if successful
     */
    static bool applicationIdentifier(
        const Application::Identifier& id,
        std::string& errorMessage);
    /**
     * @brief Adds the given chain to the storage table.
     * @return true if successful
     */
    static bool certificateChain(const CertificateChain& chain);
    /**
     * @brief Adds the given chain to the storage table.
     *
     * @note The requester will be identified by the public key within the given
     * chain.
     *
     * @param chain
     * @param errorMessage If the function returns false,
     *                     this string will contain a detailed error message
     *
     * @return true if successful
     */
    static bool certificateChain(const CertificateChain& chain,
                                 std::string& errorMessage);
    /**
     * @brief Removes the chain for the given requester.
     * @param requester
     * @param errorMessage If the function returns false,
     *                     this string will contain a detailed error message
     * @return true if successful
     */
    static bool removeCertificateChainFor(const Component::Key& requester,
                                          std::string& errorMessage);
    /**
     * @brief Clears the entire contents of the store.
     *
     * @note
     * To bring the store back into operation, it is necessary to reinitialize
     * the library (see @ref DFL::Crypto::Environment)!
     *
     * @return true if successful
     */
    static bool clear();
    /**
     * @brief Sets the CSR deploy timestamp for the given requester to now.
     * @return true if successful
     */
    static bool csrDeployedFor(const Component::Key& requester);
    /**
     * @brief Sets the CSR deploy timestamp for the given requester to now.
     * @param requester
     * @param errorMessage If the function returns false,
     *                     this string will contain a detailed error message
     * @return true if successful
     */
    static bool csrDeployedFor(const Component::Key& requester,
                               std::string& errorMessage);
    /**
     * @brief Generates keys for items in the table which need keys.
     *
     * @warning Unfortunately generation of keys is quite expensive and due to
     * its nature the duration is quite unpredictable. In environments with
     * constrained CPU resources it is advised to call this function in a low
     * priority context. It only needs to be called once per startup and calling
     * it from only one thread per device is sufficient. The best time is after
     * all modules requested a certificate and before a CSR is generated. Once
     * keys have been generated they are stored persistently. So the next time
     * this function is called it returns quickly. It is fair to assume that
     * most of the time this call returns quickly. But when it is not quick it
     * is very slow.
     *
     * @snippet Crypto/Test/UnitTest/TestStore.cpp lifecycle
     */
    static bool generateKeys();
    /**
     * @brief Removes key for the given requester.
     * @param requester
     * @param errorMessage If the function returns false,
     *                     this string will contain a detailed error message
     * @return true if successful
     */
    static bool removeKeyFor(const Component::Key& requester,
                             std::string& errorMessage);
    /**
     * @brief Generates a certificate signing request based on the given
     * requestor.
     *
     * This can only be successful if the requester is found in
     * the store and if keys have already been generated.
     * If the function returns 'none' errorMessage will contain a detailed
     * description.
     *
     * @snippet Crypto/Test/UnitTest/TestStore.cpp generateCsrFor
     */
    static OptionalCsr generateCsrFor(const Component::Key& requester,
                                      std::string& errorMessage);
    /**
     * @brief Adds the given certificate requester to the storage table.
     * @return true if successful
     * @return false if cn is empty
     * @return false if requester is already in store but with different common
     * name or different roles
     *
     * @snippet Crypto/Test/UnitTest/TestStore.cpp requestCertificateFor
     */
    static bool requestCertificateFor(const Component::Key& requester,
                                      const CommonName& cn,
                                      const Oids& roles = Oids{});
    /**
     * @brief Adds a white list for the given requester to the storage table.
     * @return true if successful
     */
    static bool whitelistFor(const Component::Key& requester,
                             const Whitelist& list);
    /**
     * @brief Adds a white list for the given requester to the storage table.
     * @param requester
     * @param list
     * @param errorMessage If the function returns false,
     *                     this string will contain a detailed error message
     * @return true if successful
     */
    static bool whitelistFor(const Component::Key& requester,
                             const Whitelist& list,
                             std::string& errorMessage);
    /**
     * @brief Adds root cas for the given requester to the storage table.
     *
     * If the function returns false @c errorMessage will contain details.
     * Otherwise it is empty.
     *
     * @snippet Crypto/Test/UnitTest/TestStore.cpp AddRootCas
     *
     * @return True on success otherwise false.
     */
    static bool rootCasFor(const Component::Key& requester,
                           const RootCas& rootCas,
                           std::string& errorMessage);
    /**
     * @brief Remove all root cas for the given requester.
     *
     * Same as @ref DFL::Crypto::Store::rootCasFor with empty root cas.
     *
     * @snippet Crypto/Test/UnitTest/TestStore.cpp RemoveRootCas
     *
     * @return Same as  @ref DFL::Crypto::Store::rootCasFor.
     */
    static bool removeAllRootCasFor(const Component::Key& requester,
                                    std::string& errorMessage);
    /**
     * @brief Adds a role authorization list for the given requester to the
     * storage table.
     *
     * If the function returns false @c errorMessage will contain details.
     * Otherwise it is empty.
     *
     * @snippet Crypto/Test/UnitTest/TestStore.cpp AddRal
     *
     * @return True on success otherwise false.
     */
    static bool roleAuthorizationListFor(const Component::Key& requester,
                                         const RoleAuthorizationList& ral,
                                         std::string& errorMessage);
    /**
     * @brief Remove role authorization list for the given requester.
     *
     * Same as @ref DFL::Crypto::Store::roleAuthorizationListFor with empty ral.
     *
     * @snippet Crypto/Test/UnitTest/TestStore.cpp RemoveRal
     *
     * @return Same as  @ref DFL::Crypto::Store::roleAuthorizationListFor.
     */
    static bool removeRoleAuthorizationListFor(const Component::Key& requester,
                                               std::string& errorMessage);
};
}
