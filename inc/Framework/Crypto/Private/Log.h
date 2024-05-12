#pragma once

#include <Framework/Crypto/Private/Registry.h>

#include <Framework/Log/Public/EventCode.h>
#include <Framework/Log/Public/Log.h>
#include <Framework/Log/Public/Severities.h>
#include <Framework/Utils/Public/DflComponentKey.h>

#include <exception>
#include <string>

namespace DFL
{
namespace Crypto
{
namespace Impl
{
const ::DFL::Log::EventCode nullEventCode(0);
const char* const emptyAssemblyId = "";
}
}
}

#define DFL_CRYPTO_IMPL_DEBUG_LOG(severity, msg)                               \
    DFL_LOG_WITH(::DFL::Crypto::Impl::Registry::debugLogger(),                 \
                 severity,                                                     \
                 msg,                                                          \
                 ::DFL::componentKey,                                          \
                 ::DFL::Crypto::Impl::nullEventCode,                           \
                 ::DFL::Crypto::Impl::emptyAssemblyId)

#define DFL_CRYPTO_DEBUG_LOG_TRACE(msg)                                        \
    DFL_CRYPTO_IMPL_DEBUG_LOG(::DFL::Log::Trace, msg)

#define DFL_CRYPTO_DEBUG_LOG_SUCCESS(msg)                                      \
    DFL_CRYPTO_IMPL_DEBUG_LOG(::DFL::Log::Success, msg)

#define DFL_CRYPTO_DEBUG_LOG_INFO(msg)                                         \
    DFL_CRYPTO_IMPL_DEBUG_LOG(::DFL::Log::Info, msg)

#define DFL_CRYPTO_DEBUG_LOG_WARNING(msg)                                      \
    DFL_CRYPTO_IMPL_DEBUG_LOG(::DFL::Log::Warning, msg)

#define DFL_CRYPTO_DEBUG_LOG_ERROR(msg)                                        \
    DFL_CRYPTO_IMPL_DEBUG_LOG(::DFL::Log::Error, msg)

#define DFL_CRYPTO_DEBUG_LOG_CURRENT_EXCEPTION(msg)                            \
    try                                                                        \
    {                                                                          \
        throw;                                                                 \
    }                                                                          \
    catch (const std::exception& e)                                            \
    {                                                                          \
        const auto logMsg = std::string(msg) + ' ' + e.what();                 \
        DFL_CRYPTO_DEBUG_LOG_WARNING(logMsg.c_str());                          \
    }                                                                          \
    catch (...)                                                                \
    {                                                                          \
        const auto logMsg = std::string(msg) + " unknown exception";           \
        DFL_CRYPTO_DEBUG_LOG_WARNING(logMsg.c_str());                          \
    }
