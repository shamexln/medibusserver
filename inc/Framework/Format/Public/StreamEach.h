#pragma once

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace DFL
{
namespace Format
{
/**
 * @brief Streams content of given range to given stream.
 *
 * @tparam InIter Given iterator must at least fullfill the InputIterator
 * concept.
 *
 * @ingroup Format
 */
template <class StreamType,
          class InIter,
          class OpenTagType,
          class CloseTagType,
          class SepType>
StreamType& streamEach(StreamType& str,
                       InIter b,
                       const InIter& e,
                       const OpenTagType& openTag,
                       const CloseTagType& closeTag,
                       const SepType& sep);
/**
 * @brief Streams content of given range to given stream.
 *
 * @tparam InIter Given iterator must at least fullfill the InputIterator
 * concept.
 *
 * @ingroup Format
 */
template <class StreamType, class InIter>
StreamType& streamEach(StreamType& str,
                       InIter b,
                       const InIter& e,
                       const char* openTag,
                       const char* closeTag);
/**
 * @brief Streams content of given range to given stream.
 *
 * @tparam Container Must return iterators on calling begin(c) and end(c).
 *
 * @ingroup Format
 */
template <class StreamType, class Container>
StreamType& streamEach(StreamType& str,
                       const Container& c,
                       const char* openTag,
                       const char* closeTag);
/**
 * @brief Streams content of given range to given stream.
 *
 * @tparam Container Must return iterators on calling begin(c) and end(c).
 *
 * @ingroup Format
 */
template <class StreamType, class Container>
StreamType& streamEach(StreamType& str, const Container& c);

template <class StreamType,
          class InIter,
          class OpenTagType,
          class CloseTagType,
          class SepType>
inline StreamType& streamEach(StreamType& str,
                              InIter b,
                              const InIter& e,
                              const OpenTagType& openTag,
                              const CloseTagType& closeTag,
                              const SepType& sep)
{
    str << openTag;
    while (b != e)
    {
        str << (*b);
        if (++b != e) str << sep;
    }
    str << closeTag;
    return str;
}

template <class StreamType, class InIter>
inline StreamType& streamEach(StreamType& str,
                              InIter b,
                              const InIter& e,
                              const char* openTag,
                              const char* closeTag)
{
    return streamEach(str, b, e, openTag, closeTag, ",");
}

template <class StreamType, class Container>
inline StreamType& streamEach(StreamType& str,
                              const Container& c,
                              const char* openTag,
                              const char* closeTag)
{
    return streamEach(str, boost::begin(c), boost::end(c), openTag, closeTag);
}

template <class StreamType, class Container>
inline StreamType& streamEach(StreamType& str, const Container& c)
{
    return streamEach(str, boost::begin(c), boost::end(c), "[", "]", ",");
}
}
}
