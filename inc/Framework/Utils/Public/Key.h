#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <Framework/Utils/Public/Instance.h>
#include <Framework/Utils/Public/Kind.h>

#include <string>

/**
 * @ingroup Utils
 * @{
 */
namespace DFL
{
namespace Component
{

/**
 * @brief Combines kind and instance of a component to identify a unique
 * instance of a component.
 *
 * Instances of this class should not be created via a constructor. Instead
 * compiletime variants are provided.
 * @snippet Utils/Test/UnitTest/TestKey.cpp CompiletimeKey
 *
 * This way the valid ranges of the kind and instance values are checked at
 * compiletime.
 */
class DFL_UTILS_EXPIMP Key
{
public:
    /**
     * @brief Creates an instance of Key using the attributes of the template
     * parameter.
     * @tparam StaticKey Holds the attributes to construct a key.
     * @return Key with the attributes set as defined by StaticKey.
     */
    template <typename StaticKey>
    static Key makeFrom();

    /**
     * @brief Native type of component kind.
     */
    using KindNativeType = Kind::NativeType;

    /**
     * @brief Native type of component instance.
     */
    using InstanceNativeType = Instance::NativeType;

    /**
     * @brief Constructs a default key.
     */
    Key() = default;

    /**
     * @brief Constructs a key from a kind and instance value.
     * @param kind Kind value of component.
     * @param instance Instance value of component.
     */
    Key(Kind const& kind, Instance const& instance);

    /**
     * @brief Evaluates if two keys are equal.
     * @param other Key to be compared with this.
     * @return True if KindValue and InstanceValue from both keys are equal
     * otherwise false.
     */
    bool operator==(Key const& other) const;

    /**
     * @brief Evaluates if two keys are unequal.
     * @param other Key to be compared with this.
     * @return True if either KindValue or InstanceValue from both keys differ
     * otherwise false.
     */
    bool operator!=(Key const& other) const;

    /**
     * @return Value of the component kind.
     */
    KindNativeType kindValue() const;

    /**
     * @return Name of the component kind.
     */
    char const* kindName() const;

    /**
     * @return Value of the component instance.
     */
    InstanceNativeType instanceValue() const;

private:
    KindNativeType m_kindValue{0};
    InstanceNativeType m_instanceValue{0};
    std::string m_kindName{};
};

template <typename StaticKey>
Key Key::makeFrom()
{
  return {
      Kind{
          StaticKey::KindValue,
          Static::c_str<typename StaticKey::NameType>::value},
      Instance{
          StaticKey::InstanceValue}};
}

/**
 * @brief Static key which holds a compiletime kind and compiletime instance
 * value of a component.
 *
 * @tparam KindType Type holding component kind.
 * @tparam InstanceType Type holding component instance.
 */
template <typename KindType, typename InstanceType>
class StaticKey : public Key
{
public:
    /**
     * @brief Value of the component kind.
     */
    static Key::KindNativeType const KindValue = KindType::Value;

    /**
     * @brief Value of the component instance.
     */
    static Key::InstanceNativeType const InstanceValue = InstanceType::Value;

    /**
     * @brief Type of component kind name.
     */
    using NameType = typename KindType::NameType;

    /**
     * @brief Constructs an instance of StaticKey.
     */
    StaticKey();

    StaticKey(const StaticKey&) = delete;
    StaticKey& operator=(const StaticKey&) = delete;
};

template <typename KindType, typename InstanceType>
inline StaticKey<KindType, InstanceType>::StaticKey()
    : Key(Kind(KindType::Value, Static::c_str<NameType>::value),
          Instance(InstanceType::Value))
{
}

}
}
/** @} */
