#pragma once

#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Component/AbstractDeviceComponentDescriptor.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Describes the static part of the \ref Sco.
 * @ingroup Mdib
 */
class ScoDescriptor: public AbstractDeviceComponentDescriptor
{
    DFL_MDIB_IMMUTABLE(ScoDescriptor)

public:
    /**
     * @brief Defaults to \ref SafetyClassification "safety classification" \ref SafetyClassification::Informational "informational"
     * without \ref type() "type" and \ref productionSpecifications() "production specification" information.
     */
    ScoDescriptor() = default;
    /**
     * @brief Constructor.
     */
    ScoDescriptor(SafetyClassification safetyClassification,
                  boost::optional<CodedValue>&& type,
                  ProductionSpecifications productionSpecifications,
                  ExtensionTypes extensions = ExtensionTypes{ });

    /**
     * @brief Constructor.
     */
    ScoDescriptor(SafetyClassification safetyClassification,
                  const boost::optional<CodedValue>& type,
                  ProductionSpecifications productionSpecifications,
                  ExtensionTypes extensions = ExtensionTypes{ });
};

inline ScoDescriptor::ScoDescriptor(SafetyClassification safetyClassification,
                                    boost::optional<CodedValue>&& type,
                                    ProductionSpecifications productionSpecifications,
                                    ExtensionTypes extensions) :
        AbstractDeviceComponentDescriptor(safetyClassification, std::move(type), std::move(productionSpecifications), std::move(extensions))
{
}

inline ScoDescriptor::ScoDescriptor(SafetyClassification safetyClassification,
                                    const boost::optional<CodedValue>& type,
                                    ProductionSpecifications productionSpecifications,
                                    ExtensionTypes extensions) :
        AbstractDeviceComponentDescriptor(safetyClassification, type, std::move(productionSpecifications), std::move(extensions))
{
}

/**
 * @brief Definition of shared pointer type \ref ScoDescriptorSharedPtr for descriptor \ref ScoDescriptor.
 * @ingroup Mdib
 */
using ScoDescriptorSharedPtr = SharedPtr<ScoDescriptor>;

} /* namespace Mdib */
} /* namespace DFL */
