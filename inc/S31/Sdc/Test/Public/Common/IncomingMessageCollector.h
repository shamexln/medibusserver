#pragma once

#include <S31/Sdc/Public/Common/SdcMessageObserver.h>

#include <Framework/Chrono/Public/SteadyClock.h>

#include <condition_variable>
#include <mutex>

namespace S31::Sdc::Test
{

    /**
     * @ingroup S31SdcCommon
     */
    struct IncomingMessage
    {
        std::string source;
        std::string destination;
        std::string xmlSoapMessage;
        DFL::Chrono::SteadyClock::TimePoint timestamp;
    };

    /**
     * @ingroup S31SdcCommon
     */
    class IncomingMessageCollector : public SdcMessageObserver
    {
    public:
        IncomingMessageCollector(std::string_view action = std::string_view{}) :
            m_action(action.empty() ? "" : (std::string{"<wsa5:Action SOAP-ENV:mustUnderstand=\"true\">"}.append(action)))
        {
        }

        void incomingMessage(const std::string& source, const std::string& destination, const std::string& xmlSoapMessage, const boost::optional<S31::Sdc::EndpointReference>& /*remoteEpr*/) override
        {
            if (!m_action.empty() && xmlSoapMessage.find(m_action) == std::string::npos)
            {
                return;
            }

            IncomingMessage msg;
            msg.source = source;
            msg.destination = destination;
            msg.xmlSoapMessage = xmlSoapMessage;
            msg.timestamp = DFL::Chrono::SteadyClock::now();

            std::unique_lock<std::mutex> lock(m_mutex);
            m_incomingMessages.push_back(std::move(msg));

            m_conditionVariable.notify_all();
        }

        std::vector<IncomingMessage> incoming()
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            return m_incomingMessages;
        }

        void resetMock()
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_incomingMessages.clear();
        }

        void waitForMessages(std::chrono::milliseconds timeout, std::size_t count)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_conditionVariable.wait_for(lock, timeout, [&] { return m_incomingMessages.size() == count; });
        }

    private:
        std::vector<IncomingMessage> m_incomingMessages;
        std::mutex m_mutex;
        std::condition_variable m_conditionVariable;
        std::string m_action;
    };
}
