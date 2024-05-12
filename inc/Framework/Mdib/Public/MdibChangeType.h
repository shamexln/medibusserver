#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Enum for type of MDIB changes.
 * @details It corresponds to the
 * - @ref DFL::Mdib::SubdividedMdibObserver, which has the corresponding callback functions, the
 * - @ref DFL::Mdib::LocalMdibAccess and
 * - @ref DFL::Mdib::RemoteMdibAccess, with their corresponding write operations.
 * @ingroup Mdib
 */
enum class MdibChangeType
{
        Description,       ///< Changed descriptors and states (any entity type is possible).
        AlertStates,       ///< Changed alert states.
        MetricStates,      ///< Changed metric states.
        ComponentStates,   ///< Changed component states.
        ContextStates,     ///< Changed context states.
        OperationStates,   ///< Changed operation states.
        WaveformStream     ///< Changed real time sample array states.
};

DFL_ENUM_CLASS_STREAM_OPERATOR(MdibChangeType, (Description)(AlertStates)(MetricStates)(ComponentStates)(ContextStates)(OperationStates)(WaveformStream))


}
}
