#pragma once

#include <S31/SetService/Public/Device/InvocationCallbackRegistry.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>

namespace S31::Osf
{

/**
 * @ingroup S31OsfDevice
 */
using ProposedPatientCallback = std::function<void(const DFL::Mdib::PatientContextState&, const DFL::Mdib::Handle& operationHandle, SetService::SynchronousDeviceTransaction&)>;

/**
 * @brief SDC device functionality to receive proposed PatientContextState messages from network.
 * @ingroup S31OsfDevice
 */
class S31_CORE_EXPIMP ProposedPatientReceiver final
{
    public:
        /**
         * @brief Registers the callback for new patient admission.
         * @details
         * It registers the given callback in the %SetService for the OSF admit patient operation and
         * enables the operation (\ref DFL::Mdib::OperatingMode::Enabled).
         * The operation has to be in the MDIB with correct type (MDC_ACT_ADMIT_PT, IEEE code 68610) and target operation set to
         * \ref DFL::Mdib::PatientContextDescriptor "PatientContextDescriptor".
         *
         * The MDC_ACT_ADMIT_PT is for new patients only, while MDC_ACT_PDMO_TXN (Patient Demographics Transaction)
         * is for updating patient data.
         *
         * MDC_ACT_PDMO_TXN description:
         * > An Operation to update one or more details of the patient demographics as a transaction.
         * > Note: Used to synchronize patient demographic objects if different participants have parts of the patient demographics.
         *
         * For more information see:
         *  - https://sourceforge.net/p/opensdc/p11073-10107-content-gathering/3/
         *  - https://sourceforge.net/p/opensdc/p11073-10107-content-gathering/2/
         *
         * @param proposedPatientCallback Callback will be called with proposed patient to admit.
         * @param invocationCallbackRegistry Source for incoming network operation.
         * @param mdibAccess Mdib with patient operation to use.
         */
        ProposedPatientReceiver(const ProposedPatientCallback& proposedPatientCallback,
                                const DFL::NotNull<std::shared_ptr<SetService::InvocationCallbackRegistry>>& invocationCallbackRegistry,
                                const DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr>& mdibAccess);

        ProposedPatientReceiver(const ProposedPatientReceiver&) = default;
        ProposedPatientReceiver& operator=(const ProposedPatientReceiver&) = default;

        /**
         * @brief Unregisters the callback from SetService and sets MDIB operation to \ref DFL::Mdib::OperatingMode::Disabled.
         */
        ~ProposedPatientReceiver() noexcept;

    private:
        class Impl;
        DFL::NotNull<std::shared_ptr<Impl>> m_impl;
};

}
