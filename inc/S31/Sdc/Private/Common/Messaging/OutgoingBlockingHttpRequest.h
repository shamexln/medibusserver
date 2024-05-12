#pragma once

#include <S31/Gsoap/S31Only/stdsoap2.h>
#include <S31/Sdc/Private/Common/Http/CreateRequestBody.h>
#include <S31/Sdc/Private/Common/Http/HttpResultCallback.h>
#include <S31/Sdc/Private/Common/Http/VerifyRequestPreconditions.h>
#include <S31/Sdc/Private/Common/ISoapContextPool.h>
#include <S31/Sdc/Private/Common/MessageLayer/GsoapEpr.h>
#include <S31/Sdc/Public/Common/Job.h>
#include <S31/Utils/Public/Errors.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Chrono/Public/SystemClock.h>
#include <Framework/Chrono/Public/ChronoIo.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/Oids.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <optional>
#include <memory>
#include <functional>

namespace S31::Sdc::Impl
{
class IOutgoingJobQueue;
class INotifyDestruction;
class HttpClientRegistry;
class HttpResult;
class HttpClient;

struct RequiredPeerRolesTag;
using RequiredPeerRoles = DFL::StrongTypedef<DFL::Oids, RequiredPeerRolesTag>;

/**
 * @brief The part of @ref OutgoingBlockingHttpRequestWithOutcome that is unrelated to @ref S31::Utils::Outcome.
 * @details
 * This class allows injection of soap context structures after
 * creation to allow late allocation of gSOAP soap structures.
 * @ingroup S31SdcCommonScheduling
 */
class S31_CORE_EXPIMP OutgoingBlockingHttpRequest: public Job
{
    public:
        ~OutgoingBlockingHttpRequest() noexcept override;

        void setSoapContextPool(std::weak_ptr<ISoapContextPool> soapPool);

        void setJobQueue(std::weak_ptr<IOutgoingJobQueue> queue);

        void setHttpClientRegistry(std::weak_ptr<HttpClientRegistry> httpClientRegistry);

        /**
         * @brief Execute the job.
         * @details The request and response handling is implemented in @ref processRequest().
         */
        void execute(const std::shared_ptr<Job>& self) final;

        /**
         * @brief Execute http request completion
         * @details The response handling is implemented in @ref processHttpResult().
         */
        void httpRequestCompletion(const HttpResult& result);

        /**
         * @brief Derived classes implement synchronous request and response handling here.
         */
        virtual void processRequest();

        /**
         * @brief Provide indication whether asynchronous request was sent successfully.
         */
        enum class RequestStatus
        {
            Success,
            Failure
        };
        /**
         * @brief Derived classes implement asynchronous request handling here.
         */
        virtual RequestStatus processRequest(std::shared_ptr<OutgoingBlockingHttpRequest> self);

        /**
         * @brief Derived classes implement asynchronous response parsing here.
         */
        virtual void processHttpResult(const HttpResult& result);

        void setSocket(DFL::NotNull<SoapPtr> soapPtrIn);

        SOAP_SOCKET getSocket() const;

        const std::string& getPeerTransportAddress() const;

        /**
         * @brief Set a listener that is called when this object is destroyed.
         * @details Only one listener is possible.
         */
        void setDestructionListener(std::weak_ptr<INotifyDestruction> destructionWatch);

    protected:
        /// A function that executes some gSOAP function and routes trough it's return value.
        using SoapProcess = std::function<int()>;

        explicit OutgoingBlockingHttpRequest(const std::string& peerTransportAddress, RequiredPeerRoles requiredPeerRoles);
        explicit OutgoingBlockingHttpRequest(const S31::Sdc::Impl::GsoapEpr& epr, RequiredPeerRoles requiredPeerRoles);

        std::optional<Utils::Error> getGsoapError(int gSoapResult);
        struct soap* getInjectedSoapHandleOrGetNewFromPool();
        const struct soap* soapPtr() const;
        void returnSoapHandle();
        const RequiredPeerRoles& requiredPeerRoles() const;
        std::weak_ptr<ISoapContextPool> soapContextPool() const;
        const std::weak_ptr<HttpClientRegistry>& httpClientRegistry() const;

        /**
         * @brief Create a job specific prefixed error message
         * @details Appends the current message to the job specific error message prefix.
         */
        DFL::Locale::Utf8 messageWithPrefix(const DFL::Locale::Utf8& currentMessage) const;

        /**
         * @brief Can be used in derived classes to execute and handle errors in gSoap related functionality.
         * @details
         * Does a (one time) retry on certain errors, i.e. to handle outlived keep-alive contexts.
         * @param process Function that does the gSoap (uses the soap context from this class).
         * @return An error evaluated from state of the soap context.
         */
        std::optional<Utils::Error> processGsoap(const SoapProcess& process);

        Utils::Utf8AppenderStream& processErrorMessagePrefix();

        /**
         * @brief Can be used in derived classes to serialize a request with gSoap.
         * @return An error evaluated from state of the soap context.
         */
        std::optional<Utils::Error> serializeRequestGsoap(std::string& soapBody, soap* soapHandle, SoapProcess serialize);

        /**
         * @brief Can be used in derived classes to parse a response with gSoap.
         * @return An error evaluated from state of the soap context.
         */
        std::optional<Utils::Error> parseResponseGsoap(const HttpResult& result, soap* soapHandle, SoapProcess parse);

        /// Function type for serializing a dynamic message with gSoap
        using GsoapDynamicSerializer = std::function<int(soap*, const ConnectionContext&)>;

        static CreateRequestBody createRequestBodyFromThis(
                std::shared_ptr<OutgoingBlockingHttpRequest> self, GsoapDynamicSerializer soapSerializer);

        static VerifyRequestPreconditions verifyPeerRequiredRolesFromThis(std::shared_ptr<OutgoingBlockingHttpRequest> self);

        static HttpResultCallback httpResultCallbackFromThis(std::shared_ptr<OutgoingBlockingHttpRequest> self);


        /**
         * @brief When the job is executed then this is called after
         * @ref S31::Sdc::Impl::OutgoingBlockingHttpRequest::processRequest() "OutgoingBlockingHttpRequest::processRequest()".
         *
         * @details The soap context is then not yet returned.
         */
        virtual void postProcessRequest() = 0;

    private:
        void initialize(const std::string& peerTransportAddress);
        DFL::Chrono::Milliseconds getDurationWaiting() const;
        DFL::Chrono::Milliseconds getDurationExecution() const;

        std::weak_ptr<INotifyDestruction> m_destructionListener;
        std::string m_peerTransportAddr;
        RequiredPeerRoles m_requiredPeerRoles;
        std::weak_ptr<ISoapContextPool> m_soapContextPool;
        std::weak_ptr<IOutgoingJobQueue> m_outgoingJobQueue;
        SoapPtr m_soapPtr;
        Utils::Utf8AppenderStream m_processErrorMessagePrefixStream;
        DFL::Locale::Utf8 m_processErrorMessagePrefix;

        // for logging
        DFL::Chrono::SystemClock::TimePoint m_creationTime;
        DFL::Chrono::SystemClock::TimePoint m_startExecutingTime;
        DFL::Chrono::SystemClock::TimePoint m_finishedTime;

        // For Asio HttpClient
        std::weak_ptr<HttpClientRegistry> m_httpClientRegistry;
};

}
