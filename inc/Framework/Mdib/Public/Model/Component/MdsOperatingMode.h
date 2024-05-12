#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief The operating mode of an \ref DFL::Mdib::Mds "MDS" that indicates the interpretation constraints
 * of the data that are provided by an %MDS and its components.
 *
 * @ingroup Mdib
 */
enum class MdsOperatingMode
{
    /// The device operates in a mode that supports the fulfillment of its clinical intended use.
    Normal,
    /// The device operates in a mode that is intended for demonstration purposes only. Arbitrary values are generated.
    Demo,
    /// The device operates in a mode that is intended for services purposes only.
    Service,
    /// The device operates in a mode that is intended for maintenance purposes only.
    Maintenance
};
DFL_ENUM_CLASS_STREAM_OPERATOR(MdsOperatingMode, (Normal)(Demo)(Service)(Maintenance))

} /* namespace Mdib */
} /* namespace DFL */
