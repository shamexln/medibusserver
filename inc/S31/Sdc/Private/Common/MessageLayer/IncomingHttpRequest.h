#pragma once

#include <S31/Sdc/Public/Common/Job.h>
#include <S31/Sdc/Private/Common/MessageLayer/IncomingNetworkRequest.h>
#include <S31/S31CoreExImp.h>

namespace S31::Sdc::Impl
{
class SocketStore;
class INotifyDestruction;

/**
 * @brief Abstract base for HTTP requests.
 * @details Will be used for new and keep-alive requests.
 * @ingroup S31SdcCommonWebServices
 */
class S31_CORE_EXPIMP IncomingHttpRequest: public IncomingNetworkRequest, public Job
{
    public:
        ~IncomingHttpRequest() noexcept override;

        void execute() override;

        void injectDestructorWatch(std::weak_ptr<INotifyDestruction> destructionWatch);

    protected:
        IncomingHttpRequest(DFL::NotNull<SoapPtr> soapPtrIn, std::shared_ptr<IWebService> webService,
                std::weak_ptr<SocketStore> sockStoreIn);

        /**
         * Registers HTTP GET callback for WSDL retrieval.
         */
        void preReceiveHook() override;

        /**
         * Implements keep-alive by storing the TCP connection.
         */
        void postDispatchHook() override;

        /**
         * Implements logging of processing errors.
         */
        void logOnError() override;

    private:
        std::weak_ptr<SocketStore> m_weakSocketStore;
        std::weak_ptr<INotifyDestruction> m_destructionWatch;
};

}
