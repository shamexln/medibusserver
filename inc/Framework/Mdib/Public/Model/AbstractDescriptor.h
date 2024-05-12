#pragma once

#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Private/HasExtensions.h>
#include <Framework/Mdib/Public/Model/SafetyClassification.h>

namespace DFL::Mdib
{

/**
 * @brief Defines foundational meta information of any object that is included in the descriptive part of the MDIB.
 * @details Any descriptor object is derived from %AbstractDescriptor.
 * @ingroup Mdib
 */
class AbstractDescriptor: public Impl::HasExtensions
{
    DFL_MDIB_IMMUTABLE(AbstractDescriptor)

    public:
       /**
        * @brief The safety classification of the data that is described with this descriptor.
        */
        SafetyClassification safetyClassification() const;

        /**
         * @brief The descriptor type that provides specific semantic information about the descriptor instance.
         * @details E.g., an \ref Mds that designates an anesthesia workstation.
         * @return Descriptor type or \c boost::none if unknown.
         */
        const boost::optional<CodedValue>& type() const;

    protected:
        /**
         * @brief Defaults to \ref SafetyClassification "safety classification" \ref SafetyClassification::Informational "informational"
         * without \ref type() "type" information.
         */
        AbstractDescriptor() = default;

        /**
         * @brief Constructor.
         */
        AbstractDescriptor(SafetyClassification safetyClassification,
                           boost::optional<CodedValue>&& type,
                           ExtensionTypes&& extensions);

        /**
         * @brief Constructor.
         */
        AbstractDescriptor(SafetyClassification safetyClassification,
                           const boost::optional<CodedValue>& type,
                           ExtensionTypes&& extensions);

    private:
        SafetyClassification m_safetyClassification = SafetyClassification::Informational;
        boost::optional<CodedValue> m_type;
};

inline AbstractDescriptor::AbstractDescriptor(SafetyClassification safetyClassification,
                                              boost::optional<CodedValue>&& type,
                                              ExtensionTypes&& extensions) :
        Impl::HasExtensions(std::move(extensions)),
        m_safetyClassification(safetyClassification),
        m_type(std::move(type))
{
}

inline AbstractDescriptor::AbstractDescriptor(SafetyClassification safetyClassification,
                                              const boost::optional<CodedValue>& type, // NOLINT(modernize-pass-by-value)
                                              ExtensionTypes&& extensions) :
        Impl::HasExtensions(std::move(extensions)),
        m_safetyClassification(safetyClassification),
        m_type(type)
{
}

inline SafetyClassification AbstractDescriptor::safetyClassification() const
{
    return m_safetyClassification;
}

inline const boost::optional<CodedValue>& AbstractDescriptor::type() const
{
    return m_type;
}

} /* namespace DFL */
