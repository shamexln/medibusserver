#pragma once

#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Private/Common/ContextData.h>
#include <S31/Sdc/Private/Common/ErrorDefinitions.h>
#include <S31/Sdc/Private/Common/Http/CreateRequestBody.h>
#include <S31/Sdc/Private/Common/Http/HttpResult.h>
#include <S31/Sdc/Private/Common/Http/HttpClient.h>
#include <S31/Sdc/Private/Common/Http/HttpClientRegistry.h>
#include <S31/Sdc/Private/Common/Http/HttpResultWaiter.h>
#include <S31/Sdc/Private/Common/Messaging/OutgoingBlockingHttpRequestWithOutcome.h>
#include <S31/Sdc/Private/Common/Messaging/OutgoingBlockingHttpRequestHelper.h>
#include <S31/Sdc/Private/Common/HttpHeader.h>
#include <S31/Sdc/Private/Common/StackConstants.h>
#include <S31/Sdc/Public/Common/CoreConfiguration.h>
#include <S31/Utils/S31Only/PtrHelper.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapDiscoveryBindingProxy.h>

#include <Framework/Chrono/Public/SteadyClock.h>
#include <Framework/Crypto/Public/Certificate.h>
#include <Framework/Crypto/Public/PrivateKey.h>
#include <Framework/Utils/Public/Uri.h>
#include <Framework/Utils/Public/Scope.h>

#include <sstream>

namespace S31::Sdc::Impl
{

/**
 * @brief Relevant results parsing a Discovery message using gSoap.
 */
template<class T_MatchOp>
struct GSoapDiscoveryMatch
{
    int gSoapErrorCode;
    T_MatchOp matchOp;
};

/**
 * @brief Job to request WS-Discovery data via HTTP (e.g. Discovery via DiscoveryProxy).
 *
 * @ingroup S31SdcWsDiscovery
 */
template<class T_ResultData, class Derived>
class HttpDiscoveryJob : public OutgoingBlockingHttpRequestWithOutcome<T_ResultData>
{
    public:
        using OutcomeHandlerPtr = typename Utils::OutcomeProvider<T_ResultData>::OutcomeHandlerPtr;
        using HandlerPtr = typename Utils::OutcomeTypes::HandlerPtr<HttpResult>;

        using OutgoingBlockingHttpRequestWithOutcome<T_ResultData>::jobName;

        HttpDiscoveryJob(const OutcomeHandlerPtr& handler, const DFL::Net::Uri& targetAddress) :
            OutgoingBlockingHttpRequestWithOutcome<T_ResultData>(
                handler, targetAddress.str(), RequiredPeerRoles{DFL::Oids{}}),
            m_targetAddress(targetAddress)
        {
        }

        /**
         * @brief Executes and processes the response to a Http Discovery Request.
         * @details Depends on the existence of a function createSoapMessage() in the derived class.
         */
        void processRequest() final
        {
            S31_STREAM_TRACE_LOGGER("Soap.WS", __func__);
            if (!this->hasOutcomeHandler())
            {
                S31_STREAM_TRACE_LOGGER("Soap.WS", appendJobName("No outcome handler. Abort processing"));
                return;
            }

            auto* soapHandle(this->getInjectedSoapHandleOrGetNewFromPool());
            SET_ERROR_AND_RETURN_ON_EMPTY_SOAPHANDLE;
            DFL::Scope::ScopeExit const returnSoap([&](){ this->returnSoapHandle(); });

            auto clientRegistry = this->httpClientRegistry().lock();
            if (!clientRegistry)
            {
                this->setOutcomeError(Sdc::Impl::Errors::Unexpected{}) << appendJobName("HttpClientRegistry is not available");
                return;
            }

            static_assert(std::is_base_of<HttpDiscoveryJob, Derived>::value, "Derived must be derived from HttpDiscoveryJob.");
            const auto& asDerived = static_cast<const Derived&>(*this);
            auto soapMessageBuilder = asDerived.createSoapMessage(DFL::asNotNull(soapHandle));

            auto client = clientRegistry->discoveryClient();

            auto waitResult = std::make_shared<HttpResultWaiter>();
            const auto startTime = DFL::Chrono::SteadyClock::now();
            client->sendRequest(
                    HttpClient::httpPost(m_targetAddress)
                            .createBodyFunction(
                                    std::move(soapMessageBuilder), HttpHeader::ContentType::applicationSoapXml())
                            .onComplete([waitResult](const HttpResult& result) { waitResult->setResult(result); })
                            .buildRequest());


            // TODO: remove waiting to make the job "non-blocking"
            //  1) Should Jobs be "enable_shared_from_this<>"?
            //  2) Or, create a "waiting object" which is the "outcome provider" for the job,
            //     and includes soap parsing logic, etc?
            if (auto result = waitResult->waitForResult(std::chrono::seconds{5}))
            {
                return handleHttpResult(soapHandle, startTime, *result);
            }
            this->setOutcomeError(Sdc::Impl::Errors::Unexpected{}) << appendJobName("No result");
        }

        /**
         * @brief Creates an outcomeHandler for the Outcome of the HttpRequest triggered by @ref processRequest().
         * @details Depends on the existence of two static functions in the Derived class type, parseSoapMessage()
         *          and processMatches(). The former function defines how the Soap Response from the DiscoveryProxy shall be parsed
         *          into a (gSoap-)Match object whose type is defined by the Derived class. The latter function defines how the Match object
         *          is transformed into the respective T_ResultData type defined by the Derived job.
         */
        void handleHttpResult(soap* soapHandle, DFL::Chrono::SteadyClock::TimePoint startTime, const HttpResult& result)
        {
            if (const auto& error = result.error())
            {
                this->setOutcomeError(*error) << appendJobName("");
                return;
            }

            SET_ERROR_AND_RETURN_ON_EMPTY_SOAPHANDLE;

            const auto endResponseTime = DFL::Chrono::SteadyClock::now();
            if (endResponseTime - startTime > StackConstants::WS_DISCOVERY_MATCH_TIMEOUT)
            {
                this->setOutcomeError(Errors::WSDiscoveryMatchTimeoutError{});
                std::ostringstream err;
                err << "Response received after " << StackConstants::WS_DISCOVERY_MATCH_TIMEOUT << " (MATCH_TIMEOUT)";
                this->outcomeErrorStream() << appendJobName(err.str());
                return;
            }

            auto* oldIs     = soapHandle->is;
            auto  restoreIs = DFL::Scope::ScopeExit([&] { soapHandle->is = oldIs; });

            // TODO: check compression on result...
            std::istringstream responseStream(result.body());
            soapHandle->is = &responseStream;

            const GSoapDiscoveryMatch<typename Derived::T_MatchOp> parseResult = Derived::parseSoapMessage(soapHandle);

            const int err = parseResult.gSoapErrorCode;
            if (err != SOAP_OK)
            {
                const auto gSoapError = this->getGsoapError(err);
                if (gSoapError)
                {
                    this->setOutcomeError(*gSoapError);
                }
                return;
            }

            if (auto matchResult = Derived::processMatches(parseResult.matchOp))
            {
                this->setOutcomeResult(std::move(matchResult.get()));
                return;
            }

            this->setOutcomeError(Errors::NoSuitableMatchResultError{}, appendJobName("No suitable Match Result"));
        }

    protected:
        DFL::Net::Uri m_targetAddress;

    private:
        DFL::Locale::Utf8 appendJobName(const std::string& errorText)
        {
            return DFL::Locale::Utf8(errorText + " (" + jobName() + ")");
        }

};

}
