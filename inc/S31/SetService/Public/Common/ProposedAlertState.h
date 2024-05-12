#pragma once

#include <Framework/Mdib/Public/Model/Alert/AlertCondition.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignal.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystem.h>
#include <Framework/Mdib/Public/Model/Alert/LimitAlertCondition.h>
#include <Framework/Mdib/Public/Model/Handle.h>

namespace S31::SetService
{

/**
 * @brief Alias for payload container used for set alert state operations.
 * @ingroup S31SetService
 */
template<class T_State>
using SetAlertStatePayload = std::pair<DFL::Mdib::Handle, T_State>;

/**
 * @brief Alias for payloads of \ref DFL::Mdib::SetAlertStateOperation "set alert system state operations".
 * @details Takes a pair of \ref DFL::Mdib::Handle "alert system handle" and \ref DFL::Mdib::AlertSystemState "alert system state".
 * @ingroup S31SetService
 */
using ProposedAlertSystemState = SetAlertStatePayload<DFL::Mdib::AlertSystemState>;

/**
 * @brief Alias for payloads of \ref DFL::Mdib::SetAlertStateOperation "set alert condition state operations".
 * @details Takes a pair of \ref DFL::Mdib::Handle "alert condition handle" and \ref DFL::Mdib::AlertConditionState "alert condition state".
 * @ingroup S31SetService
 */
using ProposedAlertConditionState = SetAlertStatePayload<DFL::Mdib::AlertConditionState>;

/**
 * @brief Alias for payloads of \ref DFL::Mdib::SetAlertStateOperation "set alert condition state operations".
 * @details Takes a pair of \ref DFL::Mdib::Handle "limit alert condition handle" and
 *          \ref DFL::Mdib::LimitAlertConditionState " limit alert condition state".
 * @ingroup S31SetService
 */
using ProposedLimitAlertConditionState = SetAlertStatePayload<DFL::Mdib::LimitAlertConditionState>;

/**
 * @brief Alias for payloads of \ref DFL::Mdib::SetAlertStateOperation "set alert signal state operations".
 * @details Takes a pair of \ref DFL::Mdib::Handle "alert signal handle" and \ref DFL::Mdib::AlertSignalState "alert signal state".
 * @ingroup S31SetService
 */
using ProposedAlertSignalState = SetAlertStatePayload<DFL::Mdib::AlertSignalState>;

}
