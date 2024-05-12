#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/AbstractDescriptor.h>
#include <Framework/Mdib/Public/Model/Alert/AlertConditionKind.h>
#include <Framework/Mdib/Public/Model/Alert/AlertConditionPriority.h>
#include <Framework/Mdib/Public/Model/Alert/CauseInfo.h>
#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Public/Model/Duration.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Range.h>
#include <Framework/Mdib/Public/Model/SafetyClassification.h>

namespace DFL
{
namespace Mdib
{
/**
 * @brief   An alert condition contains the information about a potentially or actually hazardous situation.
 * @details Examples: a physiological alarm limit has been exceeded or a sensor has been unplugged.
 * @ingroup Mdib
 */
class AlertConditionDescriptor: public AbstractDescriptor
{
        DFL_MDIB_IMMUTABLE(AlertConditionDescriptor)

    public:
        /**
         * @brief Default constructor.
         * @details Defaults
         *
         * - \ref AlertConditionDescriptor::kind() "Kind" to \ref AlertConditionKind::Other "other"
         * - \ref AlertConditionDescriptor::priority() "Priority" to \ref AlertConditionPriority::None "none"
         * - \ref AlertConditionDescriptor::defaultConditionGenerationDelay() "Default condition generation delay" to 0 seconds
         * - \ref AlertConditionDescriptor::canEscalate() "Can escalate" to none
         * - \ref AlertConditionDescriptor::canDeescalate() "Can deescalate" to none
         * - \ref AlertConditionDescriptor::sources() "Sources" to empty sequence
         * - \ref AlertConditionDescriptor::causeInfos() "Cause infos" to empty sequence
         *
         * \note Also applies defaults from \ref AbstractDescriptor.
         */
        AlertConditionDescriptor() = default;

        /**
         * @brief Full constructor.
         */
        AlertConditionDescriptor(SafetyClassification safetyClassification,
                                 boost::optional<CodedValue>&& type,
                                 AlertConditionKind kind,
                                 AlertConditionPriority priority,
                                 const Duration& defaultConditionGenerationDelay,
                                 const boost::optional<AlertConditionPriority>& canEscalate,
                                 const boost::optional<AlertConditionPriority>& canDeescalate,
                                 Handles sources,
                                 CauseInfos causeInfo,
                                 ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Full constructor.
         */
        AlertConditionDescriptor(SafetyClassification safetyClassification,
                                 const boost::optional<CodedValue>& type,
                                 AlertConditionKind kind,
                                 AlertConditionPriority priority,
                                 const Duration& defaultConditionGenerationDelay,
                                 const boost::optional<AlertConditionPriority>& canEscalate,
                                 const boost::optional<AlertConditionPriority>& canDeescalate,
                                 Handles sources,
                                 CauseInfos causeInfo,
                                 ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Kind of the alert condition.
         */
        AlertConditionKind kind() const;

        /**
         * @brief Severity of the alert condition.
         */
        AlertConditionPriority priority() const;

        /**
         * @brief Defines the period that describes the delay from the physical fulfillment of an alert condition to the
         * generation of the alert condition on the medical device.
         */
        const Duration& defaultConditionGenerationDelay() const;

        /**
         * @brief Indicates if an alert condition can escalate from one priority to another.
         */
        boost::optional<AlertConditionPriority> canEscalate() const;

        /**
         * @brief Indicates if an alert condition can deescalate from one priority to another.
         */
        boost::optional<AlertConditionPriority> canDeescalate() const;

        /**
         * @brief   List of handle references to sources (e.g., metrics) that cause the alert condition.
         * @details Examples:
         *
         * - if a source is present: the heart rate metric is the source for a "heart rate high" alert
         *   condition.
         * - if no source is present: a "cable disconnection" alert condition has no specific source.
         */
        const Handles& sources() const;

        /**
         * @brief List of cause-remedy information.
         */
        const CauseInfos& causeInfos() const;

    private:
        AlertConditionKind m_kind{AlertConditionKind::Other};
        AlertConditionPriority m_priority{AlertConditionPriority::None};
        Duration m_defaultConditionGenerationDelay{Chrono::Seconds{0}};
        boost::optional<AlertConditionPriority> m_canEscalate{};
        boost::optional<AlertConditionPriority> m_canDeescalate{};
        Handles m_sources{};
        CauseInfos m_causeInfo{};
};

inline AlertConditionDescriptor::AlertConditionDescriptor(SafetyClassification safetyClassification,
                                                          boost::optional<CodedValue>&& type,
                                                          AlertConditionKind kind,
                                                          AlertConditionPriority priority,
                                                          const Duration& defaultConditionGenerationDelay,
                                                          const boost::optional<AlertConditionPriority>& canEscalate,
                                                          const boost::optional<AlertConditionPriority>& canDeescalate,
                                                          Handles sources,
                                                          CauseInfos causeInfo,
                                                          ExtensionTypes extensions) :
        AbstractDescriptor(safetyClassification, std::move(type), std::move(extensions)),
        m_kind(kind),
        m_priority(priority),
        m_defaultConditionGenerationDelay(defaultConditionGenerationDelay),
        m_canEscalate(canEscalate),
        m_canDeescalate(canDeescalate),
        m_sources(std::move(sources)),
        m_causeInfo(std::move(causeInfo))
{
}

inline AlertConditionDescriptor::AlertConditionDescriptor(SafetyClassification safetyClassification,
                                                          const boost::optional<CodedValue>& type,
                                                          AlertConditionKind kind,
                                                          AlertConditionPriority priority,
                                                          const Duration& defaultConditionGenerationDelay,
                                                          const boost::optional<AlertConditionPriority>& canEscalate,
                                                          const boost::optional<AlertConditionPriority>& canDeescalate,
                                                          Handles sources,
                                                          CauseInfos causeInfo,
                                                          ExtensionTypes extensions) :
        AbstractDescriptor(safetyClassification, type, std::move(extensions)),
        m_kind(kind),
        m_priority(priority),
        m_defaultConditionGenerationDelay(defaultConditionGenerationDelay),
        m_canEscalate(canEscalate),
        m_canDeescalate(canDeescalate),
        m_sources(std::move(sources)),
        m_causeInfo(std::move(causeInfo))
{
}

inline AlertConditionKind AlertConditionDescriptor::kind() const
{
    return m_kind;
}

inline AlertConditionPriority AlertConditionDescriptor::priority() const
{
    return m_priority;
}

inline const Duration& AlertConditionDescriptor::defaultConditionGenerationDelay() const
{
    return m_defaultConditionGenerationDelay;
}

inline boost::optional<AlertConditionPriority> AlertConditionDescriptor::canEscalate() const
{
    return m_canEscalate;
}

inline boost::optional<AlertConditionPriority> AlertConditionDescriptor::canDeescalate() const
{
    return m_canDeescalate;
}

inline const Handles& AlertConditionDescriptor::sources() const
{
    return m_sources;
}

inline const CauseInfos& AlertConditionDescriptor::causeInfos() const
{
    return m_causeInfo;
}

/**
 * @brief Definition of shared pointer type \ref AlertConditionDescriptorSharedPtr for descriptor \ref AlertConditionDescriptor.
 * @ingroup Mdib
 */
using AlertConditionDescriptorSharedPtr = SharedPtr<AlertConditionDescriptor>;


} /* namespace Mdib */
} /* namespace DFL */
