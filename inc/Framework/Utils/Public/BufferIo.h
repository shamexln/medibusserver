#pragma once

#include <Framework/Utils/Public/Buffer.h>
#include <Framework/Format/Public/Hex.h>
#include <Framework/Format/Public/Stream.h>
#include <Framework/Format/Public/ToString.h>
#include <boost/next_prior.hpp>
#include <ostream>

/**
 * @file Utils/Public/BufferIo.h
 *
 * @brief Stream operators for @ref DFL::Buffer
 *
 * @snippet Utils/Test/UnitTest/TestBuffer.cpp Data
 * @snippet Utils/Test/UnitTest/TestBuffer.cpp Stream
 *
 * @ingroup Utils
 */
namespace DFL
{
/**
 * @brief Streams buffer into ostream.
 *
 * @ingroup Utils
 */
template<std::size_t bytes>
std::ostream& operator<<(std::ostream& out, const Buffer<bytes>& buf);
}

namespace DFL
{
namespace Format
{
/**
 * @brief Streams buffer into format stream.
 *
 * @ingroup Utils
 */
template<std::size_t bytes>
Stream& operator<<(Stream& out, const DFL::Buffer<bytes>& buf);
}
}

namespace DFL
{
template<std::size_t bytes>
inline std::ostream& operator<<(std::ostream& out, const Buffer<bytes>& buf)
{
    out << DFL::Format::toString(buf);
    return out;
}
}

namespace DFL
{
namespace Format
{
template<std::size_t bytes>
inline Stream& operator<<(Stream& out, const DFL::Buffer<bytes>& buf)
{
    // todo: issue S32-586
    // this basically doubles the logic of the DFL::Format::StreamEach function
    // but streamEach has to be extended to take functors and all format
    // manipulator like hex, bin, ... have to be const global functors
    // to make this pleasently work
    out << '[';
    for(typename DFL::Buffer<bytes>::const_iterator it(buf.cbegin()); it != buf.cend(); ++it)
    {
        out << "0x" << hex(*it);
        if(boost::next(it) != buf.cend()) out << ',';
    }
    out << ']';

    return out;
}
}
}
