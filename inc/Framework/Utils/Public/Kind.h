#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <Framework/Utils/Public/CompilerGenerated.h> // not needed but used implicitly by customer

#include <boost/mpl/string.hpp>

#include <cstdint>
#include <string>

/**
 * @ingroup Utils
 * @{
 */
namespace DFL
{
namespace Component
{
namespace Static
{
using boost::mpl::c_str;
using boost::mpl::string;
}
/**
 * @brief Holds the value of a component kind.
 */
class DFL_UTILS_EXPIMP Kind
{
public:
    /**
     * @brief Defines limits and size of kind values.
     */
    using StaticProperties = enum
    {
        BitAmount = 10,                  /**< Amount of bits for kind value */
        MaxValue = (1 << BitAmount) - 1, /**< Max. value of component kind */
        MinValue = 0,                    /**< Min. value of component kind*/
        MaxCount = MaxValue + 1          /**< Max. number of component kinds */
    };
    /**
     * @brief Native type of the component kind value.
     */
    using NativeType = uint16_t;
    /**
     * @brief Constructs a component kind.
     * @param value Uniquely represents the value of a component kind.
     * @details name is empty.
     */
    Kind(NativeType value);
    /**
     * @brief Constructs a component kind.
     * @param value Uniquely represents the value of a component kind.
     * @param name Uniquely represents the name of a component kind.
     */
    Kind(NativeType value, char const* name);
    /**
     * @return Kind value.
     */
    NativeType value() const;
    /**
     * @return Name of kind.
     */
    const std::string& name() const;

private:
    NativeType m_value;
    std::string m_name;
};

/**
 * @brief Checks range of component kind value at compile time.
 * @tparam KindValue Value of a kind.
 * @tparam StaticName Name of kind.
 */
template <Kind::NativeType KindValue, typename StaticName = Static::string<>>
class StaticKind : public Kind
{
    static_assert(KindValue <= Kind::MaxValue, "Value for kind is too high");

public:
    /**
     * @brief Value of component kind.
     */
    static Kind::NativeType const Value = KindValue;
    /**
     * @brief Type of the component kind name.
     */
    using NameType = StaticName;
    /**
     * @brief Constructs a component kind.
     */
    StaticKind();
};

template <Kind::NativeType KindValue, typename StaticName>
inline StaticKind<KindValue, StaticName>::StaticKind()
    : Kind(KindValue, Static::c_str<StaticName>::value)
{
}
}
}
/** @} */
