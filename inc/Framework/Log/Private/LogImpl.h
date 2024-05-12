#pragma once

#include <Framework/Log/Public/EventCode.h>
#include <Framework/Log/Public/Logger.h>
#include <Framework/Log/Public/Message.h>
#include <Framework/Log/Public/SecurityState.h>
#include <Framework/Log/Public/Text.h>

#include <Framework/Chrono/Public/SystemClock.h>

namespace DFL
{
namespace Log
{
namespace Impl
{
inline void doLog(Log::Logger const& logger,
                  Severity const& severity,
                  const char* txt,
                  Component::Key const& compKey,
                  EventCode const& eventCode,
                  char const* file,
                  int line,
                  char const* assemblyId = "",
                  const Log::SecurityState ss = SecurityState::None)
{
    static_cast<void>(logger(MessageBuilder{}
                                 .severity(severity)
                                 .text(Text{txt})
                                 .componentKey(compKey)
                                 .eventCode(eventCode)
                                 .file(file)
                                 .line(line)
                                 .assemblyId(assemblyId)
                                 .securityState(ss)));
}
}
}
}

/*
 Although the log function called by this macro contains just one line
 do not replace that line and remove the function call from this macro.
 The memory which is needed to create a message object is allocated on the
 stack. This memory is only freed at the end of a function call not at the end
 of a scope within the function. By redirecting our log macro to a function call
 we ensure that all stack allocated objects are freed. Otherwise this memory
 would be accumulated to stack of the client calling this macro.
 */
#define DFL_LOG_IMPL_WITH(logger,                                              \
                          severity,                                            \
                          msg,                                                 \
                          compKey,                                             \
                          eventCode,                                           \
                          assemblyId,                                          \
                          securityState)                                       \
    DFL::Log::Impl::doLog(logger,                                              \
                          severity,                                            \
                          msg,                                                 \
                          compKey,                                             \
                          DFL::Log::EventCode(eventCode),                      \
                          __FILE__,                                            \
                          __LINE__,                                            \
                          assemblyId,                                          \
                          securityState)
