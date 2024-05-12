#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Component/AbstractDeviceComponentDescriptor.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Describes the static part of a \ref Vmd.
 * @ingroup Mdib
 */
class VmdDescriptor : public AbstractDeviceComponentDescriptor
{
    DFL_MDIB_IMMUTABLE(VmdDescriptor)

    public:
        /**
         * @brief Defaults to \ref SafetyClassification "safety classification" \ref SafetyClassification::Informational "informational"
         * without further information.
         */
        VmdDescriptor() = default;

        /**
         * @brief Constructor.
         */
        VmdDescriptor(SafetyClassification safetyClassification,
                      boost::optional<CodedValue>&& type,
                      ProductionSpecifications productionSpecifications,
                      boost::optional<InstanceIdentifiers> approvedJurisdictions,
                      ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Constructor.
         */
        VmdDescriptor(SafetyClassification safetyClassification,
                      const boost::optional<CodedValue>& type,
                      ProductionSpecifications productionSpecifications,
                      boost::optional<InstanceIdentifiers> approvedJurisdictions,
                      ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief List of regions in which the the \ref Vmd is approved to be operated.
         * @return If the list does not contain any entries, then the VMD is not approved for any region.
         * If the list is not specified, then the VMD is approved to be operated in any region.
         */
        const boost::optional<InstanceIdentifiers>&  approvedJurisdictions() const;

    private:
        boost::optional<InstanceIdentifiers> m_approvedJurisdictions;

};

inline VmdDescriptor::VmdDescriptor(SafetyClassification safetyClassification,
                                    boost::optional<CodedValue>&& type,
                                    ProductionSpecifications productionSpecifications,
                                    boost::optional<InstanceIdentifiers> approvedJurisdictions,
                                    ExtensionTypes extensions) :
        AbstractDeviceComponentDescriptor(safetyClassification, std::move(type), std::move(productionSpecifications), std::move(extensions)),
        m_approvedJurisdictions(std::move(approvedJurisdictions))
{
}

inline VmdDescriptor::VmdDescriptor(SafetyClassification safetyClassification,
                                    const boost::optional<CodedValue>& type,
                                    ProductionSpecifications productionSpecifications,
                                    boost::optional<InstanceIdentifiers> approvedJurisdictions,
                                    ExtensionTypes extensions) :
        AbstractDeviceComponentDescriptor(safetyClassification, type, std::move(productionSpecifications), std::move(extensions)),
        m_approvedJurisdictions(std::move(approvedJurisdictions))
{
}

inline const boost::optional<InstanceIdentifiers>&  VmdDescriptor::approvedJurisdictions() const
{
    return m_approvedJurisdictions;
}

/**
 * @brief Definition of shared pointer type \ref VmdDescriptorSharedPtr for descriptor \ref VmdDescriptor.
 * @ingroup Mdib
 */
using VmdDescriptorSharedPtr = SharedPtr<VmdDescriptor>;


} /* namespace Mdib */
} /* namespace DFL */
