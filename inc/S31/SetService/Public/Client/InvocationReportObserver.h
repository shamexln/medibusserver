#pragma once

#include <S31/SetService/Public/Client/ClientInvocationReport.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::SetService
{

class InvocationReport;

/**
 * @brief Observer for incoming invocation reports.
 * @ingroup S31SetService
 */
class InvocationReportObserver
{
    public:
        virtual ~InvocationReportObserver() = default;

        /**
         * @brief Observer callback.
         * @param report Invocation information.
         */
        virtual void onInvocationReport(const ClientInvocationReport& report) = 0;
};

}
