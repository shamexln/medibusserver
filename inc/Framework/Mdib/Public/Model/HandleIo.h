#pragma once

#include <Framework/Format/Public/Stream.h>
#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/Handle.h>

#include <ostream>

namespace DFL
{

namespace Format
{
class Stream;
}

namespace Mdib
{

/**
 * @brief Stream data of untyped handle to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& out, const Handle& data);

/**
 * @brief Stream data of untyped handle to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Format::Stream& operator<<(Format::Stream& out, const Handle& data);

/**
 * @brief Stream data of basic handle to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup Mdib
 */
template<class T_Entity>
std::ostream& operator<<(std::ostream& out, const BasicHandle<T_Entity>& data);

/**
 * @brief Stream data of basic handle to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup Mdib
 */
template<class T_Entity>
Format::Stream& operator<<(Format::Stream& out, const BasicHandle<T_Entity>& data);




template<class T_Entity>
inline std::ostream& operator <<(std::ostream& out, const BasicHandle<T_Entity>& data)
{
    if (data.isValid())
    {
        out << data.string();
    }
    else
    {
        out << "invalid(" << data.string() << ")";
    }
    return out;
}

template<class T_Entity>
inline Format::Stream& operator <<(Format::Stream& out, const BasicHandle<T_Entity>& data)
{
    if (data.isValid())
    {
        out.operator <<(data.string());
    }
    else
    {
        out.operator <<("invalid(").operator <<(data.string()).operator <<(")");
    }
    return out;
}

} /* namespace Mdib */
} /* namespace DFL */
