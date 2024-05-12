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
 * @brief Defines the static part of a \ref SetComponentStateOperation.
 * @ingroup Mdib
 */
class SetComponentStateOperationDescriptor: public AbstractSetStateOperationDescriptor
{
    DFL_MDIB_IMMUTABLE(SetComponentStateOperationDescriptor)

    public:
        /**
         * @brief Applies defaults from \ref AbstractSetStateOperationDescriptor.
         */
        SetComponentStateOperationDescriptor();

        /**
         * @brief Full constructor with extensions.
         */
        SetComponentStateOperationDescriptor(boost::optional<SafetyClassification> safetyClassification,
                                             const boost::optional<CodedValue>& type,
                                             const Handle& operationTarget,
                                             const boost::optional<Duration>& maxTimeToFinish,
                                             const boost::optional<Duration>& invocationEffectiveTimeout,
                                             Retriggerable retriggerable,
                                             AccessLevel accessLevel,
                                             const XPathExpressions& modifiableData,
                                             ExtensionTypes extensions = ExtensionTypes{ });

};

inline SetComponentStateOperationDescriptor::SetComponentStateOperationDescriptor() :
        AbstractSetStateOperationDescriptor()
{
}

inline SetComponentStateOperationDescriptor::SetComponentStateOperationDescriptor(boost::optional<SafetyClassification> safetyClassification,
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
 * @brief Definition of shared pointer type \ref SetComponentStateOperationDescriptorSharedPtr for descriptor \ref SetComponentStateOperationDescriptor.
 * @ingroup Mdib
 */
using SetComponentStateOperationDescriptorSharedPtr = SharedPtr<SetComponentStateOperationDescriptor>;

} /* namespace Mdib */
} /* namespace DFL */
