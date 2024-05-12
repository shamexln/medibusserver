#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Operation/AbstractOperationState.h>
#include <Framework/Mdib/Public/Model/Operation/AllowedStringValue.h>
#include <string>
#include <vector>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Defines the volatile part of a \ref SetStringOperation.
 * @ingroup Mdib
 */
class SetStringOperationState: public AbstractOperationState
{
    DFL_MDIB_IMMUTABLE(SetStringOperationState)

    public:
        /**
         * @brief Default constructor that set the \ref SetStringOperationState::allowedValues() "allowed values" to an empty sequence.
         *
         * \note Also applies defaults from \ref AbstractOperationState.
         */
        SetStringOperationState();

        /**
         * @brief Full constructor.
         */
        SetStringOperationState(OperatingMode operatingMode,
                                AllowedStringValues allowedValues,
                                ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief A list of currently allowed string values that can be requested.
         * @details If the list is empty, then there is not a limitation.
         */
        const AllowedStringValues& allowedValues() const;

    private:
        AllowedStringValues m_allowedValues;
};

inline SetStringOperationState::SetStringOperationState() :
        AbstractOperationState(),
        m_allowedValues(AllowedStringValues())
{
}

inline SetStringOperationState::SetStringOperationState(OperatingMode operatingMode,
                                                        AllowedStringValues allowedValues,
                                                        ExtensionTypes extensions) :
        AbstractOperationState(operatingMode, std::move(extensions)),
        m_allowedValues(std::move(allowedValues))
{
}

inline const AllowedStringValues& SetStringOperationState::allowedValues() const
{
    return m_allowedValues;
}

/**
 * @brief Definition of shared pointer type \ref SetStringOperationStateSharedPtr for state \ref SetStringOperationState.
 * @ingroup Mdib
 */
using SetStringOperationStateSharedPtr = SharedPtr<SetStringOperationState>;

} /* namespace Mdib */
} /* namespace DFL */
