#pragma once

#include <Framework/Log/Public/Registry.h>

#include <cstdio>

namespace S31::Log::Test
{

/**
 * @brief Service and DFL crypto/mdib log would flood console with error messages otherwise.
 * @ingroup S31Log
 */
class DeactivateServiceAndDflLogging
{
public:
    DeactivateServiceAndDflLogging() noexcept
    {
        try
        {
            DFL::Log::Registry::init();
            DFL::Log::Registry::service().clear();
            DFL::Log::Registry::createOrGet("Dfl.Crypto.debug").clear();
            DFL::Log::Registry::createOrGet("Dfl.Mdib.debug").clear();
            DFL::Log::Registry::security().clear();
        }
        catch (const std::runtime_error& e)
        {
            std::printf("Failed to configure DFL logging: %s\n", e.what());
        }
        catch (...)
        {
            std::printf("Failed to configure DFL logging\n");
        }
    }
};

}