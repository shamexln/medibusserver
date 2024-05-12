#pragma once

#include <Framework/Utils/Public/NotNull.h>

#include <chrono>
#include <functional>
#include <memory>

namespace S31::Sdc
{

/**
 * @brief Notification object for LocalizedText request (in localization service)
 * @details Note that this is only about end of fetching. A possible error will be handled through the error handling.
 * @ingroup S31SdcClient
 */
class LocalizationClientRequestComplete
{
    public:
        virtual ~LocalizationClientRequestComplete() = default;

        using NotifyFunction = std::function<void()>;

        /// Use for synchronous wait
        /// @returns false if completion was not in given time
        virtual bool waitForCompletion(const std::chrono::milliseconds& maxWaitTime) = 0;

        /// @brief Use for asynchronous wait for completion.
        /// @details Is invoked immediately if no real request is needed (e.g. all text in cache already).
        virtual void registerCallback(const NotifyFunction& callback) = 0;
};

/**
 * @brief Nullable shared LocalizationClientRequestComplete.
 * @ingroup S31SdcClient
 */
using LocalizationClientRequestCompletePtrNullable = std::shared_ptr<LocalizationClientRequestComplete>;

/**
 * @brief Not null shared LocalizationClientRequestComplete.
 * @ingroup S31SdcClient
 */
using LocalizationClientRequestCompletePtr = DFL::NotNull<LocalizationClientRequestCompletePtrNullable>;

}
