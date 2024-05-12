#pragma once

#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignalVariant.h>
#include <Framework/Mdib/Public/Model/Component/Mds.h>
#include <Framework/Mdib/Public/Model/Context/EnsembleContext.h>
#include <Framework/Mdib/Public/Model/Context/EnsembleContextIndicator.h>
#include <Framework/Mdib/Public/Model/Context/LocationContext.h>
#include <Framework/Mdib/Public/Model/Context/LocationContextIndicator.h>
#include <Framework/Mdib/Public/Model/Context/PatientContext.h>
#include <Framework/Mdib/Public/Model/Context/PatientContextIndicator.h>
#include <Framework/Utils/Public/NotNull.h>

namespace DFL::Mdib
{

/**
 * @brief Factory template class to create any MDIB entities.
 * @ingroup Mdib
 */
class EntityFactory
{
    public:
        /**
         * @brief Creates any entity from the MDIB with empty descriptor and/or state.
         */
        template<class T_Entity>
        static NotNull<DFL_MDIB_SHARED_PTR<T_Entity>> create(const BasicHandle<T_Entity>& handle,
                                                             const BasicHandle<typename T_Entity::ParentType>& parent);

        /**
         * @brief Creates any entity from the MDIB.
         * @details In case of context indicator or context entities, either the state or the descriptor is ignored on construction.
         */
        template<class T_Entity>
        static NotNull<DFL_MDIB_SHARED_PTR<T_Entity>> create(const BasicHandle<T_Entity>& handle,
                                                             const NotNull<DFL_MDIB_SHARED_PTR<typename T_Entity::DescriptorType>>& descriptor,
                                                             const NotNull<DFL_MDIB_SHARED_PTR<typename T_Entity::StateType>>& state,
                                                             const BasicHandle<typename T_Entity::ParentType>& parent);

        /**
         * @brief Creates any entity from the MDIB.
         * @details In case of context indicator or context entities, either the state or the descriptor is ignored on construction.
         */
        template<class T_Entity>
        static NotNull<DFL_MDIB_SHARED_PTR<T_Entity>> create(const BasicHandle<T_Entity>& handle,
                                                             const typename T_Entity::DescriptorBuilderType& descriptor,
                                                             const typename T_Entity::StateBuilderType& state,
                                                             const BasicHandle<typename T_Entity::ParentType>& parent);

        /**
         * @brief Creates any entity from the MDIB.
         * @details If a state is required from the entity to create, then a default state is inserted.
         */
        template<class T_Entity>
        static NotNull<DFL_MDIB_SHARED_PTR<T_Entity>> create(const BasicHandle<T_Entity>& handle,
                                                             const NotNull<DFL_MDIB_SHARED_PTR<typename T_Entity::DescriptorType>>& descriptor,
                                                             const BasicHandle<typename T_Entity::ParentType>& parent);

        /**
         * @brief Creates any entity from the MDIB.
         * @details If a state is required from the entity to create, then a default state is inserted.
         */
        template<class T_Entity>
        static NotNull<DFL_MDIB_SHARED_PTR<T_Entity>> create(const BasicHandle<T_Entity>& handle,
                                                             const typename T_Entity::DescriptorBuilderType& descriptor,
                                                             const BasicHandle<typename T_Entity::ParentType>& parent);

        /**
         * @brief Creates any entity from the MDIB.
         * @details If a descriptor is required from the entity to create, then a default descriptor is inserted.
         */
        template<class T_Entity>
        static NotNull<DFL_MDIB_SHARED_PTR<T_Entity>> create(const BasicHandle<T_Entity>& handle,
                                                             const NotNull<DFL_MDIB_SHARED_PTR<typename T_Entity::StateType>>& state,
                                                             const BasicHandle<typename T_Entity::ParentType>& parent);

        /**
         * @brief Creates any entity from the MDIB.
         * @details If a descriptor is required from the entity to create, then a default descriptor is inserted.
         */
        template<class T_Entity>
        static NotNull<DFL_MDIB_SHARED_PTR<T_Entity>> create(const BasicHandle<T_Entity>& handle,
                                                             const typename T_Entity::StateBuilderType& state,
                                                             const BasicHandle<typename T_Entity::ParentType>& parent);

        /**
         * @brief Creates an \ref Mds with default descriptor and state.
         */
        static NotNull<MdsSharedPtr> create(const MdsHandle& handle);

        /**
         * @brief Creates an \ref Mds.
         */
        static NotNull<MdsSharedPtr> create(const MdsHandle& handle,
                                            const NotNull<MdsDescriptorSharedPtr>& descr,
                                            const NotNull<MdsStateSharedPtr>& state);

        /**
         * @brief Creates an \ref Mds.
         */
        static NotNull<MdsSharedPtr> create(const MdsHandle& handle,
                                            const MdsDescriptorBuilder& descr,
                                            const MdsStateBuilder& state);

        /**
         * @brief Creates an \ref Mds with a default state.
         */
        static NotNull<MdsSharedPtr> create(const MdsHandle& handle,
                                            const NotNull<MdsDescriptorSharedPtr>& descr);

        /**
         * @brief Creates an \ref Mds with a default state.
         */
        static NotNull<MdsSharedPtr> create(const MdsHandle& handle,
                                            const MdsDescriptorBuilder& descr);

        /**
         * @brief Creates an \ref Mds with a default descriptor.
         */
        static NotNull<MdsSharedPtr> create(const MdsHandle& handle,
                                            const NotNull<MdsStateSharedPtr>& state);

        /**
         * @brief Creates an \ref Mds with a default descriptor.
         */
        static NotNull<MdsSharedPtr> create(const MdsHandle& handle,
                                            const MdsStateBuilder& state);

        /**
         * @brief Updates descriptor and state of any entity from the MDIB.
         * @details In case of context indicator or context entities, either the state or the descriptor is ignored on update.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> create(const NotNull<SharedPtr<T_Entity>>& existingEntity,
                                                             const NotNull<SharedPtr<typename T_Entity::DescriptorType>>& descriptor,
                                                             const NotNull<SharedPtr<typename T_Entity::StateType>>& state);

        /**
         * @brief Updates descriptor and state of any entity from the MDIB.
         * @details In case of context indicator or context entities, either the state or the descriptor is ignored on update.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> create(const T_Entity& existingEntity,
                                                             const NotNull<SharedPtr<typename T_Entity::DescriptorType>>& descriptor,
                                                             const NotNull<SharedPtr<typename T_Entity::StateType>>& state);

        /**
         * @brief Updates descriptor and state of any entity from the MDIB.
         * @details In case of context indicator or context entities, either the state or the descriptor is ignored on update.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> create(const NotNull<SharedPtr<T_Entity>>& existingEntity,
                                                             const typename T_Entity::DescriptorBuilderType& descriptor,
                                                             const typename T_Entity::StateBuilderType& state);

        /**
         * @brief Updates descriptor of any entity from the MDIB.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> create(const NotNull<SharedPtr<T_Entity>>& existingEntity,
                                                             const NotNull<SharedPtr<typename T_Entity::DescriptorType>>& descriptor);

        /**
         * @brief Updates descriptor of any entity from the MDIB.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> create(const NotNull<SharedPtr<T_Entity>>& existingEntity,
                                                             const typename T_Entity::DescriptorBuilderType& descriptor);

        /**
         * @brief Updates state of any entity from the MDIB.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> create(const NotNull<SharedPtr<T_Entity>>& existingEntity,
                                                             const NotNull<SharedPtr<typename T_Entity::StateType>>& state);

        /**
         * @brief Updates state of any entity from the MDIB.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> create(const T_Entity& existingEntity,
                                                             const NotNull<SharedPtr<typename T_Entity::StateType>>& state);

        /**
         * @brief Updates state of any entity from the MDIB.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> create(const NotNull<SharedPtr<T_Entity>>& existingEntity,
                                                             const typename T_Entity::StateBuilderType& state);

        /**
         * @brief Updates state of any entity from the MDIB.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> create(const T_Entity& existingEntity,
                                                             const typename T_Entity::StateBuilderType& state);

        /**
         * @brief Specialization for LocationContextIndicator.
         */
        static NotNull<LocationContextIndicatorSharedPtr> create(const NotNull<LocationContextIndicatorSharedPtr>& existingEntity,
                                                                 const NotNull<LocationContextDescriptorSharedPtr>& descriptor);

        /**
         * @brief Specialization for LocationContext.
         */
        static NotNull<LocationContextSharedPtr> create(const NotNull<LocationContextSharedPtr>& existingEntity,
                                                        const NotNull<LocationContextStateSharedPtr>& state);

        /**
         * @brief Specialization for PatientContextIndicator.
         */
        static NotNull<PatientContextIndicatorSharedPtr> create(const NotNull<PatientContextIndicatorSharedPtr>& existingEntity,
                                                                const NotNull<PatientContextDescriptorSharedPtr>& descriptor);

        /**
         * @brief Specialization for PatientContext.
         */
        static NotNull<PatientContextSharedPtr> create(const NotNull<PatientContextSharedPtr>& existingEntity,
                                                       const NotNull<PatientContextStateSharedPtr>& state);

        /**
         * @brief Specialization for EnsembleContextIndicator.
         */
        static NotNull<EnsembleContextIndicatorSharedPtr> create(const NotNull<EnsembleContextIndicatorSharedPtr>& existingEntity,
                                                                 const NotNull<EnsembleContextDescriptorSharedPtr>& descriptor);

        /**
         * @brief Specialization for EnsembleContext.
         */
        static NotNull<EnsembleContextSharedPtr> create(const NotNull<EnsembleContextSharedPtr>& existingEntity,
                                                        const NotNull<EnsembleContextStateSharedPtr>& state);

        /**
         * @brief Specialization for LocationContextIndicator.
         */
        static NotNull<LocationContextIndicatorSharedPtr> create(const NotNull<LocationContextIndicatorSharedPtr>& existingEntity,
                                                                 const LocationContextDescriptorBuilder& descriptor);

        /**
         * @brief Specialization for LocationContext.
         */
        static NotNull<LocationContextSharedPtr> create(const LocationContextHandle& handle,
                                                                       const LocationContextStateBuilder& state,
                                                                       const LocationContextIndicatorHandle& parent);
        /**
         * @brief Specialization for LocationContext.
         */
        static NotNull<LocationContextSharedPtr> create(const NotNull<LocationContextSharedPtr>& existingEntity,
                                                        const LocationContextStateBuilder& state);

        /**
         * @brief Specialization for PatientContextIndicator.
         */
        static NotNull<PatientContextIndicatorSharedPtr> create(const NotNull<PatientContextIndicatorSharedPtr>& existingEntity,
                                                                const PatientContextDescriptorBuilder& descriptor);

        /**
         * @brief Specialization for PatientContext.
         */
        static NotNull<PatientContextSharedPtr> create(const NotNull<PatientContextSharedPtr>& existingEntity,
                                                       const PatientContextStateBuilder& state);

        /**
         * @brief Specialization for EnsembleContextIndicator.
         */
        static NotNull<EnsembleContextIndicatorSharedPtr> create(const NotNull<EnsembleContextIndicatorSharedPtr>& existingEntity,
                                                        const EnsembleContextDescriptorBuilder& descriptor);

        /**
         * @brief Specialization for EnsembleContext.
         */
        static NotNull<EnsembleContextSharedPtr> create(const NotNull<EnsembleContextSharedPtr>& existingEntity,
                                                        const EnsembleContextStateBuilder& state);

        /**
         * @brief Updates a \ref Mds.
         */
        static NotNull<MdsSharedPtr> create(const NotNull<MdsSharedPtr>& existingEntity,
                                            const NotNull<MdsDescriptorSharedPtr>& descr,
                                            const NotNull<MdsStateSharedPtr>& state);

        /**
         * @brief Updates a \ref Mds.
         */
        static NotNull<MdsSharedPtr> create(const NotNull<MdsSharedPtr>& existingEntity,
                                            const MdsDescriptorBuilder& descr,
                                            const MdsStateBuilder& state);

        /**
         * @brief Updates a \ref Mds "Mds'" descriptor.
         */
        static NotNull<MdsSharedPtr> create(const NotNull<MdsSharedPtr>& existingEntity,
                                            const NotNull<MdsDescriptorSharedPtr>& descr);

        /**
         * @brief Updates a \ref Mds "Mds'" descriptor.
         */
        static NotNull<MdsSharedPtr> create(const NotNull<MdsSharedPtr>& existingEntity,
                                            const MdsDescriptorBuilder& descr);

        /**
         * @brief Updates a \ref Mds "Mds'" state.
         */
        static NotNull<MdsSharedPtr> create(const NotNull<MdsSharedPtr>& existingEntity,
                                            const NotNull<MdsStateSharedPtr>& state);

        /**
         * @brief Updates a \ref Mds "Mds'" state.
         */
        static NotNull<MdsSharedPtr> create(const NotNull<MdsSharedPtr>& existingEntity,
                                            const MdsStateBuilder& state);
};

template<class T_Entity>
inline NotNull<DFL_MDIB_SHARED_PTR<T_Entity>> DFL::Mdib::EntityFactory::create(const BasicHandle<T_Entity>& handle,
                                                                               const BasicHandle<typename T_Entity::ParentType>& parent)
{
    return create(handle, asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::DescriptorType>()), asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::StateType>()), parent);
}

template<class T_Entity>
inline NotNull<DFL_MDIB_SHARED_PTR<T_Entity>> EntityFactory::create(const BasicHandle<T_Entity>& handle,
                                                                    const NotNull<DFL_MDIB_SHARED_PTR<typename T_Entity::DescriptorType>>& descriptor,
                                                                    const NotNull<DFL_MDIB_SHARED_PTR<typename T_Entity::StateType>>& state,
                                                                    const BasicHandle<typename T_Entity::ParentType>& parent)
{
    const auto versionNull(DFL::Mdib::VersionCounter(0));
    if constexpr(std::is_same_v<AlertSignalVariant, T_Entity>)
    {
        return asNotNull(DFL_MDIB_MAKE_SHARED<T_Entity>(handle, descriptor, versionNull, state, versionNull, Handle()));
    }
    else
    {
        return asNotNull(DFL_MDIB_MAKE_SHARED<T_Entity>(handle, descriptor, versionNull, state, versionNull, parent));
    }
}

template<class T_Entity>
inline NotNull<DFL_MDIB_SHARED_PTR<T_Entity>> EntityFactory::create(const BasicHandle<T_Entity>& handle,
                                                                    const NotNull<DFL_MDIB_SHARED_PTR<typename T_Entity::DescriptorType>>& descriptor,
                                                                    const BasicHandle<typename T_Entity::ParentType>& parent)
{
    return create(handle, descriptor, asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::StateType>()), parent);
}

template<class T_Entity>
inline NotNull<DFL_MDIB_SHARED_PTR<T_Entity>> EntityFactory::create(const BasicHandle<T_Entity>& handle,
                                                                    const NotNull<DFL_MDIB_SHARED_PTR<typename T_Entity::StateType>>& state,
                                                                    const BasicHandle<typename T_Entity::ParentType>& parent)
{
    return create(handle, asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::DescriptorType>()), state, parent);
}

inline NotNull<MdsSharedPtr> EntityFactory::create(const MdsHandle& handle)
{
    return create(handle, asNotNull(DFL_MDIB_MAKE_SHARED<MdsDescriptor>()), asNotNull(DFL_MDIB_MAKE_SHARED<MdsState>()));
}

inline NotNull<MdsSharedPtr> EntityFactory::create(const MdsHandle& handle, const NotNull<MdsDescriptorSharedPtr>& descr, const NotNull<MdsStateSharedPtr>& state)
{
    return create(handle, descr, state, BasicHandle<Impl::MdsParentPlaceholder>{});
}

inline NotNull<MdsSharedPtr> EntityFactory::create(const MdsHandle& handle, const NotNull<MdsDescriptorSharedPtr>& descr)
{
    return create(handle, descr, asNotNull(DFL_MDIB_MAKE_SHARED<MdsState>()));
}

inline NotNull<MdsSharedPtr> EntityFactory::create(const MdsHandle& handle, const NotNull<MdsStateSharedPtr>& state)
{
    return create(handle, asNotNull(DFL_MDIB_MAKE_SHARED<MdsDescriptor>()), state);
}

inline NotNull<MdsSharedPtr> EntityFactory::create(const NotNull<MdsSharedPtr>& existingEntity, const NotNull<MdsDescriptorSharedPtr>& descr, const NotNull<MdsStateSharedPtr>& state)
{
    return create(existingEntity->handle(), descr, state);
}

inline NotNull<MdsSharedPtr> EntityFactory::create(const NotNull<MdsSharedPtr>& existingEntity, const NotNull<MdsDescriptorSharedPtr>& descr)
{
    return create(existingEntity, descr, existingEntity->state());
}

inline NotNull<MdsSharedPtr> EntityFactory::create(const MdsHandle& handle, const MdsDescriptorBuilder& descr, const MdsStateBuilder& state)
{
    return create(handle, asNotNull(DFL_MDIB_MAKE_SHARED<MdsDescriptor>(descr.build())), asNotNull(DFL_MDIB_MAKE_SHARED<MdsState>(state.build())));
}

inline NotNull<MdsSharedPtr> EntityFactory::create(const MdsHandle& handle, const MdsDescriptorBuilder& descr)
{
    return create(handle, asNotNull(DFL_MDIB_MAKE_SHARED<MdsDescriptor>(descr.build())));
}

inline NotNull<MdsSharedPtr> EntityFactory::create(const MdsHandle& handle, const MdsStateBuilder& state)
{
    return create(handle, asNotNull(DFL_MDIB_MAKE_SHARED<MdsState>(state.build())));
}

inline NotNull<MdsSharedPtr> EntityFactory::create(const NotNull<MdsSharedPtr>& existingEntity, const MdsDescriptorBuilder& descr, const MdsStateBuilder& state)
{
    return create(existingEntity, asNotNull(DFL_MDIB_MAKE_SHARED<MdsDescriptor>(descr.build())), asNotNull(DFL_MDIB_MAKE_SHARED<MdsState>(state.build())));
}

inline NotNull<MdsSharedPtr> EntityFactory::create(const NotNull<MdsSharedPtr>& existingEntity, const MdsDescriptorBuilder& descr)
{
    return create(existingEntity, asNotNull(DFL_MDIB_MAKE_SHARED<MdsDescriptor>(descr.build())));
}

inline NotNull<MdsSharedPtr> EntityFactory::create(const NotNull<MdsSharedPtr>& existingEntity, const NotNull<MdsStateSharedPtr>& state)
{
    return create(existingEntity, existingEntity->descriptor(), state);
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> EntityFactory::create(const NotNull<SharedPtr<T_Entity>>& existingEntity,
                                                                    const NotNull<SharedPtr<typename T_Entity::DescriptorType>>& descriptor,
                                                                    const NotNull<SharedPtr<typename T_Entity::StateType>>& state)
{
    return create(*existingEntity, descriptor, state);
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> EntityFactory::create(const T_Entity& existingEntity,
                                                                    const NotNull<SharedPtr<typename T_Entity::DescriptorType>>& descriptor,
                                                                    const NotNull<SharedPtr<typename T_Entity::StateType>>& state)
{
    if constexpr (std::is_same_v<T_Entity, AlertSignalVariant>)
    {
        // This overload is required to get extra information (MDS vs. VMD) type
        // info from existing entity to create the new entity. Otherwise, the
        // type information is lost, and it cannot be inserted in the changeset
        // afterwards correctly.
        const auto versionNull(DFL::Mdib::VersionCounter(0));
        return asNotNull(
            DFL_MDIB_MAKE_SHARED<AlertSignalVariant>(existingEntity.handle(),
                                                     descriptor,
                                                     versionNull,
                                                     state,
                                                     versionNull,
                                                     toHandle(existingEntity.parent()),
                                                     existingEntity.type()));
    }
    else
    {
        return create(existingEntity.handle(),
                      descriptor,
                      state,
                      existingEntity.parent());
    }
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> EntityFactory::create(const NotNull<SharedPtr<T_Entity>>& existingEntity,
                                                                    const NotNull<SharedPtr<typename T_Entity::DescriptorType>>& descriptor)
{
    return create(existingEntity, descriptor, existingEntity->state());
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> EntityFactory::create(const NotNull<SharedPtr<T_Entity>>& existingEntity,
                                                                    const NotNull<SharedPtr<typename T_Entity::StateType>>& state)
{
    return create(existingEntity, existingEntity->descriptor(), state);
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> EntityFactory::create(const T_Entity& existingEntity,
                                                                    const NotNull<SharedPtr<typename T_Entity::StateType>>& state)
{
    return create(existingEntity, existingEntity.descriptor(), state);
}

inline NotNull<LocationContextIndicatorSharedPtr> EntityFactory::create(const NotNull<LocationContextIndicatorSharedPtr>& existingEntity,
                                                                        const NotNull<LocationContextDescriptorSharedPtr>& descriptor)
{
    const auto versionNull(DFL::Mdib::VersionCounter(0));
    return asNotNull(DFL_MDIB_MAKE_SHARED<LocationContextIndicator>(existingEntity->handle(), descriptor, versionNull, existingEntity->parent()));
}

inline NotNull<LocationContextSharedPtr> EntityFactory::create(const LocationContextHandle& handle,
                                                               const LocationContextStateBuilder& stateBuilder,
                                                               const LocationContextIndicatorHandle& parent)
{
    const auto versionNull(DFL::Mdib::VersionCounter(0));
    return asNotNull(DFL_MDIB_MAKE_SHARED<LocationContext>(handle, asNotNull(DFL_MDIB_MAKE_SHARED<LocationContextState>(stateBuilder.build())), versionNull, parent));
}

inline NotNull<LocationContextSharedPtr> EntityFactory::create(const NotNull<LocationContextSharedPtr>& existingEntity,
                                                               const NotNull<LocationContextStateSharedPtr>& state)
{
    const auto versionNull(DFL::Mdib::VersionCounter(0));
    return asNotNull(DFL_MDIB_MAKE_SHARED<LocationContext>(existingEntity->handle(), state, versionNull, existingEntity->parent()));
}

inline NotNull<PatientContextIndicatorSharedPtr> EntityFactory::create(const NotNull<PatientContextIndicatorSharedPtr>& existingEntity,
                                                                       const NotNull<PatientContextDescriptorSharedPtr>& descriptor)
{
    const auto versionNull(DFL::Mdib::VersionCounter(0));
    return asNotNull(DFL_MDIB_MAKE_SHARED<PatientContextIndicator>(existingEntity->handle(), descriptor, versionNull, existingEntity->parent()));
}

inline NotNull<PatientContextSharedPtr> EntityFactory::create(const NotNull<PatientContextSharedPtr>& existingEntity,
                                                              const NotNull<PatientContextStateSharedPtr>& state)
{
    const auto versionNull(DFL::Mdib::VersionCounter(0));
    return asNotNull(DFL_MDIB_MAKE_SHARED<PatientContext>(existingEntity->handle(), state, versionNull, existingEntity->parent()));
}

inline NotNull<EnsembleContextIndicatorSharedPtr> EntityFactory::create(const NotNull<EnsembleContextIndicatorSharedPtr>& existingEntity,
                                                                        const NotNull<EnsembleContextDescriptorSharedPtr>& descriptor)
{
    const auto versionNull(DFL::Mdib::VersionCounter(0));
    return asNotNull(DFL_MDIB_MAKE_SHARED<EnsembleContextIndicator>(existingEntity->handle(), descriptor, versionNull, existingEntity->parent()));
}

inline NotNull<EnsembleContextSharedPtr> EntityFactory::create(const NotNull<EnsembleContextSharedPtr>& existingEntity,
                                                               const NotNull<EnsembleContextStateSharedPtr>& state)
{
    const auto versionNull(DFL::Mdib::VersionCounter(0));
    return asNotNull(DFL_MDIB_MAKE_SHARED<EnsembleContext>(existingEntity->handle(), state, versionNull, existingEntity->parent()));
}

template<class T_Entity>
inline NotNull<DFL_MDIB_SHARED_PTR<T_Entity>> EntityFactory::create(const BasicHandle<T_Entity>& handle,
                                                                    const typename T_Entity::DescriptorBuilderType& descriptor,
                                                                    const typename T_Entity::StateBuilderType& state,
                                                                    const BasicHandle<typename T_Entity::ParentType>& parent)
{
    return create(handle, asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::DescriptorType>(descriptor.build())), asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::StateType>(state.build())), parent);
}

template<class T_Entity>
inline NotNull<DFL_MDIB_SHARED_PTR<T_Entity>> EntityFactory::create(const BasicHandle<T_Entity>& handle,
                                                                    const typename T_Entity::DescriptorBuilderType& descriptor,
                                                                    const BasicHandle<typename T_Entity::ParentType>& parent)
{
    return create(handle, asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::DescriptorType>(descriptor.build())), parent);
}

template<class T_Entity>
inline NotNull<DFL_MDIB_SHARED_PTR<T_Entity>> EntityFactory::create(const BasicHandle<T_Entity>& handle,
                                                                    const typename T_Entity::StateBuilderType& state,
                                                                    const BasicHandle<typename T_Entity::ParentType>& parent)
{
    return create(handle, asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::StateType>(state.build())), parent);
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> EntityFactory::create(const NotNull<SharedPtr<T_Entity>>& existingEntity,
                                                                    const typename T_Entity::DescriptorBuilderType& descriptor,
                                                                    const typename T_Entity::StateBuilderType& state)
{
    return create(existingEntity, asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::DescriptorType>(descriptor.build())), asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::StateType>(state.build())));
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> EntityFactory::create(const NotNull<SharedPtr<T_Entity>>& existingEntity,
                                                                    const typename T_Entity::DescriptorBuilderType& descriptor)
{
    return create(existingEntity, asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::DescriptorType>(descriptor.build())));
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> EntityFactory::create(const NotNull<SharedPtr<T_Entity>>& existingEntity,
                                                                    const typename T_Entity::StateBuilderType& state)
{
    return create(existingEntity, asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::StateType>(state.build())));
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> EntityFactory::create(const T_Entity& existingEntity,
                                                                    const typename T_Entity::StateBuilderType& state)
{
    return create(existingEntity, asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::StateType>(state.build())));
}

inline NotNull<LocationContextIndicatorSharedPtr> EntityFactory::create(const NotNull<LocationContextIndicatorSharedPtr>& existingEntity,
                                                                        const LocationContextDescriptorBuilder& descriptor)
{
    return create(existingEntity->handle(), asNotNull(DFL_MDIB_MAKE_SHARED<LocationContextDescriptor>(descriptor.build())), existingEntity->parent());
}

inline NotNull<LocationContextSharedPtr> EntityFactory::create(const NotNull<LocationContextSharedPtr>& existingEntity,
                                                               const LocationContextStateBuilder& state)
{
    return create(existingEntity->handle(), asNotNull(DFL_MDIB_MAKE_SHARED<LocationContextState>(state.build())), existingEntity->parent());
}

inline NotNull<PatientContextIndicatorSharedPtr> EntityFactory::create(const NotNull<PatientContextIndicatorSharedPtr>& existingEntity,
                                                                       const PatientContextDescriptorBuilder& descriptor)
{
    return create(existingEntity->handle(), asNotNull(DFL_MDIB_MAKE_SHARED<PatientContextDescriptor>(descriptor.build())), existingEntity->parent());
}

inline NotNull<PatientContextSharedPtr> EntityFactory::create(const NotNull<PatientContextSharedPtr>& existingEntity,
                                                              const PatientContextStateBuilder& state)
{
    return create(existingEntity->handle(), asNotNull(DFL_MDIB_MAKE_SHARED<PatientContextState>(state.build())), existingEntity->parent());
}

inline NotNull<EnsembleContextIndicatorSharedPtr> EntityFactory::create(const NotNull<EnsembleContextIndicatorSharedPtr>& existingEntity,
                                                                        const EnsembleContextDescriptorBuilder& descriptor)
{
    return create(existingEntity->handle(), asNotNull(DFL_MDIB_MAKE_SHARED<EnsembleContextDescriptor>(descriptor.build())), existingEntity->parent());
}

inline NotNull<EnsembleContextSharedPtr> EntityFactory::create(const NotNull<EnsembleContextSharedPtr>& existingEntity,
                                                               const EnsembleContextStateBuilder& state)
{
    return create(existingEntity->handle(), asNotNull(DFL_MDIB_MAKE_SHARED<EnsembleContextState>(state.build())), existingEntity->parent());
}

inline NotNull<MdsSharedPtr> EntityFactory::create(const NotNull<MdsSharedPtr>& existingEntity, const MdsStateBuilder& state)
{
    return create(existingEntity, asNotNull(DFL_MDIB_MAKE_SHARED<MdsState>(state.build())));
}

}
