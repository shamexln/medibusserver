#pragma once

#include <S31/Safety/Public/Information.h>
#include <S31/SetService/Private/Client/CheckerResult.h>

#include <Framework/Format/Public/Stream.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Operation/AllowedStringValue.h>
#include <Framework/Utils/Public/Utf8.h>

#include <type_traits>

namespace S31::SetService::Impl
{
/**
 * @brief Checks string payload for SetString operation regarding max length and allowed values.
 * @ingroup S31SetService
 */
class StringChecker
{
    public:

        /**
         * @brief UTF-8 payload in SetString might have max length and list of allowed values.
         */
        template<class T_OperationEntity>
        CheckerResult operator()(const T_OperationEntity& operationEntity,
                                 const DFL::Locale::Utf8& requestedStringValue)
        {
            if (auto maxLength = operationEntity.descriptor()->maxLength())
            {
                if (requestedStringValue.value().length() > *maxLength)
                {
                    DFL::Format::Stream msg;
                    msg << "string value >" << requestedStringValue.value()
                        << "< with length " << requestedStringValue.value().length()
                        << " is greater then MaxLength " << *maxLength;
                    return CheckerResult::failed(ClientError::InvalidLength, msg.cStr());
                }
            }

            const auto& allowedValues = operationEntity.state()->allowedValues();
            if (!allowedValues.empty())
            {
                if (std::find(allowedValues.begin(), allowedValues.end(), DFL::Mdib::AllowedStringValue(requestedStringValue)) == allowedValues.end())
                {
                    DFL::Format::Stream msg;
                    msg << "string value >" << requestedStringValue.value()
                        << "< is not in list of allowed values: " << allowedValues;
                    return CheckerResult::failed(ClientError::NotInAllowedValues, msg.cStr());
                }
            }
            return CheckerResult::success();
        }

        /**
         * @brief Default implementation allows everything.
         */
        template<class T_OperationEntity, class T_Data,
                typename std::enable_if<!std::is_same<T_Data,DFL::Locale::Utf8>{}, bool>::type = true>
        CheckerResult operator()(const T_OperationEntity& /*operationEntity*/,
                                 const T_Data& /*data*/)
        {
            return CheckerResult::success();
        }

};

}
