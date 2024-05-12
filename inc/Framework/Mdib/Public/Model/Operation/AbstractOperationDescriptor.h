#pragma once

#include <boost/optional.hpp>
#include <utility>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Public/Model/AbstractDescriptor.h>
#include <Framework/Mdib/Public/Model/Duration.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Operation/AccessLevel.h>
#include <Framework/Mdib/Private/HasExtensions.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Identifies that the clock information is actively being used in care delivery algorithms/protocols.
 * @ingroup Mdib
 */
enum class Retriggerable
{
        /**
         * @brief Indicates that a call to the activate operation resets the current \ref AbstractOperationDescriptor::invocationEffectiveTimeout() "invocation effective timeout".
         */
        RetriggerResetsEffectiveTimeout,

        /**
         * @brief Leaves the current \ref AbstractOperationDescriptor::invocationEffectiveTimeout() "invocation effective timeout" as it is until it times out.
         */
        RetriggerLeavesEffectiveTimeoutUntouched
};
DFL_ENUM_CLASS_STREAM_OPERATOR(Retriggerable, (RetriggerResetsEffectiveTimeout)(RetriggerLeavesEffectiveTimeoutUntouched))

/**
 * @brief Abstract description of an operation that is exposed on the \ref Sco.
 * @ingroup Mdib
 */
class AbstractOperationDescriptor: public Impl::HasExtensions
{
    DFL_MDIB_IMMUTABLE(AbstractOperationDescriptor)

    public:
        /**
         * @brief The safety classification of the data that is described with this descriptor.
         * @details In contrast to \ref AbstractDescriptor::safetyClassification(), %AbstractOperationDescriptor's
         *          safety classification has no default value. This facilitates the MDIB to discriminate between
         *          operations where the user actively decided to set the safety classification and an implied
         *          "Inf" value.
         *
         *          This is in accordance with sdc:R0028:
         *
         *          An SDC SERVICE PROVIDER SHALL provide a pm:%AbstractOperationDescriptor/\@SafetyClassification
         *          item for all pm:AbstractOperationDescriptor for all SCOs if erroneous or inadvertent invocation
         *          of the operation results in an unacceptable RISK.
         *
         *          NOTE 7- The implied safety classification for remote-control operations leads to a
         *          classification of "Inf" for all pm:AbstractOperationDescriptor which might not be the safe state
         *          for a remote-control operation and therefore it has to be considered if this is the value
         *          determined by the risk management.
         */
        boost::optional<SafetyClassification> safetyClassification() const;

         /**
          * @brief The descriptor type that provides specific semantic information about the descriptor instance.
          * @details E.g., an \ref Mds that designates an anesthesia workstation.
          * @return Descriptor type or \c boost::none if unknown.
          */
        const boost::optional<CodedValue>& type() const;

        /**
         * @brief \ref Handle reference this operation is targeted to.
         * @details
         * - In case of a single state this is the handle of the descriptor.
         * - In case that multiple states may belong to one descriptor, the operation target is the handle of one of the state instances (if the state is modified by the operation).
         */
        const Handle& operationTarget() const;

        /**
         * @brief Defines the maximum time an operation takes to get from the initial receiving of the command to a successful end.
         * @return Time duration value for finish or \c boost::none if undefined.
         */
        const boost::optional<Duration>& maxTimeToFinish() const;

        /**
         * @brief Defines a time period in which the result of an invocation is effective after it has been successfully finished.
         * @details When the time is up and the operation has not been retriggered, then the operation target might be reverted to another state.
         *
         * \note Example: if an arbitrary client remotely controls the cutter of a high frequency cutting device, due to safety reasons the cutter trigger
         *  might have a timeout until it stops automatically. To enable continuous activation, the client has to send repeated triggers within the given
         *  invocation effective timeout duration.
         * @return Timeout duration or \c boost::none if undefined
         */
        const boost::optional<Duration>& invocationEffectiveTimeout() const;

        /**
         * @brief Defines whether an operation is retriggerable.
         * @details Retriggerable is only applicable if \ref AbstractOperationDescriptor::invocationEffectiveTimeout is set. If set to \c true, then retriggerable indicates that a
         * call to the activate operation resets the current invocation effective timeout, otherwise it will be left as it is until the invocation effective timeout times out.
         */
        Retriggerable retriggerable() const;

        /**
         * @brief Defines a user group to whom access to the operation is granted.
         */
        AccessLevel accessLevel() const;

    protected:
        /**
         * @brief Default constructor.
         * @details Defaults
         *
         * - \ref AbstractOperationDescriptor::operationTarget() "Operation target" to invalid \ref Handle "handle".
         * - \ref AbstractOperationDescriptor::maxTimeToFinish() "Maximum time to finish" to none
         * - \ref AbstractOperationDescriptor::invocationEffectiveTimeout() "Effective timeout of invocation" to none
         * - \ref AbstractOperationDescriptor::retriggerable() "Retriggerable" to \c true
         * - \ref AbstractOperationDescriptor::accessLevel() "Access level" to \ref AccessLevel::User "any user"
         *
         * \note Also applies defaults from \ref AbstractDescriptor.
         */
        AbstractOperationDescriptor() = default;

        /**
         * @brief Full constructor.
         */
        AbstractOperationDescriptor(boost::optional<SafetyClassification> safetyClassification,
                                    const boost::optional<CodedValue>& type,
                                    Handle operationTarget,
                                    boost::optional<Duration> maxTimeToFinish,
                                    boost::optional<Duration> invocationEffectiveTimeout,
                                    Retriggerable retriggerable,
                                    AccessLevel accessLevel,
                                    ExtensionTypes&& extensions);

    private:
        boost::optional<SafetyClassification> m_safetyClassification{};
        boost::optional<CodedValue> m_type{};
        Handle m_operationTarget{};
        boost::optional<Duration> m_maxTimeToFinish{};
        boost::optional<Duration> m_invocationEffectiveTimeout{};
        Retriggerable m_retriggerable{Retriggerable::RetriggerResetsEffectiveTimeout};
        AccessLevel m_accessLevel{AccessLevel::User};
};

inline AbstractOperationDescriptor::AbstractOperationDescriptor(boost::optional<SafetyClassification> safetyClassification,
                                                                const boost::optional<CodedValue>& type, // NOLINT(modernize-pass-by-value)
                                                                Handle operationTarget,
                                                                boost::optional<Duration> maxTimeToFinish,
                                                                boost::optional<Duration> invocationEffectiveTimeout,
                                                                Retriggerable retriggerable,
                                                                AccessLevel accessLevel,
                                                                ExtensionTypes&& extensions) :
        Impl::HasExtensions(std::move(extensions)),
        m_safetyClassification(safetyClassification),
        m_type(type),
        m_operationTarget(std::move(operationTarget)),
        m_maxTimeToFinish(std::move(maxTimeToFinish)),
        m_invocationEffectiveTimeout(std::move(invocationEffectiveTimeout)),
        m_retriggerable(retriggerable),
        m_accessLevel(accessLevel)
{
}

inline boost::optional<SafetyClassification> AbstractOperationDescriptor::safetyClassification() const
{
    return m_safetyClassification;
}

inline const boost::optional<CodedValue>& AbstractOperationDescriptor::type() const
{
    return m_type;
}

inline const Handle& AbstractOperationDescriptor::operationTarget() const
{
    return m_operationTarget;
}

inline const boost::optional<Duration>& AbstractOperationDescriptor::maxTimeToFinish() const
{
    return m_maxTimeToFinish;
}

inline const boost::optional<Duration>& AbstractOperationDescriptor::invocationEffectiveTimeout() const
{
    return m_invocationEffectiveTimeout;
}

inline Retriggerable AbstractOperationDescriptor::retriggerable() const
{
    return m_retriggerable;
}

inline AccessLevel AbstractOperationDescriptor::accessLevel() const
{
    return m_accessLevel;
}
}
}
