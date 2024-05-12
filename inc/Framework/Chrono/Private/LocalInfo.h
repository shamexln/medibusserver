#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Public/SystemInfo.h>

namespace DFL
{
namespace Chrono
{
namespace Impl
{
/**
 * @brief Conversions from local time to system time will use this structure implicitly.
 *
 * When a local time to system time conversion is @c unique, @c result == @c unique,
 * @c first will be filled out with the correct @c SystemInfo
 * and @c second will be zero-initialized.
 * If the conversion stems from a @c nonexistent local time then @c result == @c nonexistent,
 * @c first will be filled out with the @c SystemInfo that ends just prior to the local time
 * and @c second will be filled out with the @c SystemInfo that begins just after the local time.
 * If the conversion stems from an @c ambiguous local time then @c result == @c ambiguous,
 * @c first will be filled out with the @c SystemInfo that ends just after the local time
 * and @c second will be filled out with the @c SystemInfo that starts just before the local time.
 *
 * @ingroup Chrono
 */
struct DFL_CHRONO_EXPIMP LocalInfo
{
    enum {Unique, Nonexistent, Ambiguous} result{};
    SystemInfo first{};
    SystemInfo second{};
};
}
}
}
