#pragma once

#include <S31/Log/Public/ShortText.h>
#include <S31/Log/Public/ShortTextIo.h>

#include <Framework/Utils/Public/Locale/Convert.h>
#include <Framework/Utils/Public/NotNull.h>

#include <exception>
#include <ios>
#include <memory>
#include <sstream>
#include <string>

namespace S31::Log
{

using PtrText = ShortText<16>;

/**
 * @brief Make a hex string from a pointer
 * @ingroup S31Log
 */
template <typename T>
inline PtrText ptrToString(const T* p) noexcept
{
    try
    {
        std::ostringstream ss;
        ss << "0x" << std::hex << reinterpret_cast<uintptr_t>(p);
        return PtrText{ss.str()};
    }
    catch(...)
    {
        // do not throw exception in function used for logging (also used in destructors)
        return PtrText{"0xFAILED"};
    }
}

/**
 * @brief Make a hex string from a pointer
 * @ingroup S31Log
 */
template <typename T, typename Deleter>
inline PtrText ptrToString(const std::unique_ptr<T, Deleter>& p) noexcept
{
    return ptrToString(p.get());
}

/**
 * @brief Make a hex string from a pointer
 * @ingroup S31Log
 */
template <typename T, typename Deleter>
inline PtrText ptrToString(const DFL::NotNull<std::unique_ptr<T, Deleter>>& p) noexcept
{
    return ptrToString(p.get().get());
}

/**
 * @brief Make a hex string from a pointer
 * @ingroup S31Log
 */
template <typename T>
inline PtrText ptrToString(const std::shared_ptr<T>& p) noexcept
{
    return ptrToString(p.get());
}

/**
 * @brief Make a hex string from a pointer
 * @ingroup S31Log
 */
template <typename T>
inline PtrText ptrToString(const DFL::NotNull<std::shared_ptr<T>>& p) noexcept
{
    return ptrToString(p.get().get());
}

/**
 * @brief Make a string from a wide char pointer
 * @ingroup S31Log
 */
inline std::string toString(const wchar_t* w)
{
    try
    {
        return DFL::Locale::Convert::WideString::toNarrowString(w);
    }
    catch (...)
    {
        // A not convertable string cannot be used
    }
    return {"--- exception ---"};
}

/**
 * @brief Make a hex string from an enum value
 * @ingroup S31Log
 */
template <typename E>
inline PtrText enumToHex(E value)
{
    std::ostringstream ss;
    ss << "0x" << std::hex << static_cast<typename std::underlying_type<E>::type>(value);
    return PtrText{ss.str()};
}

}
