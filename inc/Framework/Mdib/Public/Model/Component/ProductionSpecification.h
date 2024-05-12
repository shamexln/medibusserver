#pragma once

#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>
#include <Framework/Utils/Public/Utf8.h>

#include <utility>

namespace DFL
{
namespace Mdib
{

/**
 * @brief List of production specifications of the component.
 * @details The production specification describes elements such as part numbers, serial numbers, revisions, etc.
 * @ingroup Mdib
 */
class ProductionSpecification
{
    public:
        /**
         * @brief Constructor.
         */
        ProductionSpecification(CodedValue&& specificationType,
                                Locale::Utf8 specificationValue,
                                boost::optional<InstanceIdentifier>&& componentId);

        /**
         * @brief Constructor.
         */
        ProductionSpecification(const CodedValue& specificationType,
                                Locale::Utf8 specificationValue,
                                boost::optional<InstanceIdentifier>&& componentId);

        /**
         * @brief Constructor.
         */
        ProductionSpecification(CodedValue&& specificationType,
                                Locale::Utf8 specificationValue,
                                const boost::optional<InstanceIdentifier>& componentId);

        /**
         * @brief Constructor.
         */
        ProductionSpecification(const CodedValue& specificationType,
                                Locale::Utf8 specificationValue,
                                const boost::optional<InstanceIdentifier>& componentId);

        /**
         * @brief SpecType is the specification type, such as serial number, part number, hardware revision, software revision, etc.
         */
        const CodedValue& specType() const;

        /**
         * @brief List of production specifications of the component.
         * @details The production specification describes elements such as part numbers, serial numbers, revisions, etc.
         */
        const Locale::Utf8& productionSpec() const;

        /**
         * @brief Describes the internal component unique identification.
         * @details This is a provision for manufacturer specific standard components using a private object identifier (OID).
         */
        const boost::optional<InstanceIdentifier>& componentId() const;

        /**
         * @brief Test for equal.
         */
        bool operator ==(const ProductionSpecification& rhs) const;

        /**
         * @brief Test for unequal.
         */
        bool operator !=(const ProductionSpecification& rhs) const;

    private:
        CodedValue m_specType;
        Locale::Utf8 m_productionSpec;
        boost::optional<InstanceIdentifier> m_componentId;
};

/**
 * @brief Sequence of \ref ProductionSpecification.
 * @ingroup Mdib
 */
using ProductionSpecifications = std::vector<ProductionSpecification>;

inline ProductionSpecification::ProductionSpecification(CodedValue&& specificationType,
                                                        Locale::Utf8 specificationValue,
                                                        boost::optional<InstanceIdentifier>&& componentId):
        m_specType(std::move(specificationType)),
        m_productionSpec(std::move(specificationValue)),
        m_componentId(std::move(componentId))
{
}

inline ProductionSpecification::ProductionSpecification(const CodedValue& specificationType, // NOLINT(modernize-pass-by-value)
                                                        Locale::Utf8 specificationValue,
                                                        boost::optional<InstanceIdentifier>&& componentId):
        m_specType(specificationType),
        m_productionSpec(std::move(specificationValue)),
        m_componentId(std::move(componentId))
{
}

inline ProductionSpecification::ProductionSpecification(CodedValue&& specificationType,
                                                        Locale::Utf8 specificationValue,
                                                        const boost::optional<InstanceIdentifier>& componentId): // NOLINT(modernize-pass-by-value)
        m_specType(std::move(specificationType)),
        m_productionSpec(std::move(specificationValue)),
        m_componentId(componentId)
{
}

inline ProductionSpecification::ProductionSpecification(const CodedValue& specificationType, // NOLINT(modernize-pass-by-value)
                                                        Locale::Utf8 specificationValue,
                                                        const boost::optional<InstanceIdentifier>& componentId): // NOLINT(modernize-pass-by-value)
        m_specType(specificationType),
        m_productionSpec(std::move(specificationValue)),
        m_componentId(componentId)
{
}

inline const CodedValue& ProductionSpecification::specType() const
{
    return m_specType;
}

inline const Locale::Utf8& ProductionSpecification::productionSpec() const
{
    return m_productionSpec;
}

inline const boost::optional<InstanceIdentifier>& ProductionSpecification::componentId() const
{
    return m_componentId;
}

inline bool ProductionSpecification::operator ==(const ProductionSpecification& rhs) const
{
    if (this == &rhs)
    {
        return true;
    }
    return m_specType == rhs.m_specType
        && m_productionSpec == rhs.m_productionSpec
        && m_componentId == rhs.m_componentId;
}

inline bool ProductionSpecification::operator !=(const ProductionSpecification& rhs) const
{
    return !(*this == rhs);
}

} /* namespace Mdib */
} /* namespace DFL */
