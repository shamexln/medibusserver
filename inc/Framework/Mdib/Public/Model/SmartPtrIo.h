#pragma once

#include <Framework/Format/Public/Stream.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <ostream>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Stream of MDIB shared pointer.
 */
template<class T_Entity>
std::ostream& operator<<(std::ostream& str, const SharedPtr<T_Entity>& ptr);

/**
 * @brief Stream of MDIB shared pointer.
 */
template<class T_Entity>
Format::Stream& operator<<(Format::Stream& str, const SharedPtr<T_Entity>& ptr);



template<class T_Entity>
inline std::ostream& operator<<(std::ostream& str, const SharedPtr<T_Entity>& ptr)
{
    if (ptr)
    {
        str << *ptr;
    }
    else
    {
        str << "(empty ptr)";
    }
    return str;
}

template<class T_Entity>
inline Format::Stream& operator<<(Format::Stream& str, const SharedPtr<T_Entity>& ptr)
{
    if (ptr)
    {
        str << *ptr;
    }
    else
    {
        str << "(empty ptr)";
    }
    return str;
}

}
}
