#pragma once

#include <boost/optional/optional.hpp>
#include <Framework/Utils/Private/SerializationHelperImpl.h>

namespace DFL
{
namespace Serialization
{

/**
 * @brief Saves an immutable type with given NVP (name-value-pair).
 * @details The NVP is required for XML archives for example.
 * The helper function is provided, to support the load, which is more complicated
 * for immutable types, since the destination is not allowed to exist.
 * Internally it uses a raw pointer.
 * @ingroup Utils
 */
template<typename Archive, typename Type>
inline void saveNvpImmutable(Archive& ar, const char* nvpName, const Type& data)
{
    Impl::saveNvpRawPointer(ar, nvpName, &data);
}

/**
 * @brief Loads an immutable type with given NVP (name-value-pair).
 * @details The NVP is required for XML archives for example.
 * The helper function is provided, to support the load, which is more complicated
 * for immutable types, since the destination is not allowed to exist.
 * Internally it uses a raw pointer.
 * @ingroup Utils
 */
template<typename Archive, typename Type>
inline Type loadNvpImmutable(Archive& ar, const char* nvpName)
{
    auto ptr = Impl::loadNvpRawPointer<Archive, Type>(ar, nvpName);
    Type result(std::move(*ptr)); // move data from pointer to value type
    return result;
}


/**
 * @brief Saves a (not-default constructible) type with given NVP (name-value-pair).
 * @details The NVP is required for XML archives for example.
 * In contrast to boost optional serialization. This helper supports serialization of
 * not-default-constructible types.
 * Internally it uses a raw pointer.
 * @ingroup Utils
 */
template<typename Archive, typename Type>
inline void saveNvpOptional(Archive& ar, const char* nvpName, const boost::optional<Type>& data)
{
    const Type* const ptr = data ? &(*data) : nullptr;
    Impl::saveNvpRawPointer(ar, nvpName, ptr);
}

/**
 * @brief Loads a (not-default constructible) type with given NVP (name-value-pair).
 * @details The NVP is required for XML archives for example.
 * In contrast to boost optional serialization. This helper supports serialization of
 * not-default-constructible types.
 * Internally it uses a raw pointer.
 * @ingroup Utils
 */
template<typename Archive, typename Type>
inline void loadNvpOptional(Archive& ar, const char* nvpName, boost::optional<Type>& dst)
{
    if (auto ptr = Impl::loadNvpRawPointer<Archive, Type>(ar, nvpName))
    {
        dst = std::move(*ptr);
        return;
    }
    dst = boost::none;
}

}
}
