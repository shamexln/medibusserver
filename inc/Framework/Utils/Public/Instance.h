#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <Framework/Utils/Public/StaticAssert.h>

#include <cstdint>

/**
 * @ingroup Utils
 * @{
 */
namespace DFL
{
namespace Component
{
/**
 * @brief Holds the value of a component instance.
 */
class DFL_UTILS_EXPIMP Instance
{
public:
    /**
     * @brief Defines limits and size of instance values.
     */
    using StaticProperties = enum
    {
        BitAmount = 2, /**< Amount of bits for instance value */
        MaxValue = (1 << BitAmount) - 1, /**< Maximal value of a component instance. */
        MinValue = 0, /**< Minimal value of a component instance. */
        MaxCount = MaxValue + 1 /**< Maximal number of component instances */
    };
    /**
     * @brief Native type of the component instance value.
     * */
    using NativeType = uint16_t;
    /**
     * @brief Constructs a component instance
     * @param value Uniquely represents the value of a component instance.
     */
    Instance(NativeType value);
    /**
     * @brief Value of component instance.
     */
    NativeType value() const;
private:
    NativeType m_value;
};
/**
 * @brief Checks range of component instance value at compile time.
 * @tparam InstanceValue Value of a component instance.
 */
template<Instance::NativeType InstanceValue>
class StaticInstance: public Instance
{
    DFL_STATIC_ASSERT_MSG(
        InstanceValue <= Instance::MaxValue,
        "Value for Instance is too high");
public:
    /**
     * @brief Value of component instance.
     */
    static Instance::NativeType const Value = InstanceValue;
    /**
     * @brief Constructs a component instance.
     */
    StaticInstance();
};

template<Instance::NativeType InstanceValue>
inline StaticInstance<InstanceValue>::StaticInstance() :
    Instance(InstanceValue)
{
}
}
}
/** @} */
