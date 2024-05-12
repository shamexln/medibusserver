#pragma once

#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Public/Model/BodySite.h>
#include <Framework/Mdib/Public/Model/Component/PhysicalConnectorInfo.h>
#include <Framework/Mdib/Public/Model/ComponentActivation.h>
#include <Framework/Mdib/Public/Model/Duration.h>
#include <Framework/Mdib/Private/HasExtensions.h>

#include <boost/optional/optional.hpp>

namespace DFL
{
namespace Mdib
{

/**
 * @brief An abstract state for a metric.
 * @ingroup Mdib
 */
class AbstractMetricState: public Impl::HasExtensions
{
    DFL_MDIB_IMMUTABLE(AbstractMetricState)

    public:
        /**
         * @brief The activation state of a metric.
         */
        ComponentActivation activationState() const;

        /**
         * @brief Optional information about the currently active determination repetition time.
         * @details This value only applies if it is different from the default determination period that is defined in the descriptive part (see \ref AbstractMetricDescriptor::determinationPeriod).
         *
         * @return Determination period duration or \c boost::none if undefined.
         */
        const boost::optional<Duration>& activeDeterminationPeriod() const;

        /**
         * @brief Optional currently active life-time period that supersedes \ref AbstractMetricDescriptor::lifeTimePeriod.
         * @return Life-time period duration or \c boost::none if undefined.
         */
        const boost::optional<Duration>& lifeTimePeriod() const;

        /**
         * @brief Optional list of coded values that describe the body sites where the metric is derived from or where it is applied to.
         */
        const BodySites& bodySites() const;

        /**
         * @brief The physical connector info for this metric, see \ref PhysicalConnectorInfo.
         */
        const boost::optional<PhysicalConnectorInfo>& physicalConnector() const;

    protected:
        /**
         * @brief Default constructor.
         * @details Defaults
         *
         * - \ref AbstractMetricState::activationState() "Activation state" to \ref ComponentActivation::On "on"
         * - \ref AbstractMetricState::activeDeterminationPeriod() "Active determination period" to none
         * - \ref AbstractMetricState::lifeTimePeriod() "Life time period" to none
         * - \ref AbstractMetricState::bodySites() "Body sites" to empty sequence
         * - \ref AbstractMetricState::physicalConnector() "Physical connector" to none
         * - \ref DFL::Mdib::Impl::HasExtensions::extensions() "Extensions" to empty sequence
         */
        AbstractMetricState() = default;

        /**
         * @brief Full constructor (without extensions).
         */
        template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
        AbstractMetricState(Arg1&& activationState,
                            Arg2&& activeDeterminationPeriod,
                            Arg3&& lifeTimePeriod,
                            Arg4&& bodySites,
                            Arg5&& physicalConnector);

        /**
         * @brief Full constructor (with extensions).
         */
        template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
        AbstractMetricState(Arg1&& activationState,
                            Arg2&& activeDeterminationPeriod,
                            Arg3&& lifeTimePeriod,
                            Arg4&& bodySites,
                            Arg5&& physicalConnector,
                            Arg6&& extensions);

        ~AbstractMetricState() = default;

    private:
        ComponentActivation m_activationState{ComponentActivation::On};
        boost::optional<Duration> m_activeDeterminationPeriod{};
        boost::optional<Duration> m_lifeTimePeriod{};
        BodySites m_bodySites{};
        boost::optional<PhysicalConnectorInfo> m_physicalConnector{};
};

template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
inline AbstractMetricState::AbstractMetricState(Arg1&& activationState,
                                                Arg2&& activeDeterminationPeriod,
                                                Arg3&& lifeTimePeriod,
                                                Arg4&& bodySites,
                                                Arg5&& physicalConnector) :
        m_activationState(std::forward<Arg1>(activationState)),
        m_activeDeterminationPeriod(std::forward<Arg2>(activeDeterminationPeriod)),
        m_lifeTimePeriod(std::forward<Arg3>(lifeTimePeriod)),
        m_bodySites(std::forward<Arg4>(bodySites)),
        m_physicalConnector(std::forward<Arg5>(physicalConnector))
{
}

template<class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
inline AbstractMetricState::AbstractMetricState(Arg1&& activationState,
                                                Arg2&& activeDeterminationPeriod,
                                                Arg3&& lifeTimePeriod,
                                                Arg4&& bodySites,
                                                Arg5&& physicalConnector,
                                                Arg6&& extensions) :
        Impl::HasExtensions(std::forward<Arg6>(extensions)),
        m_activationState(std::forward<Arg1>(activationState)),
        m_activeDeterminationPeriod(std::forward<Arg2>(activeDeterminationPeriod)),
        m_lifeTimePeriod(std::forward<Arg3>(lifeTimePeriod)),
        m_bodySites(std::forward<Arg4>(bodySites)),
        m_physicalConnector(std::forward<Arg5>(physicalConnector))
{
}

inline ComponentActivation AbstractMetricState::activationState() const
{
    return m_activationState;
}

inline const boost::optional<Duration>& AbstractMetricState::lifeTimePeriod() const
{
    return m_lifeTimePeriod;
}

inline const boost::optional<Duration>& AbstractMetricState::activeDeterminationPeriod() const
{
    return m_activeDeterminationPeriod;
}

inline const BodySites& AbstractMetricState::bodySites() const
{
    return m_bodySites;
}

inline const boost::optional<PhysicalConnectorInfo>& AbstractMetricState::physicalConnector() const
{
    return m_physicalConnector;
}

} /* namespace Mdib */
} /* namespace DFL */
