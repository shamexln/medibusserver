#pragma once

#include <S31/Sdc/Public/Discovery/DiscoveryObserver.h>
#include <S31/S31CoreExImp.h>
#include <S31/Utils/Public/ObservableSubject.h>

namespace S31::Sdc
{

/**
 * @brief Observable subject to observe for \ref RemoteDeviceInfo "remote device information" that is discovered on the network.
 * @ingroup S31SdcDiscovery
 */
using DiscoverySubject = Utils::ObservableSubject<DiscoveryObserver>;

}
