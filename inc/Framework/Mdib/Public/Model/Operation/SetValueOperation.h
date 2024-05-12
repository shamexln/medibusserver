#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/MdsVmdTypes.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Operation/SetValueOperationDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Operation/SetValueOperationStateBuilder.h>

#include <boost/optional/optional.hpp>

#include <memory>

namespace DFL
{
namespace Mdib
{
class MdsSetValueOperation;
class MdsSco;
class VmdSetValueOperation;
class VmdSco;

/**
 * @brief Type safe handle for \ref MdsSetValueOperation.
 * @ingroup Mdib
 */
using MdsSetValueOperationHandle = BasicHandle<MdsSetValueOperation>;
/**
 * @brief Type safe handle for \ref VmdSetValueOperation.
 * @ingroup Mdib
 */
using VmdSetValueOperationHandle = BasicHandle<VmdSetValueOperation>;

/**
 * @brief Describes a numeric set operation for a specific object state in the MDIB that is exposed on the \ref Sco.
 * @tparam T_Parent Parent entity of the operation (either \ref MdsSco or \ref VmdSco).
 * \note Instead of creating a template instance, use \ref MdsSetValueOperation and \ref VmdSetValueOperation.
 * @ingroup Mdib
 */
template<class T_Entity, class T_Parent>
class SetValueOperation: public Impl::MdibEntity<T_Entity, SetValueOperationDescriptorBuilder, SetValueOperationStateBuilder, T_Parent>
{
    DFL_MDIB_IMMUTABLE(SetValueOperation)

    protected:
        /**
         * @brief Constructor.
         */
        SetValueOperation(const BasicHandle<T_Entity>& handle,
                          const DFL::NotNull<SetValueOperationDescriptorSharedPtr>& descriptor,
                          VersionCounter descriptorVersion,
                          const DFL::NotNull<SetValueOperationStateSharedPtr>& state,
                          VersionCounter stateVersion,
                          const BasicHandle<T_Parent>& parent);
};

template<class T_Entity, class T_Parent>
inline SetValueOperation<T_Entity, T_Parent>::SetValueOperation(const BasicHandle<T_Entity>& handle,
                                                                const DFL::NotNull<SetValueOperationDescriptorSharedPtr>& descriptor,
                                                                VersionCounter descriptorVersion,
                                                                const DFL::NotNull<SetValueOperationStateSharedPtr>& state,
                                                                VersionCounter stateVersion,
                                                                const BasicHandle<T_Parent>& parent) :
        Impl::MdibEntity<T_Entity, SetValueOperationDescriptorBuilder, SetValueOperationStateBuilder, T_Parent>(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

/**
 * @brief Definition of a set value operation that has a \ref MdsSco as parent.
 */
class MdsSetValueOperation: public SetValueOperation<MdsSetValueOperation, MdsSco>
{
    DFL_MDIB_IMMUTABLE(MdsSetValueOperation)

    public:
        /**
         * @brief Constructor.
         */
        MdsSetValueOperation(const MdsSetValueOperationHandle& handle,
                             const DFL::NotNull<SetValueOperationDescriptorSharedPtr>& descriptor,
                             VersionCounter descriptorVersion,
                             const DFL::NotNull<SetValueOperationStateSharedPtr>& state,
                             VersionCounter stateVersion,
                             const BasicHandle<MdsSco>& parent);
};

/**
 * @brief Definition of a set value operation that has a \ref VmdSco as parent.
 */
class VmdSetValueOperation: public SetValueOperation<VmdSetValueOperation, VmdSco>
{
    DFL_MDIB_IMMUTABLE(VmdSetValueOperation)

    public:
        /**
         * @brief Constructor.
         */
        VmdSetValueOperation(const VmdSetValueOperationHandle& handle,
                             const DFL::NotNull<SetValueOperationDescriptorSharedPtr>& descriptor,
                             VersionCounter descriptorVersion,
                             const DFL::NotNull<SetValueOperationStateSharedPtr>& state,
                             VersionCounter stateVersion,
                             const BasicHandle<VmdSco>& parent);
};

/**
 * @brief Type informations of \ref SetValueOperation
 */
DFL_MDIB_MDSVMD_TYPES(SetValueOperation)

inline MdsSetValueOperation::MdsSetValueOperation(const MdsSetValueOperationHandle& handle,
                                                  const DFL::NotNull<SetValueOperationDescriptorSharedPtr>& descriptor,
                                                  VersionCounter descriptorVersion,
                                                  const DFL::NotNull<SetValueOperationStateSharedPtr>& state,
                                                  VersionCounter stateVersion,
                                                  const BasicHandle<MdsSco>& parent):
        SetValueOperation(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

inline VmdSetValueOperation::VmdSetValueOperation(const VmdSetValueOperationHandle& handle,
                                                  const DFL::NotNull<SetValueOperationDescriptorSharedPtr>& descriptor,
                                                  VersionCounter descriptorVersion,
                                                  const DFL::NotNull<SetValueOperationStateSharedPtr>& state,
                                                  VersionCounter stateVersion,
                                                  const BasicHandle<VmdSco>& parent):
        SetValueOperation(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

/**
 * @brief Definition of shared pointer type \ref MdsSetValueOperationSharedPtr for entity \ref MdsSetValueOperation.
 */
using MdsSetValueOperationSharedPtr = SharedPtr<MdsSetValueOperation>;

/**
 * @brief Definition of shared pointer type \ref VmdSetValueOperationSharedPtr for entity \ref VmdSetValueOperation.
 */
using VmdSetValueOperationSharedPtr = SharedPtr<VmdSetValueOperation>;

} /* namespace Mdib */
} /* namespace DFL */
