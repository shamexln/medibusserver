#pragma once

#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/MdibEntityMapUtils.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/MdibEntityRange.h>

#include <map>
#include <memory>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/**
 * @brief Container to provide a generic map of handles to any entity type.
 * @ingroup Mdib
 */
class MdibEntityMap
{
    DFL_MDIB_IMMUTABLE(MdibEntityMap)

    public:
        MdibEntityMap();
        explicit MdibEntityMap(const ConstMdibEntityMapContainer& maps);

        operator ConstMdibEntityMapContainer() const;

        template<class T_Entity>
        SharedPtr<const SingleMap<T_Entity>> map() const;

        /**
         * @brief Iterator templates
         *
         * See @ref MdibChangeSet and @ref Mdib for examples.
         */
        ///@{
        template<class T_Entity>
        MdibIterator<T_Entity> begin() const;
        template<class T_Entity>
        MdibIterator<T_Entity> end() const ;
        template<class T_Entity>
        MdibIterator<T_Entity> begin(typename MdibIterator<T_Entity>::FilterFunction filterFunc) const;

        /**
         * @brief Range templates
         *
         * Can be used for ranged based for loops (C++11).
         *
         * See @ref MdibChangeSet and @ref Mdib for examples.
         */
        ///@{
        template<class T_Entity>
        MdibEntityRange<T_Entity> range() const;
        template<class T_Entity>
        MdibEntityRange<T_Entity> range(typename MdibEntityRange<T_Entity>::FilterFunction filterFunc) const;
        ///@}

        template<class T_Entity>
        SharedPtr<T_Entity> entity(const BasicHandle<T_Entity>& key) const;

    private:
        ConstMdibEntityMapContainer m_maps;
};

inline MdibEntityMap::MdibEntityMap() :
        m_maps()
{
}

inline MdibEntityMap::MdibEntityMap(const ConstMdibEntityMapContainer& maps) : // NOLINT(modernize-pass-by-value)
        m_maps(maps)
{
}

inline MdibEntityMap::operator ConstMdibEntityMapContainer() const
{
    return m_maps;
}

template<class T_Entity>
inline SharedPtr<const SingleMap<T_Entity>> MdibEntityMap::map() const
{
    return m_maps.map<T_Entity>();
}

template<class T_Entity>
inline SharedPtr<T_Entity> MdibEntityMap::entity(const BasicHandle<T_Entity>& key) const
{
    return m_maps.entity(key);
}

template<class T_Entity>
inline MdibIterator<T_Entity> MdibEntityMap::begin() const
{
    return MdibIterator<T_Entity>(map<T_Entity>()->cbegin(), map<T_Entity>()->cend());
}

template<class T_Entity>
inline MdibIterator<T_Entity> MdibEntityMap::end() const
{
    return MdibIterator<T_Entity>(map<T_Entity>()->cend(), map<T_Entity>()->cend());
}

template<class T_Entity>
inline MdibIterator<T_Entity> MdibEntityMap::begin(typename MdibIterator<T_Entity>::FilterFunction filterFunc) const
{
    return MdibIterator<T_Entity>(
        map<T_Entity>()->cbegin(),
        map<T_Entity>()->cend(),
        filterFunc);
}

template<class T_Entity>
inline MdibEntityRange<T_Entity> MdibEntityMap::range() const
{
    return MdibEntityRange<T_Entity>(begin<T_Entity>(), end<T_Entity>());
}

template<class T_Entity>
inline MdibEntityRange<T_Entity> MdibEntityMap::range(typename MdibEntityRange<T_Entity>::FilterFunction filterFunc) const
{
    return MdibEntityRange<T_Entity>(begin<T_Entity>(filterFunc), end<T_Entity>());
}

}
}
}
