#pragma once

#include <Framework/Utils/Private/ExpImp.h>

#include <array>
#include <cstddef>
#include <iosfwd>
#include <string>

namespace DFL
{

/**
 * @brief Strong typedef container for SHA1 hashes (e.g., 458d36dd188e62e1a1b06c0a895fd5dbc2e59203).
 * @ingroup Utils
 */
class DFL_UTILS_EXPIMP Sha1
{
    public:
        /**
         * @brief Hex value of 160 bit SHA1 (string with 40 hex characters).
         * @details Example value is \c 458d36dd188e62e1a1b06c0a895fd5dbc2e59203.
         */
        explicit Sha1(const std::string& sha1);

        /**
         * @brief Calculates the SHA1 hash from given data.
         */
        static Sha1 calculateFrom(const std::string& data);

        /**
         * @brief Calculates the SHA1 hash from given data (e.g., file stream).
         */
        static Sha1 calculateFrom(std::istream& data);

        /**
         * @brief Converts the SHA1 hash to (lower case) hexadecimal output.
         */
        std::string hexString() const;

        /**
         * @brief Checks two SHA1 hashes for equality.
         */
        bool operator==(const Sha1& rhs) const;

        /**
         * @brief Checks that two SHA1 hashes differ.
         */
        bool operator!=(const Sha1& rhs) const;
    private:
        Sha1();
        static constexpr std::size_t Sha1DigestLength{20};
        std::array<unsigned char, Sha1DigestLength> m_sha1{};
};

}
