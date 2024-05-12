#pragma once

#include <Framework/Config/Public/DeclSpec.h>

#if defined(S31_HISTORY_DLL_BUILD)
#define S31_HISTORY_EXPIMP DFL_DLL_EXPORT
#else
#define S31_HISTORY_EXPIMP DFL_DLL_IMPORT
#endif
