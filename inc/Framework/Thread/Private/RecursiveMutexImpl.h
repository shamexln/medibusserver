#pragma once

#include <Framework/Config/Public/Config.h>

#if defined(DFL_CONFIG_OS_WIN32)
#include <Framework/Thread/Private/RecursiveMutexImplWin32.h>
#elif defined(DFL_CONFIG_OS_VXWORKS)
#include <Framework/Thread/Private/RecursiveMutexImplVxWorks.h>
#elif defined(DFL_CONFIG_OS_UNIX)
#include <Framework/Thread/Private/RecursiveMutexImplUnix.h>
#else
#error "os not supported"
#endif
