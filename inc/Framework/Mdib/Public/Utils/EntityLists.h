#pragma once

#include <boost/preprocessor.hpp>

/*
 *
 *
 * Attention developers:
 * Be careful when altering type lists in this file as the order may be crucial for tree traversal!
 *
 *
 */



// Overrides for DFL_MDIB_ENTITIES_AS_SHARED_PTRS
#define DFL_MDIB_ENTITIES_AS_SHARED_PTRS_1(entity) \
    NotNull<SharedPtr<entity>>
#define DFL_MDIB_ENTITIES_AS_SHARED_PTRS_2(entity1,entity2) \
    NotNull<SharedPtr<entity1>>,NotNull<SharedPtr<entity2>>
#define DFL_MDIB_ENTITIES_AS_SHARED_PTRS_3(entity1,entity2,entity3) \
    NotNull<SharedPtr<entity1>>,DFL_MDIB_ENTITIES_AS_SHARED_PTRS_2(entity2,entity3)
#define DFL_MDIB_ENTITIES_AS_SHARED_PTRS_4(entity1,entity2,entity3,entity4) \
    DFL_MDIB_ENTITIES_AS_SHARED_PTRS_2(entity1,entity2),DFL_MDIB_ENTITIES_AS_SHARED_PTRS_2(entity3,entity4)
#define DFL_MDIB_ENTITIES_AS_SHARED_PTRS_5(entity1,entity2,entity3,entity4,entity5) \
    DFL_MDIB_ENTITIES_AS_SHARED_PTRS_2(entity1,entity2),DFL_MDIB_ENTITIES_AS_SHARED_PTRS_3(entity3,entity4,entity5)
#define DFL_MDIB_ENTITIES_AS_SHARED_PTRS_6(entity1,entity2,entity3,entity4,entity5,entity6) \
    DFL_MDIB_ENTITIES_AS_SHARED_PTRS_3(entity1,entity2,entity3),DFL_MDIB_ENTITIES_AS_SHARED_PTRS_3(entity4,entity5,entity6)
#define DFL_MDIB_ENTITIES_AS_SHARED_PTRS_7(entity1,entity2,entity3,entity4,entity5,entity6,entity7) \
    DFL_MDIB_ENTITIES_AS_SHARED_PTRS_3(entity1,entity2,entity3),DFL_MDIB_ENTITIES_AS_SHARED_PTRS_4(entity4,entity5,entity6,entity7)

#if !BOOST_PP_VARIADICS_MSVC
/**
 * @brief Takes MDIB entity types T1..TN and transform them to \c %DFL::NotNull<DFL::Mdib::SharedPtr<T1>>..DFL::NotNull<DFL::Mdib::SharedPtr<TN>>.
 */
#define DFL_MDIB_ENTITIES_AS_SHARED_PTRS(...) BOOST_PP_OVERLOAD(DFL_MDIB_ENTITIES_AS_SHARED_PTRS_,__VA_ARGS__)(__VA_ARGS__)
#else
// different handling for Visual C++
#define DFL_MDIB_ENTITIES_AS_SHARED_PTRS(...) \
  BOOST_PP_CAT(BOOST_PP_OVERLOAD(DFL_MDIB_ENTITIES_AS_SHARED_PTRS_,__VA_ARGS__)(__VA_ARGS__),BOOST_PP_EMPTY())
#endif

/**
 * @brief Lists all BICEPS component entity types (AbstractDeviceComponentDescriptor).
 * @details The macro puts parent entities before child entities.
 * @ingroup Mdib
 */
#define DFL_MDIB_ENTITY_COMPONENTS ::DFL::Mdib::Mds,::DFL::Mdib::MdsSco,::DFL::Mdib::Vmd,::DFL::Mdib::VmdSco,\
    ::DFL::Mdib::SystemContext,::DFL::Mdib::Channel,::DFL::Mdib::Battery,::DFL::Mdib::Clock

/**
 * @brief Lists all BICEPS component entity types (AbstractDeviceComponentDescriptor) without Mds/Vmd differentiation.
 * @details The macro puts parent entities before child entities.
 * @ingroup Mdib
 */
#define DFL_MDIB_ENTITY_COMPONENTS_BASE ::DFL::Mdib::Mds,::DFL::Mdib::Vmd,::DFL::Mdib::ScoTypes,\
    ::DFL::Mdib::SystemContext,::DFL::Mdib::Channel,::DFL::Mdib::Battery,::DFL::Mdib::Clock

/**
 * @brief Lists all BICEPS alert entity types (AbstractAlertDescriptor).
 * @details The macro puts parent entities before child entities and conditions before signals.
 * @ingroup Mdib
 */
#define DFL_MDIB_ENTITY_ALERTS ::DFL::Mdib::MdsAlertSystem,::DFL::Mdib::MdsAlertCondition,::DFL::Mdib::MdsLimitAlertCondition,\
    ::DFL::Mdib::MdsAlertSignal,::DFL::Mdib::VmdAlertSystem,::DFL::Mdib::VmdAlertCondition,\
    ::DFL::Mdib::VmdLimitAlertCondition,::DFL::Mdib::VmdAlertSignal

/**
 * @brief Lists all BICEPS alert entity types (AbstractAlertDescriptor) without Mds/Vmd differentiation.
 * @details The macro puts parent entities before child entities and conditions before signals.
 * @ingroup Mdib
 */
#define DFL_MDIB_ENTITY_ALERTS_BASE ::DFL::Mdib::AlertSystemTypes,::DFL::Mdib::AlertConditionTypes,\
    ::DFL::Mdib::LimitAlertConditionTypes,::DFL::Mdib::AlertSignalTypes

/**
 * @brief Lists all BICEPS metric entity types that are realtime and reported via waveformstream
 * @ingroup Mdib
 */
#define DFL_MDIB_ENTITY_WAVEFORM_STREAM ::DFL::Mdib::RealTimeSampleArrayMetric

/**
 * @brief Lists all BICEPS alert metric entity types that are not reported via waveformstream
 * @ingroup Mdib
 */
#define DFL_MDIB_ENTITY_METRIC_REPORT ::DFL::Mdib::EnumStringMetric,::DFL::Mdib::NumericMetric,::DFL::Mdib::StringMetric,\
    ::DFL::Mdib::DistributionSampleArrayMetric

/**
 * @brief Lists all BICEPS metric entity types (AbstractMetricDescriptor).
 * @ingroup Mdib
 */
#define DFL_MDIB_ENTITY_METRICS DFL_MDIB_ENTITY_METRIC_REPORT,DFL_MDIB_ENTITY_WAVEFORM_STREAM

/**
 * @brief Lists MDS BICEPS operation entity types.
 * @ingroup Mdib
 */
#define DFL_MDIB_ENTITY_MDS_OPERATIONS ::DFL::Mdib::MdsActivateOperation,::DFL::Mdib::MdsSetAlertStateOperation,\
    ::DFL::Mdib::MdsSetComponentStateOperation,::DFL::Mdib::MdsSetContextStateOperation,::DFL::Mdib::MdsSetMetricStateOperation,\
    ::DFL::Mdib::MdsSetStringOperation,::DFL::Mdib::MdsSetValueOperation

/**
 * @brief Lists VMD BICEPS operation entity types.
 * @ingroup Mdib
 */
#define DFL_MDIB_ENTITY_VMD_OPERATIONS ::DFL::Mdib::VmdActivateOperation, ::DFL::Mdib::VmdSetAlertStateOperation,\
    ::DFL::Mdib::VmdSetComponentStateOperation,::DFL::Mdib::VmdSetContextStateOperation,\
    ::DFL::Mdib::VmdSetMetricStateOperation,::DFL::Mdib::VmdSetStringOperation,::DFL::Mdib::VmdSetValueOperation

/**
 * @brief Lists all BICEPS operation entity types (AbstractOperationDescriptor).
 * @ingroup Mdib
 */
#define DFL_MDIB_ENTITY_OPERATIONS DFL_MDIB_ENTITY_MDS_OPERATIONS,DFL_MDIB_ENTITY_VMD_OPERATIONS

/**
 * @brief Lists all BICEPS operation entity types (AbstractOperationDescriptor) without Mds/Vmd differentiation.
 * @ingroup Mdib
 */
#define DFL_MDIB_ENTITY_OPERATIONS_BASE ::DFL::Mdib::ActivateOperationTypes,::DFL::Mdib::SetAlertStateOperationTypes,\
    ::DFL::Mdib::SetComponentStateOperationTypes,::DFL::Mdib::SetContextStateOperationTypes,::DFL::Mdib::SetMetricStateOperationTypes,\
    ::DFL::Mdib::SetStringOperationTypes,::DFL::Mdib::SetValueOperationTypes

/**
 * @brief Lists all BICEPS context state indicators.
 * @note @ref DFL_MDIB_ENTITY_CONTEXT_INDICATORS and @ref DFL_MDIB_ENTITY_CONTEXT_STATES have to be
 *            the same order (to be able to have a mapping between this types)
 *
 * @ingroup Mdib
 */
#define DFL_MDIB_ENTITY_CONTEXT_INDICATORS ::DFL::Mdib::LocationContextIndicator,\
    ::DFL::Mdib::PatientContextIndicator,::DFL::Mdib::EnsembleContextIndicator

/**
 * @brief Lists all BICEPS context state entities.
 * @note @ref DFL_MDIB_ENTITY_CONTEXT_INDICATORS and @ref DFL_MDIB_ENTITY_CONTEXT_STATES have to be
 *            the same order (to be able to have a mapping between this types)
 *
 * @ingroup Mdib
 */
#define DFL_MDIB_ENTITY_CONTEXT_STATES ::DFL::Mdib::LocationContext,\
    ::DFL::Mdib::PatientContext,::DFL::Mdib::EnsembleContext

/**
 * @brief Lists all BICEPS context entity types including indicator (AbstractContextDescriptor and AbstractContextState).
 * @ingroup Mdib
 */
#define DFL_MDIB_ENTITY_CONTEXTS DFL_MDIB_ENTITY_CONTEXT_INDICATORS,DFL_MDIB_ENTITY_CONTEXT_STATES

/**
 * @brief Lists all BICEPS entities.
 * @details Does not contain special entity types such as MdsParentPlaceholder.
 * @ingroup Mdib
 */
#define DFL_MDIB_ENTITY_ALL DFL_MDIB_ENTITY_COMPONENTS,DFL_MDIB_ENTITY_ALERTS,DFL_MDIB_ENTITY_METRICS,DFL_MDIB_ENTITY_OPERATIONS,DFL_MDIB_ENTITY_CONTEXTS

/**
 * @brief Lists all BICEPS entities that have/are states.
 * @details Does not contain special entity types such as MdsParentPlaceholder without Mds/Vmd differentiation.
 * @ingroup Mdib
 */
#define DFL_MDIB_ENTITY_ALL_BASE_STATES DFL_MDIB_ENTITY_COMPONENTS_BASE,DFL_MDIB_ENTITY_ALERTS_BASE,DFL_MDIB_ENTITY_METRICS,\
    DFL_MDIB_ENTITY_OPERATIONS_BASE,DFL_MDIB_ENTITY_CONTEXT_STATES

/**
 * @brief Lists all BICEPS entities that have/are descriptors.
 * @details Does not contain special entity types such as MdsParentPlaceholder without Mds/Vmd differentiation.
 * @ingroup Mdib
 */
#define DFL_MDIB_ENTITY_ALL_BASE_DESCRIPTORS DFL_MDIB_ENTITY_COMPONENTS_BASE,DFL_MDIB_ENTITY_ALERTS_BASE,\
    DFL_MDIB_ENTITY_METRICS,DFL_MDIB_ENTITY_OPERATIONS_BASE,DFL_MDIB_ENTITY_CONTEXT_INDICATORS

/**
 * @brief Lists BICEPS alert entity types (AbstractAlertDescriptor) in reverse order.
 * @details The macro puts parent entities after child entities and conditions before signals.
 * @ingroup Mdib
 */
#define DFL_MDIB_ENTITY_ALERTS_REVERSE ::DFL::Mdib::MdsAlertCondition,::DFL::Mdib::MdsLimitAlertCondition,\
    ::DFL::Mdib::MdsAlertSignal,::DFL::Mdib::VmdAlertCondition,\
    ::DFL::Mdib::VmdLimitAlertCondition,::DFL::Mdib::VmdAlertSignal,::DFL::Mdib::MdsAlertSystem,::DFL::Mdib::VmdAlertSystem

/**
 * @brief Lists all BICEPS context entity types including indicator (AbstractContextDescriptor and AbstractContextState) in reverse order.
 * @ingroup Mdib
 */
#define DFL_MDIB_ENTITY_CONTEXTS_REVERSE DFL_MDIB_ENTITY_CONTEXT_STATES,DFL_MDIB_ENTITY_CONTEXT_INDICATORS

/**
 * @brief Lists all BICEPS component entity types (AbstractDeviceComponentDescriptor) in reverse order.
 * @details The macro puts parent entities after child entities.
 * @ingroup Mdib
 */
#define DFL_MDIB_ENTITY_COMPONENTS_REVERSE ::DFL::Mdib::MdsSco,::DFL::Mdib::VmdSco,\
    ::DFL::Mdib::SystemContext,::DFL::Mdib::Channel,::DFL::Mdib::Battery,::DFL::Mdib::Clock,::DFL::Mdib::Vmd,::DFL::Mdib::Mds

/**
 * @brief Lists all BICEPS entities reverse.
 * @details Does not contain special entity types such as MdsParentPlaceholder.
 * @ingroup Mdib
 */
#define DFL_MDIB_ENTITY_ALL_REVERSE DFL_MDIB_ENTITY_ALERTS_REVERSE,DFL_MDIB_ENTITY_METRICS,DFL_MDIB_ENTITY_OPERATIONS,DFL_MDIB_ENTITY_CONTEXTS_REVERSE,DFL_MDIB_ENTITY_COMPONENTS_REVERSE
