#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/**
 * @brief Description of the handle validity that is returned by \ref DFL::Mdib::Impl::validityOf.
 * @ingroup Mdib
 */
enum class HandleValidity
{
    Invalid, //!< Invalid, is empty or contains illegal characters.
    Valid //!< Valid.
};

/**
 * @brief Checks the handle validity of std::string handle
 * @ingroup Mdib
 */
HandleValidity DFL_MDIB_EXPIMP validityOf(const std::string& handle);

}
}
}
