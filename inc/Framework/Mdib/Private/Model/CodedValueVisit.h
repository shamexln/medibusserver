#pragma once

#include <Framework/Mdib/Public/Model/CodedValue.h>

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
void visitMembers(Visitor& vis, const CodedValue& cv)
{
    vis(cv.codingSystem());
    vis(cv.code());
    vis(cv.conceptDescription());
    vis(cv.symbolicCodeName());
    vis(cv.translations());
    vis(cv.extensions());
}
}
}
}
