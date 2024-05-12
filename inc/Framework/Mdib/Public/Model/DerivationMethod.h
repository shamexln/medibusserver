#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Provides an enumeration to designate if a metric is populated automatically or manually.
 * @ingroup Mdib
 */
enum class DerivationMethod
{
    /// The metric value is derived by an automatic mechanism (e.g., electronically measured).
    Automatic,
    /// The metric is derived manually by a manual mechanism.
    Manual
};
DFL_ENUM_CLASS_STREAM_OPERATOR(DerivationMethod, (Automatic)(Manual))

} /* namespace Mdib */
} /* namespace DFL */
