#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/LocalDateTime.h>
#include <Framework/Chrono/Public/SystemInfo.h>
#include <Framework/Chrono/Public/UtcDateTime.h>
#include <Framework/Config/Public/Attributes.h>

namespace DFL
{
namespace Chrono
{
class TimeZone;
/**
 * @brief Provides access to hooks which can be used to redirect
 * - the timepoint source of a clock and
 * - the source of conversion methods.
 *
 * By default the hooks are assigned to functions which use the operating
 * system.
 *
 * @see Chrono/Test/Public/MockClock.h for examples on how to exchange the
 * timepoint source of a clock.
 *
 * @ingroup Chrono
 */
class DFL_CHRONO_EXPIMP Registry
{
public:
    /**
     * @brief Sets the hooks to default.
     *
     * By default the hooks are assigned to functions which use the operating
     * system.
     *
     * @snippet Chrono/Test/UnitTest/TestChronoRegistry.cpp RegistryInit
     */
    static void init();
    /**
     * @brief Sets the hooks to default.
     *
     * By default the hooks are assigned to functions which use the operating
     * system.
     *
     * @snippet Chrono/Test/UnitTest/TestChronoRegistry.cpp RegistryShutdown
     */
    static void shutdown();
    /**
     * @brief Contains hooks for redirecting the timepoint source of the
     * @ref DFL::Chrono::SystemClock.
     */
    class DFL_CHRONO_EXPIMP SystemClock
    {
    public:
        /**
         * @brief The type of the hook which determines the epoch of the system.
         */
        using TimeSinceEpoch = Microseconds (*)();
        /**
         * @brief Assigning a hook to this variable will redirect the call of
         * @ref DFL::Chrono::SystemClock::now.
         *
         * The function has to return the time which passed since the
         * 1st jan 1970 in microseconds since this is the epoch of this clock
         * After assignment any further calls to
         * @ref DFL::Chrono::SystemClock::now are passed to the assigned
         * function.
         */
        static TimeSinceEpoch timeSinceEpoch;
        /**
         * @brief The type of the hook which converts the duration since epoch
         * to a local date time.
         */
        using ToLocal = LocalDateTime (*)(const Microseconds&);
        /**
         * @brief Assigning a hook to this variable will redirect the call of
         * @ref DFL::Chrono::Convert::toLocalDateTime.
         *
         * The function has to convert the given time since epoch into a local
         * date time object. After assignment any further calls to
         * @ref DFL::Chrono::Convert::toLocalDateTime are passed to the assigned
         * function.
         */
        static ToLocal toLocal;
        /**
         * @brief The type of the hook which converts the duration since epoch
         * to a utc date time.
         * @deprecated this hook will be removed.
         */
        using ToUtc DFL_ATTRIBUTE_DEPRECATED("will be removed") =
            UtcDateTime (*)(const Microseconds&);
        /**
         * @brief Assigning a hook to this variable will redirect the call of
         * @ref DFL::Chrono::Convert::toUtcDateTime.
         * @deprecated this hook will be removed.
         * Conversion to utc can be done without any help since the epoch
         * is 1970-01-01.
         */
        DFL_ATTRIBUTE_DEPRECATED("will be removed")
        static ToUtc toUtc;
    };
    /**
     * @brief Contains hooks for redirecting the timepoint source of the
     * @ref DFL::Chrono::SteadyClock.
     */
    class DFL_CHRONO_EXPIMP SteadyClock
    {
    public:
        /**
         * @brief The type of the hook which determines the time since boot.
         */
        using TimeSinceEpoch = Microseconds (*)();
        /**
         * @brief Assigning a hook to this variable will redirect the call of
         * @ref DFL::Chrono::SteadyClock::now.
         *
         * The function has to return the time which passed since boot of the
         * system in microseconds since this is the epoch of this clock.
         * After assignment any further calls to
         * @ref DFL::Chrono::SteadyClock::now are passed to the assigned
         * function.
         */
        static TimeSinceEpoch timeSinceEpoch;
    };
    /**
     * @brief Setter/Getter for the devices current time zone.
     *
     * The setter should only be used by someone who knows what the current
     * time zone of the device shall be. The getter here is only available
     * for symetry reasons. Instead @ref DFL::Chrono::currentZone() shall be
     * used since it is more convenient.
     */
    class DFL_CHRONO_EXPIMP TimeZone
    {
    public:
        /**
         * @brief Do not use this getter, use @ref DFL::Chrono::currentZone()
         * instead.
         *
         * If a current time zone has never been set a time zone representing
         * the UTC time is returned.
         */
        static const ::DFL::Chrono::TimeZone& current();
        /**
         * @brief Sets the devices current time zone.
         *
         * The setter should only be used by someone who knows what the current
         * time zone of the device shall be.
         */
        static void current(const ::DFL::Chrono::TimeZone& newCurrentZone);
    };
    /**
     * @brief Contains hooks for redirecting the source of conversion methods.
     */
    class DFL_CHRONO_EXPIMP Convert
    {
    public:
        /**
         * @brief The type of the hook for making a current
         * @ref DFL::Chrono::SystemInfo object.
         */
        using MakeCurrentSystemInfo = SystemInfo (*)();
        /**
         * @brief Hook for making a current @ref DFL::Chrono::SystemInfo object.
         *
         * The returned @ref DFL::Chrono::SystemInfo object shall contain
         * the current offset between UTC and local time.
         */
        static MakeCurrentSystemInfo makeCurrentSystemInfo;
    };
};
}
}
