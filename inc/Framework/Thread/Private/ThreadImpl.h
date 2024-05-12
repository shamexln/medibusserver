#pragma once

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Config/Public/Config.h>
#include <Framework/Format/Public/Stream.h>

#include <string>

namespace DFL
{
namespace Thread
{
namespace Impl
{
#if defined(DFL_CONFIG_OS_VXWORKS)
using Id = int;
#endif
#if defined(DFL_CONFIG_OS_WIN32)
using Id = unsigned long;
#endif
#if defined(DFL_CONFIG_OS_UNIX)
using Id = unsigned long;
#endif
std::string name(const Id& id);

#if !defined(DFL_CONFIG_OS_VXWORKS)
// other os like e.g. windows have no name property
// for their threads thus we implement a
// generic name by converting the id to a string
inline std::string name(const Id& id)
{
    DFL::Format::Stream str{};
    str << '#' << id;
    return str.cStr();
}
#endif

}
}
}
namespace DFL
{
namespace Thread
{
namespace ThisThread
{
namespace Impl
{
void sleepFor(const Chrono::Milliseconds& ms);
Thread::Impl::Id id();
std::string name();

#if !defined(DFL_CONFIG_OS_VXWORKS)
inline std::string name()
{
    return ::DFL::Thread::Impl::name(id());
}
#endif
}
}
}
}
