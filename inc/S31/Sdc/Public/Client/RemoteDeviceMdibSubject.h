#pragma once

#include <S31/Sdc/Public/Client/RemoteDeviceMdibObserver.h>
#include <S31/S31CoreExImp.h>
#include <S31/Utils/Public/ObservableSubject.h>

namespace S31::Sdc
{

/**
 * @brief   Subject to observe %MDIB changes coming up from different remote devices.
 * @details Usually, MDIB changes are subscribed using \ref DFL::Mdib::MdibAccess. However, notifications that are
 * distributed by \ref DFL::Mdib::MdibAccess do not provide any remote device information. If remote device
 * information is required on an %MDIB changes callback, then %RemoteDeviceMdibSubject can be used.
 * \ingroup S31SdcClient
 */
using RemoteDeviceMdibSubject = Utils::ObservableSubject<Sdc::RemoteDeviceMdibObserver>;

}
