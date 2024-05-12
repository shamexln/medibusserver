#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Operation/AbstractOperationDescriptor.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Defines the static part of a \ref SetValueOperation.
 * @ingroup Mdib
 */
class SetValueOperationDescriptor: public AbstractOperationDescriptor
{
    DFL_MDIB_IMMUTABLE(SetValueOperationDescriptor)

    public:
        /**
         * @brief Applies defaults from \ref AbstractOperationDescriptor.
         */
        SetValueOperationDescriptor();

        /**
         * @brief Full constructor with extensions.
         */
        SetValueOperationDescriptor(boost::optional<SafetyClassification> safetyClassification,
                                    const boost::optional<CodedValue>& type,
                                    const Handle& operationTarget,
                                    const boost::optional<Duration>& maxTimeToFinish,
                                    const boost::optional<Duration>& invocationEffectiveTimeout,
                                    Retriggerable retriggerable,
                                    AccessLevel accessLevel,
                                    ExtensionTypes extensions = ExtensionTypes{ });

};

inline SetValueOperationDescriptor::SetValueOperationDescriptor() :
        AbstractOperationDescriptor()
{
}

inline SetValueOperationDescriptor::SetValueOperationDescriptor(boost::optional<SafetyClassification> safetyClassification,
                                                                const boost::optional<CodedValue>& type,
                                                                const Handle& operationTarget,
                                                                const boost::optional<Duration>& maxTimeToFinish,
                                                                const boost::optional<Duration>& invocationEffectiveTimeout,
                                                                Retriggerable retriggerable,
                                                                AccessLevel accessLevel,
                                                                ExtensionTypes extensions) :
        AbstractOperationDescriptor(safetyClassification,
                                    type,
                                    operationTarget,
                                    maxTimeToFinish,
                                    invocationEffectiveTimeout,
                                    retriggerable,
                                    accessLevel,
                                    std::move(extensions))
{
}

/**
 * @brief Definition of shared pointer type \ref SetValueOperationDescriptorSharedPtr for descriptor \ref SetValueOperationDescriptor.
 * @ingroup Mdib
 */
using SetValueOperationDescriptorSharedPtr = SharedPtr<SetValueOperationDescriptor>;

} /* namespace Mdib */
} /* namespace DFL */
