#pragma once

#include <Framework/Config/Public/Config.h>
#if defined(DFL_CONFIG_OS_WIN32)

#include <Framework/Log/Private/ExpImp.h>
#include <Framework/Log/Private/Logger.h>
#include <Framework/Log/Private/Windows/WindowsEventLog.h>

namespace DFL
{
namespace Log
{
class Message;
namespace Impl
{
namespace Windows
{
class DFL_LOG_EXPIMP BasicDwLogger
{
public:
    BasicDwLogger(const char* sourceName, Impl::Logger logger);

    Message operator()(const Message& message) const;

private:
    Impl::Windows::EventLog m_eventLog{};
    Impl::Logger m_logger{};
};
}
}
}
}

#endif
