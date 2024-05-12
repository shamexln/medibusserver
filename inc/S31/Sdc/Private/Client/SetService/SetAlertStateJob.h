#pragma once

#include <S31/Sdc/Private/Client/SetService/SetOperationBaseJob.h>

#include <Framework/Mdib/Public/Model/Handle.h>

#include <memory>

namespace S31::Sdc::Impl
{

/**
 * @brief SDC SetAlertState operation job.
 * @ingroup S31SdcClient
 */
template<class T_Payload, class T_GsoapState>
class SetAlertStateJob: public SetOperationBaseJob
{
    public:
        SetAlertStateJob(const std::string& urn,
                         const std::string& transportAddr,
                         const SetService::OperationHandle& operationHandle,
                         const DFL::NotNull<std::shared_ptr<S31::SetService::ClientTransactionWriter> >& transactionWriter,
                         const Safety::Information& safetyInformation,
                         const DFL::Mdib::ExtensionTypes& extensions,
                         const S31::Utils::OutcomeTypes::HandlerPtr<SetOperationJobResult>& handler,
                         const T_Payload& payload); // NOLINT(modernize-pass-by-value)

        void processRequest() override;

        boost::optional<std::string> firstChannelValue(const S31::Safety::DualChannelId& channelId) const override;

    private:
        T_Payload m_data;
};

}
