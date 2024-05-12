#pragma once

#include <Framework/Config/Public/DeclSpec.h>

#if defined(DFL_CRYPTO_DLL)
#define DFL_CRYPTO_EXPIMP DFL_DLL_EXPORT
#else
#define DFL_CRYPTO_EXPIMP DFL_DLL_IMPORT
#endif
