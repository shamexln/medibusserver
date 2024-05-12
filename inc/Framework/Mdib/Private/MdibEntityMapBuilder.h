#pragma once

#include <Framework/Mdib/Private/MdibEntityMap.h>
#include <Framework/Mdib/Private/MdibEntityMapUtils.h>

#include <map>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/**
 * @brief Allows creation of \ref MdibEntityMap instances.
 * @ingroup Mdib
 */
class MdibEntityMapBuilder
{
    public:
        MdibEntityMapBuilder();
        explicit MdibEntityMapBuilder(const MdibEntityMap& mdibEntityMap);
        operator MdibEntityMap() const;

        template<class T_Entity>
        SharedPtr<const SingleMap<T_Entity>> map() const;

        template<class T_Entity>
        SharedPtr<T_Entity> entity(const BasicHandle<T_Entity>& key) const;

        template<class T_Entity>
        MdibEntityMapBuilder& map(const SharedPtr<const SingleMap<T_Entity>>& map);

    private:
        ConstMdibEntityMapContainer m_maps;
};

inline MdibEntityMapBuilder::MdibEntityMapBuilder() :
        m_maps()
{
}

inline MdibEntityMapBuilder::MdibEntityMapBuilder(const MdibEntityMap& mdibEntityMap) :
        m_maps(mdibEntityMap)
{
}

inline MdibEntityMapBuilder::operator MdibEntityMap() const
{
    return MdibEntityMap(m_maps);
}

template<class T_Entity>
inline MdibEntityMapBuilder& MdibEntityMapBuilder::map(const SharedPtr<const SingleMap<T_Entity>>& map)
{
    m_maps.replaceMap<T_Entity>(map);
    return *this;
}

template<class T_Entity>
inline SharedPtr<const SingleMap<T_Entity>> MdibEntityMapBuilder::map() const
{
    return m_maps.map<T_Entity>();
}

template<class T_Entity>
inline SharedPtr<T_Entity> MdibEntityMapBuilder::entity(const BasicHandle<T_Entity>& key) const
{
    return m_maps.entity(key);
}

/// full template specialization: special handling for MdsParentPlaceholder
template<>
inline MdibEntityMapBuilder& MdibEntityMapBuilder::map<MdsParentPlaceholder>(const SharedPtr<const SingleMap<MdsParentPlaceholder>>& /*map*/)
{
    return *this;
}

}
}
}
