/**************************************************************************************
 *
 * DO NOT EDIT THIS FILE MANUALLY
 * THIS FILE IS GENERATED BY
 * modules\S32\Tools\MdibBuilders\RunGenerator.cmd
 *
 **************************************************************************************/

#pragma once

#include <memory>
#include <boost/optional.hpp>
#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Utils/Public/NotNull.h>

#include <Framework/Mdib/Public/Model/Component/VmdDescriptor.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Builder with fluent interface for @ref VmdDescriptor
 * @ingroup Mdib
 */
class VmdDescriptorBuilder
{
    public:
        /// @brief Typedef to the immutable @ref VmdDescriptor
        using BuiltType = VmdDescriptor;

        /// @brief Builder based on given immutable @ref VmdDescriptor
        explicit VmdDescriptorBuilder(const VmdDescriptor& vmdDescriptor=VmdDescriptor());

        /// @brief Builder based on given immutable @ref VmdDescriptor
        explicit VmdDescriptorBuilder(const DFL::NotNull<SharedPtr<VmdDescriptor>>& vmdDescriptor);

        /// @brief Overwrite all values with given immutable @ref VmdDescriptor
        VmdDescriptorBuilder& operator=(const VmdDescriptor& vmdDescriptor);

        /// @brief Explicit conversion to immutable @ref VmdDescriptor
        VmdDescriptor build() const;

        /// @brief Test whether the builder differs from the immutable @ref VmdDescriptor
        bool isChanged(const VmdDescriptor& base) const;

        /// @brief Setter for safetyClassification
        /// @{
        VmdDescriptorBuilder& safetyClassification(SafetyClassification safetyClassification);
        /// @}

        /// @brief Setter for type
        /// @{
        VmdDescriptorBuilder& type(const boost::optional<CodedValue>& type);
        VmdDescriptorBuilder& type(boost::optional<CodedValue>&& type);
        /// @}

        /// @brief Setter for productionSpecifications
        /// @{
        VmdDescriptorBuilder& productionSpecifications(const ProductionSpecifications& productionSpecifications);
        VmdDescriptorBuilder& productionSpecifications(ProductionSpecifications&& productionSpecifications);
        /// @}

        /// @brief Setter for approvedJurisdictions
        /// @{
        VmdDescriptorBuilder& approvedJurisdictions(const boost::optional<InstanceIdentifiers>& approvedJurisdictions);
        VmdDescriptorBuilder& approvedJurisdictions(boost::optional<InstanceIdentifiers>&& approvedJurisdictions);
        /// @}

        /// @brief Setter for extensions
        /// @{
        VmdDescriptorBuilder& extensions(const ExtensionTypes& extensions);
        VmdDescriptorBuilder& extensions(ExtensionTypes&& extensions);
        /// @}

        /// @brief Getter for safetyClassification
        /// @{
        SafetyClassification& safetyClassification();
        SafetyClassification safetyClassification() const;
        /// @}

        /// @brief Getter for type
        /// @{
        boost::optional<CodedValue>& type();
        const boost::optional<CodedValue>& type() const;
        /// @}

        /// @brief Getter for productionSpecifications
        /// @{
        ProductionSpecifications& productionSpecifications();
        const ProductionSpecifications& productionSpecifications() const;
        /// @}

        /// @brief Getter for approvedJurisdictions
        /// @{
        boost::optional<InstanceIdentifiers>& approvedJurisdictions();
        const boost::optional<InstanceIdentifiers>& approvedJurisdictions() const;
        /// @}

        /// @brief Getter for extensions
        /// @{
        ExtensionTypes& extensions();
        const ExtensionTypes& extensions() const;
        /// @}

    private:
        SafetyClassification m_safetyClassification;
        boost::optional<CodedValue> m_type;
        ProductionSpecifications m_productionSpecifications;
        boost::optional<InstanceIdentifiers> m_approvedJurisdictions;
        ExtensionTypes m_extensions;
};

/**
 * @brief Equal operator compares all members
 * @ingroup Mdib
 */
/// @{
DFL_MDIB_EXPIMP bool operator==(const VmdDescriptor& lhs, const VmdDescriptor& rhs);
DFL_MDIB_EXPIMP bool operator==(const VmdDescriptorBuilder& lhs, const VmdDescriptorBuilder& rhs);
DFL_MDIB_EXPIMP bool operator==(const VmdDescriptorBuilder& lhs, const VmdDescriptor& rhs);
bool operator==(const VmdDescriptor& lhs, const VmdDescriptorBuilder& rhs);
/// @}

/**
 * @brief Not equal operator compares all members
 * @ingroup Mdib
 */
/// @{
DFL_MDIB_EXPIMP bool operator!=(const VmdDescriptor& lhs, const VmdDescriptor& rhs);
bool operator!=(const VmdDescriptorBuilder& lhs, const VmdDescriptorBuilder& rhs);
bool operator!=(const VmdDescriptor& lhs, const VmdDescriptorBuilder& rhs);
bool operator!=(const VmdDescriptorBuilder& lhs, const VmdDescriptor& rhs);
/// @}

/**
 * @brief Factory function to create %Builder based on given immutable @ref VmdDescriptor
 * @ingroup Mdib
 */
/// @{
VmdDescriptorBuilder getBuilder(const VmdDescriptor& vmdDescriptor);
VmdDescriptorBuilder getBuilder(const DFL::NotNull<SharedPtr<VmdDescriptor>>& vmdDescriptor);
/// @}

/**
 * @brief Helper function throws runtime_error in case of a not equal member
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP void assertEqual(const VmdDescriptor& lhs, const VmdDescriptor& rhs);

inline VmdDescriptorBuilder::VmdDescriptorBuilder(const VmdDescriptor& vmdDescriptor) :
    m_safetyClassification(vmdDescriptor.safetyClassification()),
    m_type(vmdDescriptor.type()),
    m_productionSpecifications(vmdDescriptor.productionSpecifications()),
    m_approvedJurisdictions(vmdDescriptor.approvedJurisdictions()),
    m_extensions(vmdDescriptor.extensions())
{
}

inline VmdDescriptorBuilder::VmdDescriptorBuilder(const DFL::NotNull<SharedPtr<VmdDescriptor>>& vmdDescriptor) :
    m_safetyClassification(vmdDescriptor->safetyClassification()),
    m_type(vmdDescriptor->type()),
    m_productionSpecifications(vmdDescriptor->productionSpecifications()),
    m_approvedJurisdictions(vmdDescriptor->approvedJurisdictions()),
    m_extensions(vmdDescriptor->extensions())
{
}

inline VmdDescriptorBuilder& VmdDescriptorBuilder::operator=(const VmdDescriptor& vmdDescriptor)
{
    m_safetyClassification = vmdDescriptor.safetyClassification();
    m_type = vmdDescriptor.type();
    m_productionSpecifications = vmdDescriptor.productionSpecifications();
    m_approvedJurisdictions = vmdDescriptor.approvedJurisdictions();
    m_extensions = vmdDescriptor.extensions();
    return *this;
}

inline VmdDescriptor VmdDescriptorBuilder::build() const
{
    // NOLINTNEXTLINE(modernize-return-braced-init-list)
    return VmdDescriptor(m_safetyClassification, m_type, m_productionSpecifications, m_approvedJurisdictions, m_extensions);
}

inline bool VmdDescriptorBuilder::isChanged(const VmdDescriptor& base) const
{
    return *this != base;
}

inline VmdDescriptorBuilder& VmdDescriptorBuilder::safetyClassification(SafetyClassification safetyClassification)
{
    m_safetyClassification = safetyClassification;
    return *this;
}

inline SafetyClassification& VmdDescriptorBuilder::safetyClassification()
{
    return m_safetyClassification;
}

inline SafetyClassification VmdDescriptorBuilder::safetyClassification() const
{
    return m_safetyClassification;
}

inline VmdDescriptorBuilder& VmdDescriptorBuilder::type(const boost::optional<CodedValue>& type)
{
    m_type = type;
    return *this;
}

inline VmdDescriptorBuilder& VmdDescriptorBuilder::type(boost::optional<CodedValue>&& type)
{
    m_type = std::move(type);
    return *this;
}

inline boost::optional<CodedValue>& VmdDescriptorBuilder::type()
{
    return m_type;
}

inline const boost::optional<CodedValue>& VmdDescriptorBuilder::type() const
{
    return m_type;
}

inline VmdDescriptorBuilder& VmdDescriptorBuilder::productionSpecifications(const ProductionSpecifications& productionSpecifications)
{
    m_productionSpecifications = productionSpecifications;
    return *this;
}

inline VmdDescriptorBuilder& VmdDescriptorBuilder::productionSpecifications(ProductionSpecifications&& productionSpecifications)
{
    m_productionSpecifications = std::move(productionSpecifications);
    return *this;
}

inline ProductionSpecifications& VmdDescriptorBuilder::productionSpecifications()
{
    return m_productionSpecifications;
}

inline const ProductionSpecifications& VmdDescriptorBuilder::productionSpecifications() const
{
    return m_productionSpecifications;
}

inline VmdDescriptorBuilder& VmdDescriptorBuilder::approvedJurisdictions(const boost::optional<InstanceIdentifiers>& approvedJurisdictions)
{
    m_approvedJurisdictions = approvedJurisdictions;
    return *this;
}

inline VmdDescriptorBuilder& VmdDescriptorBuilder::approvedJurisdictions(boost::optional<InstanceIdentifiers>&& approvedJurisdictions)
{
    m_approvedJurisdictions = std::move(approvedJurisdictions);
    return *this;
}

inline boost::optional<InstanceIdentifiers>& VmdDescriptorBuilder::approvedJurisdictions()
{
    return m_approvedJurisdictions;
}

inline const boost::optional<InstanceIdentifiers>& VmdDescriptorBuilder::approvedJurisdictions() const
{
    return m_approvedJurisdictions;
}

inline VmdDescriptorBuilder& VmdDescriptorBuilder::extensions(const ExtensionTypes& extensions)
{
    m_extensions = extensions;
    return *this;
}

inline VmdDescriptorBuilder& VmdDescriptorBuilder::extensions(ExtensionTypes&& extensions)
{
    m_extensions = std::move(extensions);
    return *this;
}

inline ExtensionTypes& VmdDescriptorBuilder::extensions()
{
    return m_extensions;
}

inline const ExtensionTypes& VmdDescriptorBuilder::extensions() const
{
    return m_extensions;
}

inline bool operator==(const VmdDescriptor& lhs, const VmdDescriptorBuilder& rhs)
{
    return rhs == lhs;
}

inline bool operator!=(const VmdDescriptorBuilder& lhs, const VmdDescriptorBuilder& rhs)
{
    return !(lhs == rhs);
}

inline bool operator!=(const VmdDescriptor& lhs, const VmdDescriptorBuilder& rhs)
{
    return !(lhs == rhs);
}

inline bool operator!=(const VmdDescriptorBuilder& lhs, const VmdDescriptor& rhs)
{
    return !(lhs == rhs);
}

inline VmdDescriptorBuilder getBuilder(const VmdDescriptor& vmdDescriptor)
{
    return VmdDescriptorBuilder(vmdDescriptor);
}

inline VmdDescriptorBuilder getBuilder(const DFL::NotNull<SharedPtr<VmdDescriptor>>& vmdDescriptor)
{
    return VmdDescriptorBuilder(vmdDescriptor);
}

}
}