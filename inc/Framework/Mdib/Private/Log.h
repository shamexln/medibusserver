#pragma once

#include <atomic>
#include <exception>
#include <string>
#include <Framework/Format/Public/Stream.h>
#include <Framework/Log/Public/Log.h>
#include <Framework/Log/Public/Logger.h>
#include <Framework/Log/Public/Registry.h>
#include <Framework/Log/Public/Severities.h>
#include <Framework/Utils/Public/Instance.h>
#include <Framework/Utils/Public/Key.h>
#include <Framework/Utils/Public/Kind.h>

namespace DFL
{
namespace Mdib
{
/**
 * \brief Provides logging.
 *
 * \ingroup Mdib
 */
namespace Log
{
namespace Impl
{
using ComponentKindType = Component::StaticKind<0x0DF, Component::Static::string<'D', 'F', 'L'> >;
using ComponentInstanceType = Component::StaticInstance<0x0>;
using ComponentKeyType = Component::StaticKey<ComponentKindType, ComponentInstanceType>;

const ComponentKeyType MdibComponentKey;

const ::DFL::Log::EventCode MdibEventCode(0);
const char* const mdibAssemblyId = "";

/**
 * @brief The maximum number of occurrences of limited log messages.
 */
static const int NumberOfOccurrencesIfLimitedLogMessages = 50;
using LimitedLogMessagesInt = std::atomic_int;

/**
 * Returns a static reference to the mdib logger.
 *
 * @returns The mdib logger.
 */
inline DFL::Log::Logger& mdibDebugLogger()
{
    // use commented out implementation once PCSWORK-1187 is resolved
    return DFL::Log::Registry::createOrGet("Dfl.Mdib.debug");
    // static DFL::Log::Logger& logger = DFL::Log::Registry::createOrGet("Dfl.Mdib.debug");
    // return logger;
}

/**
 * template specialization for single argument
 */
template <typename T>
inline void writeStream(DFL::Format::Stream& out, T arg)
{
    out << arg;
}

/**
 * template specialization for generic arguments
 */
template <typename T, typename... args>
inline void writeStream(DFL::Format::Stream& out, T head, args... tail)
{
    out << head;
    writeStream(out, tail...);
}

} /* namespace Impl */

template <typename... args>
inline void writeStreamLogMessage(const DFL::Log::Severity& level, const char* file, int line, args... tail)
{
    try
    {
        DFL::Format::Stream msgStream;
        Impl::writeStream(msgStream, tail...);
        auto message = DFL::Log::Message(level, DFL::Log::Text(msgStream.cStr()), Impl::MdibComponentKey, Impl::MdibEventCode, file, line, Impl::mdibAssemblyId);
        auto& logger = Impl::mdibDebugLogger();
        logger(message);
    }
    catch(...)
    {
    }
}

} // namespace Log
} /* namespace Mdib */
} /* namespace DFL */

/**
 * @{
 * Logging macros
 *  \ingroup Mdib
 */
#define DFL_MDIB_STREAM_TRACE(...) do { DFL::Mdib::Log::writeStreamLogMessage(DFL::Log::Trace, __FILE__, __LINE__, __VA_ARGS__); } while(0)
#define DFL_MDIB_STREAM_SUCCESS(...) do { DFL::Mdib::Log::writeStreamLogMessage(DFL::Log::Success, __FILE__, __LINE__, __VA_ARGS__); } while(0)
#define DFL_MDIB_STREAM_INFO(...) do { DFL::Mdib::Log::writeStreamLogMessage(DFL::Log::Info, __FILE__, __LINE__, __VA_ARGS__); } while(0)
#define DFL_MDIB_STREAM_WARNING(...) do { DFL::Mdib::Log::writeStreamLogMessage(DFL::Log::Warning, __FILE__, __LINE__, __VA_ARGS__); } while(0)
#define DFL_MDIB_STREAM_WARNING_ONCE(...) \
    do \
    { \
        static bool logged = false; \
        if (!logged) \
        { \
            logged = true;  \
            DFL::Mdib::Log::writeStreamLogMessage(DFL::Log::Warning, __FILE__, __LINE__, __VA_ARGS__); \
        } \
    } while (0)
#define DFL_MDIB_STREAM_WARNING_LIMITED(...) \
    do \
    { \
        static DFL::Mdib::Log::Impl::LimitedLogMessagesInt logCountLeft{DFL::Mdib::Log::Impl::NumberOfOccurrencesIfLimitedLogMessages}; \
        if (logCountLeft > 0) \
        { \
            --logCountLeft; \
            DFL::Mdib::Log::writeStreamLogMessage(DFL::Log::Warning, __FILE__, __LINE__, __VA_ARGS__); \
        } \
    } while (0)
#define DFL_MDIB_STREAM_ERROR(...) do { DFL::Mdib::Log::writeStreamLogMessage(DFL::Log::Error, __FILE__, __LINE__, __VA_ARGS__); } while(0)
/**
 * @}
 */
