#pragma once

#include <S31/Gsoap/S31Only/AddressingHelper.h>
#include <S31/Gsoap/S31Only/LinkAction.h>
#include <S31/Gsoap/S31Only/generated/gsoap/soapH.h>
#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Private/Common/IWebService.h>
#include <S31/Sdc/Test/IntegrationTest/Utils/Mocks/GetBindingServiceMock.h>

#include <boost/algorithm/string/predicate.hpp>

#include <atomic>
#include <memory>
#include <mutex>

namespace S31::Sdc::Impl::Test
{

/**
 * @brief Mock for the soap handler interface.
 */
class WebServiceMock: public IWebService
{
    public:
        /// @brief Dispatch implements the DPWS specific dispatching logic of our DPWS architecture.
        /// \returns gSOAP error code without sending SOAP faults.
        /// Caller has to take care of sending SOAP fault messages.
        int dispatch(struct soap* soapHandle) override
        {
            const auto* action = S31::Gsoap::soapActionOrEmptyString(soapHandle);
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_actions.emplace_back(action);
                S31_STREAM_INFO_LOGGER("Test", "WebServiceMock::dispatch(): action = ", action);
            }
            ++m_numRequests;
            if (!boost::starts_with(action, "http://docs.oasis-open.org/ws-dd/ns/discovery")
                && !boost::starts_with(action, "http://schemas.xmlsoap.org/ws/2005/04/discovery"))
            {
                ++m_numNonDiscoveryRequests;
            }

            GetBindingServiceMock service;
            const auto result = [&]()
            {
                S31::Gsoap::LinkAction showAction{soapHandle};
                return service.dispatch(soapHandle);
            }();
            S31_STREAM_INFO_LOGGER("Test", "dispatch result: ", result);
            return result;
        }

        std::string lastAction() const
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            if (m_actions.empty())
            {
                return "";
            }

            return m_actions.back();
        }

        std::vector<std::string> actions() const
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_actions;
        }

        size_t numRequests() const
        {
            return m_numRequests;
        }

        size_t numNonDiscoveryRequests() const
        {
            return m_numNonDiscoveryRequests;
        }

        void resetWebServiceMock()
        {
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_actions.clear();
            }
            m_numRequests = 0;
            m_numNonDiscoveryRequests = 0;
        }

    private:
        mutable std::mutex m_mutex;
        std::vector<std::string> m_actions;
        std::atomic<size_t> m_numRequests{0};
        std::atomic<size_t> m_numNonDiscoveryRequests{0};

};

}
