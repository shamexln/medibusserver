#pragma once

#include <S31/Safety/Public/Information.h>
#include <S31/SetService/Private/Client/CheckerResult.h>
#include <S31/SetService/Public/Common/Argument.h>
#include <S31/SetService/Public/Common/ProposedAlertState.h>
#include <S31/SetService/Public/Common/ProposedAlertStates.h>
#include <S31/SetService/Public/Common/ProposedComponentStates.h>
#include <S31/SetService/Public/Common/ProposedContextStates.h>
#include <S31/SetService/Public/Common/ProposedMetricStates.h>

#include <Framework/Mdib/Public/Model/Handle.h>

#include <type_traits>

namespace S31::SetService::Impl
{
/**
 * @brief Proposed states container shall not be empty.
 * @ingroup S31SetService
 */
class PayloadNotEmptyChecker
{
    public:
        template<class T_Data,
                typename std::enable_if<
                        std::is_same<T_Data,S31::SetService::ProposedAlertStates>{} ||
                        std::is_same<T_Data,S31::SetService::ProposedMetricStates>{} ||
                        std::is_same<T_Data,S31::SetService::ProposedComponentStates>{} ||
                        std::is_same<T_Data,S31::SetService::ProposedContextStates>{}, bool>::type = true>
        CheckerResult operator()(const T_Data& data)
        {
            if (data.empty())
            {
                return CheckerResult::failed(ClientError::PayloadMissing, "No states for set operation");
            }
            return CheckerResult::success();
        }

        // Explicitly list all payload types that do not require an empty check.
        template<class T_Data,
                typename std::enable_if<
                        std::is_same<T_Data,S31::SetService::Arguments>{} ||
                        std::is_same<T_Data,S31::SetService::ProposedAlertSystemState>{} ||
                        std::is_same<T_Data,S31::SetService::ProposedAlertSignalState>{} ||
                        std::is_same<T_Data,S31::SetService::ProposedAlertConditionState>{} ||
                        std::is_same<T_Data,S31::SetService::ProposedLimitAlertConditionState>{} ||
                        std::is_same<T_Data,DFL::Mdib::Decimal>{} ||
                        std::is_same<T_Data,DFL::Locale::Utf8>{}, bool>::type = true>
        CheckerResult operator()(const T_Data& /*data*/)
        {
            return CheckerResult::success();
        }
};

}
