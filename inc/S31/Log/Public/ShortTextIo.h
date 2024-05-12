#pragma once

#include <S31/Log/Public/ShortText.h>

#include <Framework/Format/Public/Stream.h>
#include <Framework/Format/Public/StringViewIo.h>

#include <iostream>

namespace S31::Log
{
class KeyValue;

/**
 * @brief stream data to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup S31Log
 */
template<std::size_t Size>
inline std::ostream& operator<<(std::ostream& out, const ShortText<Size>& data)
{
    out << data.view();
    if (data.truncated())
    {
        out << "..";
    }
    return out;
}

/**
 * @brief stream data to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup S31Log
 */
template<std::size_t Size>
inline DFL::Format::Stream& operator<<(DFL::Format::Stream& out, const ShortText<Size>& data)
{
    out << data.view();
    if (data.truncated())
    {
        out << "..";
    }
    return out;
}

}
