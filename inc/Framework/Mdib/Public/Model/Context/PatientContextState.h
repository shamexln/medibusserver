#pragma once

#include <Framework/Mdib/Public/Model/Context/AbstractContextState.h>
#include <Framework/Mdib/Public/Model/Context/PatientDemographicsCoreData.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <boost/optional.hpp>

namespace DFL::Mdib
{

/**
 * @brief Dynamic part of a \ref PatientContext.
 * @ingroup Mdib
 */
class PatientContextState: public AbstractContextState
{

    DFL_MDIB_IMMUTABLE(PatientContextState)

    public:
        /**
         * @brief Applies \ref PatientContextState::patientDemographicsCoreData() "patient demographics core data" to none
         * @details \note Also applies defaults from \ref AbstractContextState.
         */
        PatientContextState() = default;

        /**
         * @brief Full constructor.
         */
        PatientContextState(const boost::optional<CodedValue>& category,
                            ContextAssociation contextAssociation,
                            const boost::optional<VersionCounter>& bindingMdibVersion,
                            const boost::optional<VersionCounter>& unbindingMdibVersion,
                            const boost::optional<Timestamp>& bindingStartTime,
                            const boost::optional<Timestamp>& bindingEndTime,
                            const InstanceIdentifiers& validators,
                            const InstanceIdentifiers& identifications,
                            const boost::optional<PatientDemographicsCoreData>& patientDemographicsCoreData,
                            ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Demographics data as defined in ISO/IEEE 11073-10201:2004 (6.10.1 Patient Demographics object).
         * @details If the medical device itself has patient-related observations (e.g., weight, height, etc.) as
         * in- or output, these should be modeled as metrics.
         *
         * \note In contrast to \ref PatientDemographicsCoreData, metrics provide a sophisticated observation description, e.g.,
         * regarding quality and time-related attributes.
         * \note \ref PatientDemographicsCoreData is intended to be used for information purposes only. Whenever a
         * value is available, it is considered as valid. Invalid values shall not be transmitted.
         * @return Patient demographics data or \c boost::none if information is invalid.
         */
        const boost::optional<PatientDemographicsCoreData>& patientDemographicsCoreData() const;

    private:
        boost::optional<PatientDemographicsCoreData> m_patientDemographicsCoreData{boost::none};
};

inline PatientContextState::PatientContextState(const boost::optional<CodedValue>& category,
                                                ContextAssociation contextAssociation,
                                                const boost::optional<VersionCounter>& bindingMdibVersion,
                                                const boost::optional<VersionCounter>& unbindingMdibVersion,
                                                const boost::optional<Timestamp>& bindingStartTime,
                                                const boost::optional<Timestamp>& bindingEndTime,
                                                const InstanceIdentifiers& validators,
                                                const InstanceIdentifiers& identifications,
                                                const boost::optional<PatientDemographicsCoreData>& patientDemographicsCoreData, // NOLINT(modernize-pass-by-value)
                                                ExtensionTypes extensions) :
        AbstractContextState(category,
                             contextAssociation,
                             bindingMdibVersion,
                             unbindingMdibVersion,
                             bindingStartTime,
                             bindingEndTime,
                             validators,
                             identifications,
                             std::move(extensions)),
        m_patientDemographicsCoreData(patientDemographicsCoreData)
{
}

inline const boost::optional<PatientDemographicsCoreData>& PatientContextState::patientDemographicsCoreData() const
{
    return m_patientDemographicsCoreData;
}

/**
 * @brief Definition of shared pointer type \ref PatientContextStateSharedPtr for state \ref PatientContextState.
 * @ingroup Mdib
 */
using PatientContextStateSharedPtr = SharedPtr<PatientContextState>;

}
