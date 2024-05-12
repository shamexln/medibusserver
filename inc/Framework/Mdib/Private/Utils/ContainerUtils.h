#pragma once

#include <Framework/Mdib/Public/Model/Handle.h>
#include <map>
#include <vector>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/**
 * @brief Designates the result of a \ref DFL::Mdib::Impl::replaceInMap() call.
 * @ingroup Mdib
 */
enum ReplaceInMapResult
{
    KeyInvalid, ///< The key (i.e., handle) was invalid.
    ValueInserted, ///< The value was inserted.
    ValueReplaced, ///< The key existed and the old value was replaced.
};

/**
 * @brief Replaces a value in or adds a value to a map.
 * @details If the key does not exist, the value is added, otherwise replaced.
 * @return \c true if key was replaced, otherwise \c false.
 * @ingroup Mdib
 */
template<class T_Entity, class T_Value, class T_Value2>
ReplaceInMapResult replaceInMap(std::map<BasicHandle<T_Entity>, T_Value>& map, const BasicHandle<T_Entity>& key, T_Value2&& value);

/**
 * @brief Removes first element from a container that matches a specific value.
 * @ingroup Mdib
 */
template<class T_Container, class T_Value>
void removeFirstValue(T_Container& container, const T_Value& value);

template<class T_Entity, class T_Value, class T_Value2>
inline ReplaceInMapResult replaceInMap(std::map<BasicHandle<T_Entity>, T_Value>& map, const BasicHandle<T_Entity>& key, T_Value2&& value)
{
    if (key.isValid())
    {
        auto it = map.find(key);
        if (it != map.end())
        {
            it->second = value;
            return ReplaceInMapResult::ValueReplaced;
        }
        map.insert(std::make_pair(key, std::forward<T_Value2>(value)));
        return ReplaceInMapResult::ValueInserted;
    }
    return ReplaceInMapResult::KeyInvalid;
}

template<class T_Container, class T_Value>
inline void removeFirstValue(T_Container& container, const T_Value& value)
{
    auto it = std::find(container.begin(), container.end(), value);
    if (it != container.end())
    {
        container.erase(it);
    }
}

}
}
}
