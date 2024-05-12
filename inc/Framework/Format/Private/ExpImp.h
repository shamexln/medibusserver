#pragma once

#include <Framework/Config/Public/DeclSpec.h>

#if defined(DFL_FORMAT_DLL)
#define DFL_FORMAT_EXPIMP DFL_DLL_EXPORT
#else
#define DFL_FORMAT_EXPIMP DFL_DLL_IMPORT
#endif
