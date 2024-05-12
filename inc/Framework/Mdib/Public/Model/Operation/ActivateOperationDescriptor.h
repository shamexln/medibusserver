#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Operation/AbstractOperationDescriptor.h>
#include <Framework/Mdib/Public/Model/Operation/XPathExpressions.h>
#include <Framework/Mdib/Public/Model/Operation/ActivateArgument.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Describes the static part of an \ref ActivateOperation.
 * @ingroup Mdib
 */
class ActivateOperationDescriptor: public AbstractOperationDescriptor
{
    DFL_MDIB_IMMUTABLE(ActivateOperationDescriptor)

    public:
        /**
         * @brief Applies defaults from \ref AbstractSetStateOperationDescriptor.
         */
        ActivateOperationDescriptor();

       /**
         * @brief Full constructor with extensions.
         */
        ActivateOperationDescriptor(boost::optional<SafetyClassification> safetyClassification,
                                    const boost::optional<CodedValue>& type,
                                    const Handle& operationTarget,
                                    const boost::optional<Duration>& maxTimeToFinish,
                                    const boost::optional<Duration>& invocationEffectiveTimeout,
                                    Retriggerable retriggerable,
                                    AccessLevel accessLevel,
                                    const ActivateArguments& arguments,
                                    ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Argument description.
         */
        const ActivateArguments& arguments() const;

    private:

        ActivateArguments m_arguments;
};

inline ActivateOperationDescriptor::ActivateOperationDescriptor() :
        AbstractOperationDescriptor()
{
}

inline ActivateOperationDescriptor::ActivateOperationDescriptor(boost::optional<SafetyClassification> safetyClassification,
                                                                const boost::optional<CodedValue>& type,
                                                                const Handle& operationTarget,
                                                                const boost::optional<Duration>& maxTimeToFinish,
                                                                const boost::optional<Duration>& invocationEffectiveTimeout,
                                                                Retriggerable retriggerable,
                                                                AccessLevel accessLevel,
                                                                const ActivateArguments& arguments, // NOLINT(modernize-pass-by-value)
                                                                ExtensionTypes extensions) :
        AbstractOperationDescriptor(safetyClassification,
                                    type,
                                    operationTarget,
                                    maxTimeToFinish,
                                    invocationEffectiveTimeout,
                                    retriggerable,
                                    accessLevel,
                                    std::move(extensions)),
        m_arguments(arguments)
{
}

/**
 * @brief Definition of shared pointer type \ref ActivateOperationDescriptorSharedPtr for descriptor \ref ActivateOperationDescriptor.
 * @ingroup Mdib
 */
using ActivateOperationDescriptorSharedPtr = SharedPtr<ActivateOperationDescriptor>;

inline const ActivateArguments& ActivateOperationDescriptor::arguments() const
{
    return m_arguments;
}

} /* namespace Mdib */
} /* namespace DFL */
