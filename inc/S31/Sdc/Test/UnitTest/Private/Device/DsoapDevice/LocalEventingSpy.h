#pragma once

#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Private/Device/DsoapDevice/ILocalEventing.h>
#include <S31/Sdc/Private/Device/IOutgoingMessage.h>

#include <Framework/Mdib/Public/Model/MdibVersionIo.h>

#include <optional>
#include <string>
#include <vector>

namespace S31::Sdc::Impl
{

class LocalEventingSpy: public ILocalEventing
{
    public:
        void setHasEventListenerReturnValueTo(bool hasEventListener)
        {
            m_hasEventListener = hasEventListener;
        }

        bool hasEventListenerForAction(std::string_view /*actionUri*/) const override
        {
            return m_hasEventListener;
        }

        bool hasEventListenerForAnyAction() const override
        {
            return m_hasEventListener;
        }

        void fireEvent(DFL::NotNull<std::unique_ptr<S31::Sdc::Impl::IOutgoingMessage>> event) override
        {
            S31_STREAM_INFO_LOGGER("Test", "Fire event ", event->messageDescription());
            DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::IOutgoingMessage>> sharedEvent(std::move(event));
            m_firedEvents.emplace_back(sharedEvent);
        }

        void setDiscoveryLocationScopes(const std::vector<std::string>& locations) override
        {
            m_discoveryLocationCalls++;
            m_updatedLocations = locations;
        }

        void setDiscoveryMdsInfoScopes(const std::vector<std::string>& types) override
        {
            m_discoveryTypeCalls++;
            m_updatedTypes = types;
        }

        void componentReportDeliveryStarting(const DFL::Mdib::MdibVersion& version) override
        {
            S31_STREAM_INFO_LOGGER("Test", "Starting MDIB version: ", version);
            m_startedReports.push_back(version);
        }

        void componentReportDeliveryCompleted(const DFL::Mdib::MdibVersion& version) noexcept override
        {
            try
            {
                S31_STREAM_INFO_LOGGER("Test", "Completed MDIB version: ", version);
                m_completedReports.push_back(version);
            }
            catch(...) {}
        }

        auto numEventsFired() const
        {
            return m_firedEvents.size();
        }

        auto numEventsFired(std::string_view action) const
        {
            auto hasAction = [&](const DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::IOutgoingMessage>>& event)
            {
                return event->soapAction() == action;
            };

            return std::count_if(m_firedEvents.begin(), m_firedEvents.end(), hasAction);
        }


        std::shared_ptr<S31::Sdc::Impl::IOutgoingMessage> lastFiredEvent() const
        {
            if (m_firedEvents.empty())
            {
                return {};
            }
            return m_firedEvents.back().get();
        }

        std::string firstFiredEventAction() const
        {
            if (m_firedEvents.empty())
            {
                return {};
            }
            return m_firedEvents.front()->soapAction();
        }

        std::shared_ptr<S31::Sdc::Impl::IOutgoingMessage> firedEventForAction(std::string_view action) const
        {
            for (const auto& firedEvent : m_firedEvents)
            {
                if (firedEvent->soapAction() == action)
                {
                    return firedEvent.get();
                }
            }
            return {};
        }

        const std::vector<std::string>& updatedLocations() const
        {
            return m_updatedLocations;
        }

        const std::vector<std::string>& updatedTypes() const
        {
            return m_updatedTypes;
        }

        int discoveryLocationCalls() const
        {
            return m_discoveryLocationCalls;
        }

        int discoveryTypeCalls() const
        {
            return m_discoveryTypeCalls;
        }

        void resetFiredEvents()
        {
            m_firedEvents.clear();
            m_updatedLocations.clear();
            m_updatedTypes.clear();
            m_discoveryLocationCalls = 0;
            m_discoveryTypeCalls = 0;
        }

        std::vector<std::string> reportActions() const
        {
            std::vector<std::string> actions;
            std::transform(std::cbegin(m_firedEvents), std::cend(m_firedEvents), std::back_inserter(actions),
                           [](const DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::IOutgoingMessage>>& p) { return p->soapAction(); });
            return actions;
        }

        const std::vector<DFL::Mdib::MdibVersion>& startedComponentReports() const
        {
            return m_startedReports;
        }

        const std::vector<DFL::Mdib::MdibVersion>& completedComponentReports() const
        {
            return m_completedReports;
        }

        void resetComponentReportTracking()
        {
            m_startedReports.clear();
            m_completedReports.clear();
        }
    private:
        bool m_hasEventListener = true;
        std::vector<DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::IOutgoingMessage>>> m_firedEvents;
        std::vector<std::string> m_updatedLocations;
        std::vector<std::string> m_updatedTypes;

        int m_discoveryLocationCalls = 0;
        int m_discoveryTypeCalls = 0;

        std::vector<DFL::Mdib::MdibVersion> m_startedReports;
        std::vector<DFL::Mdib::MdibVersion> m_completedReports;
};

}
