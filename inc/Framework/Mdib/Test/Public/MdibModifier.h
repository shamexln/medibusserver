#pragma once

#include <Framework/Mdib/Test/Public/MdibWriter.h>

namespace DFL::Mdib::Test::MdibModifier
{

/**
 * @brief Adds an MDS to the MDIB.
 * @ingroup Mdib
 */
void addMds(LocalMdibAccess& mdib);

/**
 * @brief Modifies the first MDS for a component state change.
 * @ingroup Mdib
 */
void modifyMds(LocalMdibAccess& mdib);


// --------------- implementation ----------------------

inline void addMds(LocalMdibAccess& mdib)
{
    DFL::Mdib::MdibChangeSet changes;
    DFL::Mdib::Test::Helper::appendMds(changes);
    THROW_ON_MDIB_WRITE_FAIL(mdib.writeDescription(changes));
}

inline void modifyMds(LocalMdibAccess& mdib)
{
    auto mdsRange = mdib.latestMdib()->range<DFL::Mdib::Mds>();
    if (mdsRange.empty())
    {
        throw std::runtime_error{"No MDS in local MDIB to modify state"};
    }
    const auto mds = *(mdsRange.begin());
    DFL::Mdib::MdsStateBuilder state{mds->state()};
    auto cycles =
        state.operatingCycles().get_value_or(DFL::Mdib::OperatingCycles{0});
    cycles++;
    state.operatingCycles(cycles);
    DFL::Mdib::Test::MdibWriter::writeComponentState(mdib, mds, state);
}

}
