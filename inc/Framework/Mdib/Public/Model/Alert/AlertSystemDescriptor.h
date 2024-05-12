#pragma once

#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/AbstractDescriptor.h>
#include <Framework/Mdib/Public/Model/Duration.h>

#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Utils/Public/SkillBoostSerializable.h>

#include <boost/optional.hpp>

#include <cstdint>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
struct MaxPhysiologicalParallelAlarmsTag;
struct MaxTechnicalParallelAlarmsTag;
}

/**
 * @brief The maximum number of physiological \ref AlertCondition "alarm conditions" that can be present at a point of time.
 * @ingroup Mdib
 */
using MaxPhysiologicalParallelAlarms = DFL::StrongTypedef<uint32_t, Impl::MaxPhysiologicalParallelAlarmsTag, DFL::Skill::EqualityComparable, DFL::Skill::Streamable, DFL::Skill::BoostSerializable>;

/**
 * @brief The maximum number of technical \ref AlertCondition "alarm conditions" that can be present at a point of time.
 * @ingroup Mdib
 */
using MaxTechnicalParallelAlarms = DFL::StrongTypedef<uint32_t, Impl::MaxTechnicalParallelAlarmsTag, DFL::Skill::EqualityComparable, DFL::Skill::Streamable, DFL::Skill::BoostSerializable>;

/**
 * @brief Describes the static part of an \ref AlertSystem.
 * @ingroup Mdib
 */
class AlertSystemDescriptor: public AbstractDescriptor
{
        DFL_MDIB_IMMUTABLE(AlertSystemDescriptor)

    public:
        /**
         * @brief Default constructor.
         * @details Defaults
         *
         * - \ref AlertSystemDescriptor::maxPhysiologicalAlarmListEntries() "Maximum physiological alarm list entries" to none
         * - \ref AlertSystemDescriptor::maxTechnicalAlarmListEntries() "Maximum technical alarm list entries" to none
         * - \ref AlertSystemDescriptor::selfCheckPeriod() "Self check period" to none
         *
         * \note Also applies defaults from \ref AbstractDescriptor.
         */
        AlertSystemDescriptor() = default;

        /**
         * @brief Full constructor.
         */
        AlertSystemDescriptor(SafetyClassification safetyClassification,
                              boost::optional<CodedValue>&& type,
                              boost::optional<MaxPhysiologicalParallelAlarms> maxPhysiologicalAlarmListEntries,
                              boost::optional<MaxTechnicalParallelAlarms> maxTechnicalAlarmListEntries,
                              boost::optional<Duration> selfCheckPeriod,
                              ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Full constructor.
         */
        AlertSystemDescriptor(SafetyClassification safetyClassification,
                              const boost::optional<CodedValue>& type,
                              boost::optional<MaxPhysiologicalParallelAlarms> maxPhysiologicalAlarmListEntries,
                              boost::optional<MaxTechnicalParallelAlarms> maxTechnicalAlarmListEntries,
                              boost::optional<Duration> selfCheckPeriod,
                              ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Maximum number of physiological alarm conditions.
         * @details The maximum number of physiological alarm conditions that can be present at a point of time.
         * @return The maximum number or \c boost::none if unlimited.
         */
        boost::optional<MaxPhysiologicalParallelAlarms> maxPhysiologicalAlarmListEntries() const;

        /**
         * @brief Maximum number of technical alarm conditions.
         * @details The maximum number of technical alarm conditions that can be present at a point of time.
         * @return The maximum number or \c boost::none if unlimited.
         */
        boost::optional<MaxTechnicalParallelAlarms> maxTechnicalAlarmListEntries() const;

        /**
         * @brief Self check time period.
         * @details The self check time period defines the value after which a self test of the \ref AlertSystem is performed.
         * This self check period may be used to detect if an \ref AlertSystem is still operating.
         * @return The self check period or \c boost::none if no self check period exists.
         */
        const boost::optional<Duration>& selfCheckPeriod() const;

    private:
        boost::optional<MaxPhysiologicalParallelAlarms> m_maxPhysiologicalAlarmListEntries{};
        boost::optional<MaxTechnicalParallelAlarms> m_maxTechnicalAlarmListEntries{};
        boost::optional<Duration> m_selfCheckPeriod{};
};

inline AlertSystemDescriptor::AlertSystemDescriptor(SafetyClassification safetyClassification,
                                                    boost::optional<CodedValue>&& type,
                                                    boost::optional<MaxPhysiologicalParallelAlarms> maxPhysiologicalAlarmListEntries,
                                                    boost::optional<MaxTechnicalParallelAlarms> maxTechnicalAlarmListEntries,
                                                    boost::optional<Duration> selfCheckPeriod,
                                                    ExtensionTypes extensions) :
        AbstractDescriptor(safetyClassification, std::move(type), std::move(extensions)),
        m_maxPhysiologicalAlarmListEntries(std::move(maxPhysiologicalAlarmListEntries)),
        m_maxTechnicalAlarmListEntries(std::move(maxTechnicalAlarmListEntries)),
        m_selfCheckPeriod(std::move(selfCheckPeriod))
{
}

inline AlertSystemDescriptor::AlertSystemDescriptor(SafetyClassification safetyClassification,
                                                    const boost::optional<CodedValue>& type,
                                                    boost::optional<MaxPhysiologicalParallelAlarms> maxPhysiologicalAlarmListEntries,
                                                    boost::optional<MaxTechnicalParallelAlarms> maxTechnicalAlarmListEntries,
                                                    boost::optional<Duration> selfCheckPeriod,
                                                    ExtensionTypes extensions) :
        AbstractDescriptor(safetyClassification, type, std::move(extensions)),
        m_maxPhysiologicalAlarmListEntries(std::move(maxPhysiologicalAlarmListEntries)),
        m_maxTechnicalAlarmListEntries(std::move(maxTechnicalAlarmListEntries)),
        m_selfCheckPeriod(std::move(selfCheckPeriod))
{
}

inline boost::optional<MaxPhysiologicalParallelAlarms> AlertSystemDescriptor::maxPhysiologicalAlarmListEntries() const
{
    return m_maxPhysiologicalAlarmListEntries;
}

inline boost::optional<MaxTechnicalParallelAlarms> AlertSystemDescriptor::maxTechnicalAlarmListEntries() const
{
    return m_maxTechnicalAlarmListEntries;
}

inline const boost::optional<Duration>& AlertSystemDescriptor::selfCheckPeriod() const
{
    return m_selfCheckPeriod;
}

/**
 * @brief Definition of shared pointer type \ref AlertSystemDescriptorSharedPtr for descriptor \ref AlertSystemDescriptor.
 * @ingroup Mdib
 */
using AlertSystemDescriptorSharedPtr = SharedPtr<AlertSystemDescriptor>;


} /* namespace Mdib */
} /* namespace DFL */
