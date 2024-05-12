#pragma once

#include <Framework/Format/Public/Stream.h>
#include <Framework/Format/Public/StreamEach.h>

#include <boost/container/flat_map.hpp>
#include <boost/container/flat_set.hpp>

/**
 * @file
 *
 * @brief Makes boost container streamable into @ref DFL::Format::Stream.
 *
 * @snippet Format/Test/UnitTest/TestBoostContainerIo.cpp StreamContainer
 *
 * @ingroup Format
 */
namespace boost
{
namespace container
{
/**
 * @brief Streams content of boost::container::flat_set to DFL::Format.
 *
 * @ingroup Format
 */
template <class K, class C, class A>
::DFL::Format::Stream& operator<<(::DFL::Format::Stream& str, const flat_set<K, C, A>& c);
/**
 * @brief Streams content of boost::container::flat_map to DFL::Format.
 *
 * @ingroup Format
 */
template <class K, class T, class C, class A>
::DFL::Format::Stream& operator<<(::DFL::Format::Stream& str, const flat_map<K, T, C, A>& c);

template <class K, class C, class A>
inline ::DFL::Format::Stream& operator<<(::DFL::Format::Stream& str, const flat_set<K, C, A>& c)
{
    return ::DFL::Format::streamEach(str, c, "<", ">");
}

template <class K, class T, class C, class A>
inline ::DFL::Format::Stream& operator<<(::DFL::Format::Stream& str, const flat_map<K, T, C, A>& c)
{
    return ::DFL::Format::streamEach(str, c, "<", ">");
}
}
}
