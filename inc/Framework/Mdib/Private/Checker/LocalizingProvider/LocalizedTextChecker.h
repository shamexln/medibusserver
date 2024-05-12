#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

/**
 * @brief Checks @ref DFL::Mdib::LocalizedText objects.
 * @details This checker applies to the Localizing Provider role.
 *
 * It covers the following requirements:
 *
 * PTSR_24454
 * A Localizing SDC Provider shall not use ./@@Lang in any LocalizedText element in its MDIB.
 *
 * @ingroup Mdib
 */
namespace DFL::Mdib::Impl::PlugIn::LocalizingProvider
{

class LocalizedTextChecker : public Checker
{
public:
    CheckerResult check(MdibChangeType changeType,
                        const NotNull<MdibSharedPtr>& mdib,
                        const MdibTreeStore& mdibTreeStore,
                        const MdibChangeSet& changes) override;
};

}
