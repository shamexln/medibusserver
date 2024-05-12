#pragma once

#include <S31/Safety/Public/Information.h>
#include <S31/Sdc/Private/Common/DsoapCommon/WebServiceConstants.h>
#include <S31/Sdc/Private/Common/Messaging/OutgoingBlockingHttpRequestWithOutcome.h>
#include <S31/Sdc/Private/Common/Messaging/OutgoingDualChannel.h>
#include <S31/Sdc/Private/Common/Messaging/OutgoingSafetyContext.h>
#include <S31/SetService/Public/Client/ClientTransactionWriter.h>
#include <S31/SetService/Public/Common/OperationHandle.h>
#include <S31/Utils/Public/Outcome.h>
#include <S31/S31CoreExImp.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapGetServiceBindingProxy.h>
#include <S31/Gsoap/S31Only/generated/gsoap/soapStub.h>

#include <memory>
#include <string>
#include <string_view>

namespace S31::Sdc::Impl
{

/**
 * @brief Outcome result of @ref SetOperationBaseJob.
 * @ingroup S31SdcClient
 */
struct SetOperationJobResult
{
};

/**
 * @brief Base job for SDC set operations on remote devices.
 *
 * @details This class provides common implementations for
 * parts of the set operation processing which could be
 * used by all children.
 *
 * @ingroup S31SdcClient
 */
class S31_CORE_EXPIMP SetOperationBaseJob : public Sdc::Impl::OutgoingBlockingHttpRequestWithOutcome<SetOperationJobResult>
{
    public:
        SetOperationBaseJob(std::string jobTypeName,
                            std::string_view soapAction,
                            std::string eprAddress,
                            const std::string& transportAddr,
                            const S31::SetService::OperationHandle& operationHandle,
                            DFL::NotNull<std::shared_ptr<S31::SetService::ClientTransactionWriter>> transactionWriter,
                            Safety::Information safetyInformation,
                            DFL::Mdib::ExtensionTypes extensions,
                            const S31::Utils::OutcomeTypes::HandlerPtr<SetOperationJobResult>& handler);

        ~SetOperationBaseJob() noexcept override = default;

    protected:
        std::string jobName() const override;

        void processResponse(const std::optional<Utils::Error>& error, const msg__AbstractSetResponse& response);

        virtual boost::optional<std::string> firstChannelValue(const S31::Safety::DualChannelId& channelId) const = 0;

        void addSafetyContext(struct soap* soapHandle);
        void addDualChannel(struct soap* soapStruct);

        GetServiceBindingProxy prepareSoapStructs(msg__AbstractSet& request, msg__AbstractSetResponse& response);

        std::string m_jobTypeName;
        std::string m_soapAction;
        std::string m_remoteDeviceEprAddress;
        std::string m_transportAddr;
        S31::SetService::OperationHandle m_operationHandle;
        DFL::NotNull<std::shared_ptr<S31::SetService::ClientTransactionWriter>> m_transactionWriter;
        Safety::Information m_safetyInformation;
        DFL::Mdib::ExtensionTypes m_extensions;

};

}
