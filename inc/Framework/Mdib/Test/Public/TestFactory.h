#pragma once

#include <Framework/Mdib/Private/ContextDescriptorEntity.h>
#include <Framework/Mdib/Private/ContextStateEntity.h>
#include <Framework/Mdib/Private/MdibEntity.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/Model/Alert/AlertCondition.h>
#include <Framework/Mdib/Public/Model/Alert/AlertConditionDescriptor.h>
#include <Framework/Mdib/Public/Model/Alert/AlertConditionDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Alert/AlertConditionState.h>
#include <Framework/Mdib/Public/Model/Alert/AlertConditionStateBuilder.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignal.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignalDescriptor.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignalDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignalState.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignalStateBuilder.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystem.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystemDescriptor.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystemDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystemState.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystemStateBuilder.h>
#include <Framework/Mdib/Public/Model/Alert/LimitAlertCondition.h>
#include <Framework/Mdib/Public/Model/Alert/LimitAlertConditionDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Alert/LimitAlertConditionStateBuilder.h>
#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Public/Model/CodedValueFactory.h>
#include <Framework/Mdib/Public/Model/CodedValueTranslation.h>
#include <Framework/Mdib/Public/Model/CodingSystemFactory.h>
#include <Framework/Mdib/Public/Model/Component/Channel.h>
#include <Framework/Mdib/Public/Model/Component/ChannelDescriptor.h>
#include <Framework/Mdib/Public/Model/Component/ChannelDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Component/ChannelState.h>
#include <Framework/Mdib/Public/Model/Component/ChannelStateBuilder.h>
#include <Framework/Mdib/Public/Model/Component/Clock.h>
#include <Framework/Mdib/Public/Model/Component/MdsDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Component/MdsStateBuilder.h>
#include <Framework/Mdib/Public/Model/Component/Sco.h>
#include <Framework/Mdib/Public/Model/Component/ScoDescriptor.h>
#include <Framework/Mdib/Public/Model/Component/ScoState.h>
#include <Framework/Mdib/Public/Model/Component/SystemContext.h>
#include <Framework/Mdib/Public/Model/Component/Vmd.h>
#include <Framework/Mdib/Public/Model/Component/VmdDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Component/VmdStateBuilder.h>
#include <Framework/Mdib/Public/Model/Context/EnsembleContext.h>
#include <Framework/Mdib/Public/Model/Context/EnsembleContextIndicator.h>
#include <Framework/Mdib/Public/Model/Context/LocationContext.h>
#include <Framework/Mdib/Public/Model/Context/LocationContextIndicator.h>
#include <Framework/Mdib/Public/Model/Context/PatientContext.h>
#include <Framework/Mdib/Public/Model/Context/PatientContextIndicator.h>
#include <Framework/Mdib/Public/Model/EntityFactory.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Metric/DistributionSampleArrayMetric.h>
#include <Framework/Mdib/Public/Model/Metric/DistributionSampleArrayMetricDescriptor.h>
#include <Framework/Mdib/Public/Model/Metric/DistributionSampleArrayMetricDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Metric/DistributionSampleArrayMetricState.h>
#include <Framework/Mdib/Public/Model/Metric/DistributionSampleArrayMetricStateBuilder.h>
#include <Framework/Mdib/Public/Model/Metric/EnumStringMetric.h>
#include <Framework/Mdib/Public/Model/Metric/EnumStringMetricDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Metric/EnumStringMetricStateBuilder.h>
#include <Framework/Mdib/Public/Model/Metric/NumericMetric.h>
#include <Framework/Mdib/Public/Model/Metric/NumericMetricDescriptor.h>
#include <Framework/Mdib/Public/Model/Metric/NumericMetricDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Metric/NumericMetricStateBuilder.h>
#include <Framework/Mdib/Public/Model/Metric/RealTimeSampleArrayMetric.h>
#include <Framework/Mdib/Public/Model/Metric/RealTimeSampleArrayMetricDescriptor.h>
#include <Framework/Mdib/Public/Model/Metric/RealTimeSampleArrayMetricDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Metric/RealTimeSampleArrayMetricState.h>
#include <Framework/Mdib/Public/Model/Metric/RealTimeSampleArrayMetricStateBuilder.h>
#include <Framework/Mdib/Public/Model/Metric/StringMetric.h>
#include <Framework/Mdib/Public/Model/Metric/StringMetricDescriptorBuilder.h>
#include <Framework/Mdib/Public/Model/Metric/StringMetricStateBuilder.h>
#include <Framework/Mdib/Public/Model/Operation/ActivateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetAlertStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetComponentStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetContextStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetMetricStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetStringOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetValueOperation.h>
#include <Framework/Mdib/Public/Model/VersionCounter.h>
#include <Framework/Mdib/Public/TypeTraits.h>
#include <Framework/Utils/Public/Utf8.h>
namespace DFL
{
namespace Mdib
{
namespace Test
{

namespace BaseTree
{
static const DFL::Mdib::MdsHandle Mds("base-mds");
static const DFL::Mdib::MdsAlertSystemHandle MdsAlertSystem("base-mds-alertsystem");
static const DFL::Mdib::MdsAlertConditionHandle MdsAlertCondition1("base-mds-alertcondition-1");
static const DFL::Mdib::MdsAlertConditionHandle MdsAlertCondition2("base-mds-alertcondition-2");
static const DFL::Mdib::MdsAlertConditionHandle MdsAlertCondition3("base-mds-alertcondition-3");
static const DFL::Mdib::MdsAlertConditionHandle MdsAlertCondition4("base-mds-alertcondition-4");
static const DFL::Mdib::MdsLimitAlertConditionHandle MdsLimitAlertCondition1("base-mds-limitalertcondition-1");
static const DFL::Mdib::MdsLimitAlertConditionHandle MdsLimitAlertCondition2("base-mds-limitalertcondition-2");
static const DFL::Mdib::MdsLimitAlertConditionHandle MdsLimitAlertCondition3("base-mds-limitalertcondition-3");
static const DFL::Mdib::MdsLimitAlertConditionHandle MdsLimitAlertCondition4("base-mds-limitalertcondition-4");
static const DFL::Mdib::MdsLimitAlertConditionHandle MdsLimitAlertCondition5("base-mds-limitalertcondition-5");
static const DFL::Mdib::MdsAlertSignalHandle MdsAlertSignal1("base-mds-alertSignal-1");
static const DFL::Mdib::MdsAlertSignalHandle MdsAlertSignal2("base-mds-alertSignal-2");
static const DFL::Mdib::MdsAlertSignalHandle MdsAlertSignal3("base-mds-alertSignal-3");
static const DFL::Mdib::MdsAlertSignalHandle MdsAlertSignal4("base-mds-alertSignal-4");
static const DFL::Mdib::MdsAlertSignalHandle MdsAlertSignal5("base-mds-alertSignal-5");
static const DFL::Mdib::MdsAlertSignalHandle MdsAlertSignal6("base-mds-alertSignal-6");
static const DFL::Mdib::MdsAlertSignalHandle MdsAlertSignal7("base-mds-alertSignal-7");
static const DFL::Mdib::MdsScoHandle MdsSco("base-mds-sco");
static const DFL::Mdib::VmdHandle Vmd("base-vmd");
static const DFL::Mdib::VmdAlertSystemHandle VmdAlertSystem("base-vmd-alertsystem");
static const DFL::Mdib::VmdScoHandle VmdSco("base-vmd-sco");
static const DFL::Mdib::VmdLimitAlertConditionHandle VmdLimitAlertCondition1("base-vmd-limitalertcondition-1");
static const DFL::Mdib::VmdLimitAlertConditionHandle VmdLimitAlertCondition2("base-vmd-limitalertcondition-2");
static const DFL::Mdib::VmdLimitAlertConditionHandle VmdLimitAlertCondition3("base-vmd-limitalertcondition-3");
static const DFL::Mdib::VmdLimitAlertConditionHandle VmdLimitAlertCondition4("base-vmd-limitalertcondition-4");
static const DFL::Mdib::VmdLimitAlertConditionHandle VmdLimitAlertCondition5("base-vmd-limitalertcondition-5");
static const DFL::Mdib::VmdAlertConditionHandle VmdAlertCondition1("base-vmd-alertcondition");
static const DFL::Mdib::VmdAlertConditionHandle VmdAlertCondition2("base-vmd-alertcondition2");
static const DFL::Mdib::VmdAlertSignalHandle VmdAlertSignal1("base-vmd-alertSignal1");
static const DFL::Mdib::VmdAlertSignalHandle VmdAlertSignal2("base-vmd-alertSignal2");
static const DFL::Mdib::VmdAlertSignalHandle VmdAlertSignal3("base-vmd-alertSignal3");
static const DFL::Mdib::ChannelHandle Channel("base-channel");
static const DFL::Mdib::ChannelHandle Channel2("base-channel2");
static const DFL::Mdib::LocationContextIndicatorHandle LocationIndicator("base-location-indicator");
static const DFL::Mdib::LocationContextHandle Location("base-location");
static const DFL::Mdib::PatientContextIndicatorHandle PatientIndicator("base-patient-indicator");
static const DFL::Mdib::PatientContextHandle Patient("base-patient");
static const DFL::Mdib::EnsembleContextIndicatorHandle EnsembleIndicator("base-ensemble-indicator");
static const DFL::Mdib::EnsembleContextHandle Ensemble("base-ensemble");
static const DFL::Mdib::SystemContextHandle SystemContext("base-system-context");
static const DFL::Mdib::ClockHandle Clock("base-clock");
static const DFL::Mdib::StringMetricHandle StringMetric("base-string-metric");
static const DFL::Mdib::EnumStringMetricHandle EnumStringMetric("base-enum-string-metric");
static const DFL::Mdib::NumericMetricHandle NumericMetric1("base-numeric-metric-1");
static const DFL::Mdib::NumericMetricHandle NumericMetric2("base-numeric-metric-2");
static const DFL::Mdib::NumericMetricHandle NumericMetric3("base-numeric-metric-3");
static const DFL::Mdib::NumericMetricHandle NumericMetricCh2_1("base-numeric-metric-channel2-1");
static const DFL::Mdib::NumericMetricHandle NumericMetricCh2_2("base-numeric-metric-channel2-2");
static const DFL::Mdib::NumericMetricHandle NumericMetricCh2_3("base-numeric-metric-channel2-3");
static const DFL::Mdib::NumericMetricHandle NumericMetricCh2_4("base-numeric-metric-channel2-4");
static const DFL::Mdib::NumericMetricHandle NumericMetricCh2_5("base-numeric-metric-channel2-5");
static const DFL::Mdib::RealTimeSampleArrayMetricHandle RealTimeSampleArrayMetric1("base-real-time-samples-channel2-1");
static const DFL::Mdib::RealTimeSampleArrayMetricHandle RealTimeSampleArrayMetric2("base-real-time-samples-channel2-2");
static const DFL::Mdib::RealTimeSampleArrayMetricHandle RealTimeSampleArrayMetric3("base-real-time-samples-channel2-3");
static const DFL::Mdib::RealTimeSampleArrayMetricHandle RealTimeSampleArrayMetric4("base-real-time-samples-channel2-4");
static const DFL::Mdib::RealTimeSampleArrayMetricHandle RealTimeSampleArrayMetric5("base-real-time-samples-channel2-5");
static const DFL::Mdib::DistributionSampleArrayMetricHandle DistributionSampleArrayMetric1("distribution-sample-array-metric-1");
static const DFL::Mdib::MdsActivateOperationHandle MdsActivateOperation("base-mds-activate-operation");
static const DFL::Mdib::VmdActivateOperationHandle VmdActivateOperation("base-vmd-activate-operation");
static const DFL::Mdib::MdsSetStringOperationHandle MdsSetStringOperation("base-mds-setstring-operation");
static const DFL::Mdib::VmdSetStringOperationHandle VmdSetStringOperation("base-vmd-setstring-operation");
static const DFL::Mdib::MdsSetStringOperationHandle MdsSetEnumStringOperation("base-mds-setenumstring-operation");
static const DFL::Mdib::VmdSetStringOperationHandle VmdSetEnumStringOperation("base-vmd-setenumstring-operation");
static const DFL::Mdib::MdsSetValueOperationHandle MdsSetValueOperation("base-mds-setvalue-operation");
static const DFL::Mdib::VmdSetValueOperationHandle VmdSetValueOperation("base-vmd-setvalue-operation");
static const DFL::Mdib::MdsSetContextStateOperationHandle MdsSetPatientContextStateOperation("base-mds-setpatientcontext-operation");
static const DFL::Mdib::VmdSetContextStateOperationHandle VmdSetPatientContextStateOperation("base-vmd-setpatientcontext-operation");
static const DFL::Mdib::MdsSetComponentStateOperationHandle MdsSetComponentStateOperation("base-mds-setcomponent-operation");
static const DFL::Mdib::VmdSetComponentStateOperationHandle VmdSetComponentStateOperation("base-vmd-setcomponent-operation");
static const DFL::Mdib::MdsSetAlertStateOperationHandle MdsSetAlertSystemStateOperation("base-mds-setalertsystem-operation");
static const DFL::Mdib::VmdSetAlertStateOperationHandle VmdSetAlertSystemStateOperation("base-vmd-setalertsystem-operation");
static const DFL::Mdib::MdsSetAlertStateOperationHandle MdsSetAlertConditionStateOperation("base-mds-setalertcondition-operation");
static const DFL::Mdib::VmdSetAlertStateOperationHandle VmdSetAlertConditionStateOperation("base-vmd-setalertcondition-operation");
static const DFL::Mdib::MdsSetAlertStateOperationHandle MdsSetLimitAlertConditionStateOperation("base-mds-setlimitalertcondition-operation");
static const DFL::Mdib::VmdSetAlertStateOperationHandle VmdSetLimitAlertConditionStateOperation("base-vmd-setlimitalertcondition-operation");
static const DFL::Mdib::MdsSetAlertStateOperationHandle MdsSetAlertSignalStateOperation("base-mds-setalertsignal-operation");
static const DFL::Mdib::VmdSetAlertStateOperationHandle VmdSetAlertSignalStateOperation("base-vmd-setalertsignal-operation");
static const DFL::Mdib::MdsSetContextStateOperationHandle MdsSetLocationContextStateOperation("base-mds-setlocationcontext-operation");
static const DFL::Mdib::MdsSetContextStateOperationHandle MdsSetEnsembleContextStateOperation("base-mds-setensemblecontext-operation");
static const DFL::Mdib::MdsSetMetricStateOperationHandle MdsSetMetricStateOperation("base-mds-setmetric-operation");
static const DFL::Mdib::VmdSetMetricStateOperationHandle VmdSetMetricStateOperation("base-vmd-setmetric-operation");

}

/**
 * @brief Helper class to reduce the burden of creating different MDIB structures.
 */
class TestFactory
{
    public:
        /**
         * @brief Used to determine what information is included in an initial Mdib.
         * @ingroup Mdib
         */
        enum class InitialMdibTree
        {
            BaseTree,   //!< Initialize with BaseTree which includes Mds, Vmd, SystemContext, Mds/Vmd Sco and Mds/Vmd AlertSystem
            MdsVmdOnly  //!< Initialize with only an Mds and Vmd
        };

        /**
         * @brief Creates a base tree.
         */
        static DFL::Mdib::MdibChangeSet createBaseTree();

        /**
         * @brief Creates a base tree with only an Mds and child Vmd
         */
        static DFL::Mdib::MdibChangeSet createMdsAndVmdOnlyBaseTree();

        /**
         * @brief Creates a mock entity based on a handle.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> createEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle);

        /**
         * @brief Creates a mock entity based on a handle and a parent.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> createEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle,
                                                          const DFL::Mdib::BasicHandle<typename T_Entity::ParentType>& parent);

        /**
         * @brief Specialization for LocationContextIndicator.
         */
        static NotNull<SharedPtr<DFL::Mdib::LocationContextIndicator>> createEntity(
            const DFL::Mdib::BasicHandle<DFL::Mdib::LocationContextIndicator>& handle,
            const DFL::Mdib::BasicHandle<DFL::Mdib::SystemContext>& parent);

        /**
         * @brief Specialization for PatientContextIndicator.
         */
        static NotNull<SharedPtr<DFL::Mdib::PatientContextIndicator>> createEntity(
            const DFL::Mdib::BasicHandle<DFL::Mdib::PatientContextIndicator>& handle,
            const DFL::Mdib::BasicHandle<DFL::Mdib::SystemContext>& parent);

        /**
         * @brief Creates a mock entity based on a handle, descriptor and state version.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> createEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle,
                                                          DFL::Mdib::VersionCounter descriptorVersion,
                                                          DFL::Mdib::VersionCounter stateVersion);
        /**
         * @brief Creates a mock entity based on a handle, parent, descriptor and state version.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> createEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle,
                                                          DFL::Mdib::VersionCounter descriptorVersion,
                                                          DFL::Mdib::VersionCounter stateVersion,
                                                          const DFL::Mdib::BasicHandle<typename T_Entity::ParentType>& parent);

        /**
         * @brief Creates a mock descriptor entity (context descriptor) based on a handle.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> createDescriptorEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle);

        /**
         * @brief Creates a mock descriptor entity (context descriptor) based on a handle and a parent.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> createDescriptorEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle,
                                                                    const DFL::Mdib::BasicHandle<typename T_Entity::ParentType>& parent);

        /**
         * @brief Creates a mock descriptor entity (context descriptor) based on a handle and a descriptor version.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> createDescriptorEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle,
                                                                    DFL::Mdib::VersionCounter descriptorVersion);

        /**
         * @brief Creates a mock descriptor entity (context descriptor) based on a handle, descriptor version and parent.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> createDescriptorEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle,
                                                                    DFL::Mdib::VersionCounter descriptorVersion,
                                                                    const DFL::Mdib::BasicHandle<typename T_Entity::ParentType>& parent);

        /**
         * @brief Creates a mock state entity (context state) based on a handle.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> createStateEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle);

        /**
         * @brief Creates a mock state entity (context state) based on a handle and a parent.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> createStateEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle,
                                                               const DFL::Mdib::BasicHandle<typename T_Entity::ParentType>& parent);

        /**
         * @brief Creates a mock state entity (context state) based on a handle and a state version.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> createStateEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle,
                                                               DFL::Mdib::VersionCounter stateVersion);

        /**
         * @brief Creates a mock state entity (context state) based on a handle, state version and parent.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> createStateEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle,
                                                               DFL::Mdib::VersionCounter stateVersion,
                                                               const DFL::Mdib::BasicHandle<typename T_Entity::ParentType>& parent);

        /**
         * @brief Accepts an entity and changes the type of the descriptor.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> setType(const NotNull<SharedPtr<T_Entity>> &entity, const DFL::Mdib::CodedValue &type);

        /// sets the condition's presence in the conditions state
        template<class T_AlertCondition>
        static NotNull<SharedPtr<T_AlertCondition>> setPresence(const NotNull<SharedPtr<T_AlertCondition>> &entity, DFL::Mdib::AlertConditionPresence presence);

        /// sets the condition's presence in the conditions state without updating the determination time
        template<class T_AlertCondition>
        static NotNull<SharedPtr<T_AlertCondition>> setPresenceWithoutTimestamp(const NotNull<SharedPtr<T_AlertCondition>> &entity, DFL::Mdib::AlertConditionPresence presence);

        /**
         * @brief Accepts an entity and changes the ContextAssociation of it's context state.
         */
        template<class T_Context>
        static NotNull<SharedPtr<T_Context>> setContextAssociation(const NotNull<SharedPtr<T_Context>>& entity, const DFL::Mdib::ContextAssociation& association);

        /**
         * @brief Creates an unspecified IEEE 11073 code based on handle hash.
         */
        static CodedValue hashCodedValue(const Handle& handle);

        /**
         * @brief Creates an unspecified IEEE 11073 code based on handle hash.
         */
        static CodedValue hashCodedValue(const std::string& handle);

        /**
         * @brief Sets a determination period in a metric descriptor builder
         */
        ///@{
        template<class T_DescBuilder>
        static void setDeterminationPeriodForMetric(T_DescBuilder& builder,
                                                    typename std::enable_if<DFL::Mdib::is_metric_descriptor<typename T_DescBuilder::BuiltType>::value>::type* = nullptr);
        template<class T_DescBuilder>
        static void setDeterminationPeriodForMetric(T_DescBuilder& builder,
                                                    typename std::enable_if<!DFL::Mdib::is_metric_descriptor<typename T_DescBuilder::BuiltType>::value>::type* = nullptr);
        ///@}

        /**
         * @brief Sets an allowed value for enum string metric descriptor builder
         */
        ///@{
        template<class T_DescBuilder>
        static void setAllowedValues(T_DescBuilder& builder,
                                     typename std::enable_if<std::is_same<T_DescBuilder, DFL::Mdib::EnumStringMetricDescriptorBuilder>::value>::type* = nullptr);
        template<class T_DescBuilder>
        static void setAllowedValues(T_DescBuilder& builder,
                                     typename std::enable_if<!std::is_same<T_DescBuilder, DFL::Mdib::EnumStringMetricDescriptorBuilder>::value>::type* = nullptr);
        ///@}

    private:
        /**
         * @brief Creates a mock non-operation entity based on a handle, parent, descriptor and state version.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> createEntityIn(
            const DFL::Mdib::BasicHandle<T_Entity>& handle,
            DFL::Mdib::VersionCounter descriptorVersion,
            DFL::Mdib::VersionCounter stateVersion,
            const DFL::Mdib::BasicHandle<typename T_Entity::ParentType>& parent,
            typename std::enable_if<!DFL::Mdib::is_operation<T_Entity>::value>::type* = nullptr);
        /**
         * @brief Creates a mock operation entity based on a handle, parent, descriptor and state version.
         */
        template<class T_Entity>
        static NotNull<SharedPtr<T_Entity>> createEntityIn(
            const DFL::Mdib::BasicHandle<T_Entity>& handle,
            DFL::Mdib::VersionCounter descriptorVersion,
            DFL::Mdib::VersionCounter stateVersion,
            const DFL::Mdib::BasicHandle<typename T_Entity::ParentType>& parent,
            typename std::enable_if<DFL::Mdib::is_operation<T_Entity>::value>::type* = nullptr);
};

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> TestFactory::createEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle,
                                                               DFL::Mdib::VersionCounter descriptorVersion,
                                                               DFL::Mdib::VersionCounter stateVersion,
                                                               const DFL::Mdib::BasicHandle<typename T_Entity::ParentType>& parent)
{
    static_assert(
            std::is_convertible<T_Entity, DFL::Mdib::Impl::MdibEntityDescriptor<T_Entity, typename T_Entity::DescriptorBuilderType, typename T_Entity::ParentType>>::value
            || std::is_convertible<T_Entity, DFL::Mdib::Impl::ContextStateEntity<T_Entity, typename T_Entity::DescriptorBuilderType, typename T_Entity::StateBuilderType, typename T_Entity::ParentType>>::value,
            "Only MDIB entities are allowed (i.e., objects derived from MdibEntity)"
    );
    return createEntityIn(handle, descriptorVersion, stateVersion, parent);
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> TestFactory::createEntityIn(
        const DFL::Mdib::BasicHandle<T_Entity>& handle,
        DFL::Mdib::VersionCounter descriptorVersion,
        DFL::Mdib::VersionCounter stateVersion,
        const DFL::Mdib::BasicHandle<typename T_Entity::ParentType>& parent,
        typename std::enable_if<!DFL::Mdib::is_operation<T_Entity>::value>::type*)
{
    typename T_Entity::DescriptorBuilderType desc;
    desc.type(hashCodedValue(handle.string()));
    setDeterminationPeriodForMetric(desc);
    setAllowedValues(desc);
    return asNotNull(DFL_MDIB_MAKE_SHARED<T_Entity>(handle,
        DFL::asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::DescriptorType>(desc.build())),
        descriptorVersion,
        DFL::asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::StateType>()),
        stateVersion,
        parent));
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> TestFactory::createEntityIn(
        const DFL::Mdib::BasicHandle<T_Entity>& handle,
        DFL::Mdib::VersionCounter descriptorVersion,
        DFL::Mdib::VersionCounter stateVersion,
        const DFL::Mdib::BasicHandle<typename T_Entity::ParentType>& parent,
        typename std::enable_if<DFL::Mdib::is_operation<T_Entity>::value>::type*)
{
    typename T_Entity::DescriptorBuilderType desc;
    desc.type(hashCodedValue(handle.string()));
    desc.operationTarget(toHandle(handle)); // link to own handle
    return asNotNull(DFL_MDIB_MAKE_SHARED<T_Entity>(handle,
        DFL::asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::DescriptorType>(desc.build())),
        descriptorVersion,
        DFL::asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::StateType>()),
        stateVersion,
        parent));
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> TestFactory::createDescriptorEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle,
                                                                         DFL::Mdib::VersionCounter descriptorVersion,
                                                                         const DFL::Mdib::BasicHandle<typename T_Entity::ParentType>& parent)
{
    static_assert(
            std::is_convertible<T_Entity, DFL::Mdib::Impl::ContextDescriptorEntity<T_Entity, typename T_Entity::DescriptorBuilderType, typename T_Entity::StateBuilderType, typename T_Entity::ParentType>>::value,
            "Only context descriptor entities allowed (i.e., objects derived from ContextDescriptorEntity)"
    );
    return asNotNull(DFL_MDIB_MAKE_SHARED<T_Entity>(handle, DFL::asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::DescriptorType>()), descriptorVersion, parent));
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> TestFactory::createStateEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle,
                                                                    DFL::Mdib::VersionCounter stateVersion,
                                                                    const DFL::Mdib::BasicHandle<typename T_Entity::ParentType>& parent)
{
    static_assert(
            std::is_convertible<T_Entity, DFL::Mdib::Impl::ContextStateEntity<T_Entity, typename T_Entity::DescriptorBuilderType, typename T_Entity::StateBuilderType, typename T_Entity::ParentType>>::value,
            "Only context state entities are allowed (i.e., objects derived from ContextStateEntity)"
    );
    return asNotNull(DFL_MDIB_MAKE_SHARED<T_Entity>(handle, DFL::asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::StateType>()), stateVersion, parent));
}

inline NotNull<SharedPtr<DFL::Mdib::LocationContextIndicator>> TestFactory::createEntity(
        const DFL::Mdib::BasicHandle<DFL::Mdib::LocationContextIndicator>& handle,
        const DFL::Mdib::BasicHandle<DFL::Mdib::SystemContext>& parent)
{
    return createDescriptorEntity<DFL::Mdib::LocationContextIndicator>(handle, parent);
}

inline NotNull<SharedPtr<DFL::Mdib::PatientContextIndicator>> TestFactory::createEntity(
        const DFL::Mdib::BasicHandle<DFL::Mdib::PatientContextIndicator>& handle,
        const DFL::Mdib::BasicHandle<DFL::Mdib::SystemContext>& parent)
{
    return createDescriptorEntity<DFL::Mdib::PatientContextIndicator>(handle, parent);
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> TestFactory::createEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle, const DFL::Mdib::BasicHandle<typename T_Entity::ParentType>& parent)
{
    return createEntity<T_Entity>(handle, DFL::Mdib::VersionCounter(0), DFL::Mdib::VersionCounter(0), parent);
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> TestFactory::createDescriptorEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle, const DFL::Mdib::BasicHandle<typename T_Entity::ParentType>& parent)
{
    return createDescriptorEntity<T_Entity>(handle, DFL::Mdib::VersionCounter(0), parent);
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> TestFactory::createStateEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle, const DFL::Mdib::BasicHandle<typename T_Entity::ParentType>& parent)
{
    return createStateEntity<T_Entity>(handle, DFL::Mdib::VersionCounter(0), parent);
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> TestFactory::createEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle)
{
    return createEntity<T_Entity>(handle, DFL::Mdib::VersionCounter(0), DFL::Mdib::VersionCounter(0), DFL::Mdib::BasicHandle<typename T_Entity::ParentType>());
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> TestFactory::createDescriptorEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle)
{
    return createDescriptorEntity<T_Entity>(handle, DFL::Mdib::VersionCounter(0), DFL::Mdib::BasicHandle<typename T_Entity::ParentType>());
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> TestFactory::createStateEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle)
{
    return createStateEntity<T_Entity>(handle, DFL::Mdib::VersionCounter(0), DFL::Mdib::BasicHandle<typename T_Entity::ParentType>());
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> TestFactory::createEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle,
                                                                        DFL::Mdib::VersionCounter descriptorVersion,
                                                                        DFL::Mdib::VersionCounter stateVersion)
{
    return createEntity<T_Entity>(handle, descriptorVersion, stateVersion, DFL::Mdib::BasicHandle<typename T_Entity::ParentType>());
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> TestFactory::createDescriptorEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle,
                                                                         DFL::Mdib::VersionCounter descriptorVersion)
{
    return createDescriptorEntity<T_Entity>(handle, descriptorVersion, DFL::Mdib::BasicHandle<typename T_Entity::ParentType>());
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> TestFactory::createStateEntity(const DFL::Mdib::BasicHandle<T_Entity>& handle,
                                                                    DFL::Mdib::VersionCounter stateVersion)
{
    return createStateEntity<T_Entity>(handle, stateVersion, DFL::Mdib::BasicHandle<typename T_Entity::ParentType>());
}

template<class T_Entity>
inline NotNull<SharedPtr<T_Entity>> TestFactory::setType(const NotNull<SharedPtr<T_Entity>> &entity, const DFL::Mdib::CodedValue &type)
{
    auto descBuilder = DFL::Mdib::getBuilder(entity->descriptor());
    descBuilder.type(type);

    auto stateBuilder = DFL::Mdib::getBuilder(entity->state());

    return DFL::Mdib::EntityFactory::create(entity->handle(), descBuilder, stateBuilder, entity->parent());
}

template<class T_AlertCondition>
inline NotNull<SharedPtr<T_AlertCondition>> TestFactory::setPresence(const NotNull<SharedPtr<T_AlertCondition>> &entity, const DFL::Mdib::AlertConditionPresence presence)
{
    auto stateBuilder = DFL::Mdib::getBuilder(entity->state());
    stateBuilder.presence(presence);
    stateBuilder.determinationTime(DFL::Chrono::SystemClock::now());
    return DFL::Mdib::EntityFactory::create(entity, stateBuilder);
}

template<class T_AlertCondition>
inline NotNull<SharedPtr<T_AlertCondition>> TestFactory::setPresenceWithoutTimestamp(const NotNull<SharedPtr<T_AlertCondition>> &entity, const DFL::Mdib::AlertConditionPresence presence)
{
    auto stateBuilder = DFL::Mdib::getBuilder(entity->state());
    stateBuilder.presence(presence);
    return DFL::Mdib::EntityFactory::create(entity, stateBuilder);
}

template<class T_Context>
inline NotNull<SharedPtr<T_Context>> TestFactory::setContextAssociation(const NotNull<SharedPtr<T_Context>>& entity, const DFL::Mdib::ContextAssociation& association)
{
    auto stateBuilder = DFL::Mdib::getBuilder(entity->state());
    stateBuilder.contextAssociation(association);
    return DFL::Mdib::EntityFactory::create(entity, stateBuilder);
}

namespace Helper
{

void appendSystemContext(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::MdsHandle& mds);
void appendMetric(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::ChannelHandle &channel);
void appendMetric2(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::ChannelHandle &channel);
void appendRTS(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::ChannelHandle &channel);
void appendChannel(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::VmdHandle& vmd);
void appendVmdOperation(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::VmdScoHandle& vmdSco);
void appendVmdSco(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::VmdHandle& vmd);
void appendVmdAlertCondition(
    DFL::Mdib::MdibChangeSet& changeSet,
    const DFL::Mdib::VmdAlertSystemHandle& vmdAlertSystem,
    const DFL::Mdib::AlertActivation& activation = DFL::Mdib::AlertActivation::On);
void appendVmdLimitAlertCondition(
    DFL::Mdib::MdibChangeSet& changeSet,
    const DFL::Mdib::VmdAlertSystemHandle& vmdAlertSystem,
    const DFL::Mdib::AlertActivation& activation = DFL::Mdib::AlertActivation::On);
void appendVmdLimitAlertConditionWithLimits(
    DFL::Mdib::MdibChangeSet& changeSet,
    const DFL::Mdib::VmdAlertSystemHandle& vmdAlertSystem,
    const DFL::Mdib::AlertActivation& activation = DFL::Mdib::AlertActivation::Off);
void appendVmdAlertSignal(
    DFL::Mdib::MdibChangeSet& changeSet,
    const DFL::Mdib::VmdAlertSystemHandle& vmdAlertSystem,
    const DFL::Mdib::AlertActivation& activation = DFL::Mdib::AlertActivation::On);
DFL::Mdib::VmdAlertSystemHandle appendVmdAlertSystemOnly(
    DFL::Mdib::MdibChangeSet& changeSet,
    const DFL::Mdib::VmdHandle& vmd,
    const DFL::Mdib::AlertActivation& activation = DFL::Mdib::AlertActivation::On);
void appendVmdAlertSystem(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::VmdHandle& vmd);
DFL::Mdib::VmdHandle appendVmd(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::MdsHandle& mds);
DFL::Mdib::MdsHandle appendMds(DFL::Mdib::MdibChangeSet& changeSet);
void appendMdsOperation(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::MdsScoHandle& mdsSco);
void appendMdsSco(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::MdsHandle& mds);
void appendMdsAlertCondition(
    DFL::Mdib::MdibChangeSet& changeSet,
    const DFL::Mdib::MdsAlertSystemHandle& mdsAlertSystem,
    const DFL::Mdib::AlertActivation& activation = DFL::Mdib::AlertActivation::On);
void appendMdsLimitAlertCondition(
    DFL::Mdib::MdibChangeSet& changeSet,
    const DFL::Mdib::MdsAlertSystemHandle& mdsAlertSystem,
    const DFL::Mdib::AlertActivation& activation = DFL::Mdib::AlertActivation::On);
void appendMdsLimitAlertConditionWithLimits(
    DFL::Mdib::MdibChangeSet& changeSet,
    const DFL::Mdib::MdsAlertSystemHandle& mdsAlertSystem,
    const DFL::Mdib::AlertActivation& activation = DFL::Mdib::AlertActivation::Off);
void appendMdsAlertSignal(
    DFL::Mdib::MdibChangeSet& changeSet,
    const DFL::Mdib::MdsAlertSystemHandle& mdsAlertSystem,
    const DFL::Mdib::AlertActivation& activation = DFL::Mdib::AlertActivation::On);
DFL::Mdib::MdsAlertSystemHandle appendMdsAlertSystemOnly(
    DFL::Mdib::MdibChangeSet& changeSet,
    const DFL::Mdib::MdsHandle& mds,
    const DFL::Mdib::AlertActivation& activation = DFL::Mdib::AlertActivation::On);
void appendMdsAlertSystem(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::MdsHandle& mds);

inline void appendSystemContext(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::MdsHandle& mds)
{
    const auto systemContext(BaseTree::SystemContext);
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(systemContext, mds));

    const DFL::Mdib::LocationContextIndicatorHandle locationContextIndicator(BaseTree::LocationIndicator);
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(locationContextIndicator, systemContext));
    const DFL::Mdib::LocationContextHandle locationContext(BaseTree::Location);
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(locationContext, locationContextIndicator));

    const DFL::Mdib::PatientContextIndicatorHandle patientContextIndicator(BaseTree::PatientIndicator);
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(patientContextIndicator, systemContext));
    const DFL::Mdib::PatientContextHandle patientContext(BaseTree::Patient);
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(patientContext, patientContextIndicator));

    const DFL::Mdib::EnsembleContextIndicatorHandle ensembleContextIndicator(BaseTree::EnsembleIndicator);
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(ensembleContextIndicator, systemContext));
    const DFL::Mdib::EnsembleContextHandle ensembleContext(BaseTree::Ensemble);
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(ensembleContext, ensembleContextIndicator));
}

inline void appendMetric(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::ChannelHandle &channel)
{
    {
        DFL::Mdib::StringMetricDescriptorBuilder desc;
        desc.type(DFL::Mdib::CodedValueFactory::create11073cfCode("198"));
        desc.determinationPeriod(DFL::Mdib::Duration{DFL::Chrono::Seconds{30}});
        desc.lifeTimePeriod(DFL::Mdib::Duration{DFL::Chrono::Seconds{120}});
        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::StringMetric, desc, channel));
    }

    {
        const DFL::Mdib::CodedValue cv(DFL::Mdib::CodingSystem(DFL::Mdib::CodingSystemId(DFL::Mdib::Uri("csys"))), DFL::Mdib::CodeId(DFL::Locale::Utf8("cid1")), {}, {}, CodedValueTranslations{CodedValueTranslation{DFL::Mdib::CodingSystemFactory::ieee11073CodingSystem(), TestFactory::hashCodedValue(BaseTree::NumericMetric1.string()).code()}});
        DFL::Mdib::NumericMetricDescriptorBuilder const numericMetricDescrBuilder(DFL::Mdib::NumericMetricDescriptor(
            DFL::Mdib::SafetyClassification::MedicalClassB,
            cv,
            DFL::Mdib::Unit::KILO_G,
            DFL::Mdib::BodySites(),
            DFL::Mdib::MetricCategory::Measurement,
            DFL::Mdib::DerivationMethod::Automatic,
            DFL::Mdib::MetricAvailability::Continuous,
            boost::none,
            boost::none,
            DFL::Mdib::Duration{DFL::Chrono::Seconds{30}},
            DFL::Mdib::Duration{DFL::Chrono::Seconds{120}},
            boost::none,
            DFL::Mdib::Relations(),
            DFL::Mdib::Decimal(0),
            boost::none,
            DFL::Mdib::Ranges()));

        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(
            BaseTree::NumericMetric1,
            numericMetricDescrBuilder,
            channel));
    }

    {
        const DFL::Mdib::CodedValue cv(DFL::Mdib::CodingSystem(DFL::Mdib::CodingSystemId(DFL::Mdib::Uri("csys"))), DFL::Mdib::CodeId(DFL::Locale::Utf8("cid2")),  {}, {}, CodedValueTranslations{CodedValueTranslation{DFL::Mdib::CodingSystemFactory::ieee11073CodingSystem(), TestFactory::hashCodedValue(BaseTree::NumericMetric2.string()).code()}});
        DFL::Mdib::NumericMetricDescriptorBuilder const numericMetricDescrBuilder(DFL::Mdib::NumericMetricDescriptor(
            DFL::Mdib::SafetyClassification::MedicalClassB,
            cv,
            DFL::Mdib::Unit::LITER_PER_MIN,
            DFL::Mdib::BodySites(),
            DFL::Mdib::MetricCategory::Measurement,
            DFL::Mdib::DerivationMethod::Automatic,
            DFL::Mdib::MetricAvailability::Continuous,
            boost::none,
            boost::none,
            DFL::Mdib::Duration{DFL::Chrono::Seconds{30}},
            DFL::Mdib::Duration{DFL::Chrono::Seconds{120}},
            boost::none,
            DFL::Mdib::Relations(),
            DFL::Mdib::Decimal(0),
            boost::none,
            DFL::Mdib::Ranges()));

        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(
            BaseTree::NumericMetric2,
            numericMetricDescrBuilder,
            channel));
    }

    {
        const DFL::Mdib::CodedValue cv(DFL::Mdib::CodingSystem(DFL::Mdib::CodingSystemId(DFL::Mdib::Uri("csys"))), DFL::Mdib::CodeId(DFL::Locale::Utf8("cid3")),  {}, {}, CodedValueTranslations{CodedValueTranslation{DFL::Mdib::CodingSystemFactory::ieee11073CodingSystem(), TestFactory::hashCodedValue(BaseTree::NumericMetric3.string()).code()}});
        DFL::Mdib::NumericMetricDescriptorBuilder const numericMetricDescrBuilder(DFL::Mdib::NumericMetricDescriptor(
            DFL::Mdib::SafetyClassification::MedicalClassB,
            cv,
            DFL::Mdib::Unit::KILO_G,
            DFL::Mdib::BodySites(),
            DFL::Mdib::MetricCategory::Calculation,
            DFL::Mdib::DerivationMethod::Automatic,
            DFL::Mdib::MetricAvailability::Continuous,
            boost::none,
            boost::none,
            DFL::Mdib::Duration{DFL::Chrono::Seconds{30}},
            DFL::Mdib::Duration{DFL::Chrono::Seconds{120}},
            boost::none,
            DFL::Mdib::Relations(),
            DFL::Mdib::Decimal(0),
            boost::none,
            DFL::Mdib::Ranges()));

        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(
            BaseTree::NumericMetric3,
            numericMetricDescrBuilder,
            channel));
    }

    {
        AllowedEnumValues const allowedValues{
            {DFL::Locale::Utf8("⭐")},
            {DFL::Locale::Utf8("⭐⭐")},
            {DFL::Locale::Utf8("⭐⭐⭐")},
            {DFL::Locale::Utf8("⭐⭐⭐⭐")},
            {DFL::Locale::Utf8("⭐⭐⭐⭐⭐")},
        };

        const DFL::Mdib::CodedValue cv(DFL::Mdib::CodingSystem(DFL::Mdib::CodingSystemId(DFL::Mdib::Uri("CustomCodingSystem"))), DFL::Mdib::CodeId(DFL::Locale::Utf8("EnumCode")),  {}, {}, CodedValueTranslations{CodedValueTranslation{DFL::Mdib::CodingSystemFactory::ieee11073CodingSystem(), TestFactory::hashCodedValue(BaseTree::EnumStringMetric.string()).code()}});
        EnumStringMetricDescriptorBuilder const dBuilder(EnumStringMetricDescriptor(
                    DFL::Mdib::SafetyClassification::MedicalClassB,
                    cv,
                    DFL::Mdib::Unit::DIMLESS,
                    DFL::Mdib::BodySites(),
                    DFL::Mdib::MetricCategory::Calculation,
                    DFL::Mdib::DerivationMethod::Automatic,
                    DFL::Mdib::MetricAvailability::Continuous,
                    boost::none,
                    boost::none,
                    DFL::Mdib::Duration{DFL::Chrono::Seconds{30}},
                    DFL::Mdib::Duration{DFL::Chrono::Seconds{120}},
                    boost::none,
                    DFL::Mdib::Relations(),
                    allowedValues));

        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(
            BaseTree::EnumStringMetric,
            dBuilder,
            channel));

    }
}

inline void appendMetric2(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::ChannelHandle &channel)
{
    {
        DFL::Mdib::NumericMetricDescriptorBuilder const numericMetricDescrBuilder(DFL::Mdib::NumericMetricDescriptor(
            DFL::Mdib::SafetyClassification::MedicalClassB,
            DFL::Mdib::CodedValueFactory::create11073cfCode("401"),
            DFL::Mdib::Unit::KILO_G,
            DFL::Mdib::BodySites(),
            DFL::Mdib::MetricCategory::Measurement,
            DFL::Mdib::DerivationMethod::Automatic,
            DFL::Mdib::MetricAvailability::Continuous,
            boost::none,
            boost::none,
            DFL::Mdib::Duration{DFL::Chrono::Seconds{30}},
            DFL::Mdib::Duration{DFL::Chrono::Seconds{120}},
            boost::none,
            DFL::Mdib::Relations(),
            DFL::Mdib::Decimal(0),
            boost::none,
            DFL::Mdib::Ranges()));

        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(
            BaseTree::NumericMetricCh2_1,
            numericMetricDescrBuilder,
            channel));
    }
    {
        DFL::Mdib::NumericMetricDescriptorBuilder const numericMetricDescrBuilder(DFL::Mdib::NumericMetricDescriptor(
            DFL::Mdib::SafetyClassification::MedicalClassB,
            DFL::Mdib::CodedValueFactory::create11073cfCode("402"),
            DFL::Mdib::Unit::KILO_G,
            DFL::Mdib::BodySites(),
            DFL::Mdib::MetricCategory::Calculation,
            DFL::Mdib::DerivationMethod::Automatic,
            DFL::Mdib::MetricAvailability::Continuous,
            boost::none,
            boost::none,
            DFL::Mdib::Duration{DFL::Chrono::Seconds{30}},
            DFL::Mdib::Duration{DFL::Chrono::Seconds{120}},
            boost::none,
            DFL::Mdib::Relations(),
            DFL::Mdib::Decimal(0),
            boost::none,
            DFL::Mdib::Ranges()));
        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(
            BaseTree::NumericMetricCh2_2,
            numericMetricDescrBuilder,
            channel));
    }
    {
        DFL::Mdib::NumericMetricDescriptorBuilder const numericMetricDescrBuilder(DFL::Mdib::NumericMetricDescriptor(
            DFL::Mdib::SafetyClassification::MedicalClassB,
            DFL::Mdib::CodedValueFactory::create11073cfCode("403"),
            DFL::Mdib::Unit::KILO_G,
            DFL::Mdib::BodySites(),
            DFL::Mdib::MetricCategory::Measurement,
            DFL::Mdib::DerivationMethod::Automatic,
            DFL::Mdib::MetricAvailability::Continuous,
            boost::none,
            boost::none,
            DFL::Mdib::Duration{DFL::Chrono::Seconds{30}},
            DFL::Mdib::Duration{DFL::Chrono::Seconds{120}},
            boost::none,
            DFL::Mdib::Relations(),
            DFL::Mdib::Decimal(0),
            boost::none,
            DFL::Mdib::Ranges()
            ));

        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::NumericMetricCh2_3,
            numericMetricDescrBuilder,
            channel));
    }
    {
        DFL::Mdib::NumericMetricDescriptorBuilder const numericMetricDescrBuilder(DFL::Mdib::NumericMetricDescriptor(
            DFL::Mdib::SafetyClassification::MedicalClassB,
            DFL::Mdib::CodedValueFactory::create11073cfCode("404"),
            DFL::Mdib::Unit::KILO_G,
            DFL::Mdib::BodySites(),
            DFL::Mdib::MetricCategory::Measurement,
            DFL::Mdib::DerivationMethod::Automatic,
            DFL::Mdib::MetricAvailability::Continuous,
            boost::none,
            boost::none,
            DFL::Mdib::Duration{DFL::Chrono::Seconds{30}},
            DFL::Mdib::Duration{DFL::Chrono::Seconds{120}},
            boost::none,
            DFL::Mdib::Relations(),
            DFL::Mdib::Decimal(0),
            boost::none,
            DFL::Mdib::Ranges()
            ));

        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(
            BaseTree::NumericMetricCh2_4,
            numericMetricDescrBuilder,
            channel));
    }
    {
        DFL::Mdib::NumericMetricDescriptorBuilder const numericMetricDescrBuilder(DFL::Mdib::NumericMetricDescriptor(
            DFL::Mdib::SafetyClassification::MedicalClassB,
            DFL::Mdib::CodedValueFactory::create11073cfCode("405"),
            DFL::Mdib::Unit::KILO_G,
            DFL::Mdib::BodySites(),
            DFL::Mdib::MetricCategory::Measurement,
            DFL::Mdib::DerivationMethod::Automatic,
            DFL::Mdib::MetricAvailability::Continuous,
            boost::none,
            boost::none,
            DFL::Mdib::Duration{DFL::Chrono::Seconds{30}},
            DFL::Mdib::Duration{DFL::Chrono::Seconds{120}},
            boost::none,
            DFL::Mdib::Relations(),
            DFL::Mdib::Decimal(0),
            boost::none,
            DFL::Mdib::Ranges()
            ));

        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(
            BaseTree::NumericMetricCh2_5,
            numericMetricDescrBuilder,
            channel));
    }
}

inline void appendRTS(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::ChannelHandle &channel)
{
    DFL::Mdib::RealTimeSampleArrayMetricDescriptorBuilder rtsaMetricDescrBuilder(DFL::Mdib::RealTimeSampleArrayMetricDescriptor(
        DFL::Mdib::SafetyClassification::MedicalClassB,
        DFL::Mdib::CodedValueFactory::create11073cfCode("501"),
        DFL::Mdib::Unit::CENTI_M,
        DFL::Mdib::BodySites(),
        DFL::Mdib::MetricCategory::Measurement,
        DFL::Mdib::DerivationMethod::Automatic,
        DFL::Mdib::MetricAvailability::Continuous,
        boost::none,
        boost::none,
        DFL::Mdib::Duration{DFL::Chrono::Seconds{30}},
        DFL::Mdib::Duration{DFL::Chrono::Seconds{120}},
        boost::none,
        DFL::Mdib::Relations(),
        DFL::Mdib::Decimal(0),
        DFL::Chrono::Microseconds(10),
        DFL::Mdib::Ranges()
        ));

    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(
        BaseTree::RealTimeSampleArrayMetric1,
        rtsaMetricDescrBuilder,
        channel));

    rtsaMetricDescrBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("502"));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(
        BaseTree::RealTimeSampleArrayMetric2,
        rtsaMetricDescrBuilder,
        channel));

    rtsaMetricDescrBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("503"));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(
        BaseTree::RealTimeSampleArrayMetric3,
        rtsaMetricDescrBuilder,
        channel));

    rtsaMetricDescrBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("504"));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(
        BaseTree::RealTimeSampleArrayMetric4,
        rtsaMetricDescrBuilder,
        channel));

    rtsaMetricDescrBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("505"));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(
        BaseTree::RealTimeSampleArrayMetric5,
        rtsaMetricDescrBuilder,
        channel));
    {
        DistributionSampleArrayMetricDescriptorBuilder desc;
        desc.type(DFL::Mdib::CodedValueFactory::create11073cfCode("506"));
        desc.determinationPeriod(DFL::Mdib::Duration{DFL::Chrono::Milliseconds{10}});
        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(
                BaseTree::DistributionSampleArrayMetric1, desc, channel));
    }
}


inline void appendChannel(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::VmdHandle& vmd)
{
    {
        const auto channel(BaseTree::Channel);
        DFL::Mdib::ChannelDescriptorBuilder desc;
        desc.type(DFL::Mdib::CodedValueFactory::create11073cfCode("199"));
        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(channel, desc, vmd));

        appendMetric(changeSet, channel);
    }
    {
        DFL::Mdib::ChannelDescriptorBuilder const channelDescrBuilder(DFL::Mdib::ChannelDescriptor(
            DFL::Mdib::SafetyClassification::MedicalClassB,
            DFL::Mdib::CodedValueFactory::create11073cfCode("300"),
            DFL::Mdib::ProductionSpecifications()));


        const DFL::Mdib::ChannelHandle channel(BaseTree::Channel2);
        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(
            channel,
            channelDescrBuilder,
            vmd));

        appendMetric2(changeSet, channel);
        appendRTS(changeSet, channel);
    }
}

inline void appendVmdOperation(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::VmdScoHandle& vmdSco)
{
    ActivateOperationDescriptorBuilder activateOperationDescriptorBuilder;
    activateOperationDescriptorBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("650"));
    activateOperationDescriptorBuilder.safetyClassification(DFL::Mdib::SafetyClassification::MedicalClassC);
    activateOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::Vmd));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::VmdActivateOperation, activateOperationDescriptorBuilder, vmdSco));

    SetStringOperationDescriptorBuilder setStringOperationDescriptorBuilder;
    setStringOperationDescriptorBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("651"));
    setStringOperationDescriptorBuilder.safetyClassification(DFL::Mdib::SafetyClassification::MedicalClassC);
    setStringOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::StringMetric));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::VmdSetStringOperation, setStringOperationDescriptorBuilder, vmdSco));

    SetValueOperationDescriptorBuilder setValueOperationDescriptorBuilder;
    setValueOperationDescriptorBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("652"));
    setValueOperationDescriptorBuilder.safetyClassification(DFL::Mdib::SafetyClassification::MedicalClassC);
    setValueOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::NumericMetric1));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::VmdSetValueOperation, setValueOperationDescriptorBuilder, vmdSco));

    SetContextStateOperationDescriptorBuilder setContextStateOperationDescriptorBuilder;
    setContextStateOperationDescriptorBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("653"));
    setContextStateOperationDescriptorBuilder.safetyClassification(DFL::Mdib::SafetyClassification::MedicalClassC);
    setContextStateOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::PatientIndicator));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::VmdSetPatientContextStateOperation, setContextStateOperationDescriptorBuilder, vmdSco));

    SetAlertStateOperationDescriptorBuilder setAlertStateOperationDescriptorBuilder;
    setAlertStateOperationDescriptorBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("654"));
    setAlertStateOperationDescriptorBuilder.safetyClassification(DFL::Mdib::SafetyClassification::MedicalClassC);
    setAlertStateOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::VmdAlertSystem));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::VmdSetAlertSystemStateOperation, setAlertStateOperationDescriptorBuilder, vmdSco));

    setAlertStateOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::VmdAlertCondition1));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::VmdSetAlertConditionStateOperation, setAlertStateOperationDescriptorBuilder, vmdSco));

    setAlertStateOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::VmdLimitAlertCondition1));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::VmdSetLimitAlertConditionStateOperation, setAlertStateOperationDescriptorBuilder, vmdSco));

    setAlertStateOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::VmdAlertSignal1));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::VmdSetAlertSignalStateOperation, setAlertStateOperationDescriptorBuilder, vmdSco));

    SetComponentStateOperationDescriptorBuilder setComponentStateOperationDescriptorBuilder;
    setComponentStateOperationDescriptorBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("655"));
    setComponentStateOperationDescriptorBuilder.safetyClassification(DFL::Mdib::SafetyClassification::MedicalClassC);
    setComponentStateOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::Vmd));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::VmdSetComponentStateOperation, setComponentStateOperationDescriptorBuilder, vmdSco));

    SetMetricStateOperationDescriptorBuilder setMetricStateOperationDescriptorBuilder;
    setMetricStateOperationDescriptorBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("656"));
    setMetricStateOperationDescriptorBuilder.safetyClassification(DFL::Mdib::SafetyClassification::MedicalClassC);
    setMetricStateOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::Vmd));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::VmdSetMetricStateOperation, setMetricStateOperationDescriptorBuilder, vmdSco));

    SetStringOperationDescriptorBuilder setEnumStringOperationDescriptorBuilder;
    SetStringOperationStateBuilder setEnumStringOperationStateBuilder;
    setEnumStringOperationDescriptorBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("657"));
    setEnumStringOperationDescriptorBuilder.safetyClassification(DFL::Mdib::SafetyClassification::MedicalClassC);
    setEnumStringOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::EnumStringMetric));
    AllowedStringValues const allowedValues{
        {AllowedStringValue(DFL::Locale::Utf8("⭐"))},
        {AllowedStringValue(DFL::Locale::Utf8("⭐⭐"))},
        {AllowedStringValue(DFL::Locale::Utf8("⭐⭐⭐"))},
        {AllowedStringValue(DFL::Locale::Utf8("⭐⭐⭐⭐"))},
        {AllowedStringValue(DFL::Locale::Utf8("⭐⭐⭐⭐⭐"))},
    };
    setEnumStringOperationStateBuilder.allowedValues(allowedValues);
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::VmdSetEnumStringOperation, setEnumStringOperationDescriptorBuilder, setEnumStringOperationStateBuilder, vmdSco));

/*
    SetMetricStateOperationDescriptorBuilder msBuilder;
    msBuilder.operationTarget(BaseTree::Vmd);
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::VmdSetNumericMetricStateOperation, msBuilder, vmdSco));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::VmdSetStringMetricStateOperation, msBuilder, vmdSco));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::VmdSetEnumStringMetricStateOperation, msBuilder, vmdSco));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::VmdSetRtsaMetricStateOperation, msBuilder, vmdSco));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::VmdSetDsaMetricStateOperation, msBuilder, vmdSco));
*/


}

inline void appendVmdSco(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::VmdHandle& vmd)
{
    const DFL::Mdib::VmdScoHandle vmdSco(BaseTree::VmdSco);
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(vmdSco, vmd));

    appendVmdOperation(changeSet, vmdSco);
}

inline void appendVmdAlertCondition(
    DFL::Mdib::MdibChangeSet& changeSet,
    const DFL::Mdib::VmdAlertSystemHandle& vmdAlertSystem,
    const DFL::Mdib::AlertActivation& activation)
{
    {
        DFL::Mdib::Handles sources;
        sources.push_back(toHandle(BaseTree::RealTimeSampleArrayMetric2));

        DFL::Mdib::AlertConditionDescriptorBuilder const alertConditionDescrBuilder(DFL::Mdib::AlertConditionDescriptor(
            DFL::Mdib::SafetyClassification::MedicalClassB,
            DFL::Mdib::CodedValueFactory::create11073cfCode("23456"),
            DFL::Mdib::AlertConditionKind::Technical,
            DFL::Mdib::AlertConditionPriority::Medium,
            DFL::Mdib::Duration(),
            boost::none,
            boost::none,
            sources,
            DFL::Mdib::CauseInfos()
            ));

        DFL::Mdib::AlertConditionStateBuilder const alertConditionStateBuilder(DFL::Mdib::AlertConditionState(
            activation,
            boost::none,
            boost::none,
            boost::none,
            DFL::Mdib::AlertConditionPresence::NotPresent,
            boost::none
            ));

        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(
            BaseTree::VmdAlertCondition1,
            alertConditionDescrBuilder,
            alertConditionStateBuilder,
            vmdAlertSystem));
    }
    {
        DFL::Mdib::AlertConditionStateBuilder alertConditionStateBuilder;
        alertConditionStateBuilder.activationState(activation);
        alertConditionStateBuilder.presence(DFL::Mdib::AlertConditionPresence::NotPresent);
        AlertConditionDescriptorBuilder desc;
        desc.type(DFL::Mdib::CodedValueFactory::create11073cfCode("657"));
        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::VmdAlertCondition2, desc, alertConditionStateBuilder, vmdAlertSystem));
    }
}

inline void appendVmdLimitAlertCondition(
    DFL::Mdib::MdibChangeSet& changeSet,
    const DFL::Mdib::VmdAlertSystemHandle& vmdAlertSystem,
    const DFL::Mdib::AlertActivation& activation)
{
    {
        DFL::Mdib::Handles sources;
        sources.push_back(DFL::Mdib::Handle("Non-existing-condition-source"));

        DFL::Mdib::LimitAlertConditionDescriptorBuilder const limitAlertConditionDescrBuilder1(DFL::Mdib::LimitAlertConditionDescriptor(
            DFL::Mdib::SafetyClassification::MedicalClassB,
            DFL::Mdib::CodedValueFactory::create11073cfCode("234"),
            DFL::Mdib::AlertConditionKind::Technical,
            DFL::Mdib::AlertConditionPriority::Medium,
            DFL::Mdib::Duration(),
            boost::none,
            boost::none,
            sources,
            DFL::Mdib::CauseInfos(),
            false,
            boost::none));

        DFL::Mdib::LimitAlertConditionStateBuilder const limitAlertConditionStateBuilder1(DFL::Mdib::LimitAlertConditionState(
            activation,
            boost::none,
            boost::none,
            boost::none,
            DFL::Mdib::AlertConditionPresence::NotPresent,
            boost::none,
            boost::none,
            DFL::Mdib::AlertConditionMonitoredLimits::All,
            DFL::Mdib::Range()));

        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::VmdLimitAlertCondition1,
            limitAlertConditionDescrBuilder1,
            limitAlertConditionStateBuilder1,
            vmdAlertSystem));
    }
}

inline void appendVmdLimitAlertConditionWithLimits(
    DFL::Mdib::MdibChangeSet& changeSet,
    const DFL::Mdib::VmdAlertSystemHandle& vmdAlertSystem,
    const DFL::Mdib::AlertActivation& activation)
{
    {
        DFL::Mdib::Handles sources;
        sources.push_back(DFL::Mdib::Handle("Non-existing-condition-source"));

        DFL::Mdib::LimitAlertConditionDescriptorBuilder const limitAlertConditionDescrBuilder3(DFL::Mdib::LimitAlertConditionDescriptor(
            DFL::Mdib::SafetyClassification::MedicalClassB,
            DFL::Mdib::CodedValueFactory::create11073cfCode("196650"), // MDC_EVT_HI_GT_LIM
            DFL::Mdib::AlertConditionKind::Physiological,
            DFL::Mdib::AlertConditionPriority::Medium,
            DFL::Mdib::Duration(),
            boost::none,
            boost::none,
            sources,
            DFL::Mdib::CauseInfos(),
            false,
            boost::none));

        DFL::Mdib::LimitAlertConditionStateBuilder const limitAlertConditionStateBuilder3(DFL::Mdib::LimitAlertConditionState(
            activation,
            boost::none,
            boost::none,
            boost::none,
            DFL::Mdib::AlertConditionPresence::NotPresent,
            boost::none,
            boost::none,
            DFL::Mdib::AlertConditionMonitoredLimits::All,
            DFL::Mdib::Range(boost::none, DFL::Mdib::Decimal(99,0))
        ));

        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::VmdLimitAlertCondition3,
            limitAlertConditionDescrBuilder3,
            limitAlertConditionStateBuilder3,
            vmdAlertSystem));

        DFL::Mdib::LimitAlertConditionDescriptorBuilder const limitAlertConditionDescrBuilder4(DFL::Mdib::LimitAlertConditionDescriptor(
            DFL::Mdib::SafetyClassification::MedicalClassB,
            DFL::Mdib::CodedValueFactory::create11073cfCode("196672"),
            DFL::Mdib::AlertConditionKind::Technical,
            DFL::Mdib::AlertConditionPriority::Medium,
            DFL::Mdib::Duration(),
            boost::none,
            boost::none,
            sources,
            DFL::Mdib::CauseInfos(),
            false,
            boost::none));

        DFL::Mdib::LimitAlertConditionStateBuilder const limitAlertConditionStateBuilder4(DFL::Mdib::LimitAlertConditionState(
            activation,
            boost::none,
            boost::none,
            boost::none,
            DFL::Mdib::AlertConditionPresence::NotPresent,
            boost::none,
            boost::none,
            DFL::Mdib::AlertConditionMonitoredLimits::All,
            DFL::Mdib::Range(DFL::Mdib::Decimal(9,0), boost::none)
        ));

        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::VmdLimitAlertCondition4,
            limitAlertConditionDescrBuilder4,
            limitAlertConditionStateBuilder4,
            vmdAlertSystem));

        DFL::Mdib::LimitAlertConditionDescriptorBuilder const limitAlertConditionDescrBuilder5(DFL::Mdib::LimitAlertConditionDescriptor(
            DFL::Mdib::SafetyClassification::MedicalClassB,
            DFL::Mdib::CodedValueFactory::create11073cfCode("199854"),
            DFL::Mdib::AlertConditionKind::Technical,
            DFL::Mdib::AlertConditionPriority::Medium,
            DFL::Mdib::Duration(),
            boost::none,
            boost::none,
            sources,
            DFL::Mdib::CauseInfos(),
            false,
            boost::none));

        DFL::Mdib::LimitAlertConditionStateBuilder const limitAlertConditionStateBuilder5(DFL::Mdib::LimitAlertConditionState(
            activation,
            boost::none,
            boost::none,
            boost::none,
            DFL::Mdib::AlertConditionPresence::NotPresent,
            boost::none,
            boost::none,
            DFL::Mdib::AlertConditionMonitoredLimits::All,
            DFL::Mdib::Range(DFL::Mdib::Decimal(9,0), boost::none)
        ));

        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::VmdLimitAlertCondition5,
            limitAlertConditionDescrBuilder4,
            limitAlertConditionStateBuilder4,
            vmdAlertSystem));

    }
}

inline void appendVmdAlertSignal(
    DFL::Mdib::MdibChangeSet& changeSet,
    const DFL::Mdib::VmdAlertSystemHandle& vmdAlertSystem,
    const DFL::Mdib::AlertActivation& activation)
{

    {
        auto entity = DFL::Mdib::EntityFactory::create(BaseTree::VmdAlertSignal1, vmdAlertSystem);
        auto alertSignalDescr = entity->descriptor();
        auto alertSignalDescrBuilder = DFL::Mdib::getBuilder(alertSignalDescr);

        auto alertSignalState = entity->state();
        auto alertSignalStateBuilder = DFL::Mdib::getBuilder(alertSignalState);
        alertSignalStateBuilder.activationState(activation);

        alertSignalDescrBuilder.conditionSignaledHandle(toHandle(BaseTree::VmdAlertCondition1));
        alertSignalDescrBuilder.manifestation(DFL::Mdib::AlertSignalManifestation::Visible);
        alertSignalDescrBuilder.latching(DFL::Mdib::Latching::NonLatchingSignal);
        alertSignalDescrBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("65432"));
        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(entity->handle(), alertSignalDescrBuilder, alertSignalStateBuilder, entity->parent()));
    }
    {
        auto entity = DFL::Mdib::EntityFactory::create(BaseTree::VmdAlertSignal2, vmdAlertSystem);
        auto desc = entity->descriptor();
        auto descBuilder = DFL::Mdib::getBuilder(desc);

        auto state = entity->state();
        auto stateBuilder = DFL::Mdib::getBuilder(state);
        stateBuilder.activationState(activation);

        descBuilder.conditionSignaledHandle(toHandle(BaseTree::VmdLimitAlertCondition1));
        descBuilder.manifestation(DFL::Mdib::AlertSignalManifestation::Visible);
        descBuilder.latching(DFL::Mdib::Latching::LatchingSignal);
        descBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("654"));
        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(entity->handle(), descBuilder, stateBuilder, entity->parent()));
    }
}

inline DFL::Mdib::VmdAlertSystemHandle appendVmdAlertSystemOnly(
    DFL::Mdib::MdibChangeSet& changeSet,
    const DFL::Mdib::VmdHandle& vmd,
    const DFL::Mdib::AlertActivation& activation)
{
    DFL::Mdib::AlertSystemDescriptorBuilder const alertSystemDescrBuilder(DFL::Mdib::AlertSystemDescriptor(
        DFL::Mdib::SafetyClassification::MedicalClassA,
        DFL::Mdib::CodedValueFactory::create11073cfCode("33355"),
        boost::none,
        boost::none,
        boost::none));
    DFL::Mdib::AlertSystemStateBuilder alertSystemStateBuilder;
    alertSystemStateBuilder.activationState(activation);

    DFL::Mdib::VmdAlertSystemHandle vmdAlertSystem(BaseTree::VmdAlertSystem);
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(vmdAlertSystem, alertSystemDescrBuilder, alertSystemStateBuilder, vmd));

    return vmdAlertSystem;
}

inline void appendVmdAlertSystem(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::VmdHandle& vmd)
{
    auto vmdAlertSystem = appendVmdAlertSystemOnly(changeSet, vmd);
    appendVmdAlertCondition(changeSet, vmdAlertSystem);
    appendVmdLimitAlertCondition(changeSet, vmdAlertSystem);
    appendVmdAlertSignal(changeSet, vmdAlertSystem);
}

inline DFL::Mdib::VmdHandle appendVmd(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::MdsHandle& mds)
{
    DFL::Mdib::VmdDescriptorBuilder const vmdDescrBuilder(DFL::Mdib::VmdDescriptor(
        DFL::Mdib::SafetyClassification::MedicalClassB,
        DFL::Mdib::CodedValueFactory::create11073cfCode("200"),
        DFL::Mdib::ProductionSpecifications(),
        DFL::Mdib::InstanceIdentifiers()));

    DFL::Mdib::VmdHandle vmd(BaseTree::Vmd);
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::Vmd, vmdDescrBuilder, mds));

    appendChannel(changeSet, vmd);

    return vmd;
}

inline DFL::Mdib::MdsHandle appendMds(DFL::Mdib::MdibChangeSet& changeSet)
{
    DFL::Mdib::MdsHandle mds(BaseTree::Mds);

    DFL::Mdib::MdsDescriptorBuilder const mdsDescrBuilder(DFL::Mdib::MdsDescriptor(
        DFL::Mdib::SafetyClassification::MedicalClassB,
        DFL::Mdib::CodedValueFactory::create11073cfCode("100"),
        DFL::Mdib::ProductionSpecifications(),
        boost::none,
        DFL::Mdib::InstanceIdentifiers()));

    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(mds, mdsDescrBuilder));

    return mds;
}

inline void appendMdsOperation(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::MdsScoHandle& mdsSco)
{
    ActivateOperationDescriptorBuilder activateOperationDescriptorBuilder;
    activateOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::Mds));
    activateOperationDescriptorBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("600"));
    activateOperationDescriptorBuilder.safetyClassification(DFL::Mdib::SafetyClassification::MedicalClassA);
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::MdsActivateOperation, activateOperationDescriptorBuilder, mdsSco));

    SetStringOperationDescriptorBuilder setStringOperationDescriptorBuilder;
    setStringOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::StringMetric));
    setStringOperationDescriptorBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("601"));
    setStringOperationDescriptorBuilder.safetyClassification(DFL::Mdib::SafetyClassification::MedicalClassA);
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::MdsSetStringOperation, setStringOperationDescriptorBuilder, mdsSco));

    SetValueOperationDescriptorBuilder setValueOperationDescriptorBuilder;
    setValueOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::NumericMetric1));
    setValueOperationDescriptorBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("602"));
    setValueOperationDescriptorBuilder.safetyClassification(DFL::Mdib::SafetyClassification::MedicalClassA);
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::MdsSetValueOperation, setValueOperationDescriptorBuilder, mdsSco));

    SetContextStateOperationDescriptorBuilder setContextStateOperationDescriptorBuilder;
    setContextStateOperationDescriptorBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("603"));
    setContextStateOperationDescriptorBuilder.safetyClassification(DFL::Mdib::SafetyClassification::MedicalClassA);
    setContextStateOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::PatientIndicator));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::MdsSetPatientContextStateOperation, setContextStateOperationDescriptorBuilder, mdsSco));

    setContextStateOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::LocationIndicator));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::MdsSetLocationContextStateOperation, setContextStateOperationDescriptorBuilder, mdsSco));

    setContextStateOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::EnsembleIndicator));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::MdsSetEnsembleContextStateOperation, setContextStateOperationDescriptorBuilder, mdsSco));

    SetAlertStateOperationDescriptorBuilder setAlertStateOperationDescriptorBuilder;
    setAlertStateOperationDescriptorBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("604"));
    setAlertStateOperationDescriptorBuilder.safetyClassification(DFL::Mdib::SafetyClassification::MedicalClassA);
    setAlertStateOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::MdsAlertSystem));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::MdsSetAlertSystemStateOperation, setAlertStateOperationDescriptorBuilder, mdsSco));

    setAlertStateOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::MdsAlertCondition1));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::MdsSetAlertConditionStateOperation, setAlertStateOperationDescriptorBuilder, mdsSco));

    setAlertStateOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::MdsLimitAlertCondition1));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::MdsSetLimitAlertConditionStateOperation, setAlertStateOperationDescriptorBuilder, mdsSco));

    setAlertStateOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::MdsAlertSignal1));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::MdsSetAlertSignalStateOperation, setAlertStateOperationDescriptorBuilder, mdsSco));

    SetComponentStateOperationDescriptorBuilder setComponentStateOperationDescriptorBuilder;
    setComponentStateOperationDescriptorBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("605"));
    setComponentStateOperationDescriptorBuilder.safetyClassification(DFL::Mdib::SafetyClassification::MedicalClassA);
    setComponentStateOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::Mds));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::MdsSetComponentStateOperation, setComponentStateOperationDescriptorBuilder, mdsSco));

    SetMetricStateOperationDescriptorBuilder setMetricStateOperationDescriptorBuilder;
    setMetricStateOperationDescriptorBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("606"));
    setMetricStateOperationDescriptorBuilder.safetyClassification(DFL::Mdib::SafetyClassification::MedicalClassA);
    setMetricStateOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::Mds));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::MdsSetMetricStateOperation, setMetricStateOperationDescriptorBuilder, mdsSco));

    SetStringOperationDescriptorBuilder setEnumStringOperationDescriptorBuilder;
    SetStringOperationStateBuilder setEnumStringOperationStateBuilder;
    setEnumStringOperationDescriptorBuilder.operationTarget(toHandle(BaseTree::EnumStringMetric));
    setEnumStringOperationDescriptorBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("607"));
    setEnumStringOperationDescriptorBuilder.safetyClassification(DFL::Mdib::SafetyClassification::MedicalClassA);
    AllowedStringValues const allowedValues{
        {AllowedStringValue(DFL::Locale::Utf8("⭐"))},
        {AllowedStringValue(DFL::Locale::Utf8("⭐⭐"))},
        {AllowedStringValue(DFL::Locale::Utf8("⭐⭐⭐"))},
        {AllowedStringValue(DFL::Locale::Utf8("⭐⭐⭐⭐"))},
        {AllowedStringValue(DFL::Locale::Utf8("⭐⭐⭐⭐⭐"))},
    };
    setEnumStringOperationStateBuilder.allowedValues(allowedValues);
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::MdsSetEnumStringOperation, setEnumStringOperationDescriptorBuilder, setEnumStringOperationStateBuilder, mdsSco));

/*
    SetMetricStateOperationDescriptorBuilder msBuilder;
    msBuilder.operationTarget(BaseTree::Mds);
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::MdsSetNumericMetricStateOperation, msBuilder, mdsSco));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::MdsSetStringMetricStateOperation, msBuilder, mdsSco));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::MdsSetEnumStringMetricStateOperation, msBuilder, mdsSco));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::MdsSetRtsaMetricStateOperation, msBuilder, mdsSco));
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::MdsSetDsaMetricStateOperation, msBuilder, mdsSco));
*/

}

inline void appendMdsSco(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::MdsHandle& mds)
{
    const DFL::Mdib::MdsScoHandle mdsSco(BaseTree::MdsSco);
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(mdsSco, mds));

    appendMdsOperation(changeSet, mdsSco);
}

inline void appendMdsAlertCondition(
    DFL::Mdib::MdibChangeSet& changeSet,
    const DFL::Mdib::MdsAlertSystemHandle& mdsAlertSystem,
    const DFL::Mdib::AlertActivation& activation)
{
    {
        DFL::Mdib::Handles sources;
        sources.push_back(toHandle(BaseTree::NumericMetricCh2_1));

        DFL::Mdib::AlertConditionDescriptorBuilder const alertConditionDescrBuilder(DFL::Mdib::AlertConditionDescriptor(
            DFL::Mdib::SafetyClassification::MedicalClassB,
            DFL::Mdib::CodedValueFactory::create11073cfCode("12345"),
            DFL::Mdib::AlertConditionKind::Physiological,
            DFL::Mdib::AlertConditionPriority::Low,
            DFL::Mdib::Duration(),
            boost::none,
            boost::none,
            sources,
            DFL::Mdib::CauseInfos()
            ));

        DFL::Mdib::AlertConditionStateBuilder const alertConditionStateBuilder(DFL::Mdib::AlertConditionState(
            activation,
            boost::none,
            boost::none,
            boost::none,
            DFL::Mdib::AlertConditionPresence::NotPresent,
            boost::none
            ));

        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(
            BaseTree::MdsAlertCondition1,
            alertConditionDescrBuilder,
            alertConditionStateBuilder,
            mdsAlertSystem));
    }
    {
        DFL::Mdib::AlertConditionStateBuilder alertConditionStateBuilder;
        alertConditionStateBuilder.activationState(activation);
        alertConditionStateBuilder.presence(DFL::Mdib::AlertConditionPresence::NotPresent);
        AlertConditionDescriptorBuilder desc;
        desc.type(DFL::Mdib::CodedValueFactory::create11073cfCode("206"));
        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(BaseTree::MdsAlertCondition2, desc, alertConditionStateBuilder, mdsAlertSystem));
    }
}

inline void appendMdsLimitAlertCondition(
    DFL::Mdib::MdibChangeSet& changeSet,
    const DFL::Mdib::MdsAlertSystemHandle& mdsAlertSystem,
    const DFL::Mdib::AlertActivation& activation)
{
    {
        DFL::Mdib::Handles sources;
        sources.push_back(toHandle(BaseTree::NumericMetricCh2_2));

        DFL::Mdib::LimitAlertConditionDescriptorBuilder const limitAlertConditionDescrBuilder(DFL::Mdib::LimitAlertConditionDescriptor(
            DFL::Mdib::SafetyClassification::MedicalClassB,
            DFL::Mdib::CodedValueFactory::create11073cfCode("123"),
            DFL::Mdib::AlertConditionKind::Physiological,
            DFL::Mdib::AlertConditionPriority::Low,
            DFL::Mdib::Duration(),
            boost::none,
            boost::none,
            sources,
            DFL::Mdib::CauseInfos(),
            false,
            boost::none
            ));

        DFL::Mdib::LimitAlertConditionStateBuilder const limitAlertConditionStateBuilder(DFL::Mdib::LimitAlertConditionState(
            activation,
            boost::none,
            boost::none,
            boost::none,
            DFL::Mdib::AlertConditionPresence::NotPresent,
            boost::none,
            boost::none,
            DFL::Mdib::AlertConditionMonitoredLimits::All,
            DFL::Mdib::Range()
            ));

        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(
            BaseTree::MdsLimitAlertCondition1,
            limitAlertConditionDescrBuilder,
            limitAlertConditionStateBuilder,
            mdsAlertSystem));
    }
}

inline void appendMdsLimitAlertConditionWithLimits(
    DFL::Mdib::MdibChangeSet& changeSet,
    const DFL::Mdib::MdsAlertSystemHandle& mdsAlertSystem,
    const DFL::Mdib::AlertActivation& activation)
{
    {
        DFL::Mdib::Handles sources;
        sources.push_back(toHandle(BaseTree::NumericMetricCh2_2));

        DFL::Mdib::LimitAlertConditionDescriptorBuilder const limitAlertConditionDescrBuilder3(DFL::Mdib::LimitAlertConditionDescriptor(
            DFL::Mdib::SafetyClassification::MedicalClassB,
            DFL::Mdib::CodedValueFactory::create11073cfCode("196650"), // 11073 code MDC_EVT_HI_GT_LIM
            DFL::Mdib::AlertConditionKind::Physiological,
            DFL::Mdib::AlertConditionPriority::Low,
            DFL::Mdib::Duration(),
            boost::none,
            boost::none,
            sources,
            DFL::Mdib::CauseInfos(),
            false,
            boost::none
            ));

        DFL::Mdib::LimitAlertConditionStateBuilder const limitAlertConditionStateBuilder3(DFL::Mdib::LimitAlertConditionState(
            activation,
            boost::none,
            boost::none,
            boost::none,
            DFL::Mdib::AlertConditionPresence::NotPresent,
            boost::none,
            boost::none,
            DFL::Mdib::AlertConditionMonitoredLimits::All,
            DFL::Mdib::Range(boost::none, DFL::Mdib::Decimal(99,0))
            ));

        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(
            BaseTree::MdsLimitAlertCondition3,
            limitAlertConditionDescrBuilder3,
            limitAlertConditionStateBuilder3,
            mdsAlertSystem));

        DFL::Mdib::LimitAlertConditionDescriptorBuilder const limitAlertConditionDescrBuilder4(DFL::Mdib::LimitAlertConditionDescriptor(
            DFL::Mdib::SafetyClassification::MedicalClassB,
            DFL::Mdib::CodedValueFactory::create11073cfCode("196672"), // 11073 code MDC_EVT_LO_LT_LIM.
            DFL::Mdib::AlertConditionKind::Physiological,
            DFL::Mdib::AlertConditionPriority::Low,
            DFL::Mdib::Duration(),
            boost::none,
            boost::none,
            sources,
            DFL::Mdib::CauseInfos(),
            false,
            boost::none
            ));

        DFL::Mdib::LimitAlertConditionStateBuilder const limitAlertConditionStateBuilder4(DFL::Mdib::LimitAlertConditionState(
            activation,
            boost::none,
            boost::none,
            boost::none,
            DFL::Mdib::AlertConditionPresence::NotPresent,
            boost::none,
            boost::none,
            DFL::Mdib::AlertConditionMonitoredLimits::All,
            DFL::Mdib::Range(DFL::Mdib::Decimal(1,0), boost::none)
        ));

        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(
            BaseTree::MdsLimitAlertCondition4,
            limitAlertConditionDescrBuilder4,
            limitAlertConditionStateBuilder4,
            mdsAlertSystem));

        DFL::Mdib::LimitAlertConditionDescriptorBuilder const limitAlertConditionDescrBuilder5(DFL::Mdib::LimitAlertConditionDescriptor(
            DFL::Mdib::SafetyClassification::MedicalClassB,
            DFL::Mdib::CodedValueFactory::create11073cfCode("199854"), // 11073 code MDC_EVT_DESAT
            DFL::Mdib::AlertConditionKind::Physiological,
            DFL::Mdib::AlertConditionPriority::Low,
            DFL::Mdib::Duration(),
            boost::none,
            boost::none,
            sources,
            DFL::Mdib::CauseInfos(),
            false,
            boost::none
            ));

        DFL::Mdib::LimitAlertConditionStateBuilder const limitAlertConditionStateBuilder5(DFL::Mdib::LimitAlertConditionState(
            activation,
            boost::none,
            boost::none,
            boost::none,
            DFL::Mdib::AlertConditionPresence::NotPresent,
            boost::none,
            boost::none,
            DFL::Mdib::AlertConditionMonitoredLimits::All,
            DFL::Mdib::Range(DFL::Mdib::Decimal(1,0), boost::none)
        ));

        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(
            BaseTree::MdsLimitAlertCondition5,
            limitAlertConditionDescrBuilder5,
            limitAlertConditionStateBuilder5,
            mdsAlertSystem));
    }
}

inline void appendMdsAlertSignal(
    DFL::Mdib::MdibChangeSet& changeSet,
    const DFL::Mdib::MdsAlertSystemHandle& mdsAlertSystem,
    const DFL::Mdib::AlertActivation& activation)
{
    {
        auto entity = DFL::Mdib::EntityFactory::create(BaseTree::MdsAlertSignal1, mdsAlertSystem);
        auto desc = entity->descriptor();
        auto descBuilder = DFL::Mdib::getBuilder(desc);

        auto state = entity->state();
        auto stateBuilder = DFL::Mdib::getBuilder(state);
        stateBuilder.activationState(activation);

        descBuilder.conditionSignaledHandle(toHandle(BaseTree::MdsAlertCondition1));
        descBuilder.manifestation(DFL::Mdib::AlertSignalManifestation::Audible);
        descBuilder.latching(DFL::Mdib::Latching::NonLatchingSignal);
        descBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("54321"));
        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(entity->handle(), descBuilder, stateBuilder, entity->parent()));
    }
    {
        auto entity = DFL::Mdib::EntityFactory::create(BaseTree::MdsAlertSignal2, mdsAlertSystem);
        auto desc = entity->descriptor();
        auto descBuilder = DFL::Mdib::getBuilder(desc);

        auto state = entity->state();
        auto stateBuilder = DFL::Mdib::getBuilder(state);
        stateBuilder.activationState(activation);

        descBuilder.conditionSignaledHandle(toHandle(BaseTree::MdsAlertCondition1));
        descBuilder.manifestation(DFL::Mdib::AlertSignalManifestation::Visible);
        descBuilder.latching(DFL::Mdib::Latching::NonLatchingSignal);
        descBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("54321"));
        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(entity->handle(), descBuilder, stateBuilder, entity->parent()));
    }
    {
        auto entity = DFL::Mdib::EntityFactory::create(BaseTree::MdsAlertSignal3, mdsAlertSystem);
        auto desc = entity->descriptor();
        auto descBuilder = DFL::Mdib::getBuilder(desc);

        auto state = entity->state();
        auto stateBuilder = DFL::Mdib::getBuilder(state);
        stateBuilder.activationState(activation);

        descBuilder.conditionSignaledHandle(toHandle(BaseTree::MdsLimitAlertCondition1));
        descBuilder.manifestation(DFL::Mdib::AlertSignalManifestation::Audible);
        descBuilder.latching(DFL::Mdib::Latching::NonLatchingSignal);
        descBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("123"));
        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(entity->handle(), descBuilder, stateBuilder, entity->parent()));
    }
    {
        auto entity = DFL::Mdib::EntityFactory::create(BaseTree::MdsAlertSignal4, mdsAlertSystem);
        auto desc = entity->descriptor();
        auto descBuilder = DFL::Mdib::getBuilder(desc);

        auto state = entity->state();
        auto stateBuilder = DFL::Mdib::getBuilder(state);
        stateBuilder.activationState(activation);

        descBuilder.conditionSignaledHandle(toHandle(BaseTree::MdsLimitAlertCondition1));
        descBuilder.manifestation(DFL::Mdib::AlertSignalManifestation::Visible);
        descBuilder.latching(DFL::Mdib::Latching::NonLatchingSignal);
        descBuilder.type(DFL::Mdib::CodedValueFactory::create11073cfCode("543"));
        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(entity->handle(), descBuilder, stateBuilder, entity->parent()));
    }
}

inline DFL::Mdib::MdsAlertSystemHandle appendMdsAlertSystemOnly(
    DFL::Mdib::MdibChangeSet& changeSet,
    const DFL::Mdib::MdsHandle& mds,
    const DFL::Mdib::AlertActivation& activation)
{
    DFL::Mdib::MdsAlertSystemHandle mdsAlertSystem(BaseTree::MdsAlertSystem);
    auto entity = DFL::Mdib::EntityFactory::create(mdsAlertSystem, mds);
    auto state = entity->state();
    auto stateBuilder = DFL::Mdib::getBuilder(state);
    stateBuilder.activationState(activation);
    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(entity->handle(), stateBuilder, entity->parent()));
    return mdsAlertSystem;
}

inline void appendMdsAlertSystem(DFL::Mdib::MdibChangeSet& changeSet, const DFL::Mdib::MdsHandle& mds)
{
    auto mdsAlertSystem = appendMdsAlertSystemOnly(changeSet, mds);
    appendMdsAlertCondition(changeSet, mdsAlertSystem);
    appendMdsLimitAlertCondition(changeSet, mdsAlertSystem);
    appendMdsAlertSignal(changeSet, mdsAlertSystem);
}

} // namespace Helper

inline DFL::Mdib::MdibChangeSet TestFactory::createBaseTree()
{
    MdibChangeSet changeSet;

    auto mdsHandle = Helper::appendMds(changeSet);
    auto vmdHandle = Helper::appendVmd(changeSet, mdsHandle);
    Helper::appendSystemContext(changeSet, mdsHandle);
    Helper::appendMdsSco(changeSet, mdsHandle);
    Helper::appendMdsAlertSystem(changeSet, mdsHandle);
    Helper::appendVmdSco(changeSet, vmdHandle);
    Helper::appendVmdAlertSystem(changeSet, vmdHandle);

    return changeSet;
}

inline DFL::Mdib::MdibChangeSet TestFactory::createMdsAndVmdOnlyBaseTree()
{
    MdibChangeSet changeSet;

    auto mdsHandle = Helper::appendMds(changeSet);
    Helper::appendVmd(changeSet, mdsHandle);

    return changeSet;
}

inline CodedValue TestFactory::hashCodedValue(const Handle& handle)
{
    return hashCodedValue(handle.string());
}

inline CodedValue TestFactory::hashCodedValue(const std::string& handle)
{
    auto hash = std::hash<std::string>{}(handle);
    std::ostringstream s;
    s << static_cast<uint16_t>(hash); // First partition with 16 bit values is unspecified
    return CodedValueFactory::create11073cfCode(s.str());
}

template<class T_DescBuilder>
void TestFactory::setDeterminationPeriodForMetric(T_DescBuilder& builder,
                                                  typename std::enable_if<DFL::Mdib::is_metric_descriptor<typename T_DescBuilder::BuiltType>::value>::type*)
{
    if (builder.metricAvailability() == DFL::Mdib::MetricAvailability::Continuous)
    {
        builder.determinationPeriod(DFL::Mdib::Duration{DFL::Chrono::Seconds{30}});
    }
}

template<class T_DescBuilder>
void TestFactory::setDeterminationPeriodForMetric(T_DescBuilder&,
                                                  typename std::enable_if<!DFL::Mdib::is_metric_descriptor<typename T_DescBuilder::BuiltType>::value>::type*)
{
    // nothing to do if not a metric descriptor
}

template<class T_DescBuilder>
void TestFactory::setAllowedValues(T_DescBuilder& builder,
                                   typename std::enable_if<std::is_same<T_DescBuilder, DFL::Mdib::EnumStringMetricDescriptorBuilder>::value>::type*)
{
    builder.allowedValues(DFL::Mdib::AllowedEnumValues{DFL::Locale::Utf8("abc")});
}

template<class T_DescBuilder>
void TestFactory::setAllowedValues(T_DescBuilder&,
                                   typename std::enable_if<!std::is_same<T_DescBuilder, DFL::Mdib::EnumStringMetricDescriptorBuilder>::value>::type*)
{
    // nothing to do if not enum string metric
}


}
}
}
