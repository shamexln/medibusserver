#pragma once

#include <S31/Gsoap/S31Only/stdsoap2.h>
#include <S31/S31CoreExImp.h>

#include <cstring>

#ifndef _WIN32
#include <netinet/in.h>
#include <sys/socket.h>
#endif

#ifdef _WIN32
#include <MSWSock.h>
#include <WinSock2.h>
#include <ws2def.h>
#endif

namespace S31::Sdc::Impl
{

/**
 * @brief Platform wrapper for POSIX <tt>struct msghdr</tt>.
 * @details Wrapper the access to \c recvmsg() as calls in POSIX and \c WSARecvMsg in Windows.
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP ReceiveMessageHeader
{
    public:
#ifdef _WIN32
        using MsgHeader = WSAMSG;
        using MsgControlHeader = WSACMSGHDR;
#else
        using MsgHeader = struct msghdr;
        using MsgControlHeader = struct cmsghdr;
#endif

        ReceiveMessageHeader() :
                m_ioVector(),
                m_remoteAddrLen(nullptr),
                m_header()
        {
            std::memset(&m_ioVector, 0, sizeof(m_ioVector));
            std::memset(&m_header, 0, sizeof(m_header));
            std::memset(&m_controlBuffer, 0, sizeof(m_controlBuffer));
#ifdef _WIN32
            m_header.Control.buf = m_controlBuffer;
            m_header.Control.len = sizeof(m_controlBuffer);
#else
            m_header.msg_control = m_controlBuffer;
            m_header.msg_controllen = static_cast<socklen_t>(sizeof(m_controlBuffer));
#endif
        }

#ifdef _WIN32
        ULONG getReceivedMessageFlags() const
        {
            return m_header.dwFlags;
        }
#else
        int getReceivedMessageFlags() const
        {
            return m_header.msg_flags;
        }
#endif

        size_t getControlLength() const
        {
#ifdef _WIN32
            return m_header.Control.len;
#else
            // According to VxWorks socket.h
            // > Since the socket layer expects and returns socklen_t
            // > values that are always positive when viewed as signed 'int',
            // > no run-time problems are expected when operating the socket layer
            // > with applications compiled without SOCKLEN_T_UNSIGNED.
            return static_cast<std::size_t>(m_header.msg_controllen);
#endif
        }

        void setBufferForRemoteEndpoint(struct sockaddr* remoteAddr, const SOAP_SOCKLEN_T* remoteAddrLen)
        {
#ifdef _WIN32
            m_header.name = remoteAddr;
            m_header.namelen = *remoteAddrLen;
#else
            m_header.msg_name = remoteAddr;
            m_header.msg_namelen = *remoteAddrLen;
#endif
        }

        void setBufferForPayload(char* buffer, SOAP_WINSOCKINT bufferLen)
        {
#ifdef _WIN32
            m_ioVector[0].len = static_cast<unsigned long>(bufferLen);
            m_ioVector[0].buf = buffer;
            m_header.lpBuffers = m_ioVector;
            m_header.dwBufferCount = static_cast<ULONG> (sizeof(m_ioVector) / sizeof(m_ioVector[0]));
#else
            m_ioVector[0].iov_base = static_cast<void*>(buffer);
            m_ioVector[0].iov_len = bufferLen;
            m_header.msg_iov = m_ioVector;
            m_header.msg_iovlen = static_cast<int>(sizeof(m_ioVector) / sizeof(m_ioVector[0]));
#endif
        }

        void setFlags(int flags)
        {
            m_requestFlags = flags;
        }

        /**
         * @brief Return the number of bytes received.
         * @details Return the number of bytes received, or -1 if an error occurred.
         * @param socket UDP socket to receive next datagram
         * @return the number of bytes received, or \c -1 if an error occurred.
         */
        int recvmsg(SOAP_SOCKET socket);

        const MsgHeader& getMsgHeader() const
        {
            return m_header;
        }

        unsigned int getReceiveInterfaceIndex() const
        {
            return m_receiveInterfaceIndex;
        }

        unsigned char getReceiveProtocolFamily() const
        {
            return m_receiveProtocolFamily;
        }

        unsigned char getReceiveTtl() const
        {
            return m_receiveTtl;
        }

    private:
        /**
         * @brief Sequence of buffers.
         * @details In this case the buffer for the payload is one buffer.
         */
#ifdef _WIN32
        WSABUF m_ioVector[1];
#else
        struct iovec m_ioVector[1];
#endif

        /**
         * @note It is unclear where the buffer size comes from.
         */
        char m_controlBuffer[
#ifdef CMSG_SPACE
                             CMSG_SPACE(8) + CMSG_SPACE(1024)
#else
                             8 + 1024
#endif
                             ]{};
        int m_requestFlags{0};
        SOAP_SOCKLEN_T* m_remoteAddrLen;
        MsgHeader m_header;

        unsigned int m_receiveInterfaceIndex{0};
        unsigned char m_receiveProtocolFamily{PF_UNSPEC};
        unsigned char m_receiveTtl{0};

};

}
