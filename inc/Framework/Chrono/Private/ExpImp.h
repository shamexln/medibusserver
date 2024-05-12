#pragma once

#include <Framework/Config/Public/DeclSpec.h>

#if defined(DFL_CHRONO_DLL)
#define DFL_CHRONO_EXPIMP DFL_DLL_EXPORT
#else
#define DFL_CHRONO_EXPIMP DFL_DLL_IMPORT
#endif
