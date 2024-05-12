#pragma once

#include <Framework/Config/Public/DeclSpec.h>

#if defined(S31_TESTUTILS_DLL_BUILD)
#define S31_TESTUTILS_EXPIMP DFL_DLL_EXPORT
#else
#define S31_TESTUTILS_EXPIMP DFL_DLL_IMPORT
#endif
