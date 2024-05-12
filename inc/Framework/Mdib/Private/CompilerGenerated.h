#pragma once

#include <Framework/Utils/Public/CompilerGenerated.h>

#define DFL_MDIB_IMMUTABLE(Type) \
        DFL_DEFAULT_COPYCONSTRUCTABLE(Type) \
        DFL_DEFAULT_MOVECONSTRUCTABLE(Type) \
        DFL_NOT_COPYASSIGNABLE(Type)
