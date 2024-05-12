#pragma once

#include <string>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/**
 * @brief Helper function to output a container to a stream only if it is not empty.
 * @details If the container is not empty, the description and the container will be
 * output to stream.
 * @tparam Stream The output stream type (e.g. std::ostream, \ref DFL::Format::Stream) needs \c operator<<
 * @tparam Container A container type which has an \c empty() method
 * @param out The output stream.
 * @param desc A description to output ahead of the container.
 * @param container The container to output.
 * @ingroup Mdib
 */
template<class Stream, class Container>
Stream& streamIfNotEmpty(Stream& out, const std::string& desc, const Container& container)
{
    if (!container.empty())
    {
        out << desc << container;
    }
    return out;
}

}
}
}
