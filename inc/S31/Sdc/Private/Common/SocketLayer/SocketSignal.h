#pragma once

#include <S31/Gsoap/S31Only/stdsoap2.h>
#include <S31/S31CoreExImp.h>

#include <mutex>

namespace S31::Sdc::Impl
{

/**
 * @brief Class to abstract the signaling of a socket to use within a select() call.
 *
 * @details This is interesting to "abort" a select call from outside before the timeout happened.
 *
 * @ingroup S31SdcCommonSocket
 */
class S31_CORE_EXPIMP SocketSignal
{
    public:
        SocketSignal();

        // explicitly delete copy and assign (for coverity)
        // since destructor frees resources (sockets)
        SocketSignal(const SocketSignal&) = delete;
        SocketSignal& operator=(const SocketSignal&) = delete;

        ~SocketSignal();

        void signalSocket();
        void resetSignal();
        SOAP_SOCKET getListeningSocket();

    private:

        void createMissingSockets();
        void closeSockets();

        SOAP_SOCKET m_listenSocket;
        SOAP_SOCKET m_sendSocket;

        mutable std::mutex m_mutex;
};

}
