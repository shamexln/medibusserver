#pragma once

#include <Framework/Mdib/Private/ExpImp.h>

#include <Framework/Mdib/Public/MdibSmartPtrTypes.h>
#include <Framework/Utils/Public/NotNull.h>

namespace DFL::Mdib
{
/**
 * @brief Read-only interface for an MDIB instance.
 * @details
 * If an interface with observer functionality is required use the
 * @ref DFL::Mdib::MdibAccess interface instead.
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP LatestMdib
{
public:
    virtual ~LatestMdib() = default;

    /**
     * @brief Provides the latest version of the MDIB for read only access.
     * @details Whenever you retrieve an MDIB, hold the returned pointer as
     * short as possible to avoid increasing memory footprints.
     * @return The latest MDIB.
     */
    virtual NotNull<MdibSharedPtr> latestMdib() const = 0;
};
}
