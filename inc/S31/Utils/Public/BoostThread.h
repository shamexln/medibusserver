#pragma once

#include <S31/Utils/Private/S31UtilsExImp.h>

#include <boost/thread/thread.hpp>

namespace S31::BoostThread
{
/**
 * @brief Provides boost thread attributes with a default stack size of 512Kb on VxWorks and 1024Kb on Windows.
 * @return Default boost thread attributes.
 * @ingroup S31Utils
 */
S31_UTILS_EXPIMP boost::thread::attributes defaultThreadAttributes();
}
