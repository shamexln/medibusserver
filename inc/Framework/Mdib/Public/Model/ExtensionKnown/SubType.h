#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Public/Model/ExtensionType.h>

#include <cstdint>

namespace DFL
{
namespace Mdib
{
namespace Ext
{
/**
 * @brief A further specifier for Types attached to specific pm:AbstractState elements
 *
 * @details
 * Is used by an SDC METRIC PROVIDER and is to be attached to pm:AbstractState
 * elements of type pm:VmdState, pm:ChannelState, pm:AbstractMetricState or
 * pm:AlertConditionState.
 *
 * The pm:Type of an element may be specified further for example through user
 * interaction. The SubType expressed in the pm:AbstractState can be be used to
 * refine the pm:Type that is specified in the pm:AbstractDescriptor, similar to
 * pm:AbstractMetricDescriptor/pm:BodySite and
 * pm:AbstractMetricState/pm:BodySite.
 *
 * Compared to an update of the pm:AbstractDescriptor, the SubType keeps the
 * original pm:Type in the pm:AbstractDescriptor and signifies that the SubType
 * is a more specific pm:Type.
 *
 * An SDC METRIC PROVIDER shall not provide more than one SubType extension
 * element at a time in a pm:AbstractState.
 *
 * Example usage in code:
 * @snippet Mdib/Test/UnitTest/TestParticipantModelExtensions.cpp SubTypeUsage
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP SubType
{
public:
    /**
     * @brief Constructor with all members.
     */
    SubType(const CodedValue& codedValue, std::uint64_t instanceNumber);

    /**
     * @brief CodedValue refined via the SubType extension.
     */
    const CodedValue& type() const noexcept;

    /**
     * @brief Instance of the given code.
     * @details Two extensions of the same code must have different
     * instanceNumbers.
     */
    std::uint64_t instanceNumber() const noexcept;

private:
    CodedValue m_type;
    std::uint64_t m_instanceNumber;
};

/**
 * @brief Checks for equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator==(const SubType& lhs,
                                const SubType& rhs) noexcept;

/**
 * @brief Checks for non-equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator!=(const SubType& lhs,
                                const SubType& rhs) noexcept;

}
}
}
