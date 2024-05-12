#pragma once

#include <Framework/Utils/Private/ExpImp.h>

namespace boost
{
namespace filesystem
{
class path;
}
}
namespace DFL
{
namespace Filesystem
{
namespace Impl
{
DFL_UTILS_EXPIMP boost::filesystem::path currentExeFolder();
}
}
}
