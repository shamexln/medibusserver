#pragma once

#include <boost/optional/optional.hpp>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Alert/AlertConditionDescriptor.h>

namespace DFL
{
namespace Mdib
{
/**
 * @brief Static part of a \ref LimitAlertCondition
 * @ingroup Mdib
 */
class LimitAlertConditionDescriptor: public AlertConditionDescriptor
{
    DFL_MDIB_IMMUTABLE(LimitAlertConditionDescriptor)

    public:
        /**
         * @brief Default constructor.
         * @details Defaults
         *
         * - \ref LimitAlertConditionDescriptor::maxLimits() "Maximum limits" to none
         * - \ref LimitAlertConditionDescriptor::autoLimitSupported() "Auto limit supported" to \c false
         *
         * \note Also applies defaults from \ref AlertConditionDescriptor.
         */
        LimitAlertConditionDescriptor() = default;

        /**
         * @brief Constructor.
         */
        LimitAlertConditionDescriptor(SafetyClassification safetyClassification,
                                      boost::optional<CodedValue>&& type,
                                      AlertConditionKind kind,
                                      AlertConditionPriority priority,
                                      const Duration& defaultConditionGenerationDelay,
                                      const boost::optional<AlertConditionPriority>& canEscalate,
                                      const boost::optional<AlertConditionPriority>& canDeescalate,
                                      const Handles& sources,
                                      const CauseInfos& causeInfo,
                                      bool autoLimitSupported,
                                      boost::optional<Range> maxLimits,
                                      ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Constructor.
         */
        LimitAlertConditionDescriptor(SafetyClassification safetyClassification,
                                      const boost::optional<CodedValue>& type,
                                      AlertConditionKind kind,
                                      AlertConditionPriority priority,
                                      const Duration& defaultConditionGenerationDelay,
                                      const boost::optional<AlertConditionPriority>& canEscalate,
                                      const boost::optional<AlertConditionPriority>& canDeescalate,
                                      const Handles& sources,
                                      const CauseInfos& causeInfo,
                                      bool autoLimitSupported,
                                      boost::optional<Range> maxLimits,
                                      ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief The maximum possible range for the limit bounds.
         * @details Example: the ECG values can be measured in a specific range.
         * At some point the measured values are afflicted with noise, which
         * makes them not valid for limits. Therefore, the maximum allowed range
         * can be restricted.
         * @return The maximum limits or \c boost::none if undeclared.
         */
        const boost::optional<Range>& maxLimits() const;

        /**
         * @brief Indicates whether a limit alert condition provides support for automatic limit adaption.
         */
        bool autoLimitSupported() const;

    private:
        boost::optional<Range> m_maxLimits{};
        bool m_autoLimitSupported{false};
};

inline LimitAlertConditionDescriptor::LimitAlertConditionDescriptor(SafetyClassification safetyClassification,
                                                                    boost::optional<CodedValue>&& type,
                                                                    AlertConditionKind kind,
                                                                    AlertConditionPriority priority,
                                                                    const Duration& defaultConditionGenerationDelay,
                                                                    const boost::optional<AlertConditionPriority>& canEscalate,
                                                                    const boost::optional<AlertConditionPriority>& canDeescalate,
                                                                    const Handles& sources,
                                                                    const CauseInfos& causeInfo,
                                                                    bool autoLimitSupported,
                                                                    boost::optional<Range> maxLimits,
                                                                    ExtensionTypes extensions) :
        AlertConditionDescriptor(safetyClassification,
                                 std::move(type),
                                 kind,
                                 priority,
                                 defaultConditionGenerationDelay,
                                 canEscalate,
                                 canDeescalate,
                                 sources,
                                 causeInfo,
                                 std::move(extensions)),
        m_maxLimits(std::move(maxLimits)),
        m_autoLimitSupported(autoLimitSupported)
{
}

inline LimitAlertConditionDescriptor::LimitAlertConditionDescriptor(SafetyClassification safetyClassification,
                                                                    const boost::optional<CodedValue>& type,
                                                                    AlertConditionKind kind,
                                                                    AlertConditionPriority priority,
                                                                    const Duration& defaultConditionGenerationDelay,
                                                                    const boost::optional<AlertConditionPriority>& canEscalate,
                                                                    const boost::optional<AlertConditionPriority>& canDeescalate,
                                                                    const Handles& sources,
                                                                    const CauseInfos& causeInfo,
                                                                    bool autoLimitSupported,
                                                                    boost::optional<Range> maxLimits,
                                                                    ExtensionTypes extensions) :
        AlertConditionDescriptor(safetyClassification,
                                 type,
                                 kind,
                                 priority,
                                 defaultConditionGenerationDelay,
                                 canEscalate,
                                 canDeescalate,
                                 sources,
                                 causeInfo,
                                 std::move(extensions)),
        m_maxLimits(std::move(maxLimits)),
        m_autoLimitSupported(autoLimitSupported)
{
}

inline const boost::optional<Range>& LimitAlertConditionDescriptor::maxLimits() const
{
    return m_maxLimits;
}

inline bool LimitAlertConditionDescriptor::autoLimitSupported() const
{
    return m_autoLimitSupported;
}

/**
 * @brief Definition of shared pointer type \ref LimitAlertConditionDescriptorSharedPtr for descriptor \ref LimitAlertConditionDescriptor.
 * @ingroup Mdib
 */
using LimitAlertConditionDescriptorSharedPtr = SharedPtr<LimitAlertConditionDescriptor>;


}
}
