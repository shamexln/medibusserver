#pragma once

#include <Framework/Config/Public/Config.h>

#include <boost/asio/detail/socket_option.hpp>

namespace S31::Sdc::Impl
{

/**
 * @brief Configure the SO_EXCLUSIVEADDRUSE flag listening sockets on Windows.
 */
template<class Socket>
void setExclusiveAddressUseOption(Socket& sock)
{
#ifdef DFL_CONFIG_OS_WIN32
    using ExclusiveAddrUse =
            boost::asio::detail::socket_option::boolean<BOOST_ASIO_OS_DEF(SOL_SOCKET), SO_EXCLUSIVEADDRUSE>;
    sock.set_option(ExclusiveAddrUse{true});
#else
    // On a non-windows platform this is a no-op.
    std::ignore = sock;
#endif
}
}
