#pragma once

#include <Framework/Config/Public/DeclSpec.h>

#if defined(DFL_THREAD_DLL)
#define DFL_THREAD_EXPIMP DFL_DLL_EXPORT
#else
#define DFL_THREAD_EXPIMP DFL_DLL_IMPORT
#endif
