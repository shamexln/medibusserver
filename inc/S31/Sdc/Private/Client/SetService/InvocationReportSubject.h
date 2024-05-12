#pragma once

#include <S31/SetService/Public/Client/InvocationReportObserver.h>
#include <S31/Utils/Public/ObservableSubject.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Access point to distribute incoming set service invocation reports.
 * @ingroup S31SdcClient
 */
using InvocationReportSubject = Utils::ObservableSubjectDelegate<S31::SetService::InvocationReportObserver>;

}
