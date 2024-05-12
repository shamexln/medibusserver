#pragma once

#include <S31/Sdc/Public/Client/RemoteDevicesObserver.h>
#include <mutex>

namespace S31::Sdc::Test
{

/**
 * @brief Watch 'offline' events for a given Epr and store the error.
 */
class GetOfflineErrorMessage : public S31::Sdc::RemoteDevicesObserver
{
    public:
        GetOfflineErrorMessage(const S31::Sdc::EndpointReference& epr):
            m_epr(epr.address().str())
        {}

        void online(const DFL::NotNull<std::shared_ptr<RemoteDevice>>& /*remoteDevice*/) override
        {}

        void offline(const S31::Sdc::EndpointReference& epr, const S31::Utils::Error& error) override
        {
            if (epr.address().str() == m_epr)
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_message = error.message().value();
            }
        }

        /// @returns the catched error message if there was a 'offline' call
        std::string message() const
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_message;
        }

    private:
        std::string m_epr;
        std::string m_message;
        mutable std::mutex m_mutex;
};

}
