#pragma once

#include <S31/Sdc/Private/Device/DsoapDevice/ILocalEventing.h>

#include <Framework/Mdib/Public/Model/MdibVersion.h>

#include <memory>
#include <utility>

namespace S31::Sdc::Impl
{

class ComponentReportDeliveryTracker
{
    public:
        ComponentReportDeliveryTracker(std::weak_ptr<ILocalEventing> eventing, DFL::Mdib::MdibVersion version);

        ~ComponentReportDeliveryTracker() noexcept;

    private:
        std::weak_ptr<ILocalEventing> m_eventing;
        DFL::Mdib::MdibVersion        m_mdibVersion;
};

inline ComponentReportDeliveryTracker::ComponentReportDeliveryTracker(
        std::weak_ptr<ILocalEventing> localEventing, DFL::Mdib::MdibVersion version)
    : m_eventing(std::move(localEventing))
    , m_mdibVersion(std::move(version))
{
    if (auto eventing = m_eventing.lock())
    {
        eventing->componentReportDeliveryStarting(m_mdibVersion);
    }
}

inline ComponentReportDeliveryTracker::~ComponentReportDeliveryTracker() noexcept
{
    if (auto eventing = m_eventing.lock())
    {
        eventing->componentReportDeliveryCompleted(m_mdibVersion);
    }
}
}  // namespace S31::Sdc::Impl
