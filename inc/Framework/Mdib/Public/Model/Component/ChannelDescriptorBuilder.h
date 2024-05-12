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

#include <Framework/Mdib/Public/Model/Component/ChannelDescriptor.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Builder with fluent interface for @ref ChannelDescriptor
 * @ingroup Mdib
 */
class ChannelDescriptorBuilder
{
    public:
        /// @brief Typedef to the immutable @ref ChannelDescriptor
        using BuiltType = ChannelDescriptor;

        /// @brief Builder based on given immutable @ref ChannelDescriptor
        explicit ChannelDescriptorBuilder(const ChannelDescriptor& channelDescriptor=ChannelDescriptor());

        /// @brief Builder based on given immutable @ref ChannelDescriptor
        explicit ChannelDescriptorBuilder(const DFL::NotNull<SharedPtr<ChannelDescriptor>>& channelDescriptor);

        /// @brief Overwrite all values with given immutable @ref ChannelDescriptor
        ChannelDescriptorBuilder& operator=(const ChannelDescriptor& channelDescriptor);

        /// @brief Explicit conversion to immutable @ref ChannelDescriptor
        ChannelDescriptor build() const;

        /// @brief Test whether the builder differs from the immutable @ref ChannelDescriptor
        bool isChanged(const ChannelDescriptor& base) const;

        /// @brief Setter for safetyClassification
        /// @{
        ChannelDescriptorBuilder& safetyClassification(SafetyClassification safetyClassification);
        /// @}

        /// @brief Setter for type
        /// @{
        ChannelDescriptorBuilder& type(const boost::optional<CodedValue>& type);
        ChannelDescriptorBuilder& type(boost::optional<CodedValue>&& type);
        /// @}

        /// @brief Setter for productionSpecifications
        /// @{
        ChannelDescriptorBuilder& productionSpecifications(const ProductionSpecifications& productionSpecifications);
        ChannelDescriptorBuilder& productionSpecifications(ProductionSpecifications&& productionSpecifications);
        /// @}

        /// @brief Setter for extensions
        /// @{
        ChannelDescriptorBuilder& extensions(const ExtensionTypes& extensions);
        ChannelDescriptorBuilder& extensions(ExtensionTypes&& extensions);
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

        /// @brief Getter for extensions
        /// @{
        ExtensionTypes& extensions();
        const ExtensionTypes& extensions() const;
        /// @}

    private:
        SafetyClassification m_safetyClassification;
        boost::optional<CodedValue> m_type;
        ProductionSpecifications m_productionSpecifications;
        ExtensionTypes m_extensions;
};

/**
 * @brief Equal operator compares all members
 * @ingroup Mdib
 */
/// @{
DFL_MDIB_EXPIMP bool operator==(const ChannelDescriptor& lhs, const ChannelDescriptor& rhs);
DFL_MDIB_EXPIMP bool operator==(const ChannelDescriptorBuilder& lhs, const ChannelDescriptorBuilder& rhs);
DFL_MDIB_EXPIMP bool operator==(const ChannelDescriptorBuilder& lhs, const ChannelDescriptor& rhs);
bool operator==(const ChannelDescriptor& lhs, const ChannelDescriptorBuilder& rhs);
/// @}

/**
 * @brief Not equal operator compares all members
 * @ingroup Mdib
 */
/// @{
DFL_MDIB_EXPIMP bool operator!=(const ChannelDescriptor& lhs, const ChannelDescriptor& rhs);
bool operator!=(const ChannelDescriptorBuilder& lhs, const ChannelDescriptorBuilder& rhs);
bool operator!=(const ChannelDescriptor& lhs, const ChannelDescriptorBuilder& rhs);
bool operator!=(const ChannelDescriptorBuilder& lhs, const ChannelDescriptor& rhs);
/// @}

/**
 * @brief Factory function to create %Builder based on given immutable @ref ChannelDescriptor
 * @ingroup Mdib
 */
/// @{
ChannelDescriptorBuilder getBuilder(const ChannelDescriptor& channelDescriptor);
ChannelDescriptorBuilder getBuilder(const DFL::NotNull<SharedPtr<ChannelDescriptor>>& channelDescriptor);
/// @}

/**
 * @brief Helper function throws runtime_error in case of a not equal member
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP void assertEqual(const ChannelDescriptor& lhs, const ChannelDescriptor& rhs);

inline ChannelDescriptorBuilder::ChannelDescriptorBuilder(const ChannelDescriptor& channelDescriptor) :
    m_safetyClassification(channelDescriptor.safetyClassification()),
    m_type(channelDescriptor.type()),
    m_productionSpecifications(channelDescriptor.productionSpecifications()),
    m_extensions(channelDescriptor.extensions())
{
}

inline ChannelDescriptorBuilder::ChannelDescriptorBuilder(const DFL::NotNull<SharedPtr<ChannelDescriptor>>& channelDescriptor) :
    m_safetyClassification(channelDescriptor->safetyClassification()),
    m_type(channelDescriptor->type()),
    m_productionSpecifications(channelDescriptor->productionSpecifications()),
    m_extensions(channelDescriptor->extensions())
{
}

inline ChannelDescriptorBuilder& ChannelDescriptorBuilder::operator=(const ChannelDescriptor& channelDescriptor)
{
    m_safetyClassification = channelDescriptor.safetyClassification();
    m_type = channelDescriptor.type();
    m_productionSpecifications = channelDescriptor.productionSpecifications();
    m_extensions = channelDescriptor.extensions();
    return *this;
}

inline ChannelDescriptor ChannelDescriptorBuilder::build() const
{
    // NOLINTNEXTLINE(modernize-return-braced-init-list)
    return ChannelDescriptor(m_safetyClassification, m_type, m_productionSpecifications, m_extensions);
}

inline bool ChannelDescriptorBuilder::isChanged(const ChannelDescriptor& base) const
{
    return *this != base;
}

inline ChannelDescriptorBuilder& ChannelDescriptorBuilder::safetyClassification(SafetyClassification safetyClassification)
{
    m_safetyClassification = safetyClassification;
    return *this;
}

inline SafetyClassification& ChannelDescriptorBuilder::safetyClassification()
{
    return m_safetyClassification;
}

inline SafetyClassification ChannelDescriptorBuilder::safetyClassification() const
{
    return m_safetyClassification;
}

inline ChannelDescriptorBuilder& ChannelDescriptorBuilder::type(const boost::optional<CodedValue>& type)
{
    m_type = type;
    return *this;
}

inline ChannelDescriptorBuilder& ChannelDescriptorBuilder::type(boost::optional<CodedValue>&& type)
{
    m_type = std::move(type);
    return *this;
}

inline boost::optional<CodedValue>& ChannelDescriptorBuilder::type()
{
    return m_type;
}

inline const boost::optional<CodedValue>& ChannelDescriptorBuilder::type() const
{
    return m_type;
}

inline ChannelDescriptorBuilder& ChannelDescriptorBuilder::productionSpecifications(const ProductionSpecifications& productionSpecifications)
{
    m_productionSpecifications = productionSpecifications;
    return *this;
}

inline ChannelDescriptorBuilder& ChannelDescriptorBuilder::productionSpecifications(ProductionSpecifications&& productionSpecifications)
{
    m_productionSpecifications = std::move(productionSpecifications);
    return *this;
}

inline ProductionSpecifications& ChannelDescriptorBuilder::productionSpecifications()
{
    return m_productionSpecifications;
}

inline const ProductionSpecifications& ChannelDescriptorBuilder::productionSpecifications() const
{
    return m_productionSpecifications;
}

inline ChannelDescriptorBuilder& ChannelDescriptorBuilder::extensions(const ExtensionTypes& extensions)
{
    m_extensions = extensions;
    return *this;
}

inline ChannelDescriptorBuilder& ChannelDescriptorBuilder::extensions(ExtensionTypes&& extensions)
{
    m_extensions = std::move(extensions);
    return *this;
}

inline ExtensionTypes& ChannelDescriptorBuilder::extensions()
{
    return m_extensions;
}

inline const ExtensionTypes& ChannelDescriptorBuilder::extensions() const
{
    return m_extensions;
}

inline bool operator==(const ChannelDescriptor& lhs, const ChannelDescriptorBuilder& rhs)
{
    return rhs == lhs;
}

inline bool operator!=(const ChannelDescriptorBuilder& lhs, const ChannelDescriptorBuilder& rhs)
{
    return !(lhs == rhs);
}

inline bool operator!=(const ChannelDescriptor& lhs, const ChannelDescriptorBuilder& rhs)
{
    return !(lhs == rhs);
}

inline bool operator!=(const ChannelDescriptorBuilder& lhs, const ChannelDescriptor& rhs)
{
    return !(lhs == rhs);
}

inline ChannelDescriptorBuilder getBuilder(const ChannelDescriptor& channelDescriptor)
{
    return ChannelDescriptorBuilder(channelDescriptor);
}

inline ChannelDescriptorBuilder getBuilder(const DFL::NotNull<SharedPtr<ChannelDescriptor>>& channelDescriptor)
{
    return ChannelDescriptorBuilder(channelDescriptor);
}

}
}