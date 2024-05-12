#pragma once

#include <S31/Sdc/Private/Client/WS-Eventing/SoapAction.h>
#include <S31/Sdc/Private/Client/WS-Eventing/WSEventingClientSubscriptionId.h>
#include <S31/Sdc/Private/Common/Endpoint/Executor.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Crypto/Public/DistinguishedName.h>

#include <boost/optional/optional.hpp>

#include <memory>
#include <vector>

namespace S31::Sdc::Impl
{

class IRemoteHostedServiceEndpoint;
class IWSEventingClientListener;
class GsoapEpr;

/**
 * \brief Container for all information about a client WS-Eventing subscription.
 *
 * \ingroup S31SdcClientEventing
 */
class S31_CORE_EXPIMP WSEventingClientSubscription
{
    public:
        WSEventingClientSubscription(S31::Sdc::Impl::WSEventingClientSubscriptionId id,
                                     S31::Sdc::Impl::Endpoint::Executor executor,
                                     SoapActions actions,
                                     const std::shared_ptr<S31::Sdc::Impl::IWSEventingClientListener>& callback);

        WSEventingClientSubscriptionId getId() const;
        const SoapActions& getActions() const;
        const S31::Sdc::Impl::Endpoint::Executor& executor() const;
        std::shared_ptr<S31::Sdc::Impl::IWSEventingClientListener> getCallback() const;
        void setRemoteSubscriptionManager(const std::shared_ptr<S31::Sdc::Impl::GsoapEpr>& remoteSubscriptionManager);
        std::shared_ptr<S31::Sdc::Impl::GsoapEpr> getRemoteSubscriptionManager() const;

        void setExpirationTime(DFL::Chrono::Seconds expirationTime);

        /// Checks whether the subscription is valid regarding its subscription duration and returns also a describing message if not so.
        bool isExpired(DFL::Chrono::Seconds currentTime, std::string& message) const;
        bool isSubscribedToAction(SoapAction action) const;
        DFL::Chrono::Seconds getExpirationTime() const;

        void setRenewTimeBeforeExpiration(DFL::Chrono::Seconds renewTimeBeforeExpiration);
        boost::optional<DFL::Chrono::Seconds> getRenewTimeBeforeExpiration() const;
        void resetRenewTimeBeforeExpiration();

        const DFL::Crypto::DistinguishedName& remoteDeviceDistinguishedName() const;
        void remoteDeviceDistinguishedName(const DFL::Crypto::DistinguishedName& distinguishedName);
    private:
        WSEventingClientSubscriptionId m_id;
        S31::Sdc::Impl::Endpoint::Executor m_executor;

        SoapActions m_actions;
        std::weak_ptr<S31::Sdc::Impl::IWSEventingClientListener> m_callback;
        std::shared_ptr<S31::Sdc::Impl::GsoapEpr> m_remoteSubscriptionManager;
        DFL::Chrono::Seconds m_expirationTime;
        boost::optional<DFL::Chrono::Seconds> m_renewTimeBeforeExpiration;

        DFL::Crypto::DistinguishedName m_remoteDeviceDistinguishedName;
};

}
