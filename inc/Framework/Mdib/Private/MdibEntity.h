#pragma once

#include <Framework/Mdib/Private/MdibEntityDescriptor.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>

#include <Framework/Utils/Public/NotNull.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/**
 * @brief General single state MDIB entity.
 * @details A single state MDIB entity has a
 *
 * - handle for unique identification
 * - pointer to a descriptor data container that changes in a low frequency (mostly static)
 * - descriptor version that identifies the enclosed descriptor's version
 * - pointer to a state data container that changes in a high frequency (highly volatile)
 * - state version that identifies the enclosed state's version
 *
 * @tparam T_Entity Own entity type.
 * @tparam T_DescrBuilder Descriptor builder type that holds the descriptor payload data of the entity.
 * @tparam T_StateBuilder State builder type that holds the state payload data of the entity.
 * @tparam T_Parent Parent type.
 *
 * @ingroup Mdib
 */
template<class T_Entity, class T_DescrBuilder, class T_StateBuilder, class T_Parent>
class MdibEntity: public MdibEntityDescriptor<T_Entity, T_DescrBuilder, T_Parent>
{
    public:
        using StateBuilderType = T_StateBuilder;
        using StateType = typename T_StateBuilder::BuiltType;
        using ParentType = T_Parent;

        /**
         * @brief Version of the encapsulated state.
         */
        VersionCounter stateVersion() const;

        /**
         * @brief Encapsulated state.
         */
        DFL::NotNull<SharedPtr<StateType>> state() const;

    protected:
        /**
         * Constructor to populate all fields.
         */
        MdibEntity(const BasicHandle<T_Entity>& handle,
                   const DFL::NotNull<SharedPtr<typename T_DescrBuilder::BuiltType>>& descriptor,
                   VersionCounter descriptorVersion,
                   DFL::NotNull<SharedPtr<StateType>> state,
                   VersionCounter stateVersion,
                   const BasicHandle<T_Parent>& parent);

    private:
        VersionCounter m_stateVersion;
        DFL::NotNull<SharedPtr<StateType>> m_state;
};

template<class T_Entity, class T_DescrBuilder, class T_StateBuilder, class T_Parent>
MdibEntity<T_Entity, T_DescrBuilder, T_StateBuilder, T_Parent>::MdibEntity(const BasicHandle<T_Entity>& handle,
                                                                           const DFL::NotNull<SharedPtr<typename T_DescrBuilder::BuiltType>>& descriptor,
                                                                           VersionCounter descriptorVersion,
                                                                           DFL::NotNull<SharedPtr<StateType>> state,
                                                                           VersionCounter stateVersion,
                                                                           const BasicHandle<T_Parent>& parent) :
        MdibEntityDescriptor<T_Entity, T_DescrBuilder, T_Parent>(handle, descriptor, descriptorVersion, parent),
        m_stateVersion(stateVersion),
        m_state(std::move(state))
{
}

template<class T_Entity, class T_DescrBuilder, class T_StateBuilder, class T_Parent>
VersionCounter MdibEntity<T_Entity, T_DescrBuilder, T_StateBuilder, T_Parent>::stateVersion() const
{
    return m_stateVersion;
}

template<class T_Entity, class T_DescrBuilder, class T_StateBuilder, class T_Parent>
DFL::NotNull<SharedPtr<typename T_StateBuilder::BuiltType>> MdibEntity<T_Entity, T_DescrBuilder, T_StateBuilder, T_Parent>::state() const
{
    return m_state;
}

}
}
}
