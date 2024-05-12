#pragma once

#include <Framework/Mdib/Private/ExpImp.h>

namespace DFL
{
namespace Mdib
{
namespace Ext
{
/**
 * @brief Indicate that the waveform data in the element is normalized in some
 * way.
 *
 * @details
 * This extension is intended to be attached to pm:RealTimeSampleArrayDescriptor
 * elements. It indicates that the waveform data in the element is normalized in
 * some way.
 *
 * @note An SDC SERVICE PROVIDER shall set \@ext:MustUnderstand = "true".
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP NormalizedWaveform
{
public:
    /**
     * @brief Specify whether the waveform is normalized.
     */
    explicit NormalizedWaveform(bool normalized);

    /**
     * @brief Signaling normalization state.
     * @return \c true signals that the data in a pm:RealTimeSampleArrayState
     * has been normalized.
     */
    bool isNormalized() const noexcept;
private:
    bool m_normalized{false};
};

/**
 * @brief Checks for equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator==(const NormalizedWaveform& lhs,
                                const NormalizedWaveform& rhs) noexcept;

/**
 * @brief Checks for non-equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator!=(const NormalizedWaveform& lhs,
                                const NormalizedWaveform& rhs) noexcept;

}
}
}
