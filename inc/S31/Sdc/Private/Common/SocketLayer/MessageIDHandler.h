#pragma once

#include <S31/S31CoreExImp.h>

#include <deque>
#include <map>
#include <mutex>
#include <string>

namespace S31::Sdc::Impl
{

/**
 * A class that maintains a list of recently used WS-Addressing message IDs. Used for duplicate
 * message detection. Required for SOAP-over-UDP since multicast messages should send twice to
 * avoid message loss.
 *
 * \ingroup S31SdcCommonWebServices
 */
class S31_CORE_EXPIMP MessageIDHandler
{
    public:
        explicit MessageIDHandler(unsigned int length);
        void addMessageId(const char* id);
        bool containsMessageId(const char* id) const;

    private:
        void removeFromMapNoLock(const std::string& id);
        void addToMapNoLock(const std::string& id);

        unsigned int m_length;
        /// a deque of last used ids (contains maximum m_length elements)
        std::deque<std::string> m_msgIDs_deque;
        /// a map of id + count of it's occurrence in m_msgIDs_deque
        std::map<std::string, unsigned int> m_msgIDs_map;
        mutable std::mutex m_mutex;
};

}
