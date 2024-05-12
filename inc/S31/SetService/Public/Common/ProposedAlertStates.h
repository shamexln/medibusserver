#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Model/Alert/AlertCondition.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignal.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystem.h>
#include <Framework/Mdib/Public/Model/Alert/LimitAlertCondition.h>

#include <cstddef>
#include <map>

namespace S31::SetService
{

/**
 * @brief Container for Biceps SetAlertState operation.
 *
 * @details Handles are not strong typed. The information is not required for outgoing messages
 * and for incoming it is not available to the parser. A consumer (PI) can decide what to do
 * with the proposed states and check if they belong to a MDS or VMD.
 *
 * @ingroup S31SetService
 */
class S31_CORE_EXPIMP ProposedAlertStates
{
    public:
        using size_type = std::size_t;

        void insert(const DFL::Mdib::Handle& handle, const DFL::Mdib::AlertSystemState& state);
        void insert(const DFL::Mdib::Handle& handle, const DFL::Mdib::AlertConditionState& state);
        void insert(const DFL::Mdib::Handle& handle, const DFL::Mdib::LimitAlertConditionState& state);
        void insert(const DFL::Mdib::Handle& handle, const DFL::Mdib::AlertSignalState& state);

        /**
         * @brief Total number of states for all types.
         */
        size_type size() const noexcept;

        /**
         * @brief Check if there are no states at all for all types.
         */
        bool empty() const noexcept;

        const std::map<DFL::Mdib::Handle, DFL::Mdib::AlertSystemState>& alertSystems() const;
        const std::map<DFL::Mdib::Handle, DFL::Mdib::AlertConditionState>& alertConditions() const;
        const std::map<DFL::Mdib::Handle, DFL::Mdib::LimitAlertConditionState>& limitAlertConditions() const;
        const std::map<DFL::Mdib::Handle, DFL::Mdib::AlertSignalState>& alertSignals() const;

    private:
        std::map<DFL::Mdib::Handle, DFL::Mdib::AlertSystemState> m_alertSystems;
        std::map<DFL::Mdib::Handle, DFL::Mdib::AlertConditionState> m_alertConditions;
        std::map<DFL::Mdib::Handle, DFL::Mdib::LimitAlertConditionState> m_limitAlertConditions;
        std::map<DFL::Mdib::Handle, DFL::Mdib::AlertSignalState> m_alertSignals;
};

}
