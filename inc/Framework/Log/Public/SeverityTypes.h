#pragma once

#include <Framework/Log/Private/ExpImp.h>
#include <Framework/Log/Public/Severity.h>

/**
 * @ingroup Log
 * @{
 *
 * @file
 * @brief Holds the type definitions of all severities.
 */
namespace DFL
{
namespace Log
{

/**
 * @brief Type which represents the severity trace.
 */
class DFL_LOG_EXPIMP TraceType: public Severity
{
public:
    /**
     * @brief Constructs an instance which represents the severity trace.
     */
    TraceType();
};

/**
 * @brief Constructs a Severity from TraceType
 */
DFL_LOG_EXPIMP Severity trace();

/**
 * @brief Type which represents the severity success.
 */
class DFL_LOG_EXPIMP SuccessType: public Severity
{
public:
    /**
     * @brief Constructs an instance which represents the severity success.
     */
    SuccessType();
};
/**
 * @brief Constructs a Severity from SuccessType
 */
DFL_LOG_EXPIMP Severity success();

/**
 * @brief Type which represents the severity info.
 */
class DFL_LOG_EXPIMP InfoType: public Severity
{
public:
    /**
     * @brief Constructs an instance which represents the severity info.
     */
    InfoType();
};
/**
 * @brief Constructs a Severity from InfoType
 */
DFL_LOG_EXPIMP Severity info();


/**
 * @brief Type which represents the severity warning.
 */
class DFL_LOG_EXPIMP WarningType: public Severity
{
public:
    /**
     * @brief Constructs an instance which represents the severity warning.
     */
    WarningType();
};
/**
 * @brief Constructs a Severity from WarningType
 */
DFL_LOG_EXPIMP Severity warning();

/**
 * @brief Type which represents the severity error.
 */
class DFL_LOG_EXPIMP ErrorType: public Severity
{
public:
    /**
     * @brief Constructs an instance which represents the severity error.
     */
    ErrorType();
};
/**
 * @brief Constructs a Severity from ErrorType
 */
DFL_LOG_EXPIMP Severity error();

}
}
/** @} */
