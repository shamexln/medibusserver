#pragma once

#include <S31/Sdc/Private/Common/Scheduling/IIdleKeepAliveSoapContextPool.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/SteadyClock.h>
#include <Framework/Utils/Public/NotNull.h>

#include <map>
#include <mutex>

namespace S31::Sdc::Impl
{

/**
 * @brief Pool for idle outgoing HTTP keep-alive connections.
 * @details This pool stores outgoing HTTP keep-alive sockets in SoapPtr contexts.
 * This is the way \ref gSOAP uses keep-alive. One soap context is used
 * for all HTTP requests in a keep-alive connection.
 *
 * @ingroup S31SdcCommonWebServices
 */
class S31_CORE_EXPIMP IdleKeepAliveSoapContextPool: public IIdleKeepAliveSoapContextPool
{
    public:
        /**
         *
         * @param maxIdle Limit the amount of idle keep-alive sockets
         */
        explicit IdleKeepAliveSoapContextPool(unsigned int maxIdle);
        ~IdleKeepAliveSoapContextPool() override;

        void setMaxNumberOfIdleSoapContexts(unsigned int maxNumberOfIdleSoapContexts);

        void setIdleTimeout(DFL::Chrono::Seconds idleTimeout);

        /**
         * @brief Store idle keep-alive connection within the soap context for later use.
         * @details Currently there is no pending HTTP request to the destination.
         */
        void addSoapContextForTransport(DFL::NotNull<SoapPtr> soapPtr, const std::string& transportAddress);

        boost::optional<SoapPtr> getIdleSoapContextForTransport(const std::string& transportAddress) override;

        [[nodiscard]] std::size_t size() const;
        [[nodiscard]] bool empty() const;

    private:
        void removeOldSocketsNoLock();
        std::string createIdleSocketLogMessageNoLock();

        mutable std::mutex m_mutex;

        unsigned int m_maxIdle;
        DFL::Chrono::Seconds m_idleTimeout;

        /**
         * @ingroup S31SdcCommonWebServices
         */
        class IdleData
        {
            public:
                explicit IdleData(DFL::NotNull<SoapPtr> soapPtr);
                IdleData(IdleData&&) = default;
                ~IdleData();
                [[nodiscard]] struct soap* getSoapHandle() const noexcept;
                [[nodiscard]] DFL::Chrono::SteadyClock::TimePoint getInsertTimePoint() const;
                SoapPtr releaseSoapPtr();
            private:
                SoapPtr m_soapPtr;
                DFL::Chrono::SteadyClock::TimePoint m_insertTimePoint;
        };
        std::map<std::string, IdleData> m_idleSoapContexts;
};

}
