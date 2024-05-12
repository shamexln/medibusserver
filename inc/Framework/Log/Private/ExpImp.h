#pragma once

#include <Framework/Config/Public/DeclSpec.h>

#if defined(DFL_LOG_DLL)
#define DFL_LOG_EXPIMP DFL_DLL_EXPORT
#else
#define DFL_LOG_EXPIMP DFL_DLL_IMPORT
#endif
