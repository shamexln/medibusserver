/**************************************************************************************
 *
 * DO NOT EDIT THIS FILE MANUALLY
 * THIS FILE IS GENERATED BY
 * modules\S32\Tools\MdibBuilders\RunGenerator.cmd
 *
 **************************************************************************************/

#pragma once

#include <memory>
#include <boost/optional.hpp>
#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Utils/Public/NotNull.h>

#include <Framework/Mdib/Public/Model/Operation/SetComponentStateOperationState.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Builder with fluent interface for @ref SetComponentStateOperationState
 * @ingroup Mdib
 */
class SetComponentStateOperationStateBuilder
{
    public:
        /// @brief Typedef to the immutable @ref SetComponentStateOperationState
        using BuiltType = SetComponentStateOperationState;

        /// @brief Builder based on given immutable @ref SetComponentStateOperationState
        explicit SetComponentStateOperationStateBuilder(const SetComponentStateOperationState& setComponentStateOperationState=SetComponentStateOperationState());

        /// @brief Builder based on given immutable @ref SetComponentStateOperationState
        explicit SetComponentStateOperationStateBuilder(const DFL::NotNull<SharedPtr<SetComponentStateOperationState>>& setComponentStateOperationState);

        /// @brief Overwrite all values with given immutable @ref SetComponentStateOperationState
        SetComponentStateOperationStateBuilder& operator=(const SetComponentStateOperationState& setComponentStateOperationState);

        /// @brief Explicit conversion to immutable @ref SetComponentStateOperationState
        SetComponentStateOperationState build() const;

        /// @brief Test whether the builder differs from the immutable @ref SetComponentStateOperationState
        bool isChanged(const SetComponentStateOperationState& base) const;

        /// @brief Setter for operatingMode
        /// @{
        SetComponentStateOperationStateBuilder& operatingMode(OperatingMode operatingMode);
        /// @}

        /// @brief Setter for extensions
        /// @{
        SetComponentStateOperationStateBuilder& extensions(const ExtensionTypes& extensions);
        SetComponentStateOperationStateBuilder& extensions(ExtensionTypes&& extensions);
        /// @}

        /// @brief Getter for operatingMode
        /// @{
        OperatingMode& operatingMode();
        OperatingMode operatingMode() const;
        /// @}

        /// @brief Getter for extensions
        /// @{
        ExtensionTypes& extensions();
        const ExtensionTypes& extensions() const;
        /// @}

    private:
        OperatingMode m_operatingMode;
        ExtensionTypes m_extensions;
};

/**
 * @brief Equal operator compares all members
 * @ingroup Mdib
 */
/// @{
DFL_MDIB_EXPIMP bool operator==(const SetComponentStateOperationState& lhs, const SetComponentStateOperationState& rhs);
DFL_MDIB_EXPIMP bool operator==(const SetComponentStateOperationStateBuilder& lhs, const SetComponentStateOperationStateBuilder& rhs);
DFL_MDIB_EXPIMP bool operator==(const SetComponentStateOperationStateBuilder& lhs, const SetComponentStateOperationState& rhs);
bool operator==(const SetComponentStateOperationState& lhs, const SetComponentStateOperationStateBuilder& rhs);
/// @}

/**
 * @brief Not equal operator compares all members
 * @ingroup Mdib
 */
/// @{
DFL_MDIB_EXPIMP bool operator!=(const SetComponentStateOperationState& lhs, const SetComponentStateOperationState& rhs);
bool operator!=(const SetComponentStateOperationStateBuilder& lhs, const SetComponentStateOperationStateBuilder& rhs);
bool operator!=(const SetComponentStateOperationState& lhs, const SetComponentStateOperationStateBuilder& rhs);
bool operator!=(const SetComponentStateOperationStateBuilder& lhs, const SetComponentStateOperationState& rhs);
/// @}

/**
 * @brief Factory function to create %Builder based on given immutable @ref SetComponentStateOperationState
 * @ingroup Mdib
 */
/// @{
SetComponentStateOperationStateBuilder getBuilder(const SetComponentStateOperationState& setComponentStateOperationState);
SetComponentStateOperationStateBuilder getBuilder(const DFL::NotNull<SharedPtr<SetComponentStateOperationState>>& setComponentStateOperationState);
/// @}

/**
 * @brief Helper function throws runtime_error in case of a not equal member
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP void assertEqual(const SetComponentStateOperationState& lhs, const SetComponentStateOperationState& rhs);

inline SetComponentStateOperationStateBuilder::SetComponentStateOperationStateBuilder(const SetComponentStateOperationState& setComponentStateOperationState) :
    m_operatingMode(setComponentStateOperationState.operatingMode()),
    m_extensions(setComponentStateOperationState.extensions())
{
}

inline SetComponentStateOperationStateBuilder::SetComponentStateOperationStateBuilder(const DFL::NotNull<SharedPtr<SetComponentStateOperationState>>& setComponentStateOperationState) :
    m_operatingMode(setComponentStateOperationState->operatingMode()),
    m_extensions(setComponentStateOperationState->extensions())
{
}

inline SetComponentStateOperationStateBuilder& SetComponentStateOperationStateBuilder::operator=(const SetComponentStateOperationState& setComponentStateOperationState)
{
    m_operatingMode = setComponentStateOperationState.operatingMode();
    m_extensions = setComponentStateOperationState.extensions();
    return *this;
}

inline SetComponentStateOperationState SetComponentStateOperationStateBuilder::build() const
{
    // NOLINTNEXTLINE(modernize-return-braced-init-list)
    return SetComponentStateOperationState(m_operatingMode, m_extensions);
}

inline bool SetComponentStateOperationStateBuilder::isChanged(const SetComponentStateOperationState& base) const
{
    return *this != base;
}

inline SetComponentStateOperationStateBuilder& SetComponentStateOperationStateBuilder::operatingMode(OperatingMode operatingMode)
{
    m_operatingMode = operatingMode;
    return *this;
}

inline OperatingMode& SetComponentStateOperationStateBuilder::operatingMode()
{
    return m_operatingMode;
}

inline OperatingMode SetComponentStateOperationStateBuilder::operatingMode() const
{
    return m_operatingMode;
}

inline SetComponentStateOperationStateBuilder& SetComponentStateOperationStateBuilder::extensions(const ExtensionTypes& extensions)
{
    m_extensions = extensions;
    return *this;
}

inline SetComponentStateOperationStateBuilder& SetComponentStateOperationStateBuilder::extensions(ExtensionTypes&& extensions)
{
    m_extensions = std::move(extensions);
    return *this;
}

inline ExtensionTypes& SetComponentStateOperationStateBuilder::extensions()
{
    return m_extensions;
}

inline const ExtensionTypes& SetComponentStateOperationStateBuilder::extensions() const
{
    return m_extensions;
}

inline bool operator==(const SetComponentStateOperationState& lhs, const SetComponentStateOperationStateBuilder& rhs)
{
    return rhs == lhs;
}

inline bool operator!=(const SetComponentStateOperationStateBuilder& lhs, const SetComponentStateOperationStateBuilder& rhs)
{
    return !(lhs == rhs);
}

inline bool operator!=(const SetComponentStateOperationState& lhs, const SetComponentStateOperationStateBuilder& rhs)
{
    return !(lhs == rhs);
}

inline bool operator!=(const SetComponentStateOperationStateBuilder& lhs, const SetComponentStateOperationState& rhs)
{
    return !(lhs == rhs);
}

inline SetComponentStateOperationStateBuilder getBuilder(const SetComponentStateOperationState& setComponentStateOperationState)
{
    return SetComponentStateOperationStateBuilder(setComponentStateOperationState);
}

inline SetComponentStateOperationStateBuilder getBuilder(const DFL::NotNull<SharedPtr<SetComponentStateOperationState>>& setComponentStateOperationState)
{
    return SetComponentStateOperationStateBuilder(setComponentStateOperationState);
}

}
}