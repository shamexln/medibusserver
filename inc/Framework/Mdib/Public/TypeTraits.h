#pragma once

#include <Framework/Mdib/Private/ContextDescriptorEntity.h>
#include <Framework/Mdib/Private/ContextStateEntity.h>
#include <Framework/Mdib/Public/Model/Alert/AbstractAlertState.h>
#include <Framework/Mdib/Public/Model/Alert/AlertConditionDescriptor.h>
#include <Framework/Mdib/Public/Model/Component/Sco.h>
#include <Framework/Mdib/Public/Model/Component/SystemContext.h>
#include <Framework/Mdib/Public/Model/Metric/AbstractMetricDescriptor.h>
#include <Framework/Mdib/Public/Model/Metric/AbstractMetricState.h>
#include <type_traits>

namespace DFL
{
namespace Mdib
{
class Mds;

/**
 * @brief Checks if the MDIB entity is a operation.
 * @ingroup Mdib
 */
///@{
template<typename T_Entity, typename Enable = void>
struct is_operation : public std::false_type {};

template<typename T_Entity>
struct is_operation<T_Entity, typename std::enable_if<
        std::is_base_of<
                DFL::Mdib::Sco<typename T_Entity::ParentType, typename T_Entity::ParentType::ParentType>,
                typename T_Entity::ParentType
        >::value
>::type> : public std::true_type
{
};
///@}

/**
 * @brief Checks if the MDIB entity is a alert entity.
 * @ingroup Mdib
 */
///@{
template<typename T_Entity, typename Enable = void>
struct is_alert : public std::false_type {};

template<typename T_Entity>
struct is_alert<T_Entity, typename std::enable_if<
        std::is_base_of<
                DFL::Mdib::AbstractAlertState,
                typename T_Entity::StateType
        >::value
>::type> : public std::true_type
{
};
///@}

/**
 * @brief Checks if the MDIB entity is a child descriptor of another descriptor.
 * @details \ref DFL::Mdib::Mds "Mds" is no a child descriptor, since it is the top entity.
 * \ref DFL::Mdib::LocationContext "LocationContext" is not a child descriptor, it is a multi state.
 * Typical entities that are child descriptors are
 * - \ref DFL::Mdib::Vmd
 * - \ref DFL::Mdib::NumericMetric
 * - \ref DFL::Mdib::SystemContext
 * - ...
 * @ingroup Mdib
 */
///@{
template<typename T_Entity, typename Enable = void>
struct is_child_descriptor: public std::true_type {};

template<>
struct is_child_descriptor<DFL::Mdib::Mds> : public std::false_type {};

template<typename T_Entity>
struct is_child_descriptor<T_Entity,
        typename std::enable_if<
                std::is_base_of<
                        Impl::ContextStateEntity<T_Entity, typename T_Entity::DescriptorBuilderType, typename T_Entity::StateBuilderType, typename T_Entity::ParentType>,
                        T_Entity
                >::value
        >::type
> : public std::false_type {};

///@}


/**
 * @brief Checks if the MDIB entity is either a patient, location or ensemble context.
 * @ingroup Mdib
 */
///@{
template<typename T_Entity, typename Enable = void>
struct is_multi_state: std::false_type
{
};

template<typename T_Entity>
struct is_multi_state<T_Entity, typename std::enable_if<
        std::is_base_of<
                Impl::ContextStateEntity<T_Entity, typename T_Entity::DescriptorBuilderType, typename T_Entity::StateBuilderType, typename T_Entity::ParentType>, T_Entity>::value>::type> : std::true_type
{
};
///@}

/**
 * @brief Checks if the MDIB entity has only descriptors, i.e. if it is either a patient, location or ensemble context indicator.
 * @ingroup Mdib
 */
///@{
template<class T_Entity, class Enable = void>
struct is_context_indicator: std::false_type
{
};

template<class T_Entity>
struct is_context_indicator<T_Entity, typename std::enable_if<
        std::is_same<
                DFL::Mdib::SystemContext,
                typename T_Entity::ParentType>::value>::type> : std::true_type
{
};
///@}

/**
 * @brief Checks if the MDIB entity has a metric descriptor
 * @ingroup Mdib
 */
///@{
template<typename T_Entity, typename Enable = void>
struct is_metric_descriptor: std::false_type
{
};

template<typename T_Entity>
struct is_metric_descriptor<T_Entity, typename std::enable_if<
        std::is_base_of<DFL::Mdib::AbstractMetricDescriptor, T_Entity>::value>::type> : std::true_type
{
};
///@}

/**
 * @brief Checks if the MDIB entity has a metric value
 * @ingroup Mdib
 */
///@{
template<typename T_Entity, typename Enable = void>
struct is_metric_state: std::false_type
{
};

template<typename T_Entity>
struct is_metric_state<T_Entity, typename std::enable_if<
        std::is_base_of<DFL::Mdib::AbstractMetricState, T_Entity>::value>::type> : std::true_type
{
};
///@}

/**
 * @brief Checks if the MDIB entity is a system context
 * @deprecated This is obsolete due to the fact that \c
 *            std::is_same<DFL::Mdib::SystemContext, T_Entity> could be used.
 * @ingroup Mdib
 */
///@{
template<typename T_Entity, typename Enable = void>
struct is_system_context: std::false_type
{
};

template<typename T_Entity>
struct is_system_context<T_Entity, typename std::enable_if<
        std::is_same<DFL::Mdib::SystemContext, T_Entity>::value>::type> : std::true_type
{
};
///@}

/**
 * @brief Checks if the MDIB entity is a device component
 * @ingroup Mdib
 */
///@{
template<typename T_Entity, typename Enable = void>
struct is_device_component_state: std::false_type
{
};

template<typename T_Entity>
struct is_device_component_state<T_Entity, typename std::enable_if<
        std::is_base_of<DFL::Mdib::AbstractDeviceComponentState, T_Entity>::value ||
        std::is_same<DFL::Mdib::SystemContextState, T_Entity>::value>::type> : std::true_type
{
};
///@}

/**
 * @brief Checks if the MDIB entity is an alert descriptor alert descriptor
 * @ingroup Mdib
 */
///@{
template<typename T_Entity, typename Enable = void>
struct is_alert_condition_descriptor: std::false_type
{
};

template<typename T_Entity>
struct is_alert_condition_descriptor<T_Entity, typename std::enable_if<
        std::is_base_of<DFL::Mdib::AlertConditionDescriptor, T_Entity>::value>::type> : std::true_type
{
};
///@}
}
}
