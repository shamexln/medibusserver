#pragma once

#include <Framework/Config/Public/DeclSpec.h>

#if defined(DFL_MDIB_DLL)
#define DFL_MDIB_EXPIMP DFL_DLL_EXPORT
#else
#define DFL_MDIB_EXPIMP DFL_DLL_IMPORT
#endif
