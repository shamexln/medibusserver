#pragma once

#include <Framework/Mdib/Public/Model/Component/CalibrationDocumentation.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor& vis, const CalibrationDocumentation& cd)
{
    vis(cd.localizedTexts());
    vis(cd.calibrationResults());
}
}
}
}
