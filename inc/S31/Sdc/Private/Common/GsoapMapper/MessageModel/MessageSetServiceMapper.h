#pragma once

#include <S31/Sdc/Private/Device/SetService/OperationInvokedReportPart.h>
#include <S31/SetService/Public/Client/ClientInvocationReport.h>
#include <S31/SetService/Public/Common/Argument.h>
#include <S31/SetService/Public/Common/InvocationError.h>
#include <S31/SetService/Public/Common/InvocationReport.h>
#include <S31/SetService/Public/Common/InvocationState.h>
#include <S31/SetService/Public/Common/ProposedAlertStates.h>
#include <S31/SetService/Public/Device/InitialInvocationInfo.h>

#include <boost/optional/optional.hpp>
#include <S31/Gsoap/S31Only/generated/gsoap/soapStub.h>

#include <string>

namespace DFL::Mdib
{
class MdibVersion;
}

namespace S31::Sdc::Impl::Gsoap
{

/**
 * @brief Maps all message relevant objects from the BICEPS message model.
 * @ingroup S31SdcCommon
 */
class MessageSetServiceMapper
{
    public:

        /**
         * @name Activate
         * @{
         */
        static S31::SetService::Arguments mapArgumentsFromGsoap(const std::vector<_msg__Activate_Argument>& src);
        /** @} */

        /**
         * @name SetAlertStates
         * @{
         */
         static S31::SetService::ProposedAlertStates mapAlertsFromGsoap(const _msg__SetAlertState& src);
        /** @} */

        /**
         * @name Common
         * @{
         */
        static S31::SetService::ClientInvocationReport mapClientInvocationReportFromGsoap(const DFL::Mdib::MdibVersion& mdibVersion, const _msg__OperationInvokedReport_ReportPart& src);

        static msg__InvocationState mapInvocationStateToGsoap(S31::SetService::InvocationState src);
        static S31::SetService::InvocationState mapInvocationStateFromGsoap(msg__InvocationState src);

        static msg__InvocationError mapInvocationErrorToGsoap(S31::SetService::InvocationError src);
        static S31::SetService::InvocationError mapInvocationErrorFromGsoap(msg__InvocationError src);

        static void mapInitialInvocationInfoToGsoap(msg__AbstractSetResponse& dest, const S31::SetService::InitialInvocationInfo& src);

        static _msg__OperationInvokedReport_ReportPart mapOperationInvokedReportPartToGsoap(const OperationInvokedReportPart& src);
        static OperationInvokedReportPart mapOperationInvokedReportPartFromGsoap(const _msg__OperationInvokedReport_ReportPart& src);

        static S31::SetService::ClientInvocationReport mapInvocationReportFromGsoap(const msg__AbstractSetResponse& response,
                                                                                    const S31::SetService::OperationHandle& handle,
                                                                                    const boost::optional<S31::SetService::OperationTarget>& targetHandle,
                                                                                    const boost::optional<DFL::Locale::Utf8>& soapErrorMessage);
};

}
