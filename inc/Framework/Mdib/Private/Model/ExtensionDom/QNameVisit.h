#pragma once

#include <Framework/Utils/Public/QName.h>

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
void visitMembers(Visitor& vis, const QName& qName)
{
    vis(qName.namespaceUri());
    vis(qName.prefix());
    vis(qName.localName());
}
}
}
}
