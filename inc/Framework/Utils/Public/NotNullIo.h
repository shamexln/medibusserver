#pragma once

#include <Framework/Utils/Public/NotNull.h>

#include <Framework/Format/Public/Stream.h>

#include <ostream>

/**
 * @file
 *
 * @brief Contains streaming operations for @ref DFL::NotNull.
 *
 * @ingroup Utils
 */
namespace DFL
{

/**
 * @brief Makes @ref NotNull streamable into a @ref DFL::Format::Stream.
 *
 * @ingroup Utils
 */
template<class T>
Format::Stream& operator<<(Format::Stream& str, const NotNull<T>& notNullPtr);

/**
 * @brief Makes @ref NotNull streamable into a @c std::ostream.
 *
 * @ingroup Utils
 */
template<class T>
std::ostream& operator<<(std::ostream& str, const NotNull<T>& notNullPtr);


template<class T>
inline Format::Stream& operator<<(Format::Stream& str, const NotNull<T>& notNullPtr)
{
    str << notNullPtr.get();
    return str;
}

template<class T>
inline std::ostream& operator<<(std::ostream& str, const NotNull<T>& notNullPtr)
{
    str << notNullPtr.get();
    return str;
}

}
