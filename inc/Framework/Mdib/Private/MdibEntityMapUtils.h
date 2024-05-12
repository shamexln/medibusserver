#pragma once

#include <type_traits>
#include <Framework/Mdib/Public/Utils/EntityLists.h>
#include <Framework/Mdib/Private/MdsParentPlaceholder.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Private/Utils/SmartPtrLib.h>
#include <Framework/Mdib/Public/MdibEntityRange.h>
#include <Framework/Mdib/Public/Model/Alert/AlertCondition.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignal.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystem.h>
#include <Framework/Mdib/Public/Model/Alert/LimitAlertCondition.h>
#include <Framework/Mdib/Public/Model/Component/Battery.h>
#include <Framework/Mdib/Public/Model/Component/Channel.h>
#include <Framework/Mdib/Public/Model/Component/Clock.h>
#include <Framework/Mdib/Public/Model/Component/Mds.h>
#include <Framework/Mdib/Public/Model/Component/Sco.h>
#include <Framework/Mdib/Public/Model/Component/SystemContext.h>
#include <Framework/Mdib/Public/Model/Component/Vmd.h>
#include <Framework/Mdib/Public/Model/Context/EnsembleContext.h>
#include <Framework/Mdib/Public/Model/Context/EnsembleContextIndicator.h>
#include <Framework/Mdib/Public/Model/Context/LocationContext.h>
#include <Framework/Mdib/Public/Model/Context/LocationContextIndicator.h>
#include <Framework/Mdib/Public/Model/Context/PatientContext.h>
#include <Framework/Mdib/Public/Model/Context/PatientContextIndicator.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Metric/DistributionSampleArrayMetric.h>
#include <Framework/Mdib/Public/Model/Metric/EnumStringMetric.h>
#include <Framework/Mdib/Public/Model/Metric/NumericMetric.h>
#include <Framework/Mdib/Public/Model/Metric/RealTimeSampleArrayMetric.h>
#include <Framework/Mdib/Public/Model/Metric/StringMetric.h>
#include <Framework/Mdib/Public/Model/Operation/ActivateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetAlertStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetComponentStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetContextStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetMetricStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetStringOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetValueOperation.h>
#include <Framework/Utils/Public/NotNull.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/**
 * @brief Shortcut to identify a map providing entities from a certain type.
 * @ingroup Mdib
 */
template<class T_Entity>
using SingleMap = std::map<DFL::Mdib::BasicHandle<T_Entity>, NotNull<SharedPtr<T_Entity>>>;

/**
 * @brief Shared container to hold one specific sort of MDIB entities.
 * @ingroup Mdib
 */
template<class T_Entity>
class SingleMdibEntityMapContainer
{
    protected:
        using BaseMap = SingleMap<T_Entity>;
        using MapType = SharedPtr<const BaseMap>;

        const BaseMap& map() const;

        MapType m_map;

        SingleMdibEntityMapContainer();
};


/**
 * @brief Container to hold one specific sort of MDIB entities.
 * @ingroup Mdib
 */
template<class T_Entity>
class SingleModifiableMdibEntityMapContainer
{
    protected:
        using MapType = SingleMap<T_Entity>;

        const MapType& map() const;
        MapType& map();

        MapType m_map;

        SingleModifiableMdibEntityMapContainer() = default;
};


template<template<class TC> class Container, class L, class... R> class EntityContainer;

template<template<class TC> class Container, class L>
class EntityContainer<Container, L>: protected Container<L>
{
        // All data is inherited from protected base class.
};

template<template<class TC> class Container, class L, class... R>
class EntityContainer /** @cond */ : public EntityContainer<Container, L>, public EntityContainer<Container, R...> /** @endcond */
{
        // This class is just for recursive expanding of template parameters.
};


/**
 * @brief Container to hold all maps for all entity types.
 * @details Provides access functions.
 * @tparam Container Template of the container, used to get @c mutable or @c const containers, see @ref ConstMdibEntityMapContainer, @ref MutableMdibEntityMapContainer
 * @ingroup Mdib
 */
template<template<class T> class Container>
class MdibEntityMapContainer: protected EntityContainer<Container, DFL_MDIB_ENTITY_ALL, MdsParentPlaceholder>
{
    public:
        template<class T_Entity>
        void replaceMap(const typename Container<T_Entity>::MapType& map)
        {
            Container<T_Entity>::m_map = map;
        }

        template<class T_Entity>
        const typename Container<T_Entity>::MapType& map() const
        {
            return Container<T_Entity>::m_map;
        }


        template<class T_Entity>
        typename Container<T_Entity>::MapType& modifiableMap()
        {
            return Container<T_Entity>::m_map;
        }

        template<class T_Entity>
        SharedPtr<T_Entity> entity(const BasicHandle<T_Entity>& key) const;

        template<class T_Entity>
        inline MdibIterator<T_Entity> begin() const;

        template<class T_Entity>
        MdibIterator<T_Entity> end() const;

        template<class T_Entity>
        MdibEntityRange<T_Entity> range() const;

        bool empty() const
        {
            return emptyEntity<DFL_MDIB_ENTITY_ALL, MdsParentPlaceholder>();
        }

    private:
        template<class... Args>
        bool emptyEntity(typename std::enable_if<sizeof...(Args) == 0>::type* = nullptr) const
        {
            return true;
        }

        template<class T_Entity, class ... Args>
        bool emptyEntity() const
        {
            return map<T_Entity>().empty() && emptyEntity<Args...>();
        }
};

/**
 * @brief (Shared) const container with maps for MDIB entities.
 * @ingroup Mdib
 */
using ConstMdibEntityMapContainer = MdibEntityMapContainer<SingleMdibEntityMapContainer>;

/**
 * @brief Mutable container with maps for MDIB entities.
 * @ingroup Mdib
 */
using MutableMdibEntityMapContainer = MdibEntityMapContainer<SingleModifiableMdibEntityMapContainer>;


template<class T_Entity>
inline SingleMdibEntityMapContainer<T_Entity>::SingleMdibEntityMapContainer() :
        m_map(DFL_MDIB_MAKE_SHARED<const SingleMap<T_Entity>>())
{
}

template<class T_Entity>
inline const typename SingleMdibEntityMapContainer<T_Entity>::BaseMap& SingleMdibEntityMapContainer<T_Entity>::map() const
{
        return *m_map;
}

template<class T_Entity>
inline const typename SingleModifiableMdibEntityMapContainer<T_Entity>::MapType& SingleModifiableMdibEntityMapContainer<T_Entity>::map() const
{
        return m_map;
}

template<class T_Entity>
inline typename SingleModifiableMdibEntityMapContainer<T_Entity>::MapType& SingleModifiableMdibEntityMapContainer<T_Entity>::map()
{
        return m_map;
}

template<template<class T> class Container>
template<class T_Entity>
inline MdibIterator<T_Entity> MdibEntityMapContainer<Container>::begin() const
{
    return MdibIterator<T_Entity>(map<T_Entity>().cbegin(), map<T_Entity>().cend());
}

template<template<class T> class Container>
template<class T_Entity>
inline MdibIterator<T_Entity> MdibEntityMapContainer<Container>::end() const
{
    return MdibIterator<T_Entity>(map<T_Entity>().cend(), map<T_Entity>().cend());
}

template<template<class T> class Container>
template<class T_Entity>
inline MdibEntityRange<T_Entity> MdibEntityMapContainer<Container>::range() const
{
    return MdibEntityRange<T_Entity>(begin<T_Entity>(), end<T_Entity>());
}

template<template<class T> class Container>
template<class T_Entity>
inline SharedPtr<T_Entity> MdibEntityMapContainer<Container>::entity(const BasicHandle<T_Entity>& key) const
{
    if (!key.isValid())
    {
        return SharedPtr<T_Entity>();
    }
    const auto& map = Container<T_Entity>::map();
    auto entityFromMap = map.find(key);
    if (entityFromMap == map.end())
    {
        return SharedPtr<T_Entity>();
    }

    return entityFromMap->second.get();
}

}
}
}
