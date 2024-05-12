#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/MdsVmdTypes.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Operation/SetStringOperationDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Operation/SetStringOperationStateBuilder.h>

#include <boost/optional/optional.hpp>

#include <memory>

namespace DFL
{
namespace Mdib
{
class MdsSetStringOperation;
class MdsSco;
class VmdSetStringOperation;
class VmdSco;

/**
 * @brief Type safe handle for \ref MdsSetStringOperation.
 * @ingroup Mdib
 */
using MdsSetStringOperationHandle = BasicHandle<MdsSetStringOperation>;
/**
 * @brief Type safe handle for \ref VmdSetStringOperation.
 * @ingroup Mdib
 */
using VmdSetStringOperationHandle = BasicHandle<VmdSetStringOperation>;

/**
 * @brief Describes a string set operation for a specific object state in the MDIB that is exposed on the \ref Sco.
 * @tparam T_Parent Parent entity of the operation (either \ref MdsSco or \ref VmdSco).
 * \note Instead of creating a template instance, use \ref MdsSetStringOperation and \ref VmdSetStringOperation.
 * @ingroup Mdib
 */
template<class T_Entity, class T_Parent>
class SetStringOperation: public Impl::MdibEntity<T_Entity, SetStringOperationDescriptorBuilder, SetStringOperationStateBuilder, T_Parent>
{
    DFL_MDIB_IMMUTABLE(SetStringOperation)

    protected:
        /**
         * @brief Constructor.
         */
        SetStringOperation(const BasicHandle<T_Entity>& handle,
                           const DFL::NotNull<SetStringOperationDescriptorSharedPtr>& descriptor,
                           VersionCounter descriptorVersion,
                           const DFL::NotNull<SetStringOperationStateSharedPtr>& state,
                           VersionCounter stateVersion,
                           const BasicHandle<T_Parent>& parent);
};

template<class T_Entity, class T_Parent>
inline SetStringOperation<T_Entity, T_Parent>::SetStringOperation(const BasicHandle<T_Entity>& handle,
                                                                  const DFL::NotNull<SetStringOperationDescriptorSharedPtr>& descriptor,
                                                                  VersionCounter descriptorVersion,
                                                                  const DFL::NotNull<SetStringOperationStateSharedPtr>& state,
                                                                  VersionCounter stateVersion,
                                                                  const BasicHandle<T_Parent>& parent) :
        Impl::MdibEntity<T_Entity, SetStringOperationDescriptorBuilder, SetStringOperationStateBuilder, T_Parent>(
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
class MdsSetStringOperation: public SetStringOperation<MdsSetStringOperation, MdsSco>
{
    DFL_MDIB_IMMUTABLE(MdsSetStringOperation)

    public:
        /**
         * @brief Constructor.
         */
        MdsSetStringOperation(const MdsSetStringOperationHandle& handle,
                              const DFL::NotNull<SetStringOperationDescriptorSharedPtr>& descriptor,
                              VersionCounter descriptorVersion,
                              const DFL::NotNull<SetStringOperationStateSharedPtr>& state,
                              VersionCounter stateVersion,
                              const BasicHandle<MdsSco>& parent);
};

/**
 * @brief Definition of a set context state operation that has a \ref VmdSco as parent.
 */
class VmdSetStringOperation: public SetStringOperation<VmdSetStringOperation, VmdSco>
{
    DFL_MDIB_IMMUTABLE(VmdSetStringOperation)

    public:
        /**
         * @brief Constructor.
         */
        VmdSetStringOperation(const VmdSetStringOperationHandle& handle,
                              const DFL::NotNull<SetStringOperationDescriptorSharedPtr>& descriptor,
                              VersionCounter descriptorVersion,
                              const DFL::NotNull<SetStringOperationStateSharedPtr>& state,
                              VersionCounter stateVersion,
                              const BasicHandle<VmdSco>& parent);
};

/**
 * @brief Type informations of \ref SetStringOperation
 */
DFL_MDIB_MDSVMD_TYPES(SetStringOperation)

inline MdsSetStringOperation::MdsSetStringOperation(const MdsSetStringOperationHandle& handle,
                                                    const DFL::NotNull<SetStringOperationDescriptorSharedPtr>& descriptor,
                                                    VersionCounter descriptorVersion,
                                                    const DFL::NotNull<SetStringOperationStateSharedPtr>& state,
                                                    VersionCounter stateVersion,
                                                    const BasicHandle<MdsSco>& parent):
        SetStringOperation(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

inline VmdSetStringOperation::VmdSetStringOperation(const VmdSetStringOperationHandle& handle,
                                                    const DFL::NotNull<SetStringOperationDescriptorSharedPtr>& descriptor,
                                                    VersionCounter descriptorVersion,
                                                    const DFL::NotNull<SetStringOperationStateSharedPtr>& state,
                                                    VersionCounter stateVersion,
                                                    const BasicHandle<VmdSco>& parent):
        SetStringOperation(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

/**
 * @brief Definition of shared pointer type \ref MdsSetStringOperationSharedPtr for entity \ref MdsSetStringOperation.
 */
using MdsSetStringOperationSharedPtr = SharedPtr<MdsSetStringOperation>;

/**
 * @brief Definition of shared pointer type \ref VmdSetStringOperationSharedPtr for entity \ref VmdSetStringOperation.
 */
using VmdSetStringOperationSharedPtr = SharedPtr<VmdSetStringOperation>;

} /* namespace Mdib */
} /* namespace DFL */
