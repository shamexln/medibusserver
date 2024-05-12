#pragma once

#include <S31/Utils/Private/S31UtilsExImp.h>

#include <memory>
#include <string>
#include <vector>

namespace S31::Utils
{

/**
 * @brief A container for version informations.
 * @details
 * Generally the entries are thought to be of the form e.g. ('boost', '1.70').
 *
 * This is intended to be used to collect 3rd party software versions, and similar
 * informations like the current OS. Any component/sub-components should
 * offer a function to provide this information, if suiting.
 *
 * There is some overlapping with the SBOM but this registry collects versions at run
 * time and these version may be unknown at compile time.
 *
 * This is not thread safe.
 *
 * @ingroup S31Utils
 */
class S31_UTILS_EXPIMP VersionInfo final
{
public:
    VersionInfo();

    ~VersionInfo();

    /**
     * @brief Adds an entry to the version information registry.
     *
     * @details
     * Usage example: `addVersionInfo("OpenSSL", DFL::Crypto::OpenSsl::version())`
     *
     * Duplicates will not be added. However, a key with multiple values is allowed.
     */
    void addVersionInfo(const std::string_view& key, const std::string_view& value);

    struct Item final
    {
        std::string key;
        std::string value;
    };

    using Items = std::vector<Item>;

    /**
     * @brief Get the version information that where previously added.
     * @details
     * This will contain no duplicates in respect to key+value.
     */
    Items items() const;

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

bool operator==(const VersionInfo::Item& lhs, const VersionInfo::Item& rhs);
bool operator!=(const VersionInfo::Item& lhs, const VersionInfo::Item& rhs);

/**
 * @brief Writes the version into the debug log.
 *
 * @ingroup S31Utils
 */
S31_UTILS_EXPIMP void logVersionInformation(const VersionInfo& versions);
}
