#pragma once

#include <boost/optional/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Utils/Public/LanguageTag.h>
#include <Framework/Mdib/Public/Model/Component/AbstractDeviceComponentState.h>
#include <Framework/Mdib/Public/Model/Component/MdsOperatingMode.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Definition of the state of an \ref MdsDescriptor.
 * @ingroup Mdib
 */
class MdsState: public AbstractDeviceComponentState
{
    DFL_MDIB_IMMUTABLE(MdsState)

    public:
        /**
         * @brief Defaults to \ref ComponentActivation::On "component activation on"
         * in \ref MdsOperatingMode::Normal "operating mode normal"
         * with current locale \ref Locale::LanguageTag "\"en\"".
         */
        MdsState() = default;

        /**
         * @brief Constructor.
         */
        MdsState(ComponentActivation activationState,
                 const boost::optional<Chrono::Hours>& operatingHours,
                 const boost::optional<OperatingCycles>& operatingCycles,
                 const boost::optional<CalibrationInfo>& calibrationInfo,
                 const boost::optional<CalibrationInfo>& nextCalibrationInfo,
                 const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                 Locale::LanguageTag lang,
                 MdsOperatingMode operatingMode,
                 const boost::optional<InstanceIdentifier>& operatingJurisdiction,
                 ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Current locale information.
         * @details Configured for an MDS in accordance with RFC 5646 (see http://tools.ietf.org/html/rfc5646).
         *
         * \note For example, this is the language that is used for display purposes on the UI.
         */
        const Locale::LanguageTag& lang() const;

        /**
         * @brief The operating mode of an \ref Mds.
         */
        MdsOperatingMode operatingMode() const;

        /**
         * @brief The current region information that is configured for the \ref Mds.
         * @return Region information or \c boost::none if not configured.
         */
        const boost::optional<InstanceIdentifier>& operatingJurisdiction() const;

    private:
        Locale::LanguageTag m_lang{"en"};
        MdsOperatingMode m_operatingMode{MdsOperatingMode::Normal};
        boost::optional<InstanceIdentifier> m_operatingJurisdiction{};
};

inline MdsState::MdsState(ComponentActivation activationState,
                          const boost::optional<Chrono::Hours>& operatingHours,
                          const boost::optional<OperatingCycles>& operatingCycles,
                          const boost::optional<CalibrationInfo>& calibrationInfo,
                          const boost::optional<CalibrationInfo>& nextCalibrationInfo,
                          const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                          Locale::LanguageTag lang,
                          MdsOperatingMode operatingMode,
                          const boost::optional<InstanceIdentifier>& operatingJurisdiction, // NOLINT(modernize-pass-by-value)
                          ExtensionTypes extensions) :
        AbstractDeviceComponentState(activationState, operatingHours, operatingCycles, calibrationInfo, nextCalibrationInfo, physicalConnector, std::move(extensions)),
        m_lang(std::move(lang)),
        m_operatingMode(operatingMode),
        m_operatingJurisdiction(operatingJurisdiction)
{
}


inline const Locale::LanguageTag& MdsState::lang() const
{
    return m_lang;
}

inline MdsOperatingMode MdsState::operatingMode() const
{
    return m_operatingMode;
}

inline const boost::optional<InstanceIdentifier>& MdsState::operatingJurisdiction() const
{
    return m_operatingJurisdiction;
}

/**
 * @brief Definition of shared pointer type \ref MdsStateSharedPtr for state \ref MdsState.
 * @ingroup Mdib
 */
using MdsStateSharedPtr = SharedPtr<MdsState>;


} /* namespace Mdib */
} /* namespace DFL */
