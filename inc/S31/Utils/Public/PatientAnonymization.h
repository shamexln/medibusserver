#pragma once

#include <Framework/Mdib/Public/Model/Context/PatientContextState.h>

namespace S31::PatientAnonymization
{

#ifdef S31_TEST_DISABLE_ANONYMIZED_LOGGING
#pragma message("Anonymization for patient logging DISABLED")
#endif

/***
 * @brief Anonymize a patient.
 * @param patient The patient context
 * @return A copy of given PatientContextState, but without PatientDemographicsCoreData and identifications.
 * @ingroup S31Utils
 */
inline DFL::Mdib::PatientContextState anonymize(const DFL::Mdib::PatientContextState& patient)
{
#ifdef S31_TEST_DISABLE_ANONYMIZED_LOGGING
    return patient;
#else
    return {patient.category(),
            patient.contextAssociation(),
            patient.bindingMdibVersion(),
            patient.unbindingMdibVersion(),
            patient.bindingStartTime(),
            patient.bindingEndTime(),
            patient.validators(),
            {},           // no identifications
            boost::none,  // no patient demographics
            patient.extensions()};
#endif
}

}
