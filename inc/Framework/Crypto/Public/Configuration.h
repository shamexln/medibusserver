#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <Framework/Utils/Public/Application/Identifier.h>

#include <boost/filesystem/path.hpp>
#include <boost/optional/optional.hpp>

#include <string>

namespace DFL
{
namespace Crypto
{
/**
 * @brief Holds the configuration for the crypto library.
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP Configuration
{
public:
    /**
     * @brief Creates empty configuration.
     *
     * @snippet Crypto/Test/UnitTest/TestConfiguration.cpp defaultCtor
     */
    Configuration() = default;
    /**
     * @brief Creates configuration with given storage folder.
     *
     * @snippet Crypto/Test/UnitTest/TestConfiguration.cpp folderCtor
     */
    explicit Configuration(const boost::filesystem::path& folder);
    /**
     * @brief Creates configuration with given application id.
     *
     * @snippet Crypto/Test/UnitTest/TestConfiguration.cpp idCtor
     */
    explicit Configuration(const Application::Identifier& id);
    /**
     * @brief
     * Creates configuration with given storage folder and application id.
     *
     * @snippet Crypto/Test/UnitTest/TestConfiguration.cpp fullCtor
     */
    Configuration(const boost::filesystem::path& folder,
                  const Application::Identifier& id);
    /**
     * @brief Returns the storage folder for the secure store.
     */
    const boost::optional<boost::filesystem::path>& storageFolder()
        const noexcept;
    /**
     * @brief Returns the application identifier.
     */
    const boost::optional<Application::Identifier>& applicationIdentifier()
        const noexcept;
    /**
     * @brief Exchanges the contents of configuration with those of other.
     */
    void swap(Configuration& other) noexcept;

private:
    boost::optional<boost::filesystem::path> m_storageFolder{};
    boost::optional<Application::Identifier> m_applicationIdentifier{};
};
/**
 * @brief Compares two configurations.
 *
 * @ingroup Crypto
 * @{
 */
DFL_CRYPTO_EXPIMP bool operator==(const Configuration& lhs,
                                  const Configuration& rhs) noexcept;
DFL_CRYPTO_EXPIMP bool operator!=(const Configuration& lhs,
                                  const Configuration& rhs) noexcept;
/** @} */
/**
 * @brief Exchanges the given configurations.
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP void swap(Configuration& a, Configuration& b) noexcept;
}
}
