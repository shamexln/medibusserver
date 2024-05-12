#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/Timestamp.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <cstdint>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
struct BicepsTimestampTag;
}

/**
 * @brief Timestamp in the range and resolution as defined in Biceps.
 * @details
 * From Biceps standard:
 * > An unsigned 64-bit integer value that represents a timestamp.
 * >
 * > R5001: A timestamp SHALL count the milliseconds between the current time
 * > and midnight, January 1, 1970 UTC without leap seconds.
 *
 * @ingroup Mdib
 */
using BicepsTimestamp = StrongTypedef<std::uint64_t,
                                      Impl::BicepsTimestampTag,
                                      Skill::TotallyOrdered,
                                      Skill::Streamable>;

namespace Convert
{
/**
 * @brief Converts system clock timestamp into Biceps timestamp.
 * @details
 * Due to the restriction of milliseconds resolution, the system clock timestamp
 * needs to be truncated. Keep that in mind when doing round trip tests.
 * Furthermore, value before 1970-01-01 will be set to the Biceps epoch
 * 1970-01-01 midnight to provide an existing value.
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP BicepsTimestamp toBicepsTimestamp(Timestamp) noexcept;

/**
 * @brief Converts Biceps timestamp into system clock timestamp.
 *
 * @details
 * Theoretically a Biceps timestamp might be far in the future with a value the
 * system clock does not cover. In such a case the value of the system clock
 * time point is set to the max allowed system clock time point.
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Timestamp fromBicepsTimestamp(BicepsTimestamp) noexcept;

}
}
}
