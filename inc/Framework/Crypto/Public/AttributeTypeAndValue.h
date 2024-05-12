#pragma once

#include <Framework/Crypto/Private/AttributeTypes.h>
#include <Framework/Crypto/Private/ExpImp.h>

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

#include <string>

namespace DFL
{
namespace Crypto
{
/**
 * @brief Represents an attribute of a distinguished name.
 * @details See [RFC 4514](https://www.ietf.org/rfc/rfc4514.txt)
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP AttributeTypeAndValue
{
public:
    /**
     * @brief Returns the attribute type.
     */
    const std::string& type() const;
    /**
     * @brief Returns the attribute value.
     */
    const std::string& value() const;
    /**
     * @brief Returns true if attribute type and value are not empty.
     */
    explicit operator bool() const;
    /**
     * @brief Exchanges the contents of attribute with those of other.
     */
    void swap(AttributeTypeAndValue& other) noexcept;

protected:
    /**
     * @brief Creates an empty attribute.
     */
    AttributeTypeAndValue() = default;
    /**
     * @brief Creates an attribute from the given parameter.
     *
     * @throw std::runtime_error if typ and val are not recognized by OpenSSL.
     */
    AttributeTypeAndValue(std::string typ, std::string val);

private:
    std::string m_type{};
    std::string m_value{};

    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        // m_type will be set by concrete classes upon construction
        // thus the value of the m_type member is not needed
        // to fill all attributes of a concrete class correctly
        ar & boost::serialization::make_nvp("Value", m_value);
    }
};

/**
 * @brief Compares two attributes.
 * @ingroup Crypto
 * @{
 */
DFL_CRYPTO_EXPIMP bool operator==(
    const AttributeTypeAndValue& lhs,
    const AttributeTypeAndValue& rhs) noexcept;
DFL_CRYPTO_EXPIMP bool operator!=(
    const AttributeTypeAndValue& lhs,
    const AttributeTypeAndValue& rhs) noexcept;
/** @} */
/**
 * @brief Exchanges the given attributes.
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP void swap(AttributeTypeAndValue& a, AttributeTypeAndValue& b) noexcept;

/**
 * @brief Helper class for fixing the type of AttributeTypeAndValue.
 * @ingroup Crypto
 */
template <class AttrType>
class BasicAttributeTypeAndValue : public AttributeTypeAndValue
{
public:
    /**
     * @brief Creates an attribute with type from AttrType and an empty value.
     */
    BasicAttributeTypeAndValue();
    /**
     * @brief Creates an attribute with type from AttrType and the given value.
     */
    explicit BasicAttributeTypeAndValue(std::string val);
};

template <class AttrType>
inline BasicAttributeTypeAndValue<AttrType>::BasicAttributeTypeAndValue()
    : BasicAttributeTypeAndValue{""}
{
}

template <class AttrType>
inline BasicAttributeTypeAndValue<AttrType>::BasicAttributeTypeAndValue(
    std::string val) // NOLINT(performance-unnecessary-value-param)
    : AttributeTypeAndValue(AttrType::type, std::move(val))
{
}

/**
 * @brief Represents a country name.
 *
 * @snippet Crypto/Test/UnitTest/TestAttributeTypeAndValue.cpp testAttribute
 * @snippet Crypto/Test/UnitTest/TestAttributeTypeAndValue.cpp CountryName
 *
 * @ingroup Crypto
 */
using CountryName            = BasicAttributeTypeAndValue<Impl::CType>;
/**
 * @brief Represents a state or province name.
 *
 * @snippet Crypto/Test/UnitTest/TestAttributeTypeAndValue.cpp testAttribute
 * @snippet Crypto/Test/UnitTest/TestAttributeTypeAndValue.cpp StateOrProvinceName
 *
 * @ingroup Crypto
 */
using StateOrProvinceName    = BasicAttributeTypeAndValue<Impl::StType>;
/**
 * @brief Represents a locality name.
 *
 * @snippet Crypto/Test/UnitTest/TestAttributeTypeAndValue.cpp testAttribute
 * @snippet Crypto/Test/UnitTest/TestAttributeTypeAndValue.cpp LocalityName
 *
 * @ingroup Crypto
 */
using LocalityName           = BasicAttributeTypeAndValue<Impl::LType>;
/**
 * @brief Represents an organizational name.
 *
 * @snippet Crypto/Test/UnitTest/TestAttributeTypeAndValue.cpp testAttribute
 * @snippet Crypto/Test/UnitTest/TestAttributeTypeAndValue.cpp OrganizationName
 *
 * @ingroup Crypto
 */
using OrganizationName       = BasicAttributeTypeAndValue<Impl::OType>;
/**
 * @brief Represents an organizational unit name.
 *
 * @snippet Crypto/Test/UnitTest/TestAttributeTypeAndValue.cpp testAttribute
 * @snippet Crypto/Test/UnitTest/TestAttributeTypeAndValue.cpp OrganizationalUnitName
 *
 * @ingroup Crypto
 */
using OrganizationalUnitName = BasicAttributeTypeAndValue<Impl::OuType>;
/**
 * @brief Represents a common name.
 *
 * @snippet Crypto/Test/UnitTest/TestAttributeTypeAndValue.cpp testAttribute
 * @snippet Crypto/Test/UnitTest/TestAttributeTypeAndValue.cpp CommonName
 *
 * @ingroup Crypto
 */
using CommonName = BasicAttributeTypeAndValue<Impl::CnType>;
/**
 * @brief Represents a user id.
 *
 * @snippet Crypto/Test/UnitTest/TestAttributeTypeAndValue.cpp testAttribute
 * @snippet Crypto/Test/UnitTest/TestAttributeTypeAndValue.cpp UserId
 *
 * @ingroup Crypto
 */
using UserId = BasicAttributeTypeAndValue<Impl::UidType>;
}
}

BOOST_CLASS_VERSION(::DFL::Crypto::AttributeTypeAndValue, 0)
