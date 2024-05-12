#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Operation/AbstractSetStateOperationDescriptor.h>
#include <Framework/Mdib/Public/Model/Operation/XPathExpressions.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Defines the static part of a \ref SetMetricStateOperation.
 * @ingroup Mdib
 */
class SetMetricStateOperationDescriptor: public AbstractSetStateOperationDescriptor
{
    DFL_MDIB_IMMUTABLE(SetMetricStateOperationDescriptor)

    public:
        /**
         * @brief Applies defaults from \ref AbstractSetStateOperationDescriptor.
         */
        SetMetricStateOperationDescriptor();

        /**
         * @brief Full constructor with extensions.
         */
        SetMetricStateOperationDescriptor(boost::optional<SafetyClassification> safetyClassification,
                                          const boost::optional<CodedValue>& type,
                                          const Handle& operationTarget,
                                          const boost::optional<Duration>& maxTimeToFinish,
                                          const boost::optional<Duration>& invocationEffectiveTimeout,
                                          Retriggerable retriggerable,
                                          AccessLevel accessLevel,
                                          const XPathExpressions& modifiableData,
                                          ExtensionTypes extensions = ExtensionTypes{ });
};

inline SetMetricStateOperationDescriptor::SetMetricStateOperationDescriptor() :
        AbstractSetStateOperationDescriptor()
{
}

inline SetMetricStateOperationDescriptor::SetMetricStateOperationDescriptor(boost::optional<SafetyClassification> safetyClassification,
                                                                            const boost::optional<CodedValue>& type,
                                                                            const Handle& operationTarget,
                                                                            const boost::optional<Duration>& maxTimeToFinish,
                                                                            const boost::optional<Duration>& invocationEffectiveTimeout,
                                                                            Retriggerable retriggerable,
                                                                            AccessLevel accessLevel,
                                                                            const XPathExpressions& modifiableData,
                                                                            ExtensionTypes extensions) :
        AbstractSetStateOperationDescriptor(safetyClassification,
                                            type,
                                            operationTarget,
                                            maxTimeToFinish,
                                            invocationEffectiveTimeout,
                                            retriggerable,
                                            accessLevel,
                                            modifiableData,
                                            std::move(extensions))
{
}

/**
 * @brief Definition of shared pointer type \ref SetMetricStateOperationDescriptorSharedPtr for descriptor \ref SetMetricStateOperationDescriptor.
 * @ingroup Mdib
 */
using SetMetricStateOperationDescriptorSharedPtr = SharedPtr<SetMetricStateOperationDescriptor>;

} /* namespace Mdib */
} /* namespace DFL */
