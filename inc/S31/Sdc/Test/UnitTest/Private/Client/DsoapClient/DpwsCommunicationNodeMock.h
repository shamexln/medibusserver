#pragma once

#include <S31/Sdc/Private/Client/DsoapClient/DpwsCommunicationNode.h>

namespace S31::Sdc::Impl::Test
{
DFL::NotNull<std::shared_ptr<DpwsCommunicationNode>> makeDpwsCommunicationNodeMock();
}
