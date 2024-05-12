#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>

#include <string>

namespace DFL
{
namespace Crypto
{
/**
 * @brief Holds a PEM-formatted string.
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP PemString
{
public:
    /**
     * @brief Type of size.
     */
    using SizeType = std::string::size_type;
    /**
     * @brief Constructs an empty PEM string.
     */
    PemString() = default;
    /**
     * @brief Constructs an PEM string from the given string.
     */
    explicit PemString(std::string pemStr);
    /**
     * @brief Appends an additional PEM string.
     */
    PemString& operator+=(const PemString& pemStr);
    /**
     * @brief Appends an additional PEM string.
     */
    PemString& append(const PemString& pemStr);
    /**
     * @brief Returns a non-modifiable standard C character array version of the
     * PEM string
     */
    const char* cStr() const;
    /**
     * @brief Returns the PEM string as std::string
     */
    const std::string& str() const;
    /**
     * @brief Returns the number of characters within the PEM string.
     */
    SizeType size() const;
    /**
     * @brief True if empty otherwise false.
     */
    bool empty() const;

private:
    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& boost::serialization::make_nvp("String", m_str);
    }

    std::string m_str{};
};
/**
 * @brief Compares two PEM strings.
 * Two PEM strings are equal if they hold same string.
 *
 * @ingroup Crypto
 * @{
 */
DFL_CRYPTO_EXPIMP bool operator==(const PemString& lhs, const PemString& rhs);
DFL_CRYPTO_EXPIMP bool operator!=(const PemString& lhs, const PemString& rhs);
/** @} */
/**
 * @brief Concatenates the given PEM strings.
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP PemString operator+(const PemString& lhs,
                                      const PemString& rhs);
}
}

BOOST_CLASS_VERSION(::DFL::Crypto::PemString, 0)

// https://www.boost.org/doc/libs/1_68_0/libs/serialization/doc/traits.html#tracking
// The default tracking type would be track_selectively.
// This leads to different archive output depending on customers.
// Here explicitly the tracking is disabled, to enforce a save/store in all
// cases. It is not assumed, that this type should be saved/stored only once
// when used with multiple pointers.
BOOST_CLASS_TRACKING(::DFL::Crypto::PemString,
                     boost::serialization::track_never)
