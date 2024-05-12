#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/LocalMdibAccess.h>
#include <Framework/Mdib/Public/Model/Context/LocationContext.h>
#include <Framework/Mdib/Public/Model/Context/PatientContext.h>

namespace S31::Osf
{
/**
 * @brief Infers patient and location context states to ensembles contexts automatically.
 * @details
 * When there is a EnsembleContextDescriptor of type
 * MDC_IDT_ENSEMBLE_LOCATION_INFERRED or
 * MDC_IDT_ENSEMBLE_PATIENT_INFERRED in the MDIB,
 * this helper will create/update ensemble context states for them according to
 * location and patient context states.
 *
 * @ingroup S31OsfDevice
 */
class S31_CORE_EXPIMP InferContextStates
{
    public:
        /**
         * @brief Write the context state update to the MDIB with inferred ensemble context.
         * @param mdibAccess The %MDIB to write context state changes.
         * @param location The new location to set in the MDIB.
         */
        static DFL::Mdib::WriteResult writeContext(DFL::Mdib::LocalMdibAccess& mdibAccess,
                                                   const DFL::NotNull<DFL::Mdib::LocationContextSharedPtr>& location);

        /**
         * @brief Write the context state update to the MDIB with inferred ensemble context.
         * @param mdibAccess The %MDIB to write context state changes.
         * @param patient The new patient to set in the MDIB.
         */
        static DFL::Mdib::WriteResult writeContext(DFL::Mdib::LocalMdibAccess& mdibAccess,
                                                   const DFL::NotNull<DFL::Mdib::PatientContextSharedPtr>& patient);

        /**
         * @brief Write the context state update to the MDIB with inferred ensemble context.
         * @param mdibAccess The %MDIB to write context state changes.
         * @param patient The new patient to set in the MDIB.
         * @param location The new location to set in the MDIB.
         */
        static DFL::Mdib::WriteResult writeContext(DFL::Mdib::LocalMdibAccess& mdibAccess,
                                                   const DFL::NotNull<DFL::Mdib::PatientContextSharedPtr>& patient,
                                                   const DFL::NotNull<DFL::Mdib::LocationContextSharedPtr>& location);
};

}
