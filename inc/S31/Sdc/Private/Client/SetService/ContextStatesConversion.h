#pragma once

#include <Framework/Mdib/Public/MdibSmartPtrTypes.h>

namespace DFL
{
template <class T>
class NotNull;
}
namespace S31
{
namespace SetService
{
class ProposedContextStates;
}
namespace Sdc::Impl
{
class EnhancedProposedContextStates;

/**
 * @brief converts given @ref S31::SetService::ProposedContextStates "proposed context states" to @ref S31::Sdc::Impl::EnhancedProposedContextStates.
 * @details The update maps within the @ref S31::SetService::ProposedContextStates "proposed context states" container miss the context indicator handle.
 *          Instead, they only contain the state handles.
 *          This function retrieves the indicator handles from the mdib in order to augment the context updates maps with these handles.
 * @throws std::runtime_error in case the given mdib does not contain any of the handles in @ref S31::SetService::ProposedContextStates::updates
 * @param mdib from which the indicator handles are fetched.
 * @param states container with update and insertion maps used for @ref DFL::Mdib::SetContextStateOperation "set context state operations".
 * @return @ref S31::Sdc::Impl::EnhancedProposedContextStates "Enhanced proposed context states".
 */
EnhancedProposedContextStates convertContextPayload(const DFL::Mdib::Mdib& mdib,
                                                    const SetService::ProposedContextStates& states);


}
}
