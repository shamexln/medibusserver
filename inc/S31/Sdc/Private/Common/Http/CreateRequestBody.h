#pragma once

#include <boost/asio/ip/tcp.hpp>

#include <string>

namespace S31::Sdc::Impl
{
/**
 * @brief Contains information about a given connection.
 * @details Used in \ref CreateRequestBody to augment a Http Request body with additional information.
 * @ingroup S31SdcCommon
 */
struct ConnectionContext
{
    std::string localIpAddress;
};

/**
 * @brief Function type to create a message Body for @ref S31::Sdc::Impl::HttpClientRequest.
 * @ingroup S31SdcCommon
 */
using CreateRequestBody = std::function<std::string(const ConnectionContext&)>;

}
