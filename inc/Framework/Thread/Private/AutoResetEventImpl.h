#pragma once

#include <Framework/Config/Public/Config.h>

#if defined(DFL_CONFIG_OS_WIN32)
#include <Framework/Thread/Private/AutoResetEventImplWin32.h>
#elif defined(DFL_CONFIG_OS_VXWORKS)
#include <Framework/Thread/Private/AutoResetEventImplVxWorks.h>
#elif defined(DFL_CONFIG_OS_UNIX)
#include <Framework/Thread/Private/AutoResetEventImplUnix.h>
#else
#error "platform not supported"
#endif
