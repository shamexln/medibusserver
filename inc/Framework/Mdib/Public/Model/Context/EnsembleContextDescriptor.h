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
 * @brief Static part of an \ref EnsembleContext.
 * @ingroup Mdib
 */
class EnsembleContextDescriptor: public AbstractDescriptor
{
    DFL_MDIB_IMMUTABLE(EnsembleContextDescriptor)

    public:
        /**
         * @brief Applies defaults from \ref AbstractDescriptor.
         */
        EnsembleContextDescriptor() = default;

        /**
         * @brief Full constructor.
         */
        EnsembleContextDescriptor(SafetyClassification safetyClassification,
                                  boost::optional<CodedValue>&& type,
                                  ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Full constructor.
         */
        EnsembleContextDescriptor(SafetyClassification safetyClassification,
                                  const boost::optional<CodedValue>& type,
                                  ExtensionTypes extensions = ExtensionTypes{ });
};

inline EnsembleContextDescriptor::EnsembleContextDescriptor(SafetyClassification safetyClassification,
                                                            boost::optional<CodedValue>&& type,
                                                            ExtensionTypes extensions):
        AbstractDescriptor(safetyClassification, std::move(type), std::move(extensions))
{
}

inline EnsembleContextDescriptor::EnsembleContextDescriptor(SafetyClassification safetyClassification,
                                                            const boost::optional<CodedValue>& type,
                                                            ExtensionTypes extensions):
        AbstractDescriptor(safetyClassification, type, std::move(extensions))
{
}

/**
 * @brief Definition of shared pointer type \ref EnsembleContextDescriptorSharedPtr for descriptor \ref EnsembleContextDescriptor.
 * @ingroup Mdib
 */
using EnsembleContextDescriptorSharedPtr = SharedPtr<EnsembleContextDescriptor>;


} /* namespace Mdib */
} /* namespace DFL */
