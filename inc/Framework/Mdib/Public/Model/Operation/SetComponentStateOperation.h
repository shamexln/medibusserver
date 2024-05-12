#pragma once

#include <memory>
#include <boost/optional/optional.hpp>
#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Private/Utils/MdsVmdTypes.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Operation/SetComponentStateOperationDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Operation/SetComponentStateOperationStateBuilder.h>

namespace DFL
{
namespace Mdib
{
class MdsSetComponentStateOperation;
class MdsSco;
class VmdSetComponentStateOperation;
class VmdSco;

/**
 * @brief Type safe handle for \ref MdsSetComponentStateOperation.
 * @ingroup Mdib
 */
using MdsSetComponentStateOperationHandle = BasicHandle<MdsSetComponentStateOperation>;
/**
 * @brief Type safe handle for \ref VmdSetComponentStateOperation.
 * @ingroup Mdib
 */
using VmdSetComponentStateOperationHandle = BasicHandle<VmdSetComponentStateOperation>;

/**
 * @brief Describes a component state set operation for a specific component state in the MDIB that is exposed on the \ref Sco.
 * @tparam T_Parent Parent entity of the operation (either \ref MdsSco or \ref VmdSco).
 * \note Instead of creating a template instance, use \ref MdsSetComponentStateOperation and \ref VmdSetComponentStateOperation.
 * @ingroup Mdib
 */
template<class T_Entity, class T_Parent>
class SetComponentStateOperation: public Impl::MdibEntity<T_Entity, SetComponentStateOperationDescriptorBuilder, SetComponentStateOperationStateBuilder, T_Parent>
{
    DFL_MDIB_IMMUTABLE(SetComponentStateOperation)

    protected:
        /**
         * @brief Constructor.
         */
        SetComponentStateOperation(const BasicHandle<T_Entity>& handle,
                                   const DFL::NotNull<SetComponentStateOperationDescriptorSharedPtr>& descriptor,
                                   VersionCounter descriptorVersion,
                                   const DFL::NotNull<SetComponentStateOperationStateSharedPtr>& state,
                                   VersionCounter stateVersion,
                                   const BasicHandle<T_Parent>& parent);
};

template<class T_Entity, class T_Parent>
inline SetComponentStateOperation<T_Entity, T_Parent>::SetComponentStateOperation(const BasicHandle<T_Entity>& handle,
                                                                                  const DFL::NotNull<SetComponentStateOperationDescriptorSharedPtr>& descriptor,
                                                                                  VersionCounter descriptorVersion,
                                                                                  const DFL::NotNull<SetComponentStateOperationStateSharedPtr>& state,
                                                                                  VersionCounter stateVersion,
                                                                                  const BasicHandle<T_Parent>& parent) :
        Impl::MdibEntity<T_Entity, SetComponentStateOperationDescriptorBuilder, SetComponentStateOperationStateBuilder, T_Parent>(
            handle,
            descriptor,
            descriptorVersion,
            state,
            stateVersion,
            parent)
{
}

/**
 * @brief Definition of a set component state operation that has a \ref MdsSco as parent.
 */
class MdsSetComponentStateOperation: public SetComponentStateOperation<MdsSetComponentStateOperation, MdsSco>
{
    DFL_MDIB_IMMUTABLE(MdsSetComponentStateOperation)

    public:
        /**
         * @brief Constructor.
         */
        MdsSetComponentStateOperation(const MdsSetComponentStateOperationHandle& handle,
                                      const DFL::NotNull<SetComponentStateOperationDescriptorSharedPtr>& descriptor,
                                      VersionCounter descriptorVersion,
                                      const DFL::NotNull<SetComponentStateOperationStateSharedPtr>& state,
                                      VersionCounter stateVersion,
                                      const BasicHandle<MdsSco>& parent);
};

/**
 * @brief Definition of a set component state operation that has a \ref VmdSco as parent.
 */
class VmdSetComponentStateOperation: public SetComponentStateOperation<VmdSetComponentStateOperation, VmdSco>
{
    DFL_MDIB_IMMUTABLE(VmdSetComponentStateOperation)

    public:
        /**
         * @brief Constructor.
         */
        VmdSetComponentStateOperation(const VmdSetComponentStateOperationHandle& handle,
                                      const DFL::NotNull<SetComponentStateOperationDescriptorSharedPtr>& descriptor,
                                      VersionCounter descriptorVersion,
                                      const DFL::NotNull<SetComponentStateOperationStateSharedPtr>& state,
                                      VersionCounter stateVersion,
                                      const BasicHandle<VmdSco>& parent);
};

/**
 * @brief Type informations of \ref SetComponentStateOperation
 */
DFL_MDIB_MDSVMD_TYPES(SetComponentStateOperation)

inline MdsSetComponentStateOperation::MdsSetComponentStateOperation(const MdsSetComponentStateOperationHandle& handle,
                                                                    const DFL::NotNull<SetComponentStateOperationDescriptorSharedPtr>& descriptor,
                                                                    VersionCounter descriptorVersion,
                                                                    const DFL::NotNull<SetComponentStateOperationStateSharedPtr>& state,
                                                                    VersionCounter stateVersion,
                                                                    const BasicHandle<MdsSco>& parent):
        SetComponentStateOperation(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

inline VmdSetComponentStateOperation::VmdSetComponentStateOperation(const VmdSetComponentStateOperationHandle& handle,
                                                                    const DFL::NotNull<SetComponentStateOperationDescriptorSharedPtr>& descriptor,
                                                                    VersionCounter descriptorVersion,
                                                                    const DFL::NotNull<SetComponentStateOperationStateSharedPtr>& state,
                                                                    VersionCounter stateVersion,
                                                                    const BasicHandle<VmdSco>& parent):
        SetComponentStateOperation(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

/**
 * @brief Definition of shared pointer type \ref MdsSetComponentStateOperationSharedPtr for entity \ref MdsSetComponentStateOperation.
 * @ingroup Mdib
 */
using MdsSetComponentStateOperationSharedPtr = SharedPtr<MdsSetComponentStateOperation>;

/**
 * @brief Definition of shared pointer type \ref VmdSetComponentStateOperationSharedPtr for entity \ref VmdSetComponentStateOperation.
 * @ingroup Mdib
 */
using VmdSetComponentStateOperationSharedPtr = SharedPtr<VmdSetComponentStateOperation>;

} /* namespace Mdib */
} /* namespace DFL */
