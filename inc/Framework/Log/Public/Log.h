#pragma once

#include <Framework/Log/Private/LogImpl.h>
#include <Framework/Log/Public/Registry.h>
#include <Framework/Log/Public/SecurityState.h>

/**
 * @ingroup Log
 * @{
 *
 * @file
 * @brief Defines macros for logging a text with a specific logger.
 *
 */

/**
 * @brief Passes text to a message with severity, componentkey and eventcode
 * which is processed by the given logger.
 */
#define DFL_LOG_WITH(logger, severity, msg, compKey, eventCode, assemblyId)    \
    DFL_LOG_IMPL_WITH(logger,                                                  \
                      severity,                                                \
                      msg,                                                     \
                      compKey,                                                 \
                      eventCode,                                               \
                      assemblyId,                                              \
                      ::DFL::Log::SecurityState::None)

/**
 * @brief Passes text to a message with severity, componentkey, eventcode
 * and security state which is processed by the given logger
 */
#define DFL_LOG_WITH_SS(logger,                                                \
                        severity,                                              \
                        msg,                                                   \
                        compKey,                                               \
                        eventCode,                                             \
                        assemblyId,                                            \
                        securityState)                                         \
    DFL_LOG_IMPL_WITH(logger,                                                  \
                      severity,                                                \
                      msg,                                                     \
                      compKey,                                                 \
                      eventCode,                                               \
                      assemblyId,                                              \
                      securityState)

/**
 * @brief Passes text to a message with severity, componentkey and eventcode
 * which is processed by the debug logger.
 */
#define DFL_LOG_DEBUG(severity, msg, compKey, eventCode, assemblyId)           \
    DFL_LOG_WITH(DFL::Log::Registry::debug(),                                  \
                 severity,                                                     \
                 msg,                                                          \
                 compKey,                                                      \
                 eventCode,                                                    \
                 assemblyId)

/**
 * @brief Passes text to a message with severity, componentkey and eventcode
 * which is processed by the service logger.
 */
#define DFL_LOG_SERVICE(severity, msg, compKey, eventCode, assemblyId)         \
    DFL_LOG_WITH(DFL::Log::Registry::service(),                                \
                 severity,                                                     \
                 msg,                                                          \
                 compKey,                                                      \
                 eventCode,                                                    \
                 assemblyId)

/**
 * @brief Passes text to a message with severity, componentkey and eventcode
 * which is processed by the security logger as security event.
 */
#define DFL_LOG_SECURITY_EVENT(severity, msg, compKey, eventCode, assemblyId)  \
    DFL_LOG_WITH_SS(DFL::Log::Registry::security(),                            \
                    severity,                                                  \
                    msg,                                                       \
                    compKey,                                                   \
                    eventCode,                                                 \
                    assemblyId,                                                \
                    ::DFL::Log::SecurityState::Event)

/**
 * @brief Passes text to a message with severity, componentkey and eventcode
 * which is processed by the security logger as security trap.
 */
#define DFL_LOG_SECURITY_TRAP(severity, msg, compKey, eventCode, assemblyId)   \
    DFL_LOG_WITH_SS(DFL::Log::Registry::security(),                            \
                    severity,                                                  \
                    msg,                                                       \
                    compKey,                                                   \
                    eventCode,                                                 \
                    assemblyId,                                                \
                    ::DFL::Log::SecurityState::Trap)

/** @} */
