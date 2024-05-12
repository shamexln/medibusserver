#pragma once

#include <S31/Sdc/Private/Device/SetService/OperationInvokedReportPart.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Model/MdibVersion.h>

#include <string>
#include <vector>

namespace S31::Sdc::Impl
{

/**
 * @brief Serializes to a Biceps invocation report.
 * @details
 * XML snippet could be used as SOAP message body.
 *
 * @ingroup S31SdcDevice
 */
S31_CORE_EXPIMP std::string serializeOperationInvokedReport(
        const DFL::Mdib::MdibVersion&                             mdibVersionIn,
        const std::vector<Sdc::Impl::OperationInvokedReportPart>& reportParts);

}
