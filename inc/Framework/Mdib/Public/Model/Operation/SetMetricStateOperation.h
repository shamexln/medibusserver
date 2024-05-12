#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/MdsVmdTypes.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Operation/SetMetricStateOperationDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Operation/SetMetricStateOperationStateBuilder.h>

#include <boost/optional/optional.hpp>

#include <memory>

namespace DFL
{
namespace Mdib
{
class MdsSetMetricStateOperation;
class MdsSco;
class VmdSetMetricStateOperation;
class VmdSco;

/**
 * @brief Type safe handle for \ref MdsSetMetricStateOperation.
 * @ingroup Mdib
 */
using MdsSetMetricStateOperationHandle = BasicHandle<MdsSetMetricStateOperation>;
/**
 * @brief Type safe handle for \ref VmdSetMetricStateOperation.
 * @ingroup Mdib
 */
using VmdSetMetricStateOperationHandle = BasicHandle<VmdSetMetricStateOperation>;

/**
 * @brief Describes a metric state set operation for a specific metric state in the MDIB that is exposed on the \ref Sco.
 * @tparam T_Parent Parent entity of the operation (either \ref MdsSco or \ref VmdSco).
 * \note Instead of creating a template instance, use \ref MdsSetMetricStateOperation and \ref VmdSetMetricStateOperation.
 * @ingroup Mdib
 */
template<class T_Entity, class T_Parent>
class SetMetricStateOperation: public Impl::MdibEntity<T_Entity, SetMetricStateOperationDescriptorBuilder, SetMetricStateOperationStateBuilder, T_Parent>
{
    DFL_MDIB_IMMUTABLE(SetMetricStateOperation)

    protected:
        /**
         * @brief Constructor.
         */
        SetMetricStateOperation(const BasicHandle<T_Entity>& handle,
                                const DFL::NotNull<SetMetricStateOperationDescriptorSharedPtr>& descriptor,
                                VersionCounter descriptorVersion,
                                const DFL::NotNull<SetMetricStateOperationStateSharedPtr>& state,
                                VersionCounter stateVersion,
                                const BasicHandle<T_Parent>& parent);
};

template<class T_Entity, class T_Parent>
inline SetMetricStateOperation<T_Entity, T_Parent>::SetMetricStateOperation(const BasicHandle<T_Entity>& handle,
                                                                            const DFL::NotNull<SetMetricStateOperationDescriptorSharedPtr>& descriptor,
                                                                            VersionCounter descriptorVersion,
                                                                            const DFL::NotNull<SetMetricStateOperationStateSharedPtr>& state,
                                                                            VersionCounter stateVersion,
                                                                            const BasicHandle<T_Parent>& parent) :
        Impl::MdibEntity<T_Entity, SetMetricStateOperationDescriptorBuilder, SetMetricStateOperationStateBuilder, T_Parent>(
            handle,
            descriptor,
            descriptorVersion,
            state,
            stateVersion,
            parent)
{
}

/**
 * @brief Definition of a set metric state operation that has an \ref MdsSco as parent.
 */
class MdsSetMetricStateOperation: public SetMetricStateOperation<MdsSetMetricStateOperation, MdsSco>
{
    DFL_MDIB_IMMUTABLE(MdsSetMetricStateOperation)

    public:
        /**
         * @brief Constructor.
         */
        MdsSetMetricStateOperation(const MdsSetMetricStateOperationHandle& handle,
                                   const DFL::NotNull<SetMetricStateOperationDescriptorSharedPtr>& descriptor,
                                   VersionCounter descriptorVersion,
                                   const DFL::NotNull<SetMetricStateOperationStateSharedPtr>& state,
                                   VersionCounter stateVersion,
                                   const BasicHandle<MdsSco>& parent);
};

/**
 * @brief Definition of a set metric state operation that has a \ref VmdSco as parent.
 */
class VmdSetMetricStateOperation: public SetMetricStateOperation<VmdSetMetricStateOperation, VmdSco>
{
    DFL_MDIB_IMMUTABLE(VmdSetMetricStateOperation)

    public:
        /**
         * @brief Constructor.
         */
        VmdSetMetricStateOperation(const VmdSetMetricStateOperationHandle& handle,
                                   const DFL::NotNull<SetMetricStateOperationDescriptorSharedPtr>& descriptor,
                                   VersionCounter descriptorVersion,
                                   const DFL::NotNull<SetMetricStateOperationStateSharedPtr>& state,
                                   VersionCounter stateVersion,
                                   const BasicHandle<VmdSco>& parent);
};

/**
 * @brief Type informations of \ref SetMetricStateOperation
 */
DFL_MDIB_MDSVMD_TYPES(SetMetricStateOperation)

inline MdsSetMetricStateOperation::MdsSetMetricStateOperation(const MdsSetMetricStateOperationHandle& handle,
                                                              const DFL::NotNull<SetMetricStateOperationDescriptorSharedPtr>& descriptor,
                                                              VersionCounter descriptorVersion,
                                                              const DFL::NotNull<SetMetricStateOperationStateSharedPtr>& state,
                                                              VersionCounter stateVersion,
                                                              const BasicHandle<MdsSco>& parent):
        SetMetricStateOperation(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

inline VmdSetMetricStateOperation::VmdSetMetricStateOperation(const VmdSetMetricStateOperationHandle& handle,
                                                              const DFL::NotNull<SetMetricStateOperationDescriptorSharedPtr>& descriptor,
                                                              VersionCounter descriptorVersion,
                                                              const DFL::NotNull<SetMetricStateOperationStateSharedPtr>& state,
                                                              VersionCounter stateVersion,
                                                              const BasicHandle<VmdSco>& parent):
        SetMetricStateOperation(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

/**
 * @brief Definition of shared pointer type \ref MdsSetMetricStateOperationSharedPtr for entity \ref MdsSetMetricStateOperation.
 */
using MdsSetMetricStateOperationSharedPtr = SharedPtr<MdsSetMetricStateOperation>;

/**
 * @brief Definition of shared pointer type \ref VmdSetMetricStateOperationSharedPtr for entity \ref VmdSetMetricStateOperation.
 */
using VmdSetMetricStateOperationSharedPtr = SharedPtr<VmdSetMetricStateOperation>;

} /* namespace Mdib */
} /* namespace DFL */
