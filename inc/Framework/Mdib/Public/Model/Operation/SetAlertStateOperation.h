#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/MdsVmdTypes.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Operation/SetAlertStateOperationDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Operation/SetAlertStateOperationStateBuilder.h>

#include <boost/optional/optional.hpp>

namespace DFL
{
namespace Mdib
{
class MdsSetAlertStateOperation;
class MdsSco;
class VmdSetAlertStateOperation;
class VmdSco;

/**
 * @brief Type safe handle for \ref MdsSetAlertStateOperation.
 * @ingroup Mdib
 */
using MdsSetAlertStateOperationHandle = BasicHandle<MdsSetAlertStateOperation>;
/**
 * @brief Type safe handle for \ref VmdSetAlertStateOperation.
 * @ingroup Mdib
 */
using VmdSetAlertStateOperationHandle = BasicHandle<VmdSetAlertStateOperation>;

/**
 * @brief Describes an alert state set operation for a specific alert state in the MDIB that is exposed on the \ref Sco.
 * @tparam T_Parent Parent entity of the operation (either \ref MdsSco or \ref VmdSco).
 * \note Instead of creating a template instance, use \ref MdsSetAlertStateOperation and \ref VmdSetAlertStateOperation.
 * @ingroup Mdib
 */
template<class T_Entity, class T_Parent>
class SetAlertStateOperation: public Impl::MdibEntity<T_Entity, SetAlertStateOperationDescriptorBuilder, SetAlertStateOperationStateBuilder, T_Parent>
{
    DFL_MDIB_IMMUTABLE(SetAlertStateOperation)

    protected:
        /**
         * @brief Constructor.
         */
        SetAlertStateOperation(const BasicHandle<T_Entity>& handle,
                               const DFL::NotNull<SetAlertStateOperationDescriptorSharedPtr>& descriptor,
                               VersionCounter descriptorVersion,
                               const DFL::NotNull<SetAlertStateOperationStateSharedPtr>& state,
                               VersionCounter stateVersion,
                               const BasicHandle<T_Parent>& parent);
};

template<class T_Entity, class T_Parent>
inline SetAlertStateOperation<T_Entity, T_Parent>::SetAlertStateOperation(const BasicHandle<T_Entity>& handle,
                                                                          const DFL::NotNull<SetAlertStateOperationDescriptorSharedPtr>& descriptor,
                                                                          VersionCounter descriptorVersion,
                                                                          const DFL::NotNull<SetAlertStateOperationStateSharedPtr>& state,
                                                                          VersionCounter stateVersion,
                                                                          const BasicHandle<T_Parent>& parent) :
        Impl::MdibEntity<T_Entity, SetAlertStateOperationDescriptorBuilder, SetAlertStateOperationStateBuilder, T_Parent>(
            handle,
            descriptor,
            descriptorVersion,
            state,
            stateVersion,
            parent)
{
}

/**
 * @brief Definition of a set alert state operation that has a \ref MdsSco as parent.
 */
class MdsSetAlertStateOperation: public SetAlertStateOperation<MdsSetAlertStateOperation, MdsSco>
{
    DFL_MDIB_IMMUTABLE(MdsSetAlertStateOperation)
    public:
        /**
         * @brief Constructor.
         */
        MdsSetAlertStateOperation(const MdsSetAlertStateOperationHandle& handle,
                                  const DFL::NotNull<SetAlertStateOperationDescriptorSharedPtr>& descriptor,
                                  VersionCounter descriptorVersion,
                                  const DFL::NotNull<SetAlertStateOperationStateSharedPtr>& state,
                                  VersionCounter stateVersion,
                                  const BasicHandle<MdsSco>& parent);
};

/**
 * @brief Definition of a set alert state operation that has a \ref VmdSco as parent.
 */
class VmdSetAlertStateOperation: public SetAlertStateOperation<VmdSetAlertStateOperation, VmdSco>
{
    DFL_MDIB_IMMUTABLE(VmdSetAlertStateOperation)
    public:
        /**
         * @brief Constructor.
         */
        VmdSetAlertStateOperation(const VmdSetAlertStateOperationHandle& handle,
                                  const DFL::NotNull<SetAlertStateOperationDescriptorSharedPtr>& descriptor,
                                  VersionCounter descriptorVersion,
                                  const DFL::NotNull<SetAlertStateOperationStateSharedPtr>& state,
                                  VersionCounter stateVersion,
                                  const BasicHandle<VmdSco>& parent);
};

/**
 * @brief Type information of \ref SetAlertStateOperation
 */
DFL_MDIB_MDSVMD_TYPES(SetAlertStateOperation)

inline MdsSetAlertStateOperation::MdsSetAlertStateOperation(const MdsSetAlertStateOperationHandle& handle,
                                                            const DFL::NotNull<SetAlertStateOperationDescriptorSharedPtr>& descriptor,
                                                            VersionCounter descriptorVersion,
                                                            const DFL::NotNull<SetAlertStateOperationStateSharedPtr>& state,
                                                            VersionCounter stateVersion,
                                                            const BasicHandle<MdsSco>& parent):
        SetAlertStateOperation(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

inline VmdSetAlertStateOperation::VmdSetAlertStateOperation(const VmdSetAlertStateOperationHandle& handle,
                                                            const DFL::NotNull<SetAlertStateOperationDescriptorSharedPtr>& descriptor,
                                                            VersionCounter descriptorVersion,
                                                            const DFL::NotNull<SetAlertStateOperationStateSharedPtr>& state,
                                                            VersionCounter stateVersion,
                                                            const BasicHandle<VmdSco>& parent):
        SetAlertStateOperation(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

/**
 * @brief Definition of shared pointer type \ref MdsSetAlertStateOperationSharedPtr for entity \ref MdsSetAlertStateOperation.
 */
using MdsSetAlertStateOperationSharedPtr = SharedPtr<MdsSetAlertStateOperation>;

/**
 * @brief Definition of shared pointer type \ref VmdSetAlertStateOperationSharedPtr for entity \ref VmdSetAlertStateOperation.
 */
using VmdSetAlertStateOperationSharedPtr = SharedPtr<VmdSetAlertStateOperation>;

} /* namespace Mdib */
} /* namespace DFL */
