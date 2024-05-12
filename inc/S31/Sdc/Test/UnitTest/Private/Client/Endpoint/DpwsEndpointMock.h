#pragma once

#include <S31/Sdc/Private/Client/Endpoint/DpwsEndpoint.h>
#include <S31/Utils/Public/ObservableSubject.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::Sdc::Test
{

/**
 * @brief Access interface for \ref DpwsEndpointMock.
 * @details To be used if \ref DpwsEndpointMock is held as a \c unique_ptr.
 */
class DpwsEndpointMockAccess: public S31::Utils::ObservableSubjectDelegate<S31::Sdc::Impl::Endpoint::DpwsEndpointObserver>
{
    public:
        DpwsEndpointMockAccess();

        void validate();

        unsigned int validateCalls() const;

    private:
        unsigned int m_validateCalls;
};

/**
 * @brief Mock implementation for \ref S31::Sdc::Impl::Endpoint::DpwsEndpoint.
 */
class DpwsEndpointMock: public S31::Sdc::Impl::Endpoint::DpwsEndpoint
{
    public:
        DpwsEndpointMock();

        void registerObserver(const std::weak_ptr<S31::Sdc::Impl::Endpoint::DpwsEndpointObserver>& observer) override;

        void unregisterObserver(const std::weak_ptr<S31::Sdc::Impl::Endpoint::DpwsEndpointObserver>& observer) override;

        void validate() override;

        const DFL::NotNull<std::shared_ptr<DpwsEndpointMockAccess>>& sharedMockAccess() const;

    private:
        DFL::NotNull<std::shared_ptr<DpwsEndpointMockAccess>> m_sharedMockAccess;

};

inline DpwsEndpointMockAccess::DpwsEndpointMockAccess() :
        m_validateCalls(0)
{
}

inline void DpwsEndpointMockAccess::validate()
{
    m_validateCalls++;
}

inline unsigned int DpwsEndpointMockAccess::validateCalls() const
{
    return m_validateCalls;
}

inline DpwsEndpointMock::DpwsEndpointMock() :
        m_sharedMockAccess(DFL::asNotNull(std::make_shared<DpwsEndpointMockAccess>()))
{
}

inline void DpwsEndpointMock::registerObserver(const std::weak_ptr<S31::Sdc::Impl::Endpoint::DpwsEndpointObserver>& observer)
{
    m_sharedMockAccess->registerObserver(observer);
}

inline void DpwsEndpointMock::unregisterObserver(const std::weak_ptr<S31::Sdc::Impl::Endpoint::DpwsEndpointObserver>& observer)
{
    m_sharedMockAccess->unregisterObserver(observer);
}

inline void DpwsEndpointMock::validate()
{
    m_sharedMockAccess->validate();
}

inline const DFL::NotNull<std::shared_ptr<DpwsEndpointMockAccess>>& DpwsEndpointMock::sharedMockAccess() const
{
    return m_sharedMockAccess;
}

}
