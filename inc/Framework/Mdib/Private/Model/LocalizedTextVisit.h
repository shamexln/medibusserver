#pragma once

#include <Framework/Mdib/Public/Model/LocalizedText.h>

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
void visitMembers(Visitor& vis, const LocalizedText& lt)
{
    vis(lt.languageTag());
    vis(lt.text());
    vis(lt.reference());
    vis(lt.version());
    vis(lt.textWidth());
}
}
}
}
