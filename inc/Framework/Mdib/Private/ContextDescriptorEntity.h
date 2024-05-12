#pragma once

#include <Framework/Mdib/Private/MdibEntityDescriptor.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/**
 * @brief Context descriptor MDIB entity.
 * @details A context descriptor MDIB entity is different to an \ref MdibEntity in the way that it possesses no state.
 * States of the context descriptor entity are stored in special containers (see \ref ContextStateEntity) and possess their own handle.
 *
 * @tparam T_Entity Own entity type.
 * @tparam T_DescrBuilder Descriptor builder type that describes the payload data of the \ref ContextDescriptorEntity.
 * @tparam T_StateBuilder State builder type that belongs to the corresponding \ref ContextStateEntity.
 * @tparam T_Parent Parent type.
 *
 * @ingroup Mdib
 */
template<class T_Entity, class T_DescrBuilder, class T_StateBuilder, class T_Parent>
class ContextDescriptorEntity: public MdibEntityDescriptor<T_Entity, T_DescrBuilder, T_Parent>
{
    public:
        using StateBuilderType = T_StateBuilder;
        using StateType = typename T_StateBuilder::BuiltType;

    protected:
        /**
         * Constructor to populate all fields.
         */
        ContextDescriptorEntity(const BasicHandle<T_Entity>& handle,
                                const DFL::NotNull<SharedPtr<typename T_DescrBuilder::BuiltType>>& descriptor,
                                VersionCounter descriptorVersion,
                                const BasicHandle<T_Parent>& parent);
};

template<class T_Entity, class T_DescrBuilder, class T_StateBuilder, class T_Parent>
ContextDescriptorEntity<T_Entity, T_DescrBuilder, T_StateBuilder, T_Parent>::ContextDescriptorEntity(const BasicHandle<T_Entity>& handle,
                                                                                                     const DFL::NotNull<SharedPtr<typename T_DescrBuilder::BuiltType>>& descriptor,
                                                                                                     VersionCounter descriptorVersion,
                                                                                                     const BasicHandle<T_Parent>& parent) :
        MdibEntityDescriptor<T_Entity, T_DescrBuilder, T_Parent>(handle, descriptor, descriptorVersion, parent)
{
}

}
}
}
