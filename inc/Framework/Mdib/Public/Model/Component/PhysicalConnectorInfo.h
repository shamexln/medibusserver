#pragma once

#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/HasExtensions.h>
#include <Framework/Mdib/Public/Model/LocalizedTexts.h>

#include <Framework/Utils/Public/SkillBoostSerializable.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <boost/optional/optional.hpp>

#include <cstdint>
#include <utility>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
struct PysicalConnectorNumberTag;
}

/**
 * @brief Designates the connector number of a physical connector.
 * @ingroup Mdib
 */
using PhysicalConnectorNumber = DFL::StrongTypedef<int32_t, Impl::PysicalConnectorNumberTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable, DFL::Skill::BoostSerializable>;

/**
 * @brief Defines a number in order to allow to guide the clinical user for failure.
 * @details E.g., in case of a disconnection of a sensor or an ultrasonic handpiece.
 * @ingroup Mdib
 */
class PhysicalConnectorInfo: public Impl::HasExtensions
{
    public:
        /**
         * @brief Default constructor without number, label and extensions.
         */
        PhysicalConnectorInfo() = default;

        /**
         * @brief Constructor.
         */
        PhysicalConnectorInfo(boost::optional<PhysicalConnectorNumber> number,
                              LocalizedTexts labels,
                              ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Number designates the connector number of the physical connector.
         * @return Connector number or \c boost::none if no number is available.
         */
        boost::optional<PhysicalConnectorNumber> number() const;

        /**
         * @brief A human-readable label that describes the physical connector.
         */
        const LocalizedTexts& labels() const;

    private:
        boost::optional<PhysicalConnectorNumber> m_number;
        LocalizedTexts m_labels;
};

DFL_MDIB_EXPIMP bool operator==(const PhysicalConnectorInfo& lhs, const PhysicalConnectorInfo& rhs);
DFL_MDIB_EXPIMP bool operator!=(const PhysicalConnectorInfo& lhs, const PhysicalConnectorInfo& rhs);

inline PhysicalConnectorInfo::PhysicalConnectorInfo(boost::optional<PhysicalConnectorNumber> number,
                                                    LocalizedTexts labels,
                                                    ExtensionTypes extensions):
        Impl::HasExtensions(std::move(extensions)),
        m_number(std::move(number)),
        m_labels(std::move(labels))
{
}

inline boost::optional<PhysicalConnectorNumber> PhysicalConnectorInfo::number() const
{
        return m_number;
}

inline const LocalizedTexts& PhysicalConnectorInfo::labels() const
{
        return m_labels;
}

}
}
