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
 * @brief Static part of a \ref LocationContext.
 * @ingroup Mdib
 */
class LocationContextDescriptor: public AbstractDescriptor
{
    DFL_MDIB_IMMUTABLE(LocationContextDescriptor)

    public:
        /**
         * @brief Applies defaults from \ref AbstractDescriptor.
         */
        LocationContextDescriptor() = default;

        /**
         * @brief Full constructor.
         */
        LocationContextDescriptor(SafetyClassification safetyClassification,
                                  boost::optional<CodedValue>&& type,
                                  ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Full constructor.
         */
        LocationContextDescriptor(SafetyClassification safetyClassification,
                                  const boost::optional<CodedValue>& type,
                                  ExtensionTypes extensions = ExtensionTypes{ });
};

inline LocationContextDescriptor::LocationContextDescriptor(SafetyClassification safetyClassification,
                                                            boost::optional<CodedValue>&& type,
                                                            ExtensionTypes extensions) :
        AbstractDescriptor(safetyClassification, std::move(type), std::move(extensions))
{
}

inline LocationContextDescriptor::LocationContextDescriptor(SafetyClassification safetyClassification,
                                                            const boost::optional<CodedValue>& type,
                                                            ExtensionTypes extensions) :
        AbstractDescriptor(safetyClassification, type, std::move(extensions))
{
}

/**
 * @brief Definition of shared pointer type \ref LocationContextDescriptorSharedPtr for descriptor \ref LocationContextDescriptor.
 * @ingroup Mdib
 */
using LocationContextDescriptorSharedPtr = SharedPtr<LocationContextDescriptor>;


} /* namespace Mdib */
} /* namespace DFL */
