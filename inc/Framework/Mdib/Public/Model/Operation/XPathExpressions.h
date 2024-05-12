#pragma once

#include <Framework/Mdib/Public/Model/Operation/XPathExpression.h>

#include <vector>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Sequence of \ref XPathExpressions "limited XPath expressions".
 * @ingroup Mdib
 */
using XPathExpressions = std::vector<XPathExpression>;

} /* namespace Mdib */
} /* namespace DFL */
