#pragma once

#include <Framework/Config/Public/Config.h>

#if defined(DFL_CONFIG_OS_WIN32)
#include <Framework/Thread/Private/SemaphoreImplWin32.h>
#elif defined(DFL_CONFIG_OS_VXWORKS)
#include <Framework/Thread/Private/SemaphoreImplVxWorks.h>
#elif defined(DFL_CONFIG_OS_UNIX)
#include <Framework/Thread/Private/SemaphoreImplUnix.h>
#else
#error "platform not supported"
#endif
