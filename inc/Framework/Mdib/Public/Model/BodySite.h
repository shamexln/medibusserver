#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/CodedValue.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Represents a body site as \ref CodedValue.
 * \ingroup Mdib
 */
using BodySite = CodedValue;

/**
* @brief Sequence of \ref BodySite.
* \ingroup Mdib
*/
using BodySites = std::vector<BodySite>;

} /* namespace Mdib */
} /* namespace DFL */
