#pragma once

#include <S31/Sdc/Private/Client/SetService/SetOperationBaseJob.h>
#include <S31/Sdc/Private/Common/SetService/EnhancedProposedContextStates.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Model/Handle.h>

#include <memory>

namespace S31::Sdc::Impl
{
/**
 * @brief SDC SetContextState operation job.
 * @ingroup S31SdcClient
 */
class S31_CORE_EXPIMP SetContextJob : public SetOperationBaseJob
{
    public:
        SetContextJob(const std::string& urn,
                      const std::string& transportAddr,
                      const SetService::OperationHandle& operationHandle,
                      const DFL::NotNull<std::shared_ptr<S31::SetService::ClientTransactionWriter>>& transactionWriter,
                      const Safety::Information& safetyInformation,
                      const DFL::Mdib::ExtensionTypes& extensions,
                      const S31::Utils::OutcomeTypes::HandlerPtr<SetOperationJobResult>& handler,
                      EnhancedProposedContextStates data);

        void processRequest() override;

        boost::optional<std::string> firstChannelValue(const S31::Safety::DualChannelId& channelId ) const override;

    private:
        template<class T_Ctxt, class T_GsoapState>
        void constructProposedContextState(_msg__SetContextState* request) const;

        EnhancedProposedContextStates m_proposedContextStates;

};

}
