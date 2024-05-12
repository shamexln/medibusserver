#pragma once

#include <S31/Gsoap/S31Only/stdsoap2.h>
#include <S31/Sdc/Private/Common/SoapPtr.h>
#include <S31/Sdc/Private/Common/SocketLayer/ISocketSelect.h>
#include <S31/Sdc/Public/Common/MaxResultCount.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/SteadyClock.h>
#include <Framework/Utils/Public/NotNull.h>

#include <boost/optional/optional.hpp>

#include <mutex>
#include <vector>

namespace S31::Sdc::Impl
{
class SocketSignal;

/**
 * @brief Storage for incoming TCP keep-alive sockets to remote peers.
 *
 * @details This class allows the IncomingNetworkJobs to return
 * sockets to the SocketController for listening of
 * data from a remote user. This allows to reuse TCP
 * connections for reception of soap messages.
 *
 * @ingroup S31SdcCommonSocket
 */
class SocketStore
{
    public:
        explicit SocketStore(std::weak_ptr<SocketSignal> socketSignalIn);
        ~SocketStore();

        void setIdleTimeout(DFL::Chrono::Seconds idleTimeout);
        void setMaxIdleSockets(unsigned int maxIdleSockets);

        void addIdleSocket(DFL::NotNull<SoapPtr> soapPtrIn);

        [[nodiscard]] IncomingHttpRequestPtrs addReadSocketsOrProvideSocketsCloseJobs(
                SOAP_SOCKET& fd_max, fd_set& readSet, MaxResultCount maxResultCount, fd_set& exceptSet);

        SoapPtr getNextReadableSocket(const fd_set& readSet, const fd_set& exceptSet);

        std::vector<SoapPtr> getNextReadableSockets(const fd_set& readSet, MaxResultCount maxResultCount, const fd_set& exceptSet);

    private:

        void removeIdleSocketsNoLock();

        /**
         * @ingroup S31SdcCommonSocket
         */
        class IdleData
        {
            public:
                explicit IdleData(DFL::NotNull<SoapPtr> soapPtr);
                IdleData(IdleData&& rhs) noexcept;
                IdleData& operator=(IdleData&& rhs) noexcept;
                IdleData(const IdleData& rhs) = delete;
                IdleData& operator=(const IdleData& rhs) = delete;

                [[nodiscard]] DFL::Chrono::SteadyClock::TimePoint getLastUsedTime() const;

                [[nodiscard]] SOAP_SOCKET getSocket() const;

                SoapPtr releaseSoapPtr();

            private:
                DFL::Chrono::SteadyClock::TimePoint m_lastUsedTime;
                SoapPtr m_soapPtr;
        };

        std::mutex m_mutex;
        DFL::Chrono::Seconds m_idleTimeout;
        std::weak_ptr<SocketSignal> m_socketSignal;
        std::vector<IdleData> m_idleSockets;
        unsigned int m_maxIdleSockets;
};

}
