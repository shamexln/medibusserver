#pragma once

#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibSmartPtr.h>
#include <Framework/Mdib/Public/Model/Alert/AbstractAlertState.h>
#include <Framework/Mdib/Public/Model/Component/AbstractDeviceComponentState.h>
#include <Framework/Mdib/Public/Model/Component/Channel.h>
#include <Framework/Mdib/Public/Model/Component/Mds.h>
#include <Framework/Mdib/Public/Model/Component/SystemContext.h>
#include <Framework/Mdib/Public/Model/Component/Vmd.h>
#include <Framework/Mdib/Public/Model/Metric/AbstractMetricState.h>
#include <Framework/Mdib/Public/Model/Operation/AbstractOperationState.h>

#include <Framework/Utils/Public/NotNull.h>

#include <type_traits>

namespace DFL::Mdib::Impl
{

/**
 * @brief Check for inactivity of an entity state.
 * @ingroup Mdib
 */
///@{
template<class State>
inline bool isInactive(const NotNull<SharedPtr<State>> &state,
                typename std::enable_if<std::is_base_of<AbstractDeviceComponentState, State>::value>::type* = nullptr)
{
    return state->activationState() == ComponentActivation::Off;
}

inline bool isInactive(const NotNull<SharedPtr<SystemContextState>> &state)
{
    return state->activationState() == ComponentActivation::Off;
}

template<class State>
inline bool isInactive(const NotNull<SharedPtr<State>> &state,
                typename std::enable_if<std::is_base_of<AbstractAlertState, State>::value >::type* = nullptr)
{
    return state->activationState() == AlertActivation::Off;
}

template<class State>
inline bool isInactive(const NotNull<SharedPtr<State>> &state,
                typename std::enable_if<std::is_base_of<AbstractMetricState, State>::value >::type* = nullptr)
{
    return state->activationState() == ComponentActivation::Off;
}

template<class State>
inline bool isInactive(const NotNull<SharedPtr<State>> &state,
                typename std::enable_if<std::is_base_of<AbstractOperationState, State>::value >::type* = nullptr)
{
    return state->operatingMode() == OperatingMode::NotAvailable;
}
///@}

/**
 * @brief Check for activity of an entity state.
 * @ingroup Mdib
 */
template<class State>
inline bool isActive(const NotNull<SharedPtr<State>> &state)
{
    return !isInactive(state);
}

/**
 * @brief Get a new state object in which the entity is deactivated.
 *
 * Different templates variants for several state types.
 *
 * @ingroup Mdib
 */
///@{
template <class Entity>
inline typename DFL::NotNull<SharedPtr<typename Entity::StateType>> getDeactivatedState(const DFL::NotNull<SharedPtr<typename Entity::StateType>> &state,
                                                      typename std::enable_if<std::is_base_of<AbstractDeviceComponentState, typename Entity::StateType>::value>::type* = nullptr)
{
    auto stateBuilder = DFL::Mdib::getBuilder(state);
    stateBuilder.activationState(ComponentActivation::Off);
    return asNotNull(DFL_MDIB_MAKE_SHARED<typename Entity::StateType>(stateBuilder.build()));
}

template <class SystemContext>
inline typename DFL::NotNull<SharedPtr<SystemContextState>> getDeactivatedState(const DFL::NotNull<SharedPtr<SystemContextState>> &state)
{
    auto stateBuilder = DFL::Mdib::getBuilder(state);
    stateBuilder.activationState(ComponentActivation::Off);
    return asNotNull(DFL_MDIB_MAKE_SHARED<SystemContextState>(stateBuilder.build()));
}

template <class Entity>
inline typename DFL::NotNull<SharedPtr<typename Entity::StateType>> getDeactivatedState(const DFL::NotNull<SharedPtr<typename Entity::StateType>> &state,
                                                      typename std::enable_if<std::is_base_of<AbstractAlertState, typename Entity::StateType>::value>::type* = nullptr)
{
    auto stateBuilder = DFL::Mdib::getBuilder(state);
    stateBuilder.activationState(AlertActivation::Off);
    return asNotNull(DFL_MDIB_MAKE_SHARED<typename Entity::StateType>(stateBuilder.build()));
}

template <class Entity>
inline typename DFL::NotNull<SharedPtr<typename Entity::StateType>> getDeactivatedState(const DFL::NotNull<SharedPtr<typename Entity::StateType>> &state,
                                                      typename std::enable_if<std::is_base_of<AbstractMetricState, typename Entity::StateType>::value>::type* = nullptr)
{
    auto stateBuilder = DFL::Mdib::getBuilder(state);
    stateBuilder.activationState(ComponentActivation::Off);
    return asNotNull(DFL_MDIB_MAKE_SHARED<typename Entity::StateType>(stateBuilder.build()));
}

template <class Entity>
inline typename DFL::NotNull<SharedPtr<typename Entity::StateType>> getDeactivatedState(const DFL::NotNull<SharedPtr<typename Entity::StateType>> &state,
                                                      typename std::enable_if<std::is_base_of<AbstractOperationState, typename Entity::StateType>::value>::type* = nullptr)
{
    auto stateBuilder = DFL::Mdib::getBuilder(state);
    stateBuilder.operatingMode(OperatingMode::NotAvailable);
    return asNotNull(DFL_MDIB_MAKE_SHARED<typename Entity::StateType>(stateBuilder.build()));
}
///@}

template<class Component>
inline bool componentGoesToOff(const NotNull<SharedPtr<Component>>& component, const NotNull<MdibSharedPtr>& mdib)
{
    if (component->state()->activationState() != ComponentActivation::Off)
    {
        return false;
    }
    auto componentInMdib = mdib->entity(component->handle());
    return (componentInMdib && componentInMdib->state()->activationState() != ComponentActivation::Off);
}

inline bool parentComponentGoesToOff(const NotNull<SharedPtr<Mds>>& /*component*/, const NotNull<MdibSharedPtr>& /*mdib*/)
{
    return false;
}

inline bool parentComponentGoesToOff(const NotNull<SharedPtr<Vmd>>& component, const NotNull<MdibSharedPtr>& mdib)
{
    auto mds = mdib->query().parent(component);
    if (!mds)
    {
        return false;
    }

    return componentGoesToOff(DFL::asNotNull(mds), mdib);
}

inline bool parentComponentGoesToOff(const NotNull<SharedPtr<Channel>>& channel, const NotNull<MdibSharedPtr>& mdib)
{
    auto vmd = mdib->query().parent(channel);
    if (!vmd)
    {
        return false;
    }

    auto vmdOff = componentGoesToOff(DFL::asNotNull(vmd), mdib);
    if (vmdOff)
    {
        return true;
    }

    return parentComponentGoesToOff(DFL::asNotNull(vmd), mdib);
}

/// Do 'operation' for all MDIB entity classes that are relevant for activation check/consistency and that are possibly children of something
#define ALL_ENTITIES(operation) \
    operation(Battery) \
    operation(Channel) \
    operation(Clock) \
    /* operation(Mds) */ /* cannot be a child of anyone */ \
    operation(MdsSco) \
    operation(SystemContext) \
    operation(Vmd) \
    operation(VmdSco) \
    \
    operation(MdsAlertCondition) \
    operation(MdsLimitAlertCondition) \
    operation(MdsAlertSignal) \
    operation(MdsAlertSystem) \
    operation(VmdAlertCondition) \
    operation(VmdLimitAlertCondition) \
    operation(VmdAlertSignal) \
    operation(VmdAlertSystem) \
    \
    operation(DistributionSampleArrayMetric) \
    operation(EnumStringMetric) \
    operation(NumericMetric) \
    operation(RealTimeSampleArrayMetric) \
    operation(StringMetric) \
    \
    /* ... no handling of contexts ... */ \
    \
    operation(MdsActivateOperation) \
    operation(MdsSetAlertStateOperation) \
    operation(MdsSetComponentStateOperation) \
    operation(MdsSetContextStateOperation) \
    operation(MdsSetMetricStateOperation) \
    operation(MdsSetStringOperation) \
    operation(MdsSetValueOperation) \
    operation(VmdActivateOperation) \
    operation(VmdSetAlertStateOperation) \
    operation(VmdSetComponentStateOperation) \
    operation(VmdSetContextStateOperation) \
    operation(VmdSetMetricStateOperation) \
    operation(VmdSetStringOperation) \
    operation(VmdSetValueOperation)

} // namespace Impl
