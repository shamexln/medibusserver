#pragma once

#include <S31/Base/S31Only/Exception.h>

#include <exception>
#include <cstdint>
#include <string>
#include <sstream>

namespace S31::Sdc::Impl
{

/**
 * @brief Structure used for information of a local socket endpoint.
 *
 * \ingroup S31SdcCommonSocket
 */
class SocketEndpoint
{
    public:
        /**
         * @brief Address family such as AF_INET or AF_INET6.
         */
        unsigned short addressFamily{};

        std::string ip;

        /**
         * @brief Port number as string.
         */
        std::string service;

        [[nodiscard]] std::uint16_t getPortNumber() const;
};

inline std::uint16_t SocketEndpoint::getPortNumber() const
{
    try
    {
        return static_cast<std::uint16_t>(std::stoi(service));
    }
    catch (const std::exception& e)
    {
        S31_THROW_EXCEPTION(
                InternalDataMappingFailed,
                "Extraction of port number failed during call to std::stoi(service='" << service << "'). " << e.what());
    }
}

}
