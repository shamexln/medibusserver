#pragma once

#include <S31/Sdc/Private/Client/WS-Eventing/WSEventingClientSubscriptionId.h>
#include <S31/Sdc/Public/Client/NewSubscriptionActiveNotifier.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Utils/Public/CompilerGenerated.h>

#include <boost/optional/optional.hpp>

#include <algorithm>
#include <condition_variable>
#include <functional>
#include <mutex>

namespace S31::Sdc::Impl
{

/**
 * @brief Implementation of NewSubscriptionActiveNotifier.
 *
 * @ingroup S31SdcClient
 */
class S31_CORE_EXPIMP NewSubscriptionActiveNotifierImpl: public NewSubscriptionActiveNotifier
{
        DFL_NOT_COPYABLE(NewSubscriptionActiveNotifierImpl)
    public:

        explicit NewSubscriptionActiveNotifierImpl(boost::optional<Impl::WSEventingClientSubscriptionId> subscriptionId):
            m_subscriptionId(std::move(subscriptionId))
        {}

        const boost::optional<Impl::WSEventingClientSubscriptionId>& subscriptionId() const;

        void subscriptionIsActive(const WSEventingClientSubscriptionId& id);

        bool waitForActivation(const DFL::Chrono::Milliseconds& maxWaitTime) override;

        void registerCallback(const NotifyFunction& callback) override;
    private:

        bool m_isActive = false;
        boost::optional<Impl::WSEventingClientSubscriptionId> m_subscriptionId;
        NotifyFunction m_callback;
        std::mutex m_mutex;

        std::condition_variable m_waitConditionVar;
        std::mutex m_waitMutex;
};

}
