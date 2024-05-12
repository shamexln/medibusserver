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
 * @brief Defines the static part of a \ref SetAlertStateOperation.
 * @ingroup Mdib
 */
class SetAlertStateOperationDescriptor: public AbstractSetStateOperationDescriptor
{
    DFL_MDIB_IMMUTABLE(SetAlertStateOperationDescriptor)

    public:
        /**
         * @brief Applies defaults from \ref AbstractSetStateOperationDescriptor.
         */
        SetAlertStateOperationDescriptor();

        /**
         * @brief Full constructor with extensions.
         */
        SetAlertStateOperationDescriptor(boost::optional<SafetyClassification> safetyClassification,
                                         const boost::optional<CodedValue>& type,
                                         const Handle& operationTarget,
                                         const boost::optional<Duration>& maxTimeToFinish,
                                         const boost::optional<Duration>& invocationEffectiveTimeout,
                                         Retriggerable retriggerable,
                                         AccessLevel accessLevel,
                                         const XPathExpressions& modifiableData,
                                         ExtensionTypes extensions = ExtensionTypes{ });
};

inline SetAlertStateOperationDescriptor::SetAlertStateOperationDescriptor():
        AbstractSetStateOperationDescriptor()
{
}

inline SetAlertStateOperationDescriptor::SetAlertStateOperationDescriptor(boost::optional<SafetyClassification> safetyClassification,
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
 * @brief Definition of shared pointer type \ref SetAlertStateOperationDescriptorSharedPtr for descriptor \ref SetAlertStateOperationDescriptor.
 * @ingroup Mdib
 */
using SetAlertStateOperationDescriptorSharedPtr = SharedPtr<SetAlertStateOperationDescriptor>;

} /* namespace Mdib */
} /* namespace DFL */
