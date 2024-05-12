#pragma once

#include <Framework/Format/Public/Stream.h>
#include <Framework/Format/Public/StreamEach.h>
#include <Framework/Mdib/Public/MdibEntityRange.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Streams content to given stream.
 *
 * @param str Stream to put data into.
 * @param r Range from which data is streamed.
 * @return Stream with formatted data from container inside.
 * @ingroup Mdib
 */
///@{
template<class T_Entity>
Format::Stream& operator<<(Format::Stream& str, const MdibEntityRange<T_Entity>& r);

template<class T_Entity>
std::ostream& operator<<(std::ostream& str, const MdibEntityRange<T_Entity>& r);
///@}

template<class T_Entity>
inline Format::Stream& operator<<(Format::Stream& str, const MdibEntityRange<T_Entity>& r)
{
    return Format::streamEach(str, r.begin(), r.end(), "[", "]", ",");
}

template<class T_Entity>
inline std::ostream& operator<<(std::ostream& str, const MdibEntityRange<T_Entity>& r)
{
    return Format::streamEach(str, r.begin(), r.end(), "[", "]", ",");
}

}
}
