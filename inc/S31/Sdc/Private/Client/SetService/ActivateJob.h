#pragma once

#include <S31/Sdc/Private/Client/SetService/SetOperationBaseJob.h>
#include <S31/SetService/Public/Common/Argument.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Model/Handle.h>

#include <memory>

namespace S31::Sdc::Impl
{

/**
 * @brief SDC Activate operation job.
 * @ingroup S31SdcClient
 */
class S31_CORE_EXPIMP ActivateJob : public SetOperationBaseJob
{
    public:
        ActivateJob(const std::string& urn,
                    const std::string& transportAddr,
                    const SetService::OperationHandle& operationHandle,
                    const DFL::NotNull<std::shared_ptr<S31::SetService::ClientTransactionWriter>>& transactionWriter,
                    const Safety::Information& safetyInformation,
                    const DFL::Mdib::ExtensionTypes& extensions,
                    const S31::Utils::OutcomeTypes::HandlerPtr<SetOperationJobResult>& handler,
                    S31::SetService::Arguments arguments);

        void processRequest() override;

        boost::optional<std::string> firstChannelValue(const S31::Safety::DualChannelId& channelId) const override;

    private:
        S31::SetService::Arguments m_arguments;
};

}
