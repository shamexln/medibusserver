#pragma once

#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/VersionCounter.h>

#include <Framework/Utils/Public/NotNull.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/**
 * @brief Container for one context state.
 * @details The container has a
 *
 * - handle for unique identification
 * - state version that identifies the enclosed states's version
 * - pointer to a state data container
 *
 * @tparam T_Entity Own entity type.
 * @tparam T_DescrBuilder Descriptor builder that belongs to the corresponding \ref ContextDescriptorEntity.
 * @tparam T_StateBuilder State builder type type that describes the payload data of the \ref ContextStateEntity.
 * @tparam T_Parent Parent type, which is the corresponding \ref ContextDescriptorEntity.
 *
 * @ingroup Mdib
 */
template<class T_Entity, class T_DescrBuilder, class T_StateBuilder, class T_Parent>
class ContextStateEntity
{
    public:
        using EntityType = T_Entity;
        using DescriptorBuilderType = T_DescrBuilder;
        using DescriptorType = typename T_DescrBuilder::BuiltType;
        using StateBuilderType = T_StateBuilder;
        using StateType = typename T_StateBuilder::BuiltType;
        using ParentType = T_Parent;

        /**
         * @brief Unique identification of the multi state.
         */
        const BasicHandle<T_Entity>& handle() const;

        /**
         * @brief Version of the encapsulated state.
         */
        VersionCounter stateVersion() const;

        /**
         * @brief Encapsulated state.
         */
        DFL::NotNull<SharedPtr<StateType>> state() const;

        /**
         * @brief Parent entity.
         * @details Parent entities are context entities only.
         */
        const BasicHandle<T_Parent>& parent() const;

    protected:
        /**
         * Constructor to populate all fields.
         */
        ContextStateEntity(const BasicHandle<T_Entity>& handle,
                           DFL::NotNull<SharedPtr<StateType>> state,
                           VersionCounter stateVersion,
                           const BasicHandle<T_Parent>& parent);

    private:
        BasicHandle<T_Entity> m_handle;
        VersionCounter m_stateVersion;
        DFL::NotNull<SharedPtr<StateType>> m_state;
        BasicHandle<T_Parent> m_parent;
};

template<class T_Entity, class T_DescrBuilder, class T_StateBuilder, class T_Parent>
ContextStateEntity<T_Entity, T_DescrBuilder, T_StateBuilder, T_Parent>::ContextStateEntity(const BasicHandle <T_Entity>& handle,
                                                                                           DFL::NotNull<SharedPtr<StateType>> state,
                                                                                           VersionCounter stateVersion,
                                                                                           const BasicHandle <T_Parent>& parent) :
        m_handle(BasicHandle<T_Entity>(handle.string())),
        m_stateVersion(stateVersion),
        m_state(std::move(state)),
        m_parent(BasicHandle<T_Parent>(parent.string()))
{
}

template<class T_Entity, class T_DescrBuilder, class T_StateBuilder, class T_Parent>
const BasicHandle<T_Entity>& ContextStateEntity<T_Entity, T_DescrBuilder, T_StateBuilder, T_Parent>::handle() const
{
    return m_handle;
}

template<class T_Entity, class T_DescrBuilder, class T_StateBuilder, class T_Parent>
VersionCounter ContextStateEntity<T_Entity, T_DescrBuilder, T_StateBuilder, T_Parent>::stateVersion() const
{
    return m_stateVersion;
}

template<class T_Entity, class T_DescrBuilder, class T_StateBuilder, class T_Parent>
DFL::NotNull<SharedPtr<typename T_StateBuilder::BuiltType>> ContextStateEntity<T_Entity, T_DescrBuilder, T_StateBuilder, T_Parent>::state() const
{
    return m_state;
}

template<class T_Entity, class T_DescrBuilder, class T_StateBuilder, class T_Parent>
const BasicHandle<T_Parent>& ContextStateEntity<T_Entity, T_DescrBuilder, T_StateBuilder, T_Parent>::parent() const
{
    return m_parent;
}

}
}
}
