#pragma once

#include <mutex>
#include <string>

namespace S31::Sdc::Impl
{

/**
 * \brief Container to store the latest generated message
 * \ingroup S31SdcCommonWebServices
 */
class UpdatedMessage
{
    public:
        UpdatedMessage() = default;

        std::string message()
        {
            std::scoped_lock<std::mutex> const lock(m_mutex);
            return m_msg;
        }

        void message(const std::string& msg)
        {
            std::scoped_lock<std::mutex> const lock(m_mutex);
            m_msg = msg;
        }

        void message(std::string&& msg)
        {
            std::scoped_lock<std::mutex> const lock(m_mutex);
            m_msg = std::move(msg);
        }

    private:
        std::mutex m_mutex;
        std::string m_msg;
};

} /* namespace Impl::Sdc::S31 */
