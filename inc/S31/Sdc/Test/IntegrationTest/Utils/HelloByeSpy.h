#pragma once

#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Private/Common/CommunicationEndpoint.h>
#include <S31/Sdc/Private/Common/Scheduling/JobScheduler.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/IDiscoveryClient.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/IHelloByeObserver.h>
#include <S31/Sdc/Public/Common/ThreadPoolDispatcher.h>
#include <S31/Sdc/Test/Utils/CommonConfigurator.h>

#include <chrono>
#include <gmock/gmock.h>

#include <condition_variable>
#include <mutex>

namespace S31::Sdc::Test
{
class HelloByeSpy : public Impl::IHelloByeObserver, public std::enable_shared_from_this<HelloByeSpy>
{
public:

    explicit HelloByeSpy(std::string uuid)
    {
        m_eprHelloByeMap.emplace(std::make_pair(std::move(uuid), std::make_unique<HelloByeCounter>()));
    }

    explicit HelloByeSpy(const std::vector<std::string>& deviceEprs)
    {
        for (const auto& epr : deviceEprs)
        {
            m_eprHelloByeMap.emplace(std::make_pair(epr, std::make_unique<HelloByeCounter>()));
        }
    }

    void hello(const S31::Sdc::EndpointReference& eprAddress,
               const S31::Sdc::Impl::QNameList& /*types*/,
               const std::vector<std::string>& /*scopes*/,
               const std::string& /*xAddresses*/,
               S31::Sdc::MetadataVersion /*metadataVersion*/,
               const std::string& /*remoteIp*/) override
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        S31_STREAM_TRACE_LOGGER("Test", "Received hello from:", eprAddress.address().str());
        if (m_eprHelloByeMap.count(eprAddress.address().str()) == 1)
        {
            ++(m_eprHelloByeMap[eprAddress.address().str()]->m_helloCounter);
            m_cond.notify_all();
        }
    }

    void bye(const S31::Sdc::EndpointReference& eprAddress) override
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        S31_STREAM_TRACE_LOGGER("Test", "Received bye from:", eprAddress.address().str());
        if (m_eprHelloByeMap.count(eprAddress.address().str()) == 1)
        {
            ++(m_eprHelloByeMap[eprAddress.address().str()]->m_byeCounter);
            m_cond_bye.notify_all();
        }
    }

    void waitForHello()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cond.wait_for(lock, std::chrono::seconds(10));
    }

    void waitForByeFrom(const S31::Sdc::EndpointReference& epr, std::chrono::milliseconds timeout)
    {
        std::unique_lock<std::mutex> lock(m_mutex_bye);
        m_cond_bye.wait_for(lock, timeout, [&]{return (m_eprHelloByeMap[epr.address().str()]->m_byeCounter > 0) ;});
    }

    int helloCount(const std::string& epr) const
    {
        return m_eprHelloByeMap.at(epr)->m_helloCounter;
    }

    int byeCount(const std::string& epr) const
    {
        return m_eprHelloByeMap.at(epr)->m_byeCounter;
    }

    void start()
    {
        m_dispatcher = std::make_shared<S31::Sdc::ThreadPoolDispatcher>(S31::Sdc::NumberOfThreads(2));

        m_commEndpoint = std::make_shared<S31::Sdc::Impl::CommunicationEndpoint>(
                DFL::asNotNull(std::make_shared<S31::CoreConfiguration>(
                        S31::Sdc::Test::CommonConfigurator::defaultConfiguration())),
                m_dispatcher->dispatcher());

        m_dispatcher->injectJobQueue(DFL::asNotNull(std::make_shared<S31::Sdc::Impl::JobScheduler>(m_commEndpoint->scheduling().get())));

        auto discoveryClient = m_commEndpoint->discoveryClient();
        discoveryClient->registerListener(shared_from_this());

        m_dispatcher->start();
    }

private:
    struct HelloByeCounter
    {
        HelloByeCounter() = default;
        int m_helloCounter{0};
        int m_byeCounter{0};
    };

    std::condition_variable m_cond;
    std::mutex m_mutex;
    std::condition_variable m_cond_bye;
    std::mutex m_mutex_bye;
    std::map<std::string, std::unique_ptr<HelloByeCounter>> m_eprHelloByeMap;

    std::shared_ptr<S31::Sdc::Impl::CommunicationEndpoint> m_commEndpoint;
    std::shared_ptr<S31::Sdc::IDispatcher> m_dispatcher;
};

}
