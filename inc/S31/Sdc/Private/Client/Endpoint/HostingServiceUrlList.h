#pragma once

#include <S31/Sdc/Private/Common/Endpoint/ResettableUrlList.h>

namespace S31::Sdc::Impl::Endpoint
{

/**
 * @brief URL list used to manage hosting services physical addresses (XAddrs).
 * @ingroup S31SdcClient
 */
using HostingServiceUrlList = ResettableUrlList;

}
