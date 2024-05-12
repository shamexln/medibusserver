#pragma once

#include <boost/asio/buffer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/udp.hpp>

#include <array>
#include <functional>
#include <string>
#include <string_view>

namespace S31::Sdc::Test
{

/**
 * @brief Sends a UDP datagram.
 * @details
 * This test helper can be used to send UDP unicast and multicast datagrams.
 *
 * Follows https://www.boost.org/doc/libs/1_75_0/doc/html/boost_asio/example/cpp11/multicast/sender.cpp
 */
inline void sendUdpDatagram(std::string_view ip, unsigned short port, std::string_view message)
{
    boost::asio::io_context ioContext;
    boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::make_address(ip), port);
    boost::asio::ip::udp::socket socket(ioContext, endpoint.protocol());
    socket.send_to(boost::asio::buffer(message), endpoint);
    ioContext.run();
}

/**
 * @brief Helper class to collect multiple messages from a UDP socket.
 * @details This class will receive datagrams from a UDP socket,
 * and run a callback for each with the message contents and source
 * endpoint.
 */
class UdpCollector
{
    public:
        using Callback = std::function<void(std::string_view, const boost::asio::ip::udp::endpoint&)>;

        UdpCollector(boost::asio::ip::udp::socket& socket, Callback callback)
            : m_socket(socket)
            , m_callback(std::move(callback))
        {
        }

        void receiveMessages()
        {
            m_socket.async_receive_from(
                    boost::asio::buffer(m_receiveBuffer),
                    m_remoteEndpoint,
                    [this](const auto& error, const auto& bytesReceived)
                    {
                        if (error || !m_callback)
                        {
                            return;
                        }
                        m_callback(std::string_view(m_receiveBuffer.data(), bytesReceived), m_remoteEndpoint);
                        receiveMessages();
                    });
        }

    private:
        boost::asio::ip::udp::socket&  m_socket;
        boost::asio::ip::udp::endpoint m_remoteEndpoint;
        std::array<char, 2048>         m_receiveBuffer;
        Callback                       m_callback;
};

/**
 * @brief Sends a UDP datagram, waits for responses.
 * @details
 * This test helper can be used to send UDP unicast and multicast datagrams. Waits for \c timeout
 * milliseconds to receive responses.
 *
 */
inline void sendAndReceiveUdpDatagram(
        std::string_view          ip,
        unsigned short            port,
        std::string_view          message,
        std::chrono::milliseconds timeout,
        UdpCollector::Callback    callback)
{
    boost::asio::io_context        ioContext;
    boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::make_address(ip), port);
    boost::asio::ip::udp::socket   socket(ioContext, endpoint.protocol());
    UdpCollector                   collector{socket, std::move(callback)};

    socket.send_to(boost::asio::buffer(message), endpoint);

    collector.receiveMessages();
    ioContext.run_for(timeout);
}
}

namespace S31Test::Sdc
{

[[deprecated("use S31::Sdc::Test::sendUdpDatagram")]]
inline void sendUdpDatagram(std::string_view ip, unsigned short port, std::string_view message)
{
    S31::Sdc::Test::sendUdpDatagram(ip, port, message);
}

}
