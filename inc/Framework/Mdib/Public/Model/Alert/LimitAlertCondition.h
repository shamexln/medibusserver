#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/MdsVmdTypes.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Alert/LimitAlertConditionDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Alert/LimitAlertConditionStateBuilder.h>

namespace DFL
{
namespace Mdib
{
class MdsLimitAlertCondition;
class MdsAlertSignal;
class MdsAlertSystem;
class VmdLimitAlertCondition;
class VmdAlertSignal;
class VmdAlertSystem;

/**
 * @brief Type safe handle for \ref MdsLimitAlertCondition.
 * @ingroup Mdib
 */
using MdsLimitAlertConditionHandle = BasicHandle<MdsLimitAlertCondition>;
/**
 * @brief Type safe handle for \ref VmdLimitAlertCondition.
 * @ingroup Mdib
 */
using VmdLimitAlertConditionHandle = BasicHandle<VmdLimitAlertCondition>;

/**
 * @brief Specialization of an \ref AlertCondition.
 * @brief An \ref AlertCondition that is active if at least one limit for
 * a referenced metric (\ref NumericMetric, \ref RealTimeSampleArrayMetric) has been violated.
 * @ingroup Mdib
 */
template<class T_Entity, class T_Parent, class T_AlertSignal>
class LimitAlertCondition: public Impl::MdibEntity<T_Entity, LimitAlertConditionDescriptorBuilder, LimitAlertConditionStateBuilder, T_Parent>
{
        DFL_MDIB_IMMUTABLE(LimitAlertCondition)

    protected:
        /**
         * @brief Constructor.
         */
        LimitAlertCondition(const BasicHandle<T_Entity>& handle,
                            const DFL::NotNull<LimitAlertConditionDescriptorSharedPtr>& descriptor,
                            VersionCounter descriptorVersion,
                            const DFL::NotNull<LimitAlertConditionStateSharedPtr>& state,
                            VersionCounter stateVersion,
                            const BasicHandle<T_Parent>& parent);
};

/**
 * @brief Definition of a \ref LimitAlertCondition that has an \ref MdsAlertSystem as parent.
 */
class MdsLimitAlertCondition: public LimitAlertCondition<MdsLimitAlertCondition, MdsAlertSystem, MdsAlertSignal>
{
        DFL_MDIB_IMMUTABLE(MdsLimitAlertCondition)

    public:
        /**
         * @brief Constructor.
         */
        MdsLimitAlertCondition(const MdsLimitAlertConditionHandle& handle,
                               const DFL::NotNull<LimitAlertConditionDescriptorSharedPtr>& descriptor,
                               VersionCounter descriptorVersion,
                               const DFL::NotNull<LimitAlertConditionStateSharedPtr>& state,
                               VersionCounter stateVersion,
                               const BasicHandle<MdsAlertSystem>& parent);
};

/**
 * @brief Definition of a \ref LimitAlertCondition that has a \ref VmdAlertSystem as parent.
 */
class VmdLimitAlertCondition: public LimitAlertCondition<VmdLimitAlertCondition, VmdAlertSystem, VmdAlertSignal>
{
        DFL_MDIB_IMMUTABLE(VmdLimitAlertCondition)
    public:
        /**
         * @brief Constructor.
         */
        VmdLimitAlertCondition(const VmdLimitAlertConditionHandle& handle,
                               const DFL::NotNull<LimitAlertConditionDescriptorSharedPtr>& descriptor,
                               VersionCounter descriptorVersion,
                               const DFL::NotNull<LimitAlertConditionStateSharedPtr>& state,
                               VersionCounter stateVersion,
                               const BasicHandle<VmdAlertSystem>& parent);
};

/**
 * @brief Type information of \ref LimitAlertCondition
 */
DFL_MDIB_MDSVMD_TYPES(LimitAlertCondition)

template<class T_Entity, class T_Parent, class T_AlertSignal>
inline LimitAlertCondition<T_Entity, T_Parent, T_AlertSignal>::LimitAlertCondition(
            const BasicHandle <T_Entity>& handle,
            const DFL::NotNull<LimitAlertConditionDescriptorSharedPtr>& descriptor,
            VersionCounter descriptorVersion,
            const DFL::NotNull<LimitAlertConditionStateSharedPtr>& state,
            VersionCounter stateVersion,
            const BasicHandle <T_Parent>& parent) :
        Impl::MdibEntity<T_Entity, LimitAlertConditionDescriptorBuilder, LimitAlertConditionStateBuilder, T_Parent>(
            handle,
            descriptor,
            descriptorVersion,
            state,
            stateVersion,
            parent)
{
}

inline MdsLimitAlertCondition::MdsLimitAlertCondition(const MdsLimitAlertConditionHandle& handle,
                                                      const DFL::NotNull<LimitAlertConditionDescriptorSharedPtr>& descriptor,
                                                      VersionCounter descriptorVersion,
                                                      const DFL::NotNull<LimitAlertConditionStateSharedPtr>& state,
                                                      VersionCounter stateVersion,
                                                      const BasicHandle<MdsAlertSystem>& parent):
        LimitAlertCondition(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

inline VmdLimitAlertCondition::VmdLimitAlertCondition(const VmdLimitAlertConditionHandle& handle,
                                                      const DFL::NotNull<LimitAlertConditionDescriptorSharedPtr>& descriptor,
                                                      VersionCounter descriptorVersion,
                                                      const DFL::NotNull<LimitAlertConditionStateSharedPtr>& state,
                                                      VersionCounter stateVersion,
                                                      const BasicHandle<VmdAlertSystem>& parent):
        LimitAlertCondition(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

/**
 * @brief Definition of shared pointer type \ref MdsLimitAlertConditionSharedPtr for entity \ref MdsLimitAlertCondition.
 */
using MdsLimitAlertConditionSharedPtr = SharedPtr<MdsLimitAlertCondition>;

/**
 * @brief Definition of shared pointer type \ref VmdLimitAlertConditionSharedPtr for entity \ref VmdLimitAlertCondition.
 */
using VmdLimitAlertConditionSharedPtr = SharedPtr<VmdLimitAlertCondition>;

} /* namespace Mdib */
} /* namespace DFL */
