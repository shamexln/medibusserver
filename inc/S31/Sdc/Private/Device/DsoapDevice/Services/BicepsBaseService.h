#pragma once

#include <S31/Error/Public/GeneratedRemosErrorCodes.h>
#include <S31/Log/Public/Logger.h>
#include <S31/Safety/Public/Context.h>
#include <S31/Safety/Public/DualChannel.h>
#include <S31/Safety/Public/Information.h>
#include <S31/Safety/Public/Requirement.h>
#include <S31/Safety/Public/SerializableInformation.h>
#include <S31/Sdc/Private/Common/GsoapMapper/MessageModel/MessageSetServiceMapper.h>
#include <S31/BicepsXml/S31Only/ParticipantBaseMapper.h>
#include <S31/Sdc/Private/Common/GsoapMapper/SafetyModel/SafetyMapper.h>
#include <S31/Sdc/Private/Common/Messaging/SoapHeaderUtils.h>
#include <S31/Sdc/Private/Common/SafetyRequirementsHelper.h>
#include <S31/Sdc/Private/Device/DsoapDevice/LocalDevice.h>
#include <S31/Sdc/Public/Device/DualChannelFactoryManager.h>
#include <S31/SetService/Public/Common/Argument.h>
#include <S31/SetService/Public/Device/ScoController.h>

#include <Framework/Mdib/Public/LatestMdibSmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/MdibVersion.h>
#include <Framework/Utils/Public/CompilerGenerated.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapGetServiceBindingService.h>

#include <any>
#include <string>
#include <string_view>

namespace S31::Sdc::Impl
{
/*!
 * \brief Enum used to indicate whether \ref S31::Safety::DualChannel mapping is required for a particular set operation
 *
 * \ingroup S31SdcDevice
 */
enum class DualChannelMapping
{
    IsRequired,
    NotApplicable
};
DFL_ENUM_CLASS_STREAM_OPERATOR(DualChannelMapping, (IsRequired)(NotApplicable))

/*!
 * \brief Base implementation of Web Services for BICEPS.
 *
 * All BICEPS service shall inherit from this class to avoid duplicate implementation.
 * \ingroup S31SdcDevice
 */
class BicepsBaseService: protected GetServiceBindingService
{
        // gSOAP assign and copy do not work as expected (Coverity findings)
        DFL_NOT_COPYABLE(BicepsBaseService)

    protected:
        explicit BicepsBaseService(struct soap* soapHandle);

        /**
         * @brief Extracts dual channel and context information from SOAP header block.
         */
        Safety::SerializableInformation extractSafetyInformation() const;

        template<class T_Request, class T_Response, class T_IncomingData, class T_MappingFunc>
        int handleSetOperation(
                T_Request*                                                      request,
                T_Response&                                                     response,
                std::string_view                                                replyActionUri,
                const std::weak_ptr<SetService::ScoController>&                 weakScoController,
                const DFL::Mdib::LatestMdibWeakPtr&                             weakLatestMdib,
                const DFL::NotNull<std::shared_ptr<DualChannelFactoryManager>>& dualChannelFactoryManager,
                const std::weak_ptr<Sdc::Impl::SubscriberInfo>&                 weakSubscriberInfo,
                const DualChannelMapping&                                       dualChannelMapping,
                const T_IncomingData&                                           incomingData,
                T_MappingFunc                                                   mapperFunc,
                const SetService::ClientInformation&                            clientInfo);

        template<class T_Request>
        static void writeFailureToServiceLog(unsigned int remosCode,
                                             const std::string& messageStart,
                                             T_Request* request,
                                             const S31::Safety::SerializableInformation& safetyInfo,
                                             const std::string& reason);

        template<class T_Request>
        int mapAndCheckInvocationInfo(T_Request* request,
                                      msg__AbstractSetResponse& resp,
                                      const SetService::InitialInvocationInfo& initialInvocationInfo);
private:
        static Safety::DualChannel mapIncomingDualChannel(const Safety::DualChannelHashes& dcHashes,
                                                          const Sdc::DualChannelFactoryManager& dualChannelFactoryManager,
                                                          const std::string& incomingStr);

};

template<class T_Request, class T_Response, class T_IncomingData, class T_MappingFunc>
inline int BicepsBaseService::handleSetOperation(
        T_Request*                                                      request,
        T_Response&                                                     response,
        std::string_view                                                replyActionUri,
        const std::weak_ptr<SetService::ScoController>&                 weakScoController,
        const DFL::Mdib::LatestMdibWeakPtr&                             weakLatestMdib,
        const DFL::NotNull<std::shared_ptr<DualChannelFactoryManager>>& dualChannelFactoryManager,
        const std::weak_ptr<Sdc::Impl::SubscriberInfo>&                 weakSubscriberInfo,
        const DualChannelMapping&                                       dualChannelMapping,
        const T_IncomingData&                                           incomingData,
        T_MappingFunc                                                   mapperFunc,
        const SetService::ClientInformation&                            clientInfo)
{
    const auto& incomingSafetyInformation = extractSafetyInformation();

    int const gsoapError = S31::Sdc::Impl::SoapHeaderUtils::prepareReply(request->soap, replyActionUri);
    if (gsoapError != SOAP_OK)
    {
        return gsoapError;
    }

    auto latestMdib = weakLatestMdib.lock();
    if (!latestMdib)
    {
        writeFailureToServiceLog<T_Request>(S31::Error::RemosCodes::REMOS_ERR_SET_OPERATION_INVOCATION_FAILURE, "BicepsBaseService: invocation failure ", request, incomingSafetyInformation, "Local MDIB not found");
        return SoapHeaderUtils::prepareSoapReceiverFault(request->soap, "Local MDIB not found", nullptr);
    }

    auto scoController = weakScoController.lock();
    if (!scoController)
    {
        writeFailureToServiceLog<T_Request>(S31::Error::RemosCodes::REMOS_ERR_SET_OPERATION_INVOCATION_FAILURE, "BicepsBaseService: invocation failure ", request, incomingSafetyInformation, "SCO controller not found");
        return SoapHeaderUtils::prepareSoapReceiverFault(request->soap, "SCO controller not found", nullptr);
    }

    auto subscriberInfo = weakSubscriberInfo.lock();
    if (!subscriberInfo)
    {
        S31_STREAM_TRACE_LOGGER("S31.Sdc", "BicepsSetService: Subscriber information not available");
        return SoapHeaderUtils::prepareSoapReceiverFault(request->soap, "Subscriber information not found", nullptr);
    }
    if (!subscriberInfo->hasSubscriber(clientInfo.distinguishedName()))
    {
        S31_STREAM_TRACE_LOGGER("S31.Sdc", "BicepsSetService: Client has not subscribed for OperationInvokedReports in advance");
        return SoapHeaderUtils::prepareSoapSenderFault(request->soap, "Client has not subscribed for OperationInvokedReports in advance", nullptr);
    }

    auto mdib = latestMdib->latestMdib();
    auto operationHandleVariant = S31::Sdc::Impl::SafetyRequirementsHelper::findTypedOperationHandle(request->OperationHandleRef, *mdib);
    if (!operationHandleVariant)
    {
        DFL::Format::Stream msg;
        msg << "Unknown OperationHandleRef: ";
        if (request->OperationHandleRef.string().size() <= 100)
        {
            msg << request->OperationHandleRef;
        }
        else
        {
            msg << request->OperationHandleRef.string().substr(0, 100) << "...";
        }
        return SoapHeaderUtils::prepareSoapSenderFault(request->soap, msg.cStr(), nullptr);
    }

    Safety::DualChannel dualChannel;
    if (dualChannelMapping == DualChannelMapping::IsRequired)
    {
        // The std::any_cast only works if incomingData actually contains a string.
        // Therefore, dual channel mapping only works with SetString and SetValue for now.
        dualChannel = mapIncomingDualChannel(incomingSafetyInformation.dualChannel(), *dualChannelFactoryManager, std::any_cast<std::string>(incomingData));
    }

    auto serviceExtensions = Sdc::Impl::Gsoap::ParticipantBaseMapper::mapExtensionsFromGsoap(request->ext__Extension);

    try
    {
        auto mappedIncomingData = mapperFunc(incomingData, mdib);
        try
        {
            auto initialInvocationInfo = scoController->handleRequest(request->OperationHandleRef, mappedIncomingData, incomingSafetyInformation.context(), dualChannel, clientInfo, serviceExtensions);
            Sdc::Impl::Gsoap::MessageSetServiceMapper::mapInitialInvocationInfoToGsoap(response, initialInvocationInfo);
            return mapAndCheckInvocationInfo<T_Request>(request, response, initialInvocationInfo);
        }
        catch (const std::exception& exception)
        {
            writeFailureToServiceLog<T_Request>(S31::Error::RemosCodes::REMOS_ERR_SET_OPERATION_INVOCATION_FAILURE, "BicepsBaseService: invocation failure ", request, incomingSafetyInformation, exception.what());
            DFL::Format::Stream msg;
            msg << "Invocation failed with: " << exception.what();
            return SoapHeaderUtils::prepareSoapReceiverFault(request->soap, msg.cStr(), nullptr);
        }
    }
    catch (const std::exception& exception)
    {
        writeFailureToServiceLog<T_Request>(S31::Error::RemosCodes::REMOS_ERR_SET_OPERATION_INVOCATION_FAILURE, "BicepsBaseService: mapping failure ", request, incomingSafetyInformation, exception.what());
        DFL::Format::Stream msg;
        msg << "Data mapping failed with: " << exception.what();
        return SoapHeaderUtils::prepareSoapSenderFault(request->soap, msg.cStr(), nullptr);
    }
}

template<class T_Request>
inline int BicepsBaseService::mapAndCheckInvocationInfo(T_Request* request,
                                                        msg__AbstractSetResponse& resp,
                                                        const SetService::InitialInvocationInfo& initialInvocationInfo)
{
    const auto& incomingSafetyInformation = extractSafetyInformation();
    Sdc::Impl::Gsoap::MessageSetServiceMapper::mapInitialInvocationInfoToGsoap(resp, initialInvocationInfo);
    if (initialInvocationInfo.invocationState() == SetService::InvocationState::Started
        || initialInvocationInfo.invocationState() == SetService::InvocationState::Waiting
        || initialInvocationInfo.invocationState() == SetService::InvocationState::Finished
        || initialInvocationInfo.invocationState() == SetService::InvocationState::FinishedWithModification)
    {
        return SOAP_OK;
    }

    const auto& errorMessages = initialInvocationInfo.errorMessages();
    if (!errorMessages.empty())
    {
        // in case that there are messages, suppose that there is already a log message.
        return SOAP_OK;
    }
    writeFailureToServiceLog<T_Request>(S31::Error::RemosCodes::REMOS_ERR_SET_OPERATION_INVOCATION_FAILURE, "BicepsBaseService: invocation failure ", request, incomingSafetyInformation, "No appropriate initial invocation report");
    return SoapHeaderUtils::prepareSoapReceiverFault(request->soap, "No appropriate initial invocation report", nullptr);
}

}
