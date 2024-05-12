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
/**
 * @brief Returns the absolute current working directory path, as if by ISO/IEC 9945 getcwd().
 *
 * @throw std::runtime_error in case of an error.
 *
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP boost::filesystem::path currentPath();
/**
 * @brief Returns the folder where the current executable is running in.
 *
 * On windows it uses GetModuleFileNameA
 * (https://docs.microsoft.com/en-us/windows/desktop/api/libloaderapi/nf-libloaderapi-getmodulefilenamea).
 * On VxWorks taskInfoGet combined with rtpInfoGet are used.
 * On other operating systems the realpath of /proc/self/exe is used.
 *
 * @throw std::runtime_error in case of an error.
 *
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP boost::filesystem::path currentExeFolder();
}
}
