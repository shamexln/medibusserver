#pragma once

#include <boost/serialization/nvp.hpp>
#include <Framework/Utils/Public/ScopeExit.h>
#include <memory>

namespace DFL
{
namespace Serialization
{
namespace Impl
{

/**
 * @brief Saves a raw pointer with given NVP (name-value-pair).
 * @details The NVP is required for XML archives for example.
 * @ingroup Utils
 */
template<typename Archive, typename Type>
inline void saveNvpRawPointer(Archive& ar, const char* nvpName, const Type* data)
{
    ar << ::boost::serialization::make_nvp(nvpName, data);
}

/**
 * @brief Loads a raw pointer with given NVP (name-value-pair) from archive.
 * @details A raw pointer is loaded, but it will be returned as std::unique_ptr to transfer ownership.
 * @ingroup Utils
 */
template<typename Archive, typename Type>
inline std::unique_ptr<Type> loadNvpRawPointer(Archive& ar, const char* nvpName)
{
    Type* ptr = nullptr;
    ScopeExit cleanup{[&](){ delete ptr; ptr = nullptr; }};
    ar >> ::boost::serialization::make_nvp(nvpName, ptr);

    // move raw pointer to unique_ptr
    std::unique_ptr<Type> result(ptr);
    cleanup.dismiss(); // do not double free owning raw pointer

    return result;
}

}
}
}
