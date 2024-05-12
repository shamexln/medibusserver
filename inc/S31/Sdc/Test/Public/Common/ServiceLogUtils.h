#pragma once

#include <S31/Sdc/Test/Public/Common/LogMessageInvocation.h>

#include <Framework/Log/Public/Logger.h>
#include <Framework/Log/Public/Registry.h>

namespace S31::Sdc::Test
{
/**
 * @brief Helper function to create and use \ref DFL::Log::Registry.
 * @ingroup S31SdcCommon
 */
class ServiceLogUtils
{
    public:
        static inline DFL::Log::Logger& prepareServiceLoggerWithoutFilter();

        template <typename Matcher_T>
        static inline DFL::Log::Logger& prepareServiceLogger(
                unsigned int remosCode,
                Matcher_T matcher,
                const LogMessageInvocationPtr& serviceHookInvoker);

        template <typename Matcher_T>
        static inline void addToServiceLogger(DFL::Log::Logger& serviceLogger,
                const LogMessageInvocationPtr& serviceHookInvoker,
                unsigned int remosCode,
                Matcher_T matcher);
};

inline DFL::Log::Logger& ServiceLogUtils::prepareServiceLoggerWithoutFilter()
{
    DFL::Log::Registry::init();
    auto& servicelogger = DFL::Log::Registry::service();
    servicelogger.clear();
    return servicelogger;
}

template <typename Matcher_T>
inline void ServiceLogUtils::addToServiceLogger(DFL::Log::Logger& serviceLogger,
        const LogMessageInvocationPtr& serviceHookInvoker,
        unsigned int remosCode,
        Matcher_T matcher)
{
    // put the matcher on the heap + type erasure
    std::shared_ptr<TextMatcher> pMatcher = std::make_shared<Matcher_T>(std::move(matcher.pattern()));

    std::weak_ptr<LogMessageInvocation> weakServiceHookInvoker = serviceHookInvoker;
    // This is not thread safe in DFL!
    serviceLogger.pushBack([remosCode, pMatcher, weakServiceHookInvoker](DFL::Log::Message const& msg)
                           {
                               if (auto invoker = weakServiceHookInvoker.lock())
                               {
                                   if (msg.eventCode().value() == remosCode)
                                   {
                                       const std::string messageTxt(msg.text().cStr());
                                       invoker->setInvocationStatusIfMessageMatches(messageTxt, *pMatcher);
                                   }
                               }
                               return msg;
                           });
}

template <typename Matcher_T>
inline DFL::Log::Logger& ServiceLogUtils::prepareServiceLogger(unsigned int remosCode,
        Matcher_T matcher,
        const LogMessageInvocationPtr& serviceHookInvoker)
{
    auto& servicelogger = prepareServiceLoggerWithoutFilter();
    addToServiceLogger(
            servicelogger,
            serviceHookInvoker,
            remosCode,
            std::move(matcher));

    return servicelogger;
}

}
