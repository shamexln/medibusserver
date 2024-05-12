#pragma once

#include <Framework/Utils/Private/ExpImp.h>

#include <iosfwd>

namespace DFL
{
namespace Component
{
class Key;
/**
 * @brief Streams Key object to ostream.
 *
 * @param out Stream to put Key object in.
 * @param key Key object to be put into stream
 * @return The given stream object.
 *
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::ostream& operator<<(std::ostream& out, Key const& key);
}
}
namespace DFL
{
namespace Format
{
class Stream;
/**
 * @brief Streams Key object to ostream.
 *
 * @param out Stream to put Key object in.
 * @param key Key object to be put into stream
 * @return The given stream object.
 *
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP Stream& operator<<(Stream& out, Component::Key const& key);
}
}
