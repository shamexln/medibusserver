#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Component/AbstractDeviceComponentDescriptor.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Describes the static part of a \ref Channel.
 * @ingroup Mdib
 */
class ChannelDescriptor : public AbstractDeviceComponentDescriptor
{
    DFL_MDIB_IMMUTABLE(ChannelDescriptor)

    public:
        /**
         * @brief Defaults to \ref SafetyClassification "safety classification" \ref SafetyClassification::Informational "informational"
         * without \ref type() "type" and \ref productionSpecifications() "production specification" information.
         */
        ChannelDescriptor() = default;

        /**
         * @brief Constructor.
         */
        ChannelDescriptor(SafetyClassification safetyClassification,
                          boost::optional<CodedValue>&& type,
                          ProductionSpecifications productionSpecifications,
                          ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Constructor.
         */
        ChannelDescriptor(SafetyClassification safetyClassification,
                          const boost::optional<CodedValue>& type,
                          ProductionSpecifications productionSpecifications,
                          ExtensionTypes extensions = ExtensionTypes{ });
};

inline ChannelDescriptor::ChannelDescriptor(SafetyClassification safetyClassification,
                                            boost::optional<CodedValue>&& type,
                                            ProductionSpecifications productionSpecifications,
                                            ExtensionTypes extensions):
        AbstractDeviceComponentDescriptor(safetyClassification, std::move(type), std::move(productionSpecifications), std::move(extensions))
{
}

inline ChannelDescriptor::ChannelDescriptor(SafetyClassification safetyClassification,
                                            const boost::optional<CodedValue>& type,
                                            ProductionSpecifications productionSpecifications,
                                            ExtensionTypes extensions):
        AbstractDeviceComponentDescriptor(safetyClassification, type, std::move(productionSpecifications), std::move(extensions))
{
}

/**
 * @brief Definition of shared pointer type \ref ChannelDescriptorSharedPtr for descriptor \ref ChannelDescriptor.
 * @ingroup Mdib
 */
using ChannelDescriptorSharedPtr = SharedPtr<ChannelDescriptor>;


} /* namespace Mdib */
} /* namespace DFL */
