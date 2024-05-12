#pragma once

#include <memory>
#include <boost/optional/optional.hpp>
#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Private/Utils/MdsVmdTypes.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Utils/Entities.h>
#include <Framework/Mdib/Public/Utils/EntityLists.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Component/ScoDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Component/ScoStateBuilder.h>

#include <variant>

namespace DFL::Mdib
{
class Mds;
class MdsSco;
class Vmd;
class VmdSco;

class MdsActivateOperation;
class MdsSetAlertStateOperation;
class MdsSetComponentStateOperation;
class MdsSetContextStateOperation;
class MdsSetMetricStateOperation;
class MdsSetStringOperation;
class MdsSetValueOperation;

class VmdActivateOperation;
class VmdSetAlertStateOperation;
class VmdSetComponentStateOperation;
class VmdSetContextStateOperation;
class VmdSetMetricStateOperation;
class VmdSetStringOperation;
class VmdSetValueOperation;

/**
 * @brief Type safe handle for \ref MdsSco.
 * @ingroup Mdib
 */
using MdsScoHandle = BasicHandle<MdsSco>;
/**
 * @brief Type safe handle for \ref VmdSco.
 * @ingroup Mdib
 */
using VmdScoHandle = BasicHandle<VmdSco>;

/**
 * @brief A service control object (SCO) to define remote control operations.
 * @details Any \ref AbstractOperationDescriptor::operationTarget within an SCO shall
 * only reference sibling or child descriptors of the SCO enclosing entity.
 * @ingroup Mdib
 */
template<class T_Entity, class T_Parent>
class Sco: public Impl::MdibEntity<T_Entity, ScoDescriptorBuilder, ScoStateBuilder, T_Parent>
{
    DFL_MDIB_IMMUTABLE(Sco)

    protected:
        /**
         * @brief Constructor.
         */
        Sco(const BasicHandle<T_Entity>& handle,
            const DFL::NotNull<ScoDescriptorSharedPtr>& descriptor,
            VersionCounter descriptorVersion,
            const DFL::NotNull<ScoStateSharedPtr>& state,
            VersionCounter stateVersion,
            const BasicHandle<T_Parent>& parent);
};

template<class T_Entity, class T_Parent>
inline Sco<T_Entity, T_Parent>::Sco(const BasicHandle<T_Entity>& handle,
                                    const DFL::NotNull<ScoDescriptorSharedPtr>& descriptor,
                                    VersionCounter descriptorVersion,
                                    const DFL::NotNull<ScoStateSharedPtr>& state,
                                    VersionCounter stateVersion,
                                    const BasicHandle<T_Parent>& parent) :
        Impl::MdibEntity<T_Entity, ScoDescriptorBuilder, ScoStateBuilder, T_Parent>(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

/**
 * @brief Definition of an SCO that has an MDS as parent.
 */
class MdsSco: public Sco<MdsSco, Mds>
{
    DFL_MDIB_IMMUTABLE(MdsSco)

    public:
        /// @brief Child types of an SCO match any operation.
        using ChildType = std::variant<DFL_MDIB_ENTITIES_AS_SHARED_PTRS(DFL_MDIB_ENTITY_MDS_OPERATIONS)>;
        /// @brief Container for visitor pattern.
        using ChildEntities = Entities<DFL_MDIB_ENTITY_MDS_OPERATIONS>;

        /**
         * @brief Constructor.
         */
        MdsSco(const MdsScoHandle& handle,
               const DFL::NotNull<ScoDescriptorSharedPtr>& descriptor,
               VersionCounter descriptorVersion,
               const DFL::NotNull<ScoStateSharedPtr>& state,
               VersionCounter stateVersion,
               const BasicHandle<Mds>& parent);
};

/**
 * @brief Definition of an SCO that has a VMD as parent.
 */
class VmdSco: public Sco<VmdSco, Vmd>
{
    DFL_MDIB_IMMUTABLE(VmdSco)

    public:
        /// @brief Child types of an SCO match any operation.
        using ChildType = std::variant<DFL_MDIB_ENTITIES_AS_SHARED_PTRS(DFL_MDIB_ENTITY_VMD_OPERATIONS)>;
        /// @brief Container for visitor pattern.
        using ChildEntities = Entities<DFL_MDIB_ENTITY_VMD_OPERATIONS>;

        /**
         * @brief Constructor.
         */
        VmdSco(const VmdScoHandle& handle,
               const DFL::NotNull<ScoDescriptorSharedPtr>& descriptor,
               VersionCounter descriptorVersion,
               const DFL::NotNull<ScoStateSharedPtr>& state,
               VersionCounter stateVersion,
               const BasicHandle<Vmd>& parent);
};

/**
 * @brief Type information of \ref Sco
 */
DFL_MDIB_MDSVMD_TYPES(Sco)

inline MdsSco::MdsSco(const MdsScoHandle& handle,
                      const DFL::NotNull<ScoDescriptorSharedPtr>& descriptor,
                      VersionCounter descriptorVersion,
                      const DFL::NotNull<ScoStateSharedPtr>& state,
                      VersionCounter stateVersion,
                      const BasicHandle<Mds>& parent):
        Sco(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

inline VmdSco::VmdSco(const VmdScoHandle& handle,
                      const DFL::NotNull<ScoDescriptorSharedPtr>& descriptor,
                      VersionCounter descriptorVersion,
                      const DFL::NotNull<ScoStateSharedPtr>& state,
                      VersionCounter stateVersion,
                      const BasicHandle<Vmd>& parent):
        Sco(handle, descriptor, descriptorVersion, state, stateVersion, parent)
{
}

/**
 * @brief Definition of shared pointer type \ref MdsScoSharedPtr for entity \ref MdsSco.
 */
using MdsScoSharedPtr = SharedPtr<MdsSco>;

/**
 * @brief Definition of shared pointer type \ref VmdScoSharedPtr for entity \ref VmdSco.
 */
using VmdScoSharedPtr = SharedPtr<VmdSco>;

}
