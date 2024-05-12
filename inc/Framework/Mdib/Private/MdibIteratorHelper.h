#pragma once

#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>

#include <Framework/Utils/Public/NotNull.h>

#include <map>
#include <vector>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/**
 * @brief Type for iterators that run random access containers.
 */
template<class T_Value, class T_Key>
using RandomAccess = std::map<T_Key, T_Value>;

/**
 * @brief Type for iterators that run sequential access containers.
 */
template<class T_Value>
using SequentialAccess = std::vector<T_Value>;

/**
 * @brief Common types/traits for iterators used in the MDIB user interface.
 * @ingroup Mdib
 */
template<class T>
class MdibIteratorTraits
{
    public:
        /// @brief Iterator trait
        using value_type = T;
        /// @brief Iterator trait
        using reference = T &;
        /// @brief Iterator trait
        using pointer = T *;
        /// @brief Iterator trait
        using difference_type = int;
        /// @brief Iterator trait
        using iterator_category = std::forward_iterator_tag;
};

}
}
}
