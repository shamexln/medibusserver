#pragma once

#include <S31/BicepsXml/S31Only/Report.h>
#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Private/Common/ErrorDefinitions.h>

#include <Framework/Mdib/Public/Model/HandleIo.h>
#include <Framework/Mdib/Public/Model/MdibVersionIo.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Utils/Public/Utf8Io.h>

#include <boost/mpl/transform.hpp>

namespace S31::Sdc::Impl::Report
{

namespace Types
{

/// Transformation types for use with boost::mpl
/// @{
template<class T>
struct MakeDescriptorType
{
    using type = DFL::NotNull<DFL::Mdib::SharedPtr<typename T::DescriptorType>>;
};

template<class T>
struct MakeStateType
{
    using type = DFL::NotNull<DFL::Mdib::SharedPtr<typename T::StateType>>;
};
/// @}

/// boost::mpl transformations to get the sets of state types and descriptor types
/// @{
using EntitiesOfStates      = boost::mpl::vector<DFL_MDIB_ENTITY_ALL_BASE_STATES>;
using EntitiesOfDescriptors = boost::mpl::vector<DFL_MDIB_ENTITY_ALL_BASE_DESCRIPTORS>;
using States                = boost::mpl::transform<EntitiesOfStates, MakeStateType<boost::mpl::_1>>::type;
using Descriptors           = boost::mpl::transform<EntitiesOfDescriptors, MakeDescriptorType<boost::mpl::_1>>::type;
/// @}

}  // namespace Types

/**
 * @brief Type trait: get T from T's state (T::StateType)
 * @ingroup S31CoreBicepsXml
 */
template<class State>
struct EntityTypeOfState
{
    using StatePtr = DFL::NotNull<DFL::Mdib::SharedPtr<State>>;
    using iter     = typename boost::mpl::find_if<Types::States, std::is_same<boost::mpl::_1, StatePtr>>::type;
    using type     = typename boost::mpl::at<Types::EntitiesOfStates, boost::mpl::int_<iter::pos::value>>::type;
};

/**
 * @brief Type trait: get T from T's descriptor (T::DescriptorType)
 * @ingroup S31CoreBicepsXml
 */
template<class Descriptor>
struct EntityTypeOfDescriptor
{
    using DescriptorPtr = DFL::NotNull<DFL::Mdib::SharedPtr<Descriptor>>;
    using iter = typename boost::mpl::find_if<Types::Descriptors, std::is_same<boost::mpl::_1, DescriptorPtr>>::type;
    using type = typename boost::mpl::at<Types::EntitiesOfDescriptors, boost::mpl::int_<iter::pos::value>>::type;
};

/// type trait to tell whether a state belongs to a Mds.../Vmd... type or not
/// @{
template<class State, class Enable = void>
struct isStateOfMdsVmdEntity : std::false_type
{
};

template<class State>
struct isStateOfMdsVmdEntity<
        State,
        typename std::enable_if<
                std::is_base_of<DFL::Mdib::Impl::MdsVmdTypesBase, typename EntityTypeOfState<State>::type>::value>::
                type> : std::true_type
{
};
/// @}

/// type trait to tell whether a descriptor belongs to a Mds.../Vmd... type or not
/// @{
template<class Descriptor, class Enable = void>
struct isDescriptorOfMdsVmdEntity : std::false_type
{
};

template<class Descriptor>
struct isDescriptorOfMdsVmdEntity<
        Descriptor,
        typename std::enable_if<std::is_base_of<
                DFL::Mdib::Impl::MdsVmdTypesBase,
                typename EntityTypeOfDescriptor<Descriptor>::type>::value>::type> : std::true_type
{
};
/// @}

/// type trait to tell whether a descriptor belongs to a Context Indicator type or not
/// @{
template<class Descriptor, class Enable = void>
struct isDescriptorOfContextIndicator : std::false_type
{
};

template<class Descriptor>
struct isDescriptorOfContextIndicator<
        Descriptor,
        typename std::enable_if<std::is_base_of<
                DFL::Mdib::AbstractContextState,
                typename EntityTypeOfDescriptor<Descriptor>::type::StateType>::value>::type> : std::true_type
{
};
/// @}

/**
 * @brief Get Context of a ContextIndicator.
 * @ingroup S31CoreBicepsXml
 */
template<class Indicator>
struct ContextOfContextIndicator
{
    static_assert(
            std::is_base_of<DFL::Mdib::AbstractContextState, typename Indicator::StateType>::value,
            "Not a context indicator.");
    using iter =
            typename boost::mpl::find_if<Types::EntitiesOfDescriptors, std::is_same<boost::mpl::_1, Indicator>>::type;
    using type = typename boost::mpl::at<Types::EntitiesOfStates, boost::mpl::int_<iter::pos::value>>::type;
};

/**
 * @brief Possible results of an add-to-changeset-operation
 * @details Needed for handling of Mds.../Vmd... entities
 * @ingroup S31SdcCommon
 */
enum class AddToChangeSetResult
{
    Handled, ///< either inserted or an error (commonly results in skipping this data)
    NotHandled ///< not added, but if this was e.g. an Mds entity the corresponding Vmd entity might be valid.
};

/**
 * @brief Visitor to handle entity states received from network.
 * @ingroup S31SdcCommon
 */
class ChangeSetInserterState
{
    public:
        ChangeSetInserterState(DFL::Mdib::MdibChangeSet& cs,
                               const DFL::Mdib::Mdib& mdib,
                               const ReportState& state,
                               const StateModifications& /*modifications*/):
            m_changeSet(cs),
            m_mdib(mdib),
            m_state(DFL::asNotNull(&state))
        {}

        void setCurrentReportPart(const ReportState& state)
        {
            m_state = DFL::asNotNull(&state);
        }

        template <typename State>
        void operator() (const DFL::NotNull<DFL::Mdib::SharedPtr<State>>& v,
            typename std::enable_if<!isStateOfMdsVmdEntity<State>::value>::type* = nullptr)
        {
            if (!m_state->descriptorHandle.isValid())
            {
                S31_THROW_EXCEPTION_WITH_ERROR(Errors::IncomingDataNotUnderstood{},
                    "Invalid descriptor handle " << m_state->descriptorHandle << " in state report");
            }

            using Entity = typename EntityTypeOfState<State>::type;
            const auto res = addToChangeSet<State, Entity>(v);

            if (res == AddToChangeSetResult::NotHandled)
            {
                S31_THROW_EXCEPTION_WITH_ERROR(Errors::IncomingDataNotUnderstood{},
                    "State '" << m_state->descriptorHandle << "' not updated. (No entity found for update)");
            }
        }

        template <typename State>
        void operator() (const DFL::NotNull<DFL::Mdib::SharedPtr<State>>& state,
                         typename std::enable_if<isStateOfMdsVmdEntity<State>::value>::type* = nullptr)
        {
            S31_STREAM_TRACE_LOGGER("Sdc", "ChangeSetInserterState:: operator(): handling mds/vmd states");

            if (!m_state->descriptorHandle.isValid())
            {
                S31_THROW_EXCEPTION_WITH_ERROR(Errors::IncomingDataNotUnderstood{},
                    "Invalid handle '" << m_state->descriptorHandle << "' in state report");
            }

            // find out whether this belongs to an MDS entity or an VMD entity
            using EntityTypes = typename EntityTypeOfState<State>::type;
            auto res = addToChangeSet<State, typename EntityTypes::MdsType>(state);

            if (res == AddToChangeSetResult::NotHandled)
            {
                res = addToChangeSet<State, typename EntityTypes::VmdType>(state);
            }

            if (res == AddToChangeSetResult::NotHandled)
            {
                S31_THROW_EXCEPTION_WITH_ERROR(Errors::IncomingDataNotUnderstood{},
                    "State '" << m_state->descriptorHandle << "' not updated. (No entity found for update)");
            }
        }

    private:
        template <class State, class Entity>
        AddToChangeSetResult addToChangeSet(const DFL::NotNull<DFL::Mdib::SharedPtr<State>>& state,
                            typename std::enable_if<std::is_base_of<DFL::Mdib::AbstractContextState, State>::value>::type* = nullptr)
        {
            const auto handle = DFL::Mdib::BasicHandle<Entity>(m_state->contextStateHandle);
            const auto descriptorHandle =  DFL::Mdib::BasicHandle<typename Entity::ParentType>(m_state->descriptorHandle);
            if (!handle.isValid())
            {
                S31_THROW_EXCEPTION_WITH_ERROR(Errors::IncomingDataNotUnderstood{}, "ContextState with invalid handle " << handle);
            }

            // update existing state?
            const auto previousState = m_mdib.entity(handle);
            if (previousState)
            {
                if (m_state->stateVersion <= previousState->stateVersion())
                {
                    // known state version
                    S31_STREAM_TRACE_LOGGER("Sdc", "ContextState ", handle,
                                           " in version already known. Received: ", m_state->stateVersion,
                                           ", already have: ", previousState->stateVersion());
                    return AddToChangeSetResult::Handled;
                }
            }

            const auto indicator = m_mdib.entity(descriptorHandle);
            if (!indicator)
            {
                S31_THROW_EXCEPTION_WITH_ERROR(Errors::IncomingDataNotUnderstood{}, "ContextState " << handle << " has no descriptor " << descriptorHandle);
            }
            if (m_state->descriptorVersion != indicator->descriptorVersion())
            {
                S31_THROW_EXCEPTION_WITH_ERROR(Errors::StateDescriptorVersionMismatch{},
                                      "Context state " << handle
                                      << " update/insertion received whose descriptor ("
                                      << indicator->handle() <<") version is invalid. "
                                      << "Received: " << m_state->descriptorVersion
                                      << ", expected: " << indicator->descriptorVersion() << ".");
            }

            auto newContextState = DFL::asNotNull(DFL_MDIB_MAKE_SHARED<Entity>(
                handle,
                state,
                m_state->stateVersion,
                descriptorHandle));

            if (newContextState->state()->contextAssociation() == DFL::Mdib::ContextAssociation::NotAssociated)
            {
                m_changeSet.addOneToRemove(newContextState);
                return AddToChangeSetResult::Handled;
            }

            if (previousState)
            {
                m_changeSet.addOneToUpdate(newContextState);
            }
            else
            {
                m_changeSet.addOneToInsert(newContextState);
            }

            return AddToChangeSetResult::Handled;
        }

        template <class State, class Entity>
        AddToChangeSetResult addToChangeSet(const DFL::NotNull<DFL::Mdib::SharedPtr<State>>& state,
                            typename std::enable_if<!std::is_base_of<DFL::Mdib::AbstractContextState, State>::value>::type* = nullptr)
        {
            auto oldEntity = m_mdib.entity(DFL::Mdib::BasicHandle<Entity>(m_state->descriptorHandle));
            if (!oldEntity)
            {
                return AddToChangeSetResult::NotHandled;
            }

            if (m_state->stateVersion <= oldEntity->stateVersion())
            {
                S31_STREAM_TRACE_LOGGER("Sdc", "Skip ", oldEntity->handle(), ". No newer version. Received: ", m_state->stateVersion, ", already have: ", oldEntity->stateVersion());
                return AddToChangeSetResult::Handled;
            }
            if (m_state->descriptorVersion != oldEntity->descriptorVersion())
            {
                S31_THROW_EXCEPTION_WITH_ERROR(Errors::StateDescriptorVersionMismatch{},
                      "State update received for " << oldEntity->handle()
                      << " with invalid descriptor version. "
                      << "Received: " << m_state->descriptorVersion
                      << ", expected: " << oldEntity->descriptorVersion() << ".");
            }

            auto newEntity = DFL_MDIB_MAKE_SHARED<Entity>(
                        oldEntity->handle(), oldEntity->descriptor(), oldEntity->descriptorVersion(),
                        state, m_state->stateVersion, oldEntity->parent());

            m_changeSet.addOneToUpdate(DFL::asNotNull(newEntity));
            S31_STREAM_TRACE_LOGGER("Sdc", "Update state ", oldEntity->handle());
            return AddToChangeSetResult::Handled;
        }

        DFL::Mdib::MdibChangeSet& m_changeSet;
        const DFL::Mdib::Mdib& m_mdib;
        DFL::NotNull<const ReportState*> m_state;
};

/**
 * @brief Visitor to handle entity descriptors received from network.
 * @ingroup S31SdcCommon
 */
class ChangeSetInserterDescriptor
{
    public:
        ChangeSetInserterDescriptor(
                               DFL::Mdib::MdibChangeSet& cs,
                               const DFL::Mdib::Mdib& mdib,
                               const ReportDescriptor& descriptor,
                               const DescriptorModifications& modifications):
            m_changeSet(cs),
            m_mdib(mdib),
            m_descriptor(DFL::asNotNull(&descriptor)),
            m_modifications(modifications)
        {}

        void setCurrentReportPart(const ReportDescriptor& descriptor)
        {
            m_descriptor = DFL::asNotNull(&descriptor);
        }

        template <typename Descriptor>
        void operator() (const DFL::NotNull<DFL::Mdib::SharedPtr<Descriptor>>& d,
                         typename std::enable_if<!isDescriptorOfMdsVmdEntity<Descriptor>::value
                            && isDescriptorOfContextIndicator<Descriptor>::value
                         >::type* = nullptr)
        {
            using Indicator = typename EntityTypeOfDescriptor<Descriptor>::type;
            if (auto entity = checkVersionAndMakeEntityWithDefaultState<Descriptor, Indicator>(d))
            {
                S31_STREAM_TRACE_LOGGER("Sdc",
                     m_descriptor->changeType, " context descriptor ", entity->handle());
                if (m_descriptor->changeType == DescriptionModificationType::Create)
                {
                    m_changeSet.addOneToInsert(DFL::asNotNull(entity));
                    handleContextStates(d);
                }

                if (m_descriptor->changeType == DescriptionModificationType::Update)
                {
                    m_changeSet.addOneToUpdate(DFL::asNotNull(entity));
                    handleContextStates(d);
                }

                if (m_descriptor->changeType == DescriptionModificationType::Delete)
                {
                    m_changeSet.addOneToRemove(DFL::asNotNull(entity));
                }
            }
        }

        template <typename Descriptor>
        void operator() (const DFL::NotNull<DFL::Mdib::SharedPtr<Descriptor>>& d,
                         typename std::enable_if<!isDescriptorOfMdsVmdEntity<Descriptor>::value
                            && !isDescriptorOfContextIndicator<Descriptor>::value
                         >::type* = nullptr)
        {
            using Entity = typename EntityTypeOfDescriptor<Descriptor>::type;

            if (m_descriptor->changeType == DescriptionModificationType::Create)
            {
                insertedEntity<Descriptor, Entity>(d);
            }

            if (m_descriptor->changeType == DescriptionModificationType::Update)
            {
                updatedEntity<Descriptor, Entity>(d);
            }

            if (m_descriptor->changeType == DescriptionModificationType::Delete)
            {
                removedEntity<Descriptor, Entity>(d);
            }
        }

        template <typename Descriptor>
        void operator() (const DFL::NotNull<DFL::Mdib::SharedPtr<Descriptor>>& d,
                         typename std::enable_if<isDescriptorOfMdsVmdEntity<Descriptor>::value>::type* = nullptr)
        {
            using Entity = typename EntityTypeOfDescriptor<Descriptor>::type;

            auto throwError = [&](){
                S31_THROW_EXCEPTION_WITH_ERROR(Errors::IncomingDataNotUnderstood{},
                    "Could not resolve parent type (Mds.../Vmd...) for descriptor report (" << m_descriptor->changeType << ") for "
                    << m_descriptor->handle  << " with parent " << m_descriptor->parentHandle);
            };

            if (m_descriptor->changeType == DescriptionModificationType::Create)
            {
                if (isMdsOrVmdType<typename Entity::MdsType>())
                {
                    insertedEntity<Descriptor, typename Entity::MdsType>(d);
                }
                else if (isMdsOrVmdType<typename Entity::VmdType>())
                {
                    insertedEntity<Descriptor, typename Entity::VmdType>(d);
                }
                else
                {
                    throwError();
                }
                return;
            }

            if (m_descriptor->changeType == DescriptionModificationType::Update)
            {
                if (isMdsOrVmdType<typename Entity::MdsType>())
                {
                    updatedEntity<Descriptor, typename Entity::MdsType>(d);
                }
                else if (isMdsOrVmdType<typename Entity::VmdType>())
                {
                    updatedEntity<Descriptor, typename Entity::VmdType>(d);
                }
                else
                {
                    throwError();
                }
                return;
            }

            if (m_descriptor->changeType == DescriptionModificationType::Delete)
            {
                if (isMdsOrVmdType<typename Entity::MdsType>())
                {
                    removedEntity<Descriptor, typename Entity::MdsType>(d);
                }
                else if (isMdsOrVmdType<typename Entity::VmdType>())
                {
                    removedEntity<Descriptor, typename Entity::VmdType>(d);
                }
                else
                {
                    throwError();
                }
                return;
            }
        }

    private:
        template <class Handle>
        bool versionIsNewer(const Handle& handle) const
        {
            // in case of 'delete' version can be the same, in the other cases it has to be a newer one.

            if (m_descriptor->changeType == DescriptionModificationType::Delete)
            {
                if (const auto oldEntity = m_mdib.entity(handle))
                {
                    if (oldEntity->descriptorVersion() > m_descriptor->version)
                    {
                        S31_THROW_EXCEPTION_WITH_ERROR(Errors::IncomingDataNotUnderstood{},
                            "Descriptor version " << m_descriptor->version << " of "
                            << handle << " already known, have version " <<  oldEntity->descriptorVersion()
                            << ", while " << m_descriptor->changeType);
                    }
                }
                return true;
            }

            if (const auto oldEntity = m_mdib.entity(handle))
            {
                if (oldEntity->descriptorVersion() >= m_descriptor->version)
                {
                    S31_THROW_EXCEPTION_WITH_ERROR(Errors::IncomingDataNotUnderstood{},
                        "Descriptor version " <<  m_descriptor->version << " of "
                        << handle << " already known, have version " <<  oldEntity->descriptorVersion()
                        << ", while " << m_descriptor->changeType);
                }
            }
            return true;
        }

        /// Creates the current entity (as Mdib entity) with default state (for removed entities and context indicators)
        template <class Descriptor, class Entity>
        DFL::Mdib::SharedPtr<Entity> checkVersionAndMakeEntityWithDefaultState(const DFL::NotNull<DFL::Mdib::SharedPtr<Descriptor>>& d)
        {
            using Parent = typename Entity::ParentType;

            const auto handle = DFL::Mdib::BasicHandle<Entity>(m_descriptor->handle);
            if (!handle.isValid())
            {
                S31_THROW_EXCEPTION_WITH_ERROR(Errors::IncomingDataNotUnderstood{},
                    "Descriptor handle '" << handle << "' is not valid.");
            }
            if (!versionIsNewer(handle))
            {
                S31_STREAM_TRACE_LOGGER("Sdc", "Skipping descriptor ", handle, " because version is not newer");
                return nullptr;
            }

            return DFL_MDIB_MAKE_SHARED<Entity>(
                handle,
                d,
                m_descriptor->version,
                DFL::asNotNull(DFL_MDIB_MAKE_SHARED<typename Entity::StateType>()),
                DFL::Mdib::VersionCounter(0),
                DFL::Mdib::BasicHandle<Parent>(m_descriptor->parentHandle));
        }

        /// Creates the current entity (as Mdib entity)
        template <class Descriptor, class Entity>
        DFL::Mdib::SharedPtr<Entity> checkVersionAndMakeEntity(const DFL::NotNull<DFL::Mdib::SharedPtr<Descriptor>>& d)
        {
            using Parent = typename Entity::ParentType;
            using StatePtr = DFL::NotNull<DFL::Mdib::SharedPtr<typename Entity::StateType>>;

            const auto handle = DFL::Mdib::BasicHandle<Entity>(m_descriptor->handle);
            if (!handle.isValid())
            {
                S31_THROW_EXCEPTION_WITH_ERROR(Errors::IncomingDataNotUnderstood{},
                    "Descriptor handle '" << handle << "' is not valid.");
            }
            if (!versionIsNewer(handle))
            {
                return nullptr;
            }

            const auto stateIt = m_modifications.getLastMatchingElement(m_descriptor->handle);
            if (stateIt == m_modifications.stateIndex().end())
            {
                S31_THROW_EXCEPTION_WITH_ERROR(Errors::IncomingDataNotUnderstood{},
                    "Descriptor report (" <<  m_descriptor->changeType << ") for "
                    << handle << " has no state. ");
            }

            const auto& stateReport = m_modifications.states()[stateIt->second];
            const StatePtr* state = std::get_if<StatePtr>(&stateReport.element);
            if (!state)
            {
                S31_THROW_EXCEPTION_WITH_ERROR(Errors::IncomingDataNotUnderstood{},
                    "Descriptor report (" << m_descriptor->changeType << ") for "
                    << handle << " has no state off suiting type.");
            }

            if (m_descriptor->version != stateReport.descriptorVersion)
            {
                S31_THROW_EXCEPTION_WITH_ERROR(Errors::IncomingDataNotUnderstood{},
                    "Descriptor report (" << m_descriptor->changeType << ") for "
                    << handle << " has a state with a non-matching descriptor version. Descriptor: "
                    << m_descriptor->version << ", state's descriptor: " << stateReport.descriptorVersion);
            }

            return DFL_MDIB_MAKE_SHARED<Entity>(
                handle,
                d,
                m_descriptor->version,
                *state,
                stateReport.stateVersion,
                DFL::Mdib::BasicHandle<Parent>(m_descriptor->parentHandle));
        }

        template <class Descriptor, class Entity>
        void insertedEntity(const DFL::NotNull<DFL::Mdib::SharedPtr<Descriptor>>& d)
        {
            if (auto entity = checkVersionAndMakeEntity<Descriptor, Entity>(d))
            {
                m_changeSet.addOneToInsert(DFL::asNotNull(entity));
            }
        }

        template <class Descriptor, class Entity>
        void updatedEntity(const DFL::NotNull<DFL::Mdib::SharedPtr<Descriptor>>& d)
        {
            if (auto entity = checkVersionAndMakeEntity<Descriptor, Entity>(d))
            {
                m_changeSet.addOneToUpdate(DFL::asNotNull(entity));
            }
        }

        template <class Descriptor, class Entity>
        void removedEntity(const DFL::NotNull<DFL::Mdib::SharedPtr<Descriptor>>& d)
        {
            if (auto entity = checkVersionAndMakeEntityWithDefaultState<Descriptor, Entity>(d))
            {
                m_changeSet.addOneToRemove(DFL::asNotNull(entity));
            }
        }

        template<class T_Entity>
        static bool checkEntity(const DFL::Mdib::Handle& handle,
                                const DFL::Mdib::MdibChangeSet& changeSet,
                                const DFL::Mdib::Mdib& mdib)
        {
            if (changeSet.insertedEntity(typename DFL::Mdib::BasicHandle<T_Entity>(handle)))
            {
                return true;
            }

            if (changeSet.updatedEntity(typename DFL::Mdib::BasicHandle<T_Entity>(handle)))
            {
                return true;
            }

            if (mdib.entity(typename DFL::Mdib::BasicHandle<T_Entity>(handle)))
            {
                return true;
            }
            return false;
        }

        template <class MdsOrVmdType>
        bool isMdsOrVmdType()
        {
            using Parent = typename MdsOrVmdType::ParentType;
            const auto handle = m_descriptor->parentHandle;
            return checkEntity<Parent>(handle, m_changeSet, m_mdib);
        }

        template <typename Descriptor>
        void handleContextStates(const DFL::NotNull<DFL::Mdib::SharedPtr<Descriptor>>& /*d*/)
        {
            using Indicator = typename EntityTypeOfDescriptor<Descriptor>::type;
            using Context = typename ContextOfContextIndicator<Indicator>::type;
            using StatePtr = DFL::NotNull<DFL::Mdib::SharedPtr<typename Context::StateType>>;

            // range states
            auto stateRange = m_modifications.stateIndex().equal_range(m_descriptor->handle);
            for (auto stateIt = stateRange.first; stateIt != stateRange.second; ++stateIt)
            {
                const auto& stateReport = m_modifications.states()[stateIt->second];
                const auto handle = DFL::Mdib::BasicHandle<Context>(stateReport.contextStateHandle);
                if (!handle.isValid())
                {
                    S31_THROW_EXCEPTION_WITH_ERROR(Errors::IncomingDataNotUnderstood{},
                        "Context state handle '" << handle << "' is not valid.");
                }
                const StatePtr* state =  std::get_if<StatePtr>(&stateReport.element);
                if (!state)
                {
                    S31_THROW_EXCEPTION_WITH_ERROR(Errors::IncomingDataNotUnderstood{},
                        "Context state " << handle << " is not of suiting type for " << m_descriptor->handle);
                }

                // update existing entity?
                const auto previousEntity = m_mdib.entity(handle);
                if (previousEntity && stateReport.stateVersion <= previousEntity->stateVersion())
                {
                    S31_STREAM_TRACE_LOGGER("Sdc", "ContextState with handle ", handle, " in version already known");
                    continue;
                }

                if (m_descriptor->version != stateReport.descriptorVersion)
                {
                    S31_THROW_EXCEPTION_WITH_ERROR(Errors::IncomingDataNotUnderstood{},
                        "Descriptor report (" << m_descriptor->changeType << ") for "
                        << m_descriptor->handle << " has a context state " << handle
                        << " with a non-matching descriptor version. Descriptor: "
                        << m_descriptor->version << ", state's descriptor: " << stateReport.descriptorVersion);
                }

                auto entity = DFL_MDIB_MAKE_SHARED<Context>(
                    handle,
                    *state,
                    stateReport.stateVersion,
                    DFL::Mdib::BasicHandle<Indicator>(m_descriptor->handle));

                if (entity->state()->contextAssociation() == DFL::Mdib::ContextAssociation::NotAssociated)
                {
                    m_changeSet.addOneToRemove(DFL::asNotNull(entity));
                    continue;
                }

                if (previousEntity)
                {
                    m_changeSet.addOneToUpdate(DFL::asNotNull(entity));
                }
                else
                {
                    m_changeSet.addOneToInsert(DFL::asNotNull(entity));
                }
            }
        }

        DFL::Mdib::MdibChangeSet& m_changeSet;
        const DFL::Mdib::Mdib& m_mdib;
        DFL::NotNull<const ReportDescriptor*> m_descriptor;
        const DescriptorModifications& m_modifications;
};


/**
 * @brief Makes MdibChangeSet from Reports
 * @ingroup S31SdcCommon
 */
template <class Modifications>
class ChangeSetBuilder
{
    public:

        ChangeSetBuilder(                
                const DFL::Mdib::Mdib& mdib,
                const Modifications& report):
            m_mdib(mdib),
            m_report(report)
        {}

        DFL::Mdib::MdibChangeSet build()
        {
            DFL::Mdib::MdibChangeSet result;

            if (!checkMdibVersion(m_mdib, m_report))
            {
                return result;
            }

            if (m_report.elements.empty())
            {
                return result;
            }

            Inserter inserter(result, m_mdib, *m_report.elements.begin(), m_report);
            for (const auto& reportPart : m_report.elements)
            {
                inserter.setCurrentReportPart(reportPart);
                std::visit(inserter, reportPart.element);
            }

            return result;
        }

    private:
        /**
         * @brief Type function to get the Inserter type for a Modification type
         */
        template <typename Mod>
        struct InserterOfModification
        {
            using AllModifications = boost::mpl::vector<DescriptorModifications, StateModifications>;
            using AllInserters = boost::mpl::vector<ChangeSetInserterDescriptor, ChangeSetInserterState>;
            using iter = typename boost::mpl::find_if<AllModifications, std::is_same<boost::mpl::_1, Mod>>::type;
            using type = typename boost::mpl::at<AllInserters, boost::mpl::int_<iter::pos::value>>::type;
        };
        using Inserter = typename InserterOfModification<Modifications>::type;

        bool checkMdibVersion(const DFL::Mdib::Mdib& mdib, const Modifications& modifications)
        {
            const auto& mdibVersion = mdib.mdibVersion();
            const auto& reportVersion = modifications.mdibVersion;

            if (mdibVersion.isOlderVersionOf(reportVersion) || mdibVersion == reportVersion)
            {
                return true;
            }

            if (mdibVersion.isOtherSequenceOf(reportVersion))
            {
                S31_THROW_EXCEPTION_WITH_ERROR(Errors::MdibSequenceChanged{},
                    "New MDIB sequence detected. Cannot handle report. old: "
                    <<  mdibVersion << " new: " << reportVersion);
            }

            S31_STREAM_TRACE_LOGGER("Sdc",
                "Received Mdib version is an older version than existing. Have ", mdibVersion, ", received ", reportVersion);
            return false;
        }

        const DFL::Mdib::Mdib& m_mdib;
        const Modifications& m_report;
};

using ChangeSetBuilderState = ChangeSetBuilder<StateModifications>;
using ChangeSetBuilderDescriptor = ChangeSetBuilder<DescriptorModifications>;

}
