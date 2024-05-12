#pragma once

#include <S31/Sdc/Public/Common/MaxResultCount.h>
#include <S31/Utils/Public/UniquePtrVector.h>

#include <Framework/Chrono/Public/Duration.h>

#include <memory>
#include <vector>

namespace S31::Sdc::Impl
{

class IncomingHttpRequest;

using IncomingHttpRequestPtrs = Utils::UniquePtrVector<IncomingHttpRequest>;

/**
 * @brief Interface to hide the implementation of \c select() call for testing purposes.
 * @ingroup S31SdcCommonSocket
 */
class ISocketSelect
{
    public:
        virtual ~ISocketSelect() = default;

        /**
         * @brief Aborts the current @c select() call to return before requested timeout.
         */
        virtual void abortAcceptSockets() = 0;

        /**
         * @brief Wait on all sockets (including TCP sockets) for incoming data.
         * @returns If one or multiple sockets had data then for a subset of these jobs are created and returned.
         */
        virtual IncomingHttpRequestPtrs acceptSocketsWithHttp(DFL::Chrono::Milliseconds timeout, MaxResultCount maxResultCount) = 0;

        /**
         * @brief Only wait on sockets that do not create blocking @ref IncomingHttpRequest jobs.
         */
        virtual void acceptSocketsWithoutHttp(DFL::Chrono::Milliseconds timeout) = 0;

};

}
