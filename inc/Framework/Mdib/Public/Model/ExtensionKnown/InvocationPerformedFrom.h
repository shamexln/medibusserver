#pragma once

#include <Framework/Mdib/Private/ExpImp.h>

namespace DFL
{
namespace Mdib
{
namespace Ext
{

/**
 * @brief Conveys the vicinity of an SDC Service Consumer in which it is allowed
 * to invoke an SCO operation at an SDC Service Provider.
 * @ingroup Mdib
 */
enum class Vicinity
{
    /**
     * @brief Same as not including the extension.
     * @details
     * It demands the SDC Operation Consumer to potentially understand the
     * extension in case it ever switches to a different state.
     */
    Any = 0,

    /**
     * @brief Situational awareness and means of intervention are equivalent to
     * the intended operator position of the Provider.
     * @details
     * The situational awareness of course may differ due to a different user
     * interface of the Consumer.
     *
     * Example: SDC OPERATION CONSUMER is located directly next to the SDC
     * OPERATION PROVIDER as in an anesthesia workstation.
     */
    ImmediateVicinity,

    /**
     * @brief Situational awareness of the patient and the POC ENVIRONMENT as
     * well as means of intervention are similar to the intended operator
     * position of the Provider.
     * @details
     * Example: SDC OPERATION CONSUMER is located at opposite bedside of the SDC
     * OPERATION PROVIDER.
     */
    CloseVicinity,

    /**
     * @brief From the operator position the user has a direct view to the POC
     * ENVIRONMENT and patient and is able to assess the overall situation.
     * @details
     * The user can be notified about alarms of the SDC SERVICE PROVIDER. The
     * operator position allows prompt intervention, e.g. in the case of a high
     * priority alarm.
     *
     * Example: SDC OPERATION PROVIDER and patient are inside an isolation room
     * and the SDC OPERATION CONSUMER is located in front of the isolation room.
     * The room is equipped with a window allowing visual assessment of the
     * situation inside from the operator position of the SDC OPERATION
     * CONSUMER. Users are notified about alarms via a distributed alarm
     * system.
     */
    ActionableVicinity,

    /**
     * @brief Remote (Non-Actionable Vicinity).
     * @details The invocation request has been issued from an SDC Operation
     * Consumer that is physically located in a distance where an operator of
     * the SDC Operation Consumer may not detect a deteriorated patient
     * condition. The user can be notified about alarms of the SDC SERVICE
     * PROVIDER.
     *
     * Example: SDC OPERATION CONSUMER is located at a central position of a
     * care unit allowing remote access to several SDC OPERATION PROVIDERs.
     * Users are notified about alarms via a distributed alarm
     * system.
     */
    Remote
};

/**
 * @brief Expresses the vicinity of an operation descriptor.
 *
 * @details
 * InvocationPerformedFrom is an extension intended to be attached to
 * pm:AbstractOperationDescriptor extension elements. It expresses the vicinity
 * in which an SDC Service Consumer has to reside in order to be permitted to
 * invoke an SCO operation at an SDC Service Provider. SDC Participants have to
 * adhere to the following requirements:
 *
 * - An SDC Service Consumer shall not invoke an SCO operation at an SDC Service
 *   Provider if it is not located at the \@Vicinity attribute stipulated by the
 *   InvocationPerformedFrom extension.
 * - An SDC Service Consumer may add multiple InvocationPerformedFrom extensions
 *   to one ext:Extension element of a pm:AbstractOperationDescriptor if
 *   multiple vicinities exist from where an SDC Service Consumer is allowed to
 *   execute the SCO operation.
 * - For a pm:AbstractOperationDescriptor an SDC Service Consumer shall
 *   interpret all InvocationPerformedFrom extensions by logically linking them
 *   by an "or".
 *
 * Note: Since multiple InvocationPerformedFrom extensions are linked with a
 * logical "or", a set of vicinities that includes the "Any" vicinity allows an
 * SDC Service Consumer to invoke an SCO operation from any radius regardless of
 * other vicinities in that set.
 *
 * @note An SDC Service Provider shall set \@ext:MustUnderstand = "true".
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP InvocationPerformedFrom
{
public:
    /**
     * @brief Ctor with all members.
     */
    explicit InvocationPerformedFrom(Vicinity vicinity);

    /**
     * @brief Allowed vicinity for requesting the execution of an SCO operation.
     */
    Vicinity vicinity() const noexcept;

private:
    Vicinity m_vicinity{Vicinity::Any};
};

/**
 * @brief Checks for equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator==(const InvocationPerformedFrom& lhs,
                                const InvocationPerformedFrom& rhs) noexcept;

/**
 * @brief Checks for non-equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator!=(const InvocationPerformedFrom& lhs,
                                const InvocationPerformedFrom& rhs) noexcept;

}
}
}
