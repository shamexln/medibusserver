#pragma once

#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibEntityRange.h>
#include <Framework/Mdib/Public/Model/Alert/AlertCondition.h>
#include <Framework/Mdib/Public/Model/Alert/AlertConditionDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Alert/AlertConditionStateSerialize.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignal.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignalDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignalStateSerialize.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystem.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystemDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystemStateSerialize.h>
#include <Framework/Mdib/Public/Model/Alert/LimitAlertCondition.h>
#include <Framework/Mdib/Public/Model/Alert/LimitAlertConditionDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Alert/LimitAlertConditionStateSerialize.h>
#include <Framework/Mdib/Public/Model/Component/Battery.h>
#include <Framework/Mdib/Public/Model/Component/BatteryDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Component/BatteryStateSerialize.h>
#include <Framework/Mdib/Public/Model/Component/Channel.h>
#include <Framework/Mdib/Public/Model/Component/ChannelDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Component/ChannelStateSerialize.h>
#include <Framework/Mdib/Public/Model/Component/Clock.h>
#include <Framework/Mdib/Public/Model/Component/ClockDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Component/ClockStateSerialize.h>
#include <Framework/Mdib/Public/Model/Component/MdsDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Component/MdsStateSerialize.h>
#include <Framework/Mdib/Public/Model/Component/ScoDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Component/ScoStateSerialize.h>
#include <Framework/Mdib/Public/Model/Component/SystemContextDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Component/SystemContextStateSerialize.h>
#include <Framework/Mdib/Public/Model/Component/Vmd.h>
#include <Framework/Mdib/Public/Model/Component/VmdDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Component/VmdStateSerialize.h>
#include <Framework/Mdib/Public/Model/Context/EnsembleContextDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Context/EnsembleContextStateSerialize.h>
#include <Framework/Mdib/Public/Model/Context/LocationContextDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Context/LocationContextStateSerialize.h>
#include <Framework/Mdib/Public/Model/Context/LocationDetailSerialize.h>
#include <Framework/Mdib/Public/Model/Context/PatientContextDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Context/PatientContextStateSerialize.h>
#include <Framework/Mdib/Public/Model/EntityFactory.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Metric/DistributionSampleArrayMetric.h>
#include <Framework/Mdib/Public/Model/Metric/DistributionSampleArrayMetricDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Metric/DistributionSampleArrayMetricStateSerialize.h>
#include <Framework/Mdib/Public/Model/Metric/EnumStringMetric.h>
#include <Framework/Mdib/Public/Model/Metric/EnumStringMetricDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Metric/EnumStringMetricStateSerialize.h>
#include <Framework/Mdib/Public/Model/Metric/NumericMetric.h>
#include <Framework/Mdib/Public/Model/Metric/NumericMetricDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Metric/NumericMetricStateSerialize.h>
#include <Framework/Mdib/Public/Model/Metric/RealTimeSampleArrayMetric.h>
#include <Framework/Mdib/Public/Model/Metric/RealTimeSampleArrayMetricDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Metric/RealTimeSampleArrayMetricStateSerialize.h>
#include <Framework/Mdib/Public/Model/Metric/StringMetric.h>
#include <Framework/Mdib/Public/Model/Metric/StringMetricDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Metric/StringMetricStateSerialize.h>
#include <Framework/Mdib/Public/Model/Operation/ActivateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/ActivateOperationDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Operation/ActivateOperationStateSerialize.h>
#include <Framework/Mdib/Public/Model/Operation/SetAlertStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetAlertStateOperationDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Operation/SetAlertStateOperationStateSerialize.h>
#include <Framework/Mdib/Public/Model/Operation/SetComponentStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetComponentStateOperationDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Operation/SetComponentStateOperationStateSerialize.h>
#include <Framework/Mdib/Public/Model/Operation/SetContextStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetContextStateOperationDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Operation/SetContextStateOperationStateSerialize.h>
#include <Framework/Mdib/Public/Model/Operation/SetMetricStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetMetricStateOperationDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Operation/SetMetricStateOperationStateSerialize.h>
#include <Framework/Mdib/Public/Model/Operation/SetStringOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetStringOperationDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Operation/SetStringOperationStateSerialize.h>
#include <Framework/Mdib/Public/Model/Operation/SetValueOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetValueOperationDescriptorSerialize.h>
#include <Framework/Mdib/Public/Model/Operation/SetValueOperationStateSerialize.h>
#include <Framework/Mdib/Public/Model/VersionCounterSerialize.h>
#include <Framework/Mdib/Public/TypeTraits.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/SerializationHelper.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>

#include <type_traits>

/// Things from here shall not end up in production code.
namespace S31::Sdc::Experimental::Impl
{
enum class EntityTypeId
{
    None,
    Mds,
    MdsSco,
    Vmd,
    VmdSco,
    SystemContext,
    Channel,
    Battery,
    Clock,
    MdsAlertSystem,
    MdsAlertCondition,
    MdsLimitAlertCondition,
    MdsAlertSignal,
    VmdAlertSystem,
    VmdAlertCondition,
    VmdLimitAlertCondition,
    VmdAlertSignal,
    RealTimeSampleArrayMetric,
    EnumStringMetric,
    NumericMetric,
    StringMetric,
    DistributionSampleArrayMetric,
    MdsActivateOperation,
    MdsSetAlertStateOperation,
    MdsSetComponentStateOperation,
    MdsSetContextStateOperation,
    MdsSetMetricStateOperation,
    MdsSetStringOperation,
    MdsSetValueOperation,
    VmdActivateOperation,
    VmdSetAlertStateOperation,
    VmdSetComponentStateOperation,
    VmdSetContextStateOperation,
    VmdSetMetricStateOperation,
    VmdSetStringOperation,
    VmdSetValueOperation,
    LocationContextIndicator,
    PatientContextIndicator,
    EnsembleContextIndicator,
    LocationContext,
    PatientContext,
    EnsembleContext
};

template<class T_Entity> struct MapEntityTypeId {};

template<> struct MapEntityTypeId<DFL::Mdib::Mds> : std::integral_constant<EntityTypeId, EntityTypeId::Mds> {};
template<> struct MapEntityTypeId<DFL::Mdib::MdsSco> : std::integral_constant<EntityTypeId, EntityTypeId::MdsSco> {};
template<> struct MapEntityTypeId<DFL::Mdib::Vmd> : std::integral_constant<EntityTypeId, EntityTypeId::Vmd> {};
template<> struct MapEntityTypeId<DFL::Mdib::VmdSco> : std::integral_constant<EntityTypeId, EntityTypeId::VmdSco> {};
template<> struct MapEntityTypeId<DFL::Mdib::SystemContext> : std::integral_constant<EntityTypeId, EntityTypeId::SystemContext> {};
template<> struct MapEntityTypeId<DFL::Mdib::Channel> : std::integral_constant<EntityTypeId, EntityTypeId::Channel> {};
template<> struct MapEntityTypeId<DFL::Mdib::Battery> : std::integral_constant<EntityTypeId, EntityTypeId::Battery> {};
template<> struct MapEntityTypeId<DFL::Mdib::Clock> : std::integral_constant<EntityTypeId, EntityTypeId::Clock> {};
template<> struct MapEntityTypeId<DFL::Mdib::MdsAlertSystem> : std::integral_constant<EntityTypeId, EntityTypeId::MdsAlertSystem> {};
template<> struct MapEntityTypeId<DFL::Mdib::MdsAlertCondition> : std::integral_constant<EntityTypeId, EntityTypeId::MdsAlertCondition> {};
template<> struct MapEntityTypeId<DFL::Mdib::MdsLimitAlertCondition> : std::integral_constant<EntityTypeId, EntityTypeId::MdsLimitAlertCondition> {};
template<> struct MapEntityTypeId<DFL::Mdib::MdsAlertSignal> : std::integral_constant<EntityTypeId, EntityTypeId::MdsAlertSignal> {};
template<> struct MapEntityTypeId<DFL::Mdib::VmdAlertSystem> : std::integral_constant<EntityTypeId, EntityTypeId::VmdAlertSystem> {};
template<> struct MapEntityTypeId<DFL::Mdib::VmdAlertCondition> : std::integral_constant<EntityTypeId, EntityTypeId::VmdAlertCondition> {};
template<> struct MapEntityTypeId<DFL::Mdib::VmdLimitAlertCondition> : std::integral_constant<EntityTypeId, EntityTypeId::VmdLimitAlertCondition> {};
template<> struct MapEntityTypeId<DFL::Mdib::VmdAlertSignal> : std::integral_constant<EntityTypeId, EntityTypeId::VmdAlertSignal> {};
template<> struct MapEntityTypeId<DFL::Mdib::RealTimeSampleArrayMetric> : std::integral_constant<EntityTypeId, EntityTypeId::RealTimeSampleArrayMetric> {};
template<> struct MapEntityTypeId<DFL::Mdib::EnumStringMetric> : std::integral_constant<EntityTypeId, EntityTypeId::EnumStringMetric> {};
template<> struct MapEntityTypeId<DFL::Mdib::NumericMetric> : std::integral_constant<EntityTypeId, EntityTypeId::NumericMetric> {};
template<> struct MapEntityTypeId<DFL::Mdib::StringMetric> : std::integral_constant<EntityTypeId, EntityTypeId::StringMetric> {};
template<> struct MapEntityTypeId<DFL::Mdib::DistributionSampleArrayMetric> : std::integral_constant<EntityTypeId, EntityTypeId::DistributionSampleArrayMetric> {};
template<> struct MapEntityTypeId<DFL::Mdib::MdsActivateOperation> : std::integral_constant<EntityTypeId, EntityTypeId::MdsActivateOperation> {};
template<> struct MapEntityTypeId<DFL::Mdib::MdsSetAlertStateOperation> : std::integral_constant<EntityTypeId, EntityTypeId::MdsSetAlertStateOperation> {};
template<> struct MapEntityTypeId<DFL::Mdib::MdsSetComponentStateOperation> : std::integral_constant<EntityTypeId, EntityTypeId::MdsSetComponentStateOperation> {};
template<> struct MapEntityTypeId<DFL::Mdib::MdsSetContextStateOperation> : std::integral_constant<EntityTypeId, EntityTypeId::MdsSetContextStateOperation> {};
template<> struct MapEntityTypeId<DFL::Mdib::MdsSetMetricStateOperation> : std::integral_constant<EntityTypeId, EntityTypeId::MdsSetMetricStateOperation> {};
template<> struct MapEntityTypeId<DFL::Mdib::MdsSetStringOperation> : std::integral_constant<EntityTypeId, EntityTypeId::MdsSetStringOperation> {};
template<> struct MapEntityTypeId<DFL::Mdib::MdsSetValueOperation> : std::integral_constant<EntityTypeId, EntityTypeId::MdsSetValueOperation> {};
template<> struct MapEntityTypeId<DFL::Mdib::VmdActivateOperation> : std::integral_constant<EntityTypeId, EntityTypeId::VmdActivateOperation> {};
template<> struct MapEntityTypeId<DFL::Mdib::VmdSetAlertStateOperation> : std::integral_constant<EntityTypeId, EntityTypeId::VmdSetAlertStateOperation> {};
template<> struct MapEntityTypeId<DFL::Mdib::VmdSetComponentStateOperation> : std::integral_constant<EntityTypeId, EntityTypeId::VmdSetComponentStateOperation> {};
template<> struct MapEntityTypeId<DFL::Mdib::VmdSetContextStateOperation> : std::integral_constant<EntityTypeId, EntityTypeId::VmdSetContextStateOperation> {};
template<> struct MapEntityTypeId<DFL::Mdib::VmdSetMetricStateOperation> : std::integral_constant<EntityTypeId, EntityTypeId::VmdSetMetricStateOperation> {};
template<> struct MapEntityTypeId<DFL::Mdib::VmdSetStringOperation> : std::integral_constant<EntityTypeId, EntityTypeId::VmdSetStringOperation> {};
template<> struct MapEntityTypeId<DFL::Mdib::VmdSetValueOperation> : std::integral_constant<EntityTypeId, EntityTypeId::VmdSetValueOperation> {};
template<> struct MapEntityTypeId<DFL::Mdib::LocationContextIndicator> : std::integral_constant<EntityTypeId, EntityTypeId::LocationContextIndicator> {};
template<> struct MapEntityTypeId<DFL::Mdib::PatientContextIndicator> : std::integral_constant<EntityTypeId, EntityTypeId::PatientContextIndicator> {};
template<> struct MapEntityTypeId<DFL::Mdib::EnsembleContextIndicator> : std::integral_constant<EntityTypeId, EntityTypeId::EnsembleContextIndicator> {};
template<> struct MapEntityTypeId<DFL::Mdib::LocationContext> : std::integral_constant<EntityTypeId, EntityTypeId::LocationContext> {};
template<> struct MapEntityTypeId<DFL::Mdib::PatientContext> : std::integral_constant<EntityTypeId, EntityTypeId::PatientContext> {};
template<> struct MapEntityTypeId<DFL::Mdib::EnsembleContext> : std::integral_constant<EntityTypeId, EntityTypeId::EnsembleContext> {};

// Strategy choice to allow State Update changes avoid serializing unchanging descriptor data
enum class RecordingStrategy
{
    RecordBothStateAndDescriptor,
    RecordStateOnly
};

template<class T_Entity, class Archive, typename std::enable_if<!DFL::Mdib::is_multi_state<T_Entity>::value, bool>::type = true>
void saveDescriptorVersion(Archive& ar, const T_Entity& entity, RecordingStrategy strategy)
{
    if (strategy != RecordingStrategy::RecordStateOnly)
    {
        const auto& descriptorVersion = entity.descriptorVersion();
        ar & boost::serialization::make_nvp("DescriptorVersion", descriptorVersion);
    }
}

template<class T_Entity, class Archive, typename std::enable_if<DFL::Mdib::is_multi_state<T_Entity>::value, bool>::type = true>
void saveDescriptorVersion(Archive& /*ar*/, const T_Entity& /*entity*/, RecordingStrategy /*strategy*/)
{
    // Multi state has no descriptor
}

template<class T_Entity, class Archive, typename std::enable_if<!DFL::Mdib::is_multi_state<T_Entity>::value, bool>::type = true>
void saveDescriptor(Archive& ar, const T_Entity& entity, RecordingStrategy strategy)
{
    if (strategy != RecordingStrategy::RecordStateOnly)
    {
        DFL::Serialization::saveNvpImmutable(ar, "Descriptor", *entity.descriptor());
    }
}

template<class T_Entity, class Archive, typename std::enable_if<DFL::Mdib::is_multi_state<T_Entity>::value, bool>::type = true>
void saveDescriptor(Archive& /*ar*/, const T_Entity& /*entity*/, RecordingStrategy /*strategy*/)
{
    // Multi state has no descriptor
}

template<class T_Entity, class Archive, typename std::enable_if<!DFL::Mdib::is_context_indicator<T_Entity>::value, bool>::type = true>
void saveStateVersion(Archive& ar, const T_Entity& entity)
{
    const auto& stateVersion = entity.stateVersion();
    ar & boost::serialization::make_nvp("StateVersion", stateVersion);
}

template<class T_Entity, class Archive, typename std::enable_if<DFL::Mdib::is_context_indicator<T_Entity>::value, bool>::type = true>
void saveStateVersion(Archive& /*ar*/, const T_Entity& /*entity*/)
{
    // Context indicator has no state
}

template<class T_Entity, class Archive, typename std::enable_if<!DFL::Mdib::is_context_indicator<T_Entity>::value, bool>::type = true>
void saveState(Archive& ar, const T_Entity& entity)
{
    DFL::Serialization::saveNvpImmutable(ar, "State", *entity.state());
}

template<class T_Entity, class Archive, typename std::enable_if<DFL::Mdib::is_context_indicator<T_Entity>::value, bool>::type = true>
void saveState(Archive& /*ar*/, const T_Entity& /*entity*/)
{
    // Context indicator has no state
}

template<class T_Entity, class Archive>
void saveHandle(Archive& ar, const T_Entity& entity)
{
    // Save as string to avoid copy to (generic) handle
    ar & boost::serialization::make_nvp("Handle", entity.handle().string());
}

template<class T_Entity, class Archive>
void saveParent(Archive& ar, const T_Entity& entity)
{
    // Save as string to avoid copy to (generic) handle
    ar & boost::serialization::make_nvp("Parent", entity.parent().string());
}

template<class T_Entity, class Archive>
void saveEntity(Archive& ar, const T_Entity& entity, RecordingStrategy strategy)
{
    saveHandle(ar, entity);
    saveParent(ar, entity);
    saveDescriptorVersion(ar, entity, strategy);
    saveDescriptor(ar, entity, strategy);
    saveStateVersion(ar, entity);
    saveState(ar, entity);
}

template<class T_Entity, class Archive, typename std::enable_if<!DFL::Mdib::is_multi_state<T_Entity>::value, bool>::type = true>
DFL::Mdib::VersionCounter loadDescriptorVersion(Archive& ar, RecordingStrategy strategy)
{
    DFL::Mdib::VersionCounter descriptorVersion;
    if (strategy != RecordingStrategy::RecordStateOnly)
    {
        ar & boost::serialization::make_nvp("DescriptorVersion", descriptorVersion);
    }
    return descriptorVersion;
}

template<class T_Entity, class Archive, typename std::enable_if<DFL::Mdib::is_multi_state<T_Entity>::value, bool>::type = true>
DFL::Mdib::VersionCounter loadDescriptorVersion(Archive& /*ar*/, RecordingStrategy /*strategy*/)
{
    // Multi state does not have descriptor, return an empty placeholder
    return {};
}

template<class T_Entity, class Archive, typename std::enable_if<!DFL::Mdib::is_multi_state<T_Entity>::value, bool>::type = true>
DFL::NotNull<DFL::Mdib::SharedPtr<typename T_Entity::DescriptorType>> loadDescriptor(Archive& ar, RecordingStrategy strategy)
{
    using DescriptorType = typename T_Entity::DescriptorType;

    if (strategy != RecordingStrategy::RecordStateOnly)
    {
        return DFL::asNotNull(std::make_shared<DescriptorType>(
            DFL::Serialization::loadNvpImmutable<Archive, DescriptorType>(ar, "Descriptor")));
    }
    // return an empty placeholder if no descriptor was serialized
    return DFL::asNotNull(std::make_shared<DescriptorType>());
}

template<class T_Entity, class Archive, typename std::enable_if<DFL::Mdib::is_multi_state<T_Entity>::value, bool>::type = true>
DFL::NotNull<DFL::Mdib::SharedPtr<typename T_Entity::DescriptorType>> loadDescriptor(Archive& /*ar*/, RecordingStrategy /*strategy*/)
{
    // Multi state does not have descriptor, return an empty placeholder
    using DescriptorType = typename T_Entity::DescriptorType;
    return DFL::asNotNull(std::make_shared<DescriptorType>());
}

template<class T_Entity, class Archive, typename std::enable_if<!DFL::Mdib::is_context_indicator<T_Entity>::value, bool>::type = true>
DFL::Mdib::VersionCounter loadStateVersion(Archive& ar)
{
    DFL::Mdib::VersionCounter stateVersion;
    ar & boost::serialization::make_nvp("StateVersion", stateVersion);
    return stateVersion;
}

template<class T_Entity, class Archive, typename std::enable_if<DFL::Mdib::is_context_indicator<T_Entity>::value, bool>::type = true>
DFL::Mdib::VersionCounter loadStateVersion(Archive& /*ar*/)
{
    // Context indicator does not have state, return an empty placeholder
    return {};
}

template<class T_Entity, class Archive, typename std::enable_if<!DFL::Mdib::is_context_indicator<T_Entity>::value, bool>::type = true>
DFL::NotNull<DFL::Mdib::SharedPtr<typename T_Entity::StateType>> loadState(Archive& ar)
{
    using StateType = typename T_Entity::StateType;
    return DFL::asNotNull(std::make_shared<StateType>(
        DFL::Serialization::loadNvpImmutable<Archive, StateType>(ar, "State")));
}

template<class T_Entity, class Archive, typename std::enable_if<DFL::Mdib::is_context_indicator<T_Entity>::value, bool>::type = true>
DFL::NotNull<DFL::Mdib::SharedPtr<typename T_Entity::StateType>> loadState(Archive& /*ar*/)
{
    // Context indicator does not have state, return an empty placeholder
    using StateType = typename T_Entity::StateType;
    return DFL::asNotNull(std::make_shared<StateType>());
}

template<class T_Entity, class Archive>
DFL::Mdib::BasicHandle<T_Entity> loadHandle(Archive& ar)
{
    std::string handle;
    ar & boost::serialization::make_nvp("Handle", handle);
    return DFL::Mdib::BasicHandle<T_Entity>(handle);
}

template<class T_Entity, class Archive>
DFL::Mdib::BasicHandle<typename T_Entity::ParentType> loadParent(Archive& ar)
{
    std::string parent;
    ar & boost::serialization::make_nvp("Parent", parent);
    return DFL::Mdib::BasicHandle<typename T_Entity::ParentType>(parent);
}

template<class T_Entity, class Archive>
DFL::NotNull<DFL::Mdib::SharedPtr<T_Entity>> loadEntity(Archive& ar, RecordingStrategy strategy)
{
    auto handle = loadHandle<T_Entity>(ar);
    auto parent = loadParent<T_Entity>(ar);
    auto descriptorVersion = loadDescriptorVersion<T_Entity>(ar, strategy);
    auto descriptor = loadDescriptor<T_Entity>(ar, strategy);
    auto stateVersion = loadStateVersion<T_Entity>(ar);
    auto state = loadState<T_Entity>(ar);

    return DFL::asNotNull(DFL_MDIB_MAKE_SHARED<T_Entity>(
        handle,
        descriptor,
        descriptorVersion,
        state,
        stateVersion,
        parent));
}

template<class Archive>
class SaveInsertedVisitor
{
    public:
        template<class T_Entity>
        DFL::Mdib::VisitorProcessing visitEntity(Archive& ar, const DFL::Mdib::MdibChangeSet& changes, const DFL::Mdib::Handle& handleToSave)
        {
            auto handle = DFL::Mdib::BasicHandle<T_Entity>{handleToSave};
            if (auto entity = changes.insertedEntity(handle))
            {
                const EntityTypeId typeValue = MapEntityTypeId<T_Entity>();
                ar & boost::serialization::make_nvp("Type", typeValue);
                saveEntity(ar, *entity, RecordingStrategy::RecordBothStateAndDescriptor);

                return DFL::Mdib::VisitorProcessing::Cancel;
            }
            return DFL::Mdib::VisitorProcessing::Proceed;
        }
};

template<class Archive>
class SaveUpdatedVisitor
{
    public:
        explicit SaveUpdatedVisitor(RecordingStrategy strategy) :
            m_strategy(strategy)
        {
        }

        template<class T_Entity>
        void visitEntity(Archive& ar, const DFL::Mdib::MdibChangeSet& changeset)
        {
            auto range = changeset.updatedEntities<T_Entity>();
            for (const auto& entity : range)
            {
                const EntityTypeId typeValue = MapEntityTypeId<T_Entity>();
                ar & boost::serialization::make_nvp("Type", typeValue);
                saveEntity(ar, *entity, m_strategy);
            }
        }
    private:
        const RecordingStrategy m_strategy;
};

template<class Archive>
class SaveRemovedVisitor
{
    public:
        template<class T_Entity>
        void visitEntity(Archive& ar, const DFL::Mdib::MdibChangeSet& changeset)
        {
            auto range = changeset.removedEntities<T_Entity>();
            for (const auto& entity : range)
            {
                const EntityTypeId typeValue = MapEntityTypeId<T_Entity>();
                ar & boost::serialization::make_nvp("Type", typeValue);
                saveHandle(ar, *entity);
            }
        }
};

template<class Archive>
class LoadInsertedVisitor
{
    public:
        template<class T_Entity>
        void visitEntity(Archive& ar, DFL::Mdib::MdibChangeSet& changes, EntityTypeId typeToLoad)
        {
            if (typeToLoad == MapEntityTypeId<T_Entity>())
            {
                auto entity = loadEntity<T_Entity>(ar, RecordingStrategy::RecordBothStateAndDescriptor);
                changes.addOneToInsert(entity);
            }
        }
};

template<class Archive>
class LoadUpdatedVisitor
{
    public:
        explicit LoadUpdatedVisitor(RecordingStrategy strategy) :
            m_strategy(strategy)
        {
        }
        template<class T_Entity>
        void visitEntity(Archive& ar, DFL::Mdib::MdibChangeSet& changes, EntityTypeId typeToLoad)
        {
            if (typeToLoad == MapEntityTypeId<T_Entity>())
            {
                auto entity = loadEntity<T_Entity>(ar, m_strategy);
                changes.addOneToUpdate(entity);
            }
        }
    private:
        const RecordingStrategy m_strategy;
};

template<class Archive>
class LoadRemovedVisitor
{
    public:
        template<class T_Entity>
        void visitEntity(Archive& ar, DFL::Mdib::MdibChangeSet& changes, EntityTypeId typeToLoad)
        {
            if (typeToLoad == MapEntityTypeId<T_Entity>())
            {
                auto handle = loadHandle<T_Entity>(ar);
                changes.addOneToRemove(handle);
            }
        }
};

template<class Entities, class Archive>
void saveUpdatedStateChanges(Archive& ar, const DFL::Mdib::MdibChangeSet& changes)
{
    SaveUpdatedVisitor<Archive> visitor{RecordingStrategy::RecordStateOnly};
    Entities::applyVisitor(visitor, ar, changes);

    const auto endList = EntityTypeId::None;
    ar & boost::serialization::make_nvp("Type", endList);
}

template<class Entities, class Archive>
void saveAllChanges(Archive& ar, const DFL::Mdib::MdibChangeSet& changes)
{
    // Note: Recording empty flags for Insert, Update, or Remove sections
    // is an optimization to reduce overhead size of the archived data.

    const auto endList = EntityTypeId::None;

    bool emptyInserted = changes.emptyInsertedEntities();
    ar & BOOST_SERIALIZATION_NVP(emptyInserted);
    if (!emptyInserted)
    {
        SaveInsertedVisitor<Archive> visitor;

        const auto& insertOrderedHandles = changes.insertionOrder();
        for (const auto& insertedHandle : insertOrderedHandles)
        {
            Entities::applyVisitorWithEarlyExit(visitor, ar, changes, insertedHandle);
        }

        ar & boost::serialization::make_nvp("Type", endList);
    }

    bool emptyUpdated = changes.emptyUpdatedEntities();
    ar & BOOST_SERIALIZATION_NVP(emptyUpdated);
    if (!emptyUpdated)
    {
        SaveUpdatedVisitor<Archive> visitor{RecordingStrategy::RecordBothStateAndDescriptor};
        Entities::applyVisitor(visitor, ar, changes);

        ar & boost::serialization::make_nvp("Type", endList);
    }

    bool emptyRemoved = changes.emptyRemovedEntities();
    ar & BOOST_SERIALIZATION_NVP(emptyRemoved);
    if (!emptyRemoved)
    {
        SaveRemovedVisitor<Archive> visitor;
        Entities::applyVisitor(visitor, ar, changes);

        ar & boost::serialization::make_nvp("Type", endList);
    }
}

template<class Entities, class Visitor, class Archive>
void loadEntitiesLoop(Visitor& visitor, Archive& ar, DFL::Mdib::MdibChangeSet& changes)
{
    EntityTypeId typeToLoad{};
    ar & boost::serialization::make_nvp("Type", typeToLoad);

    while(typeToLoad != EntityTypeId::None)
    {
        Entities::applyVisitor(visitor, ar, changes, typeToLoad);
        ar & boost::serialization::make_nvp("Type", typeToLoad);
    }
}

template<class Entities, class Archive>
void loadUpdatedStateChanges(Archive& ar, DFL::Mdib::MdibChangeSet& changes)
{
    LoadUpdatedVisitor<Archive> visitor{RecordingStrategy::RecordStateOnly};
    loadEntitiesLoop<Entities>(visitor, ar, changes);
}

template<class Entities, class Archive>
void loadAllChanges(Archive& ar, DFL::Mdib::MdibChangeSet& changes)
{
    // Note: Insert, Update, or Remove sections may be empty, which
    // are indicated by boolean flags loaded from the archive.

    bool emptyInserted{false};
    ar & BOOST_SERIALIZATION_NVP(emptyInserted);
    if (!emptyInserted)
    {
        LoadInsertedVisitor<Archive> visitor;
        loadEntitiesLoop<Entities>(visitor, ar, changes);
    }

    bool emptyUpdated{false};
    ar & BOOST_SERIALIZATION_NVP(emptyUpdated);
    if (!emptyUpdated)
    {
        LoadUpdatedVisitor<Archive> visitor{RecordingStrategy::RecordBothStateAndDescriptor};
        loadEntitiesLoop<Entities>(visitor, ar, changes);
    }

    bool emptyRemoved{false};
    ar & BOOST_SERIALIZATION_NVP(emptyRemoved);
    if (!emptyRemoved)
    {
        LoadRemovedVisitor<Archive> visitor;
        loadEntitiesLoop<Entities>(visitor, ar, changes);
    }
}

}
