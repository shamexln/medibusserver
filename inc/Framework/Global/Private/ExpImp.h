#pragma once

// This header file has to be compatible with c source files.
// Therefore the standard mechanism (which uses boost) cannot be used here.
#include <Framework/Global/Common.h>

#if defined(DFL_GLOBAL_DLL)
#define DFL_GLOBAL_EXPIMP  DLL_EXPORT
#else
#define DFL_GLOBAL_EXPIMP  DLL_IMPORT
#endif
