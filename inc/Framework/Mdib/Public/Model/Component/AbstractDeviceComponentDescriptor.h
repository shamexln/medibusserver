#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Public/Model/AbstractDescriptor.h>
#include <Framework/Mdib/Public/Model/Component/ProductionSpecification.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Describes a basic device component.
 * @ingroup Mdib
 */
class AbstractDeviceComponentDescriptor: public AbstractDescriptor
{
    DFL_MDIB_IMMUTABLE(AbstractDeviceComponentDescriptor)

    public:
        /**
         * @brief List of production specifications of the component.
         * @details The production specification describes elements such as part numbers, serial numbers, revisions, etc.
         * @return List of production specifications or \c boost::none if undefined.
         */
        const ProductionSpecifications& productionSpecifications() const;

    protected:
        /**
         * @brief Defaults to \ref SafetyClassification "safety classification" \ref SafetyClassification::Informational "informational"
         * without \ref type() "type" and \ref productionSpecifications() "production specification" information.
         */
        AbstractDeviceComponentDescriptor() = default;

        /**
         * @brief Constructor.
         */
        AbstractDeviceComponentDescriptor(SafetyClassification safetyClassification,
                                          boost::optional<CodedValue>&& type,
                                          ProductionSpecifications&& productionSpecifications,
                                          ExtensionTypes&& extensions);

        /**
         * @brief Constructor.
         */
        AbstractDeviceComponentDescriptor(SafetyClassification safetyClassification,
                                          const boost::optional<CodedValue>& type,
                                          ProductionSpecifications&& productionSpecifications,
                                          ExtensionTypes&& extensions);

    private:
        ProductionSpecifications m_productionSpecifications;
};

inline AbstractDeviceComponentDescriptor::AbstractDeviceComponentDescriptor(SafetyClassification safetyClassification,
                                                                            boost::optional<CodedValue>&& type,
                                                                            ProductionSpecifications&& productionSpecifications,
                                                                            ExtensionTypes&& extensions):
        AbstractDescriptor(safetyClassification, std::move(type), std::move(extensions)),
        m_productionSpecifications(std::move(productionSpecifications))
{
}

inline AbstractDeviceComponentDescriptor::AbstractDeviceComponentDescriptor(SafetyClassification safetyClassification,
                                                                            const boost::optional<CodedValue>& type,
                                                                            ProductionSpecifications&& productionSpecifications,
                                                                            ExtensionTypes&& extensions):
        AbstractDescriptor(safetyClassification, type, std::move(extensions)),
        m_productionSpecifications(std::move(productionSpecifications))
{
}

inline const ProductionSpecifications& AbstractDeviceComponentDescriptor::productionSpecifications() const
{
    return m_productionSpecifications;
}

} /* namespace Mdib */
} /* namespace DFL */
