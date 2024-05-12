#pragma once

#include <S31/Sdc/Public/Device/ClientSubscriptionObserver.h>
#include <S31/S31CoreExImp.h>
#include <S31/Utils/Public/ObservableSubject.h>

namespace S31::Sdc
{

/**
 * @brief Observable subject to observe for \ref SubscriptionInfo "Client subscriptions information" for this device.
 * @ingroup S31SdcClient
 */
using SubscriptionInfoSubject = Utils::ObservableSubject<Sdc::SubscriptionInfoObserver>;

}
