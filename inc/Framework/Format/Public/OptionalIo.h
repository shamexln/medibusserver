#pragma once

#include <Framework/Format/Private/ExpImp.h>
#include <Framework/Format/Public/Stream.h>

#include <boost/optional/optional.hpp>

#include <optional>

namespace boost
{
/**
 * @brief Makes boost::optional streamable into a @ref DFL::Format::Stream.
 *
 * @snippet Format/Test/UnitTest/TestOptional.cpp StreamOptional
 *
 * @ingroup Format
 */
template <class T>
inline ::DFL::Format::Stream& operator<<(::DFL::Format::Stream& str,
                                         const boost::optional<T>& opt)
{
    if (opt)
    {
        str << opt.get();
    }
    else
    {
        str << "--";
    }
    return str;
}
}

namespace DFL::Format
{
/**
 * @brief Makes std::optional streamable into a @ref DFL::Format::Stream.
 *
 * @snippet Format/Test/UnitTest/TestOptional.cpp StreamStdOptional
 *
 * @ingroup Format
 */
template <class T>
inline ::DFL::Format::Stream& operator<<(::DFL::Format::Stream& str,
                                         const std::optional<T>& opt)
{
    if (opt)
    {
        str << *opt;
    }
    else
    {
        str << "--";
    }
    return str;
}
}


