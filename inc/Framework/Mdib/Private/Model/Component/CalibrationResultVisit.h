#pragma once

#include <Framework/Mdib/Public/Model/Component/CalibrationResult.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
/**
 * @brief Calls the visitor for each member.
 *
 * @param vis visitor
 * @param calibrationResult @ref DFL::Mdib::CalibrationResult value to visit
 */
template <class Visitor>
void visitMembers(Visitor& vis, const CalibrationResult& calibrationResult)
{
    vis(calibrationResult.code());
    vis(calibrationResult.value());
}
}
}
}
