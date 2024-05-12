#pragma once

#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Component/AbstractDeviceComponentDescriptor.h>
#include <Framework/Mdib/Public/Model/SafetyClassification.h>
#include <Framework/Mdib/Private/HasExtensions.h>

#include <boost/optional.hpp>

#include <utility>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Describes the static part of a \ref SystemContext.
 * @ingroup Mdib
 */
class SystemContextDescriptor: public AbstractDeviceComponentDescriptor
{
    DFL_MDIB_IMMUTABLE(SystemContextDescriptor)

    public:
        /**
         * @brief Constructor.
         */
        SystemContextDescriptor() = default;

        /**
         * @brief Constructor.
         */
        explicit SystemContextDescriptor(ExtensionTypes extensions);

        /**
         * @brief Constructor.
         */
        SystemContextDescriptor(SafetyClassification safetyClassification,
                                const boost::optional<CodedValue>& type,
                                ProductionSpecifications productionSpecifications,
                                ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Constructor.
         */
        SystemContextDescriptor(SafetyClassification safetyClassification,
                                boost::optional<CodedValue>&& type,
                                ProductionSpecifications productionSpecifications,
                                ExtensionTypes extensions = ExtensionTypes{ });
};

inline SystemContextDescriptor::SystemContextDescriptor(ExtensionTypes extensions) :
        AbstractDeviceComponentDescriptor(SafetyClassification::Informational, boost::none, ProductionSpecifications{}, std::move(extensions))
{
}

inline SystemContextDescriptor::SystemContextDescriptor(SafetyClassification safetyClassification,
                                                        const boost::optional<CodedValue>& type,
                                                        ProductionSpecifications productionSpecifications,
                                                        ExtensionTypes extensions) :
        AbstractDeviceComponentDescriptor(safetyClassification, type, std::move(productionSpecifications), std::move(extensions))
{
}

inline SystemContextDescriptor::SystemContextDescriptor(SafetyClassification safetyClassification,
                                                        boost::optional<CodedValue>&& type,
                                                        ProductionSpecifications productionSpecifications,
                                                        ExtensionTypes extensions) :
        AbstractDeviceComponentDescriptor(safetyClassification, std::move(type), std::move(productionSpecifications), std::move(extensions))
{
}

/**
 * @brief Definition of shared pointer type \ref SystemContextDescriptorSharedPtr for descriptor \ref SystemContextDescriptor.
 * @ingroup Mdib
 */
using SystemContextDescriptorSharedPtr = SharedPtr<SystemContextDescriptor>;


} /* namespace Mdib */
} /* namespace DFL */
