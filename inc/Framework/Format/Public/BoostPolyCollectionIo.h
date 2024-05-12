#pragma once

#include <Framework/Format/Public/Stream.h>
#include <Framework/Format/Public/StreamEach.h>

#include <boost/ptr_container/ptr_vector.hpp>

/**
 * @file
 *
 * @brief Makes boost poly collection streamable into @ref DFL::Format::Stream.
 *
 * @snippet Format/Test/UnitTest/TestBoostPolyCollectionIo.cpp StreamContainer
 *
 * @ingroup Format
 */
namespace boost
{
/**
 * @brief Streams content of boost::ptr_vector to DFL::Format.
 *
 * @ingroup Format
 */
template <class T, class A>
::DFL::Format::Stream& operator<<(::DFL::Format::Stream& str, const ptr_vector<T, A>& c);

template <class T, class A>
inline ::DFL::Format::Stream& operator<<(::DFL::Format::Stream& str, const ptr_vector<T, A>& c)
{
    return ::DFL::Format::streamEach(str, c);
}
}
