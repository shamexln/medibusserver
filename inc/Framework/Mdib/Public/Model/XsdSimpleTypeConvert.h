#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/XsdSimpleType.h>

#include <boost/optional.hpp>

#include <string>

namespace DFL
{
namespace Mdib
{
namespace Convert
{

/**
 * @brief Convert enum value to official string representation (without namespace prefix).
 * @ingroup Mdib
 */
std::string DFL_MDIB_EXPIMP toStandardStringName(XsdSimpleType type);

/**
 * @brief Convert enum value from string representation to enum value.
 * @ingroup Mdib
 */
boost::optional<XsdSimpleType> DFL_MDIB_EXPIMP toOptionalXsdSimpleType(const std::string& type);

}
}
}
