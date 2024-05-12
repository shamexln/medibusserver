#pragma once

#include <Framework/Config/Public/DeclSpec.h>

#if defined(DFL_ENCODING_DLL)
#define DFL_ENCODING_EXPIMP DFL_DLL_EXPORT
#else
#define DFL_ENCODING_EXPIMP DFL_DLL_IMPORT
#endif
