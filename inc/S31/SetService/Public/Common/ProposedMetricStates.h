#pragma once

#include <S31/S31CoreExImp.h>

#include <S31/SetService/Public/Common/ProposedStates.h>

#include <Framework/Mdib/Public/Model/Component/Sco.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Metric/DistributionSampleArrayMetric.h>
#include <Framework/Mdib/Public/Model/Metric/EnumStringMetric.h>
#include <Framework/Mdib/Public/Model/Metric/NumericMetric.h>
#include <Framework/Mdib/Public/Model/Metric/RealTimeSampleArrayMetric.h>
#include <Framework/Mdib/Public/Model/Metric/StringMetric.h>
#include <Framework/Mdib/Public/Utils/EntityLists.h>

#include <map>

namespace S31::SetService
{

/**
 * @brief Alias for the updated states of the type \ref DFL::Mdib::NumericMetric.
 * @details Takes \ref DFL::Mdib::NumericMetricHandle "numeric metric handle" as key and \ref DFL::Mdib::NumericMetricState "numeric metric state" as value.
 * @ingroup S31SetService
 */
using NumericMetricUpdates = StateUpdatesMap<DFL::Mdib::NumericMetric>;

/**
 * @brief Alias for the updated states of the type \ref DFL::Mdib::StringMetric.
 * @details Takes \ref DFL::Mdib::StringMetricHandle "string metric handle" as key and \ref DFL::Mdib::StringMetricState "string metric state" as value.
 * @ingroup S31SetService
 */
using StringMetricUpdates = StateUpdatesMap<DFL::Mdib::StringMetric>;

/**
 * @brief Alias for the updated states of the type \ref DFL::Mdib::EnumStringMetric.
 * @details Takes \ref DFL::Mdib::EnumStringMetricHandle "enum string metric handle" as key and \ref DFL::Mdib::EnumStringMetricState "enum string metric state" as value.
 * @ingroup S31SetService
 */
using EnumStringMetricUpdates = StateUpdatesMap<DFL::Mdib::EnumStringMetric>;

/**
 * @brief Alias for the updated states of the type \ref DFL::Mdib::RealTimeSampleArrayMetric.
 * @details Takes \ref DFL::Mdib::RealTimeSampleArrayMetricHandle "realtime sample array handle" as key and \ref DFL::Mdib::RealTimeSampleArrayMetricState "realtime sample array state" as value.
 * @ingroup S31SetService
 */
using RealTimeSampleArrayMetricUpdates = StateUpdatesMap<DFL::Mdib::RealTimeSampleArrayMetric>;

/**
 * @brief Alias for the updated states of the type \ref DFL::Mdib::DistributionSampleArrayMetric.
 * @details Takes \ref DFL::Mdib::DistributionSampleArrayMetricHandle "distribution sample array handle" as key and \ref DFL::Mdib::DistributionSampleArrayMetricState "distribution sample array state" as value.
 * @ingroup S31SetService
 */
using DistributionSampleArrayMetricUpdates = StateUpdatesMap<DFL::Mdib::DistributionSampleArrayMetric>;

/**
 * @brief This class provides a container for set metric state operations.
 * @details @ref DFL::Mdib::SetMetricStateOperation "Set metric state operations" allows setting of
 *          @ref DFL::Mdib::NumericMetricState "NumericMetricState",
 *          @ref DFL::Mdib::StringMetricState "StringMetricState",
 *          @ref DFL::Mdib::EnumStringMetricState "EnumStringMetricState",
 *          @ref DFL::Mdib::RealTimeSampleArrayMetricState "RealTimeSampleArrayMetricState",
 *          @ref DFL::Mdib::DistributionSampleArrayMetricState "DistributionSampleArrayMetricState"
 *           at the same time.
 * @ingroup S31SetService
 */
class S31_CORE_EXPIMP ProposedMetricStates
{
    public:
        using ProposedMetricUpdates = ProposedUpdates<DFL_MDIB_ENTITY_METRICS>;

        /**
         * @brief Set the map for updates of type T_Entity to map.
         * @param map holds proposed component state updates for type T_Entity.
         */
        template<class T_Map>
        void updates(T_Map&& map)
        {
            m_updates.states<T_Map>(std::forward<T_Map>(map));
        }

        /**
         * @return State updates for type T_Entity.
         */
        template<class T_Entity>
        const StateUpdatesMap<T_Entity>& updates() const
        {
            return m_updates.states<T_Entity>();
        }

        /**
         * @brief Check if the container is empty.
         * @return True if the container contains no state updates.
         */
        bool empty() const
        {
            return m_updates.empty();
        }

    private:
        ProposedMetricUpdates m_updates;
};

}
