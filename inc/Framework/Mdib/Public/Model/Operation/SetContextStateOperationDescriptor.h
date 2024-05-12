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
 * @brief Defines the static part of a \ref SetContextStateOperation.
 * @ingroup Mdib
 */
class SetContextStateOperationDescriptor: public AbstractSetStateOperationDescriptor
{
    DFL_MDIB_IMMUTABLE(SetContextStateOperationDescriptor)

    public:

        /**
         * @brief Applies defaults from \ref AbstractSetStateOperationDescriptor.
         */
        SetContextStateOperationDescriptor();

        /**
         * @brief Full constructor with extensions.
         */
        SetContextStateOperationDescriptor(boost::optional<SafetyClassification> safetyClassification,
                                           const boost::optional<CodedValue>& type,
                                           const Handle& operationTarget,
                                           const boost::optional<Duration>& maxTimeToFinish,
                                           const boost::optional<Duration>& invocationEffectiveTimeout,
                                           Retriggerable retriggerable,
                                           AccessLevel accessLevel,
                                           const XPathExpressions& modifiableData,
                                           ExtensionTypes extensions = ExtensionTypes{ });

};

inline SetContextStateOperationDescriptor::SetContextStateOperationDescriptor() :
        AbstractSetStateOperationDescriptor()
{
}

inline SetContextStateOperationDescriptor::SetContextStateOperationDescriptor(boost::optional<SafetyClassification> safetyClassification,
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
 * @brief Definition of shared pointer type \ref SetContextStateOperationDescriptorSharedPtr for descriptor \ref SetContextStateOperationDescriptor.
 * @ingroup Mdib
 */
using SetContextStateOperationDescriptorSharedPtr = SharedPtr<SetContextStateOperationDescriptor>;


} /* namespace Mdib */
} /* namespace DFL */
