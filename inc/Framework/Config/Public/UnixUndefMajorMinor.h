#pragma once

#include <Framework/Config/Public/Config.h>

#if defined(DFL_CONFIG_OS_UNIX)
// In Linux builds the gcc compiler reports the following warning:
//
//    In the GNU C Library, "major" is defined
//    by <sys/sysmacros.h>. For historical compatibility, it is
//    currently defined by <sys/types.h> as well, but we plan to
//    remove this soon. To use "major", include <sys/sysmacros.h>
//    directly. If you did not intend to use a system-defined macro
//    "major", you should undefine it after including <sys/types.h>.
//
// An include of this file means that the major and minor macros are
// not used. Therefore, sys/types.h is included and as proposed the
// macros are undefined.
#include <sys/types.h>
#if defined(major)
#undef major
#endif
#if defined(minor)
#undef minor
#endif
#endif
