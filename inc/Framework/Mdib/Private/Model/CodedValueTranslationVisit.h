#pragma once

#include <Framework/Mdib/Public/Model/CodedValueTranslation.h>

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
void visitMembers(Visitor& vis, const CodedValueTranslation& cv)
{
    vis(cv.codingSystem());
    vis(cv.code());
    vis(cv.extensions());
}
}
}
}
