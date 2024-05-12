#pragma once

#include <S31/Sdc/Public/Client/RemoteDevicesProvider.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/Utils/Public/Errors.h>
#include <S31/Sdc/Test/Utils/s31core_it_utils_exp_imp.h>

#include <Framework/Utils/Public/NotNull.h>

#include <boost/optional/optional.hpp>

#include <chrono>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>

namespace S31::Sdc::Test
{

/**
 * @brief Waits for the given device to go offline.
 */
class S31_CORE_IT_UTIL_EXPIMP OfflineWatcher:
        public Sdc::RemoteDevicesObserver,
        public std::enable_shared_from_this<OfflineWatcher>
{
    public:
        using ErrorPredicate = std::function<bool(const Utils::Error&)>;

        OfflineWatcher(
                const DFL::NotNull<std::shared_ptr<RemoteDevicesProvider>>& remoteDevicesProvider,
                const EndpointReference& endpointReference,
                const ErrorPredicate& pred);

        void startWaiting();

        /// if wait() fails, here is a description why
        const std::string& failMessage() const;

        /// waits for the defined 'offline' to be happen
        bool wait(std::chrono::milliseconds maxWaitTime);

        const Utils::Error& offlineError() const;

        void online(const DFL::NotNull<std::shared_ptr<S31::Sdc::RemoteDevice>>& remoteDevice) override;

        void offline(const EndpointReference& epr, const S31::Utils::Error& error) override;
    private:
        DFL::NotNull<std::shared_ptr<RemoteDevicesProvider>> m_remoteDevicesProvider;
        EndpointReference m_endpointReference;
        ErrorPredicate m_pred;
        std::string m_failMessage;
        Utils::Error m_offlineError;
        bool m_gotOffline = false;
        std::mutex m_mutex;
        std::condition_variable m_conditionVariable;

};

}
