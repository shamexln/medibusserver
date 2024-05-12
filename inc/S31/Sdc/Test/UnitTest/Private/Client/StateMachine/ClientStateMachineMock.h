#pragma once

#include <S31/Sdc/Private/Client/Endpoint/DpwsEndpoint.h>
#include <S31/Utils/Public/ObservableSubject.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::Sdc::Test
{

/**
 * @brief Access interface for \ref ClientStateMachineMock.
 * @details To be used if \ref ClientStateMachineMock is held as a \c unique_ptr.
 */
class ClientStateMachineMockAccess: public S31::Utils::ObservableSubjectDelegate<S31::Sdc::Impl::Csm::ClientStateMachineObserver>
{
    public:
        ClientStateMachineMockAccess() = default;

        void connect();

        void disconnect(Utils::Error error);

        void handleError(const S31::Utils::Error& error);

        void validate();

        unsigned int connectCalls() const;

        unsigned int validateCalls() const;

        const std::vector<Utils::Error>& disconnectCalls() const;

        const std::vector<Utils::Error>& handleErrorCalls() const;

    private:
        unsigned int m_connectCalls{};
        unsigned int m_validateCalls{};
        std::vector<Utils::Error> m_disconnectCalls;
        std::vector<Utils::Error> m_handleErrorCalls;
};

/**
 * @brief Mock implementation for \ref S31::Sdc::Impl::Csm::ClientStateMachine.
 */
class ClientStateMachineMock: public S31::Sdc::Impl::Csm::ClientStateMachine
{
    public:
        ClientStateMachineMock();

        void connect(const Impl::SoapActions& mdibChangeReports) override;

        void disconnect(const Utils::Error& error) override;

        void validate() override;

        std::shared_ptr<RemoteDevice> remoteDevice() const override;

        void handleError(const Utils::Error& error) override;

        void registerObserver(const std::weak_ptr<S31::Sdc::Impl::Csm::ClientStateMachineObserver>& observer) override;

        void unregisterObserver(const std::weak_ptr<S31::Sdc::Impl::Csm::ClientStateMachineObserver>& observer) override;

        const DFL::NotNull<std::shared_ptr<ClientStateMachineMockAccess>>& sharedMockAccess() const;

    private:
        DFL::NotNull<std::shared_ptr<ClientStateMachineMockAccess>> m_sharedMockAccess;

};

inline ClientStateMachineMock::ClientStateMachineMock() :
        m_sharedMockAccess(DFL::asNotNull(std::make_shared<ClientStateMachineMockAccess>()))
{
}

inline void ClientStateMachineMockAccess::connect()
{
    m_connectCalls++;
}

inline void ClientStateMachineMockAccess::disconnect(Utils::Error error)
{
    m_disconnectCalls.push_back(std::move(error));
}

inline void ClientStateMachineMockAccess::handleError(const S31::Utils::Error& error)
{
    m_disconnectCalls.push_back(error);
}

inline void ClientStateMachineMockAccess::validate()
{
    m_validateCalls++;
}

inline unsigned int ClientStateMachineMockAccess::connectCalls() const
{
    return m_connectCalls;
}

inline unsigned int ClientStateMachineMockAccess::validateCalls() const
{
    return m_validateCalls;
}

inline const std::vector<Utils::Error>& ClientStateMachineMockAccess::disconnectCalls() const
{
    return m_disconnectCalls;
}

inline const std::vector<Utils::Error>& ClientStateMachineMockAccess::handleErrorCalls() const
{
    return m_handleErrorCalls;
}

inline void ClientStateMachineMock::connect(const Impl::SoapActions& /* subscriptionTypes */)
{
    m_sharedMockAccess->connect();
}

inline void ClientStateMachineMock::disconnect(const Utils::Error& error)
{
    m_sharedMockAccess->disconnect(error);
}

inline void ClientStateMachineMock::validate()
{
    m_sharedMockAccess->validate();
}

inline std::shared_ptr<RemoteDevice> ClientStateMachineMock::remoteDevice() const
{
    return nullptr;
}

inline void ClientStateMachineMock::handleError(const S31::Utils::Error& error)
{
    m_sharedMockAccess->handleError(error);
}

inline void ClientStateMachineMock::registerObserver(const std::weak_ptr<S31::Sdc::Impl::Csm::ClientStateMachineObserver>& observer)
{
    m_sharedMockAccess->registerObserver(observer);
}

inline void ClientStateMachineMock::unregisterObserver(const std::weak_ptr<S31::Sdc::Impl::Csm::ClientStateMachineObserver>& observer)
{
    m_sharedMockAccess->unregisterObserver(observer);
}

inline const DFL::NotNull<std::shared_ptr<ClientStateMachineMockAccess>>& ClientStateMachineMock::sharedMockAccess() const
{
    return m_sharedMockAccess;
}

}
