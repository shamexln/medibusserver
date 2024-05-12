#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/MdsVmdTypes.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Alert/AlertConditionDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Alert/AlertConditionStateBuilder.h>

namespace DFL
{
namespace Mdib
{
class MdsAlertCondition;
class MdsAlertSignal;
class MdsAlertSystem;
class VmdAlertCondition;
class VmdAlertSignal;
class VmdAlertSystem;

/**
 * @brief Type safe handle for \ref MdsAlertCondition.
 * @ingroup Mdib
 */
using MdsAlertConditionHandle = BasicHandle<MdsAlertCondition>;
/**
 * @brief Type safe handle for \ref VmdAlertCondition.
 * @ingroup Mdib
 */
using VmdAlertConditionHandle = BasicHandle<VmdAlertCondition>;

/**
 * @brief Description of one alert condition that can be detected by surrounding \ref AlertSystem.
 * @ingroup Mdib
 */
template<class T_Entity, class T_Parent, class T_AlertSignal>
class AlertCondition: public Impl::MdibEntity<T_Entity, AlertConditionDescriptorBuilder, AlertConditionStateBuilder, T_Parent>
{
        DFL_MDIB_IMMUTABLE(AlertCondition)

    protected:
        /**
         * @brief Constructor.
         */
        AlertCondition(const BasicHandle<T_Entity>& handle,
                       const DFL::NotNull<AlertConditionDescriptorSharedPtr>& descriptor,
                       VersionCounter descriptorVersion,
                       const DFL::NotNull<AlertConditionStateSharedPtr>& state,
                       VersionCounter stateVersion,
                       const BasicHandle<T_Parent>& parent);
};

/**
 * @brief Definition of an \ref AlertCondition that has an \ref MdsAlertSystem as parent.
 */
class MdsAlertCondition: public AlertCondition<MdsAlertCondition, MdsAlertSystem, MdsAlertSignal>
{
    DFL_MDIB_IMMUTABLE(MdsAlertCondition)

    public:
        /**
         * @brief Constructor.
         */
        MdsAlertCondition(const MdsAlertConditionHandle& handle,
                          const DFL::NotNull<AlertConditionDescriptorSharedPtr>& descriptor,
                          VersionCounter descriptorVersion,
                          const DFL::NotNull<AlertConditionStateSharedPtr>& state,
                          VersionCounter stateVersion,
                          const BasicHandle<MdsAlertSystem>& parent);
};

/**
 * @brief Definition of an \ref AlertCondition that has a \ref VmdAlertSystem as parent.
 */
class VmdAlertCondition: public AlertCondition<VmdAlertCondition, VmdAlertSystem, VmdAlertSignal>
{
    DFL_MDIB_IMMUTABLE(VmdAlertCondition)

    public:
        /**
         * @brief Constructor.
         */
        VmdAlertCondition(const VmdAlertConditionHandle& handle,
                          const DFL::NotNull<AlertConditionDescriptorSharedPtr>& descriptor,
                          VersionCounter descriptorVersion,
                          const DFL::NotNull<AlertConditionStateSharedPtr>& state,
                          VersionCounter stateVersion,
                          const BasicHandle<VmdAlertSystem>& parent);
};

template<class T_Entity, class T_Parent, class T_AlertSignal>
inline AlertCondition<T_Entity, T_Parent, T_AlertSignal>::AlertCondition(
            const BasicHandle<T_Entity>& handle,
            const DFL::NotNull<AlertConditionDescriptorSharedPtr>& descriptor,
            VersionCounter descriptorVersion,
            const DFL::NotNull<AlertConditionStateSharedPtr>& state,
            VersionCounter stateVersion,
            const BasicHandle<T_Parent>& parent) :
        Impl::MdibEntity<T_Entity, AlertConditionDescriptorBuilder, AlertConditionStateBuilder, T_Parent>(
            handle,
            descriptor,
            descriptorVersion,
            state,
            stateVersion,
            parent)
{
}

/**
 * @brief Type information of \ref AlertCondition
 */
DFL_MDIB_MDSVMD_TYPES(AlertCondition)

inline MdsAlertCondition::MdsAlertCondition(const MdsAlertConditionHandle& handle,
                                            const DFL::NotNull<AlertConditionDescriptorSharedPtr>& descriptor,
                                            VersionCounter descriptorVersion,
                                            const DFL::NotNull<AlertConditionStateSharedPtr>& state,
                                            VersionCounter stateVersion,
                                            const BasicHandle<MdsAlertSystem>& parent) :
        AlertCondition(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

inline VmdAlertCondition::VmdAlertCondition(const VmdAlertConditionHandle& handle,
                                            const DFL::NotNull<AlertConditionDescriptorSharedPtr>& descriptor,
                                            VersionCounter descriptorVersion,
                                            const DFL::NotNull<AlertConditionStateSharedPtr>& state,
                                            VersionCounter stateVersion,
                                            const BasicHandle<VmdAlertSystem>& parent) :
        AlertCondition(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

/**
 * @brief Definition of shared pointer type \ref MdsAlertConditionSharedPtr for entity \ref MdsAlertCondition.
 */
using MdsAlertConditionSharedPtr = SharedPtr<MdsAlertCondition>;

/**
 * @brief Definition of shared pointer type \ref VmdAlertConditionSharedPtr for entity \ref VmdAlertCondition.
 */
using VmdAlertConditionSharedPtr = SharedPtr<VmdAlertCondition>;

}
}
