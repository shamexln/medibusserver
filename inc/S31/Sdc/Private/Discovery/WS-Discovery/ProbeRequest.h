#pragma once

#include <Framework/Chrono/Public/SteadyClock.h>

#include <memory>

namespace S31::Sdc::Impl
{

class IProbeMatchesCallback;

/**
 * Stores information about probe requests that are required for handling the reply.
 *
 * \ingroup S31SdcWsDiscovery
 */
class ProbeRequest
{
    public:
        explicit ProbeRequest(const std::shared_ptr<IProbeMatchesCallback>& callback);

        bool isOutdated() const;

        std::shared_ptr<IProbeMatchesCallback> getCallback() const;

    private:
        std::weak_ptr<IProbeMatchesCallback> m_callback;
        DFL::Chrono::SteadyClock::TimePoint m_requestTime;
};

}
