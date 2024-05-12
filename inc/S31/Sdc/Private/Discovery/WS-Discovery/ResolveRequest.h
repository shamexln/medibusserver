#pragma once

#include <Framework/Chrono/Public/SteadyClock.h>

#include <memory>

namespace S31::Sdc::Impl
{

class IResolveMatchesCallback;

/**
 * Stores information about resolve requests that are required for handling the reply.
 *
 * \ingroup S31SdcWsDiscovery
 */
class ResolveRequest
{
    public:
        explicit ResolveRequest(std::weak_ptr<IResolveMatchesCallback> callback);
        [[nodiscard]] bool isOutdated() const;

        [[nodiscard]] std::weak_ptr<IResolveMatchesCallback> getCallback() const;

    private:
        std::weak_ptr<IResolveMatchesCallback> m_callback;
        DFL::Chrono::SteadyClock::TimePoint m_requestTime;
};

}
