#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/MdsVmdTypes.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Operation/SetContextStateOperationDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Operation/SetContextStateOperationStateBuilder.h>

#include <boost/optional/optional.hpp>

namespace DFL
{
namespace Mdib
{
class MdsSetContextStateOperation;
class MdsSco;
class VmdSetContextStateOperation;
class VmdSco;

/**
 * @brief Type safe handle for \ref MdsSetContextStateOperation.
 * @ingroup Mdib
 */
using MdsSetContextStateOperationHandle = BasicHandle<MdsSetContextStateOperation>;
/**
 * @brief Type safe handle for \ref VmdSetContextStateOperation.
 * @ingroup Mdib
 */
using VmdSetContextStateOperationHandle = BasicHandle<VmdSetContextStateOperation>;

/**
 * @brief Describes a context state set operation for a specific context state in the MDIB that is exposed on the \ref Sco.
 * @tparam T_Parent Parent entity of the operation (either \ref MdsSco or \ref VmdSco).
 * \note Instead of creating a template instance, use \ref MdsSetContextStateOperation and \ref VmdSetContextStateOperation.
 * @ingroup Mdib
 */
template<class T_Entity, class T_Parent>
class SetContextStateOperation: public Impl::MdibEntity<T_Entity, SetContextStateOperationDescriptorBuilder, SetContextStateOperationStateBuilder, T_Parent>
{
    DFL_MDIB_IMMUTABLE(SetContextStateOperation)

    protected:
        /**
         * @brief Constructor.
         */
        SetContextStateOperation(const BasicHandle<T_Entity>& handle,
                                 const DFL::NotNull<SetContextStateOperationDescriptorSharedPtr>& descriptor,
                                 VersionCounter descriptorVersion,
                                 const DFL::NotNull<SetContextStateOperationStateSharedPtr>& state,
                                 VersionCounter stateVersion,
                                 const BasicHandle<T_Parent>& parent);
};

template<class T_Entity, class T_Parent>
inline SetContextStateOperation<T_Entity, T_Parent>::SetContextStateOperation(const BasicHandle<T_Entity>& handle,
                                                                              const DFL::NotNull<SetContextStateOperationDescriptorSharedPtr>& descriptor,
                                                                              VersionCounter descriptorVersion,
                                                                              const DFL::NotNull<SetContextStateOperationStateSharedPtr>& state,
                                                                              VersionCounter stateVersion,
                                                                              const BasicHandle<T_Parent>& parent) :
        Impl::MdibEntity<T_Entity, SetContextStateOperationDescriptorBuilder, SetContextStateOperationStateBuilder, T_Parent>(
            handle,
            descriptor,
            descriptorVersion,
            state,
            stateVersion,
            parent)
{
}

/**
 * @brief Definition of a set context state operation that has a \ref MdsSco as parent.
 */
class MdsSetContextStateOperation: public SetContextStateOperation<MdsSetContextStateOperation, MdsSco>
{
    DFL_MDIB_IMMUTABLE(MdsSetContextStateOperation)

    public:
        /**
         * @brief Constructor.
         */
        MdsSetContextStateOperation(const MdsSetContextStateOperationHandle& handle,
                                    const DFL::NotNull<SetContextStateOperationDescriptorSharedPtr>& descriptor,
                                    VersionCounter descriptorVersion,
                                    const DFL::NotNull<SetContextStateOperationStateSharedPtr>& state,
                                    VersionCounter stateVersion,
                                    const BasicHandle<MdsSco>& parent);
};

/**
 * @brief Type informations of \ref SetContextStateOperation
 */
DFL_MDIB_MDSVMD_TYPES(SetContextStateOperation)

/**
 * @brief Definition of a set context state operation that has a \ref VmdSco as parent.
 */
class VmdSetContextStateOperation: public SetContextStateOperation<VmdSetContextStateOperation, VmdSco>
{
    DFL_MDIB_IMMUTABLE(VmdSetContextStateOperation)

    public:
        /**
         * @brief Constructor.
         */
        VmdSetContextStateOperation(const VmdSetContextStateOperationHandle& handle,
                                    const DFL::NotNull<SetContextStateOperationDescriptorSharedPtr>& descriptor,
                                    VersionCounter descriptorVersion,
                                    const DFL::NotNull<SetContextStateOperationStateSharedPtr>& state,
                                    VersionCounter stateVersion,
                                    const BasicHandle<VmdSco>& parent);
};

inline MdsSetContextStateOperation::MdsSetContextStateOperation(const MdsSetContextStateOperationHandle& handle,
                                                                const DFL::NotNull<SetContextStateOperationDescriptorSharedPtr>& descriptor,
                                                                VersionCounter descriptorVersion,
                                                                const DFL::NotNull<SetContextStateOperationStateSharedPtr>& state,
                                                                VersionCounter stateVersion,
                                                                const BasicHandle<MdsSco>& parent):
        SetContextStateOperation(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

inline VmdSetContextStateOperation::VmdSetContextStateOperation(const VmdSetContextStateOperationHandle& handle,
                                                                const DFL::NotNull<SetContextStateOperationDescriptorSharedPtr>& descriptor,
                                                                VersionCounter descriptorVersion,
                                                                const DFL::NotNull<SetContextStateOperationStateSharedPtr>& state,
                                                                VersionCounter stateVersion,
                                                                const BasicHandle<VmdSco>& parent):
        SetContextStateOperation(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

/**
 * @brief Definition of shared pointer type \ref MdsSetContextStateOperationSharedPtr for entity \ref MdsSetContextStateOperation.
 */
using MdsSetContextStateOperationSharedPtr = SharedPtr<MdsSetContextStateOperation>;

/**
 * @brief Definition of shared pointer type \ref VmdSetContextStateOperationSharedPtr for entity \ref VmdSetContextStateOperation.
 */
using VmdSetContextStateOperationSharedPtr = SharedPtr<VmdSetContextStateOperation>;

} /* namespace Mdib */
} /* namespace DFL */
