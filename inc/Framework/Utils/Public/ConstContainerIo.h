#pragma once

#include <Framework/Utils/Public/ConstContainer.h>

#include <Framework/Format/Public/Stream.h>
#include <Framework/Format/Public/StreamEach.h>

#include <ostream>

namespace DFL
{
namespace Utils
{
/**
 * @brief Creates readable form of the given container.
 *
 * @snippet Utils/Test/UnitTest/TestConstContainer.cpp usings
 * @snippet Utils/Test/UnitTest/TestConstContainer.cpp streaming
 *
 * @ingroup Utils
 */
template <class Container>
inline std::ostream& operator<<(std::ostream& str,
                                const ConstContainer<Container>& c)
{
    return Format::streamEach(str, c);
}
}
namespace Format
{
/**
 * @brief Creates readable form of the given container.
 *
 * @snippet Utils/Test/UnitTest/TestConstContainer.cpp usings
 * @snippet Utils/Test/UnitTest/TestConstContainer.cpp streaming
 *
 * @ingroup Utils
 */
template <class Container>
inline Stream& operator<<(Stream& str,
                          const Utils::ConstContainer<Container>& c)
{
    return Format::streamEach(str, c);
}
}
}
