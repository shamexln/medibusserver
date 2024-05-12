#pragma once

#include <S31/Sdc/Public/Client/RemoteDevicesObserver.h>
#include <S31/S31CoreExImp.h>
#include <S31/Utils/Public/ObservableSubject.h>

namespace S31::Sdc
{

/**
 * @brief Observable subject to observe for \ref RemoteDevice "remote device" online/offline callbacks.
 * @ingroup S31SdcClient
 */
class S31_CORE_EXPIMP RemoteDevicesSubject: public Utils::ObservableSubject<Sdc::RemoteDevicesObserver>
{
};

}
