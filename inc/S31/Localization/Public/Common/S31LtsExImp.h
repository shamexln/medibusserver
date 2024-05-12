#pragma once

#include <Framework/Config/Public/DeclSpec.h>

#if defined(S31_LTS_DLL_BUILD)
#define S31_LTS_EXPIMP DFL_DLL_EXPORT
#else
#define S31_LTS_EXPIMP DFL_DLL_IMPORT
#endif
