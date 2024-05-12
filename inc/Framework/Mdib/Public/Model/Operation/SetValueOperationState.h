#pragma once

#include <boost/optional.hpp>
#include <utility>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Operation/AbstractOperationState.h>
#include <Framework/Mdib/Public/Model/Range.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Defines the volatile part of a \ref SetValueOperation.
 * @ingroup Mdib
 */
class SetValueOperationState: public AbstractOperationState
{
    DFL_MDIB_IMMUTABLE(SetValueOperationState)

    public:
        /**
         * @brief Default constructor that set the \ref SetValueOperationState::allowedRanges() "allowed ranges" to an empty sequence.
         *
         * \note Also applies defaults from \ref AbstractOperationState.
         */
        SetValueOperationState();

        /**
         * @brief Constructor.
         */
        SetValueOperationState(OperatingMode operatingMode,
                               Ranges allowedRanges,
                               ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief The currently allowed ranges that can be requested.
         * @details The given ranges need to be a (strict or non-strict) subset of the technical range of the referenced descriptor.
         * @return A list of allowed ranges that can be requested
         */
        const Ranges& allowedRanges() const;

    private:
        Ranges m_allowedRanges;
};

inline SetValueOperationState::SetValueOperationState():
        AbstractOperationState(),
        m_allowedRanges(Ranges())
{
}

inline SetValueOperationState::SetValueOperationState(OperatingMode operatingMode,
                                                      Ranges allowedRanges,
                                                      ExtensionTypes extensions) :
        AbstractOperationState(operatingMode, std::move(extensions)),
        m_allowedRanges(std::move(allowedRanges))
{
}

inline const Ranges& SetValueOperationState::allowedRanges() const
{
    return m_allowedRanges;
}

/**
 * @brief Definition of shared pointer type \ref SetValueOperationStateSharedPtr for state \ref SetValueOperationState.
 * @ingroup Mdib
 */
using SetValueOperationStateSharedPtr = SharedPtr<SetValueOperationState>;

} /* namespace Mdib */
} /* namespace DFL */
