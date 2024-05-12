#pragma once

#include <Framework/Config/Public/Config.h>

#if defined(DFL_CONFIG_OS_WIN32)
#include <Framework/Config/Public/WindowsProxy.h>
#endif

#if defined(DFL_CONFIG_OS_VXWORKS)
#include <vxWorks.h>
#endif
