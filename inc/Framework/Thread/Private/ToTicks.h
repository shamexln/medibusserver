#pragma once

#include <Framework/Config/Public/Config.h>

#if defined(DFL_CONFIG_OS_WIN32)
#elif defined(DFL_CONFIG_OS_VXWORKS)
#include <Framework/Thread/Private/ToTicksVxWorks.h>
#elif defined(DFL_CONFIG_OS_UNIX)
#else
#error "platform not supported"
#endif
