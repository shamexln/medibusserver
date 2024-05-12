#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Kind specifies the relationship between the METRIC and referenced containment tree entries.
 * @details  Referenced containment tree entries are defined in \ref Relation::entries
 * @ingroup Mdib
 */
enum class Kind
{
    /// The metric is a recommendation for the containment tree entries defined in \ref Relation::entries
    Recommendation,
    /// This METRIC is a pre-setting for the containment tree entries defined in \ref Relation::entries.
    Presetting,
    /// The METRIC is part of a set of summary statistics for a sample where other METRICs that belong to the summary statistics are defined in \ref Relation::entries.
    SetOfSummaryStatistics,
    /// When changed, the metric has an effect on the containment tree entries defined in \ref Relation::entries If Kind is "EffectOnContainmentTreeEntries", \ref Relation::code should be set to classify the effect.
    EffectOnContainmentTreeEntries,
    /// The metric is derived from the containment tree entries defined in \ref Relation::entries. If Kind is "DerivedFromContainmentTreeEntries",
    DerivedFromContainmentTreeEntries,
    /// Relation is specified by other means, e.g., \ref Relation::code or extension element.
    Other
};
DFL_ENUM_CLASS_STREAM_OPERATOR(Kind, (Recommendation)(Presetting)(SetOfSummaryStatistics)(EffectOnContainmentTreeEntries)(DerivedFromContainmentTreeEntries)(Other))

} /* namespace Mdib */
} /* namespace DFL */
