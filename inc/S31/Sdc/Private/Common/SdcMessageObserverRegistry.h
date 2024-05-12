#pragma once

#include <S31/Sdc/Public/Common/SdcMessageObserver.h>
#include <S31/Utils/Public/ObservableSubject.h>

namespace S31::Sdc::Impl
{
using SdcMessageObserverRegistry = S31::Utils::ObservableSubjectDelegate<SdcMessageObserver>;
}
