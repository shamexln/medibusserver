#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/AbstractDescriptor.h>
#include <Framework/Mdib/Public/Model/SafetyClassification.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Static part of a \ref PatientContext.
 * @ingroup Mdib
 */
class PatientContextDescriptor: public AbstractDescriptor
{
    DFL_MDIB_IMMUTABLE(PatientContextDescriptor)

    public:
        /**
         * @brief Applies defaults from \ref AbstractDescriptor.
         */
        PatientContextDescriptor() = default;

        /**
         * @brief Full constructor.
         */
        PatientContextDescriptor(SafetyClassification safetyClassification,
                                 boost::optional<CodedValue>&& type,
                                 ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Full constructor.
         */
        PatientContextDescriptor(SafetyClassification safetyClassification,
                                 const boost::optional<CodedValue>& type,
                                 ExtensionTypes extensions = ExtensionTypes{ });
};

inline PatientContextDescriptor::PatientContextDescriptor(SafetyClassification safetyClassification,
                                                          boost::optional<CodedValue>&& type,
                                                          ExtensionTypes extensions) :
        AbstractDescriptor(safetyClassification, std::move(type), std::move(extensions))
{
}

inline PatientContextDescriptor::PatientContextDescriptor(SafetyClassification safetyClassification,
                                                          const boost::optional<CodedValue>& type,
                                                          ExtensionTypes extensions) :
        AbstractDescriptor(safetyClassification, type, std::move(extensions))
{
}

/**
 * @brief Definition of shared pointer type \ref PatientContextDescriptorSharedPtr for descriptor \ref PatientContextDescriptor.
 * @ingroup Mdib
 */
using PatientContextDescriptorSharedPtr = SharedPtr<PatientContextDescriptor>;


} /* namespace Mdib */
} /* namespace DFL */
