#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/CodedValue.h>

#include <Framework/Utils/Public/StrongTypedef.h>

#include <cstdint>

namespace DFL
{
namespace Mdib
{
namespace Ext
{
namespace Impl
{
struct SampleIndexTag {};
}

/**
 * @brief Index number that points to a sample in the past to which the annotation
 * is applied to retrospectively.
 * @details This index must be negative.  The value -1 indicates the last sample of
 * the previous waveform frame.
 * @ingroup Mdib
 */
using SampleIndex = DFL::StrongTypedef<std::int32_t, Impl::SampleIndexTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

/**
 * @brief Annotations to samples of previous waveform frames.
 * @details
 * RetrospectiveAnnotation allows for an SDC Service Provider to apply
 * annotations to samples of previous waveform frames.
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP RetrospectiveAnnotation
{
public:
    /**
     * @brief Constructor with all members.
     */
    RetrospectiveAnnotation(CodedValues annotations, SampleIndex sampleIndex);

    /**
     * @brief The annotation codes that are applied to a previous sample.
     */
    const CodedValues& annotations() const noexcept;

    /**
     * @brief Index number that points to a sample in the past.
     * @details
     * Index number that points to a sample in the past to which the annotations
     * in Annotation are to be applied to retrospectively. The referenced sample
     * can be calculated by the following formula: ReferencedSample =
     * OffsetSample + SampleIndex, where OffsetSample points to the first sample
     * in the \@Samples list of the pm:RealTimeSampleArrayMetricState element in
     * which the referenced annotation is included. ReferencedSample virtually
     * references a sample from the past, namely at the time T when the sample
     * was measured, with T =
     * pm:RealTimeSampleArrayMetricState/\@DeterminationTime - |SampleIndex| *
     * pm:RealTimeSampleArrayMetricDescriptor/\@SamplePeriod.
     */
    SampleIndex sampleIndex() const noexcept;

private:
    CodedValues m_annotations;
    SampleIndex m_sampleIndex;
};

/**
 * @brief Subsumes multiple RetrospectiveAnnotation elements.
 * @details RetrospectiveAnnotations is supposed to be attached to
 * pm:SampleArrayValue/pm:Extension.
 *
 * Example usage in code:
 * @snippet Mdib/Test/UnitTest/TestParticipantModelExtensions.cpp RetrospectiveAnnotationsUsage
 * @ingroup Mdib
 */
using RetrospectiveAnnotations = std::vector<RetrospectiveAnnotation>;

/**
 * @brief Checks for equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator==(const RetrospectiveAnnotation& lhs,
                                const RetrospectiveAnnotation& rhs) noexcept;

/**
 * @brief Checks for non-equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator!=(const RetrospectiveAnnotation& lhs,
                                const RetrospectiveAnnotation& rhs) noexcept;

}
}
}
