#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/EnumClass.h>

#include <string>
#include <vector>

namespace DFL::Crypto
{
class Whitelist;
}

namespace S31::Nomenclature
{
/**
 * @brief State of a common name on a whitelist.
 * @ingroup S31Nomenclature
 */
enum class WhiteListingState
{
        /**
         * @brief Is not whitelisted.
         */
        NotWhitelisted,

        /**
         * @brief Only whitelisted due to the wildcard string.
         * @details The common name is not explicitly listed in the allowed
         * common name list.
         */
        WildcardWhitelisted,

        /**
         * @brief Common name explicitly whitelisted.
         * @details
         * The common name of the certificate is explicitly whitelisted.
         * No wildcard match required. This is the "best" state.
         */
        ExplicitlyWhitelistedByCommonName
};

DFL_ENUM_CLASS_STREAM_OPERATOR(WhiteListingState, (NotWhitelisted)(WildcardWhitelisted)(ExplicitlyWhitelistedByCommonName))


/**
 * @brief Encapsulates the whitelist used in \ref S31::CoreConfiguration "S31 core configuration".
 * @details Also provides additional functionality to check whether a peer is whitelisted.
 * @ingroup S31Nomenclature
 */
class S31_CORE_EXPIMP Whitelist
{
    public:

        // Consider Whitelist() = delete; but would now break CoreConfiguration() with deprecated member \ref S31::CoreConfiguration::whitelistedPeers
        explicit Whitelist() = default;

        /**
         * @brief Constructor using \ref DFL::Crypto::Whitelist as parameter.
         * @details Entries in \ref DFL::Crypto::Whitelist are in one contiguous string, separated by CRLFs.
         */
        explicit Whitelist(DFL::Crypto::Whitelist whitelist);

        /**
         * @brief Checks whether the whitelist is empty.
         * @return true if the whitelist is empty.
         */
        bool empty() const noexcept;

        /**
         * @brief Checks whether a given string is whitelisted or all strings are whitelisted.
         * @details All strings are whitelisted if the magic string "*_*_305" or "*" is found in m_whitelist.
         */
        WhiteListingState check(const std::string& value) const;

    private:

        /**
         * @brief Lists all Whitelist entries
         */
        std::vector<std::string> m_whitelist;
};

}
