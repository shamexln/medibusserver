#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Context/AbstractContextState.h>
#include <Framework/Mdib/Public/Model/Context/ContextAssociation.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>

namespace DFL::Mdib
{

/**
 * @brief Static part of an \ref EnsembleContext.
 * @ingroup Mdib
 */
class EnsembleContextState: public AbstractContextState
{
    DFL_MDIB_IMMUTABLE(EnsembleContextState)

    public:
        /**
         * @brief Applies defaults from \ref AbstractContextState.
         */
        EnsembleContextState();

        /**
         * @brief Full constructor.
         */
        EnsembleContextState(const boost::optional<CodedValue>& category,
                             ContextAssociation contextAssociation,
                             const boost::optional<VersionCounter>& bindingMdibVersion,
                             const boost::optional<VersionCounter>& unbindingMdibVersion,
                             const boost::optional<Timestamp>& bindingStartTime,
                             const boost::optional<Timestamp>& bindingEndTime,
                             const InstanceIdentifiers& validators,
                             const InstanceIdentifiers& identifications,
                             ExtensionTypes extensions = ExtensionTypes{ });
};

inline EnsembleContextState::EnsembleContextState() :
        AbstractContextState()
{
}

inline EnsembleContextState::EnsembleContextState(const boost::optional<CodedValue>& category,
                                                  ContextAssociation contextAssociation,
                                                  const boost::optional<VersionCounter>& bindingMdibVersion,
                                                  const boost::optional<VersionCounter>& unbindingMdibVersion,
                                                  const boost::optional<Timestamp>& bindingStartTime,
                                                  const boost::optional<Timestamp>& bindingEndTime,
                                                  const InstanceIdentifiers& validators,
                                                  const InstanceIdentifiers& identifications,
                                                  ExtensionTypes extensions) :
        AbstractContextState(category,
                             contextAssociation,
                             bindingMdibVersion,
                             unbindingMdibVersion,
                             bindingStartTime,
                             bindingEndTime,
                             validators,
                             identifications,
                             std::move(extensions))
{
}

/**
 * @brief Definition of shared pointer type \ref EnsembleContextStateSharedPtr for state \ref EnsembleContextState.
 * @ingroup Mdib
 */
using EnsembleContextStateSharedPtr = SharedPtr<EnsembleContextState>;


} /* namespace DFL */
