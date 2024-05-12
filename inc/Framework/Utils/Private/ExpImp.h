#pragma once

#include <Framework/Config/Public/DeclSpec.h>

#if defined(DFL_UTILS_DLL)
#define DFL_UTILS_EXPIMP DFL_DLL_EXPORT
#else
#define DFL_UTILS_EXPIMP DFL_DLL_IMPORT
#endif
