#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/MdsVmdTypes.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystemDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystemStateBuilder.h>

namespace DFL
{
namespace Mdib
{
class Mds;
class MdsAlertSystem;
class VmdAlertSystem;
class MdsAlertCondition;
class MdsLimitAlertCondition;
class MdsAlertSignal;
class Vmd;
class VmdAlertCondition;
class VmdLimitAlertCondition;
class VmdAlertSignal;

/**
 * @brief Type safe handle for \ref MdsAlertSystem.
 * @ingroup Mdib
 */
using MdsAlertSystemHandle = BasicHandle<MdsAlertSystem>;
/**
 * @brief Type safe handle for \ref VmdAlertSystem.
 * @ingroup Mdib
 */
using VmdAlertSystemHandle = BasicHandle<VmdAlertSystem>;

/**
 * @brief Comprises \ref AlertCondition and \ref AlertSignal objects.
 * @details \ref Mds and \ref Vmd may include an %AlertSystem, which in turn detects \ref AlertCondition objects
 * and generates \ref AlertSignal objects. More information can be found in \ref AlertSystemDescriptor and \ref AlertSystemState.
 * @ingroup Mdib
 */
template<class T_Entity, class T_Parent>
class AlertSystem: public Impl::MdibEntity<T_Entity, AlertSystemDescriptorBuilder, AlertSystemStateBuilder, T_Parent>
{
    DFL_MDIB_IMMUTABLE(AlertSystem)
    protected:
        /**
         * @brief Constructor.
         */
        AlertSystem(const BasicHandle<T_Entity>& handle,
                    const DFL::NotNull<AlertSystemDescriptorSharedPtr>& descriptor,
                    VersionCounter descriptorVersion,
                    const DFL::NotNull<AlertSystemStateSharedPtr>& state,
                    VersionCounter stateVersion,
                    const BasicHandle<T_Parent>& parent);
};

/**
 * @brief Specific \ref AlertSystem that is used by \ref Mds.
 */
class MdsAlertSystem: public AlertSystem<MdsAlertSystem, Mds>
{
    DFL_MDIB_IMMUTABLE(MdsAlertSystem)
    public:
        /// Type of alert condition that can be in this alert system type
        using AlertConditionType = MdsAlertCondition;
        /// Type of limit alert condition that can be in this alert system type
        using LimitAlertConditionType = MdsLimitAlertCondition;
        /// Type of alert signal that can be in this alert system type
        using AlertSignalType = MdsAlertSignal;

        /**
         * @brief Constructor.
         */
        MdsAlertSystem(const MdsAlertSystemHandle& handle,
                       const DFL::NotNull<AlertSystemDescriptorSharedPtr>& descriptor,
                       VersionCounter descriptorVersion,
                       const DFL::NotNull<AlertSystemStateSharedPtr>& state,
                       VersionCounter stateVersion,
                       const BasicHandle<Mds>& parent);

};

/**
 * @brief Specific \ref AlertSystem that is used by \ref Vmd.
 */
class VmdAlertSystem: public AlertSystem<VmdAlertSystem, Vmd>
{
    DFL_MDIB_IMMUTABLE(VmdAlertSystem)
    public:
        /// Type of alert condition that can be in this alert system type
        using AlertConditionType = VmdAlertCondition;
        /// Type of limit alert condition that can be in this alert system type
        using LimitAlertConditionType = VmdLimitAlertCondition;
        /// Type of alert signal that can be in this alert system type
        using AlertSignalType = VmdAlertSignal;

        /**
         * @brief Constructor.
         */
        VmdAlertSystem(const VmdAlertSystemHandle& handle,
                       const DFL::NotNull<AlertSystemDescriptorSharedPtr>& descriptor,
                       VersionCounter descriptorVersion,
                       const DFL::NotNull<AlertSystemStateSharedPtr>& state,
                       VersionCounter stateVersion,
                       const BasicHandle<Vmd>& parent);
};


/**
 * @brief Type information of \ref AlertSystem
 */
DFL_MDIB_MDSVMD_TYPES(AlertSystem)


template<class T_Entity, class T_Parent>
inline AlertSystem<T_Entity, T_Parent>::AlertSystem(const BasicHandle<T_Entity>& handle,
                                                    const DFL::NotNull<AlertSystemDescriptorSharedPtr>& descriptor,
                                                    VersionCounter descriptorVersion,
                                                    const DFL::NotNull<AlertSystemStateSharedPtr>& state,
                                                    VersionCounter stateVersion,
                                                    const BasicHandle<T_Parent>& parent) :
        Impl::MdibEntity<T_Entity, AlertSystemDescriptorBuilder, AlertSystemStateBuilder, T_Parent>(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

inline MdsAlertSystem::MdsAlertSystem(const MdsAlertSystemHandle& handle,
                                      const DFL::NotNull<AlertSystemDescriptorSharedPtr>& descriptor,
                                      VersionCounter descriptorVersion,
                                      const DFL::NotNull<AlertSystemStateSharedPtr>& state,
                                      VersionCounter stateVersion,
                                      const BasicHandle<Mds>& parent) :
        AlertSystem(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

inline VmdAlertSystem::VmdAlertSystem(const VmdAlertSystemHandle& handle,
                                      const DFL::NotNull<AlertSystemDescriptorSharedPtr>& descriptor,
                                      VersionCounter descriptorVersion,
                                      const DFL::NotNull<AlertSystemStateSharedPtr>& state,
                                      VersionCounter stateVersion,
                                      const BasicHandle<Vmd>& parent) :
        AlertSystem(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}


/**
 * @brief Definition of shared pointer type \ref MdsAlertSystemSharedPtr for entity \ref MdsAlertSystem.
 */
using MdsAlertSystemSharedPtr = SharedPtr<MdsAlertSystem>;

/**
 * @brief Definition of shared pointer type \ref VmdAlertSystemSharedPtr for entity \ref VmdAlertSystem.
 */
using VmdAlertSystemSharedPtr = SharedPtr<VmdAlertSystem>;

}
}
