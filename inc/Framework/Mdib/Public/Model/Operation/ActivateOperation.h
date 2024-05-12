#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/MdsVmdTypes.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Operation/ActivateOperationDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Operation/ActivateOperationStateBuilder.h>

#include <boost/optional/optional.hpp>

namespace DFL
{
namespace Mdib
{
class MdsActivateOperation;
class MdsSco;
class VmdActivateOperation;
class VmdSco;

/**
 * @brief Type safe handle for \ref MdsActivateOperation.
 * @ingroup Mdib
 */
using MdsActivateOperationHandle = BasicHandle<MdsActivateOperation>;
/**
 * @brief Type safe handle for \ref VmdActivateOperation.
 * @ingroup Mdib
 */
using VmdActivateOperationHandle = BasicHandle<VmdActivateOperation>;

/**
 * @brief Describes an activate operation that is exposed on the \ref Sco.
 * @details Activate operations are any parameterized operations that trigger an arbitrary action. The action that is triggered
 * is defined by the \ref AbstractDescriptor::type element.
 * @tparam T_Parent Parent entity of the operation (either \ref MdsSco or \ref VmdSco).
 * \note Instead of creating a template instance, use \ref MdsActivateOperation and \ref VmdActivateOperation.
 * @ingroup Mdib
 */
template<class T_Entity, class T_Parent>
class ActivateOperation: public Impl::MdibEntity<T_Entity, ActivateOperationDescriptorBuilder, ActivateOperationStateBuilder, T_Parent>
{
    DFL_MDIB_IMMUTABLE(ActivateOperation)

    protected:
        /**
         * @brief Constructor.
         */
        ActivateOperation(const BasicHandle<T_Entity>& handle,
                          const DFL::NotNull<ActivateOperationDescriptorSharedPtr>& descriptor,
                          VersionCounter descriptorVersion,
                          const DFL::NotNull<ActivateOperationStateSharedPtr>& state,
                          VersionCounter stateVersion,
                          const BasicHandle<T_Parent>& parent);
};

template<class T_Entity, class T_Parent>
inline ActivateOperation<T_Entity, T_Parent>::ActivateOperation(const BasicHandle<T_Entity>& handle,
                                                                const DFL::NotNull<ActivateOperationDescriptorSharedPtr>& descriptor,
                                                                VersionCounter descriptorVersion,
                                                                const DFL::NotNull<ActivateOperationStateSharedPtr>& state,
                                                                VersionCounter stateVersion,
                                                                const BasicHandle<T_Parent>& parent) :
        Impl::MdibEntity<T_Entity, ActivateOperationDescriptorBuilder, ActivateOperationStateBuilder, T_Parent>(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

/**
 * @brief Definition of an \ref ActivateOperation "activate operation" that has a \ref MdsSco as parent.
 */
class MdsActivateOperation: public ActivateOperation<MdsActivateOperation, MdsSco>
{
    DFL_MDIB_IMMUTABLE(MdsActivateOperation)

    public:
        /**
         * @brief Constructor.
         */
        MdsActivateOperation(const MdsActivateOperationHandle& handle,
                             const DFL::NotNull<ActivateOperationDescriptorSharedPtr>& descriptor,
                             VersionCounter descriptorVersion,
                             const DFL::NotNull<ActivateOperationStateSharedPtr>& state,
                             VersionCounter stateVersion,
                             const BasicHandle<MdsSco>& parent);
};

/**
 * @brief Definition of an \ref ActivateOperation "activate operation" that has a \ref VmdSco as parent.
 */
class VmdActivateOperation: public ActivateOperation<VmdActivateOperation, VmdSco>
{
    DFL_MDIB_IMMUTABLE(VmdActivateOperation)

    public:
        /**
         * @brief Constructor.
         */
        VmdActivateOperation(const VmdActivateOperationHandle& handle,
                             const DFL::NotNull<ActivateOperationDescriptorSharedPtr>& descriptor,
                             VersionCounter descriptorVersion,
                             const DFL::NotNull<ActivateOperationStateSharedPtr>& state,
                             VersionCounter stateVersion,
                             const BasicHandle<VmdSco>& parent);
};

/**
 * @brief Type informations of \ref ActivateOperation
 */
DFL_MDIB_MDSVMD_TYPES(ActivateOperation)

inline MdsActivateOperation::MdsActivateOperation(const MdsActivateOperationHandle& handle,
                                                  const DFL::NotNull<ActivateOperationDescriptorSharedPtr>& descriptor,
                                                  VersionCounter descriptorVersion,
                                                  const DFL::NotNull<ActivateOperationStateSharedPtr>& state,
                                                  VersionCounter stateVersion,
                                                  const BasicHandle<MdsSco>& parent):
        ActivateOperation(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

inline VmdActivateOperation::VmdActivateOperation(const VmdActivateOperationHandle& handle,
                                                  const DFL::NotNull<ActivateOperationDescriptorSharedPtr>& descriptor,
                                                  VersionCounter descriptorVersion,
                                                  const DFL::NotNull<ActivateOperationStateSharedPtr>& state,
                                                  VersionCounter stateVersion,
                                                  const BasicHandle<VmdSco>& parent):
        ActivateOperation(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

/**
 * @brief Definition of shared pointer type \ref MdsActivateOperationSharedPtr for entity \ref MdsActivateOperation.
 */
using MdsActivateOperationSharedPtr = SharedPtr<MdsActivateOperation>;

/**
 * @brief Definition of shared pointer type \ref VmdActivateOperationSharedPtr for entity \ref VmdActivateOperation.
 */
using VmdActivateOperationSharedPtr = SharedPtr<VmdActivateOperation>;

} /* namespace Mdib */
} /* namespace DFL */
