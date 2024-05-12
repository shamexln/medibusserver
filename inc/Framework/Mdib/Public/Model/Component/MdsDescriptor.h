#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Component/AbstractDeviceComponentDescriptor.h>
#include <Framework/Mdib/Public/Model/Component/MetaData.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Describes the static part of an \ref Mds.
 * @ingroup Mdib
 */
class MdsDescriptor: public AbstractDeviceComponentDescriptor
{
    DFL_MDIB_IMMUTABLE(MdsDescriptor)

    public:
        /**
         * @brief Defaults to \ref SafetyClassification "safety classification" \ref SafetyClassification::Informational "informational"
         * without further information.
         */
        MdsDescriptor() = default;

        /**
         * @brief Constructor.
         */
        MdsDescriptor(SafetyClassification safetyClassification,
                      boost::optional<CodedValue>&& type,
                      ProductionSpecifications productionSpecifications,
                      boost::optional<MetaData>&& metaData,
                      boost::optional<InstanceIdentifiers> approvedJurisdictions,
                      ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Constructor.
         */
        MdsDescriptor(SafetyClassification safetyClassification,
                      boost::optional<CodedValue>&& type,
                      ProductionSpecifications productionSpecifications,
                      const boost::optional<MetaData>& metaData,
                      boost::optional<InstanceIdentifiers> approvedJurisdictions,
                      ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Constructor.
         */
        MdsDescriptor(SafetyClassification safetyClassification,
                      const boost::optional<CodedValue>& type,
                      ProductionSpecifications productionSpecifications,
                      boost::optional<MetaData>&& metaData,
                      boost::optional<InstanceIdentifiers> approvedJurisdictions,
                      ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Constructor.
         */
        MdsDescriptor(SafetyClassification safetyClassification,
                      const boost::optional<CodedValue>& type,
                      ProductionSpecifications productionSpecifications,
                      const boost::optional<MetaData>& metaData,
                      boost::optional<InstanceIdentifiers> approvedJurisdictions,
                      ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Describes medical device meta data.
         */
        const boost::optional<MetaData>& metaData() const;

        /**
         * @brief List of regions in which a device component is approved to be operated.
         * @details If the list does not contain any entries, then the device component is not approved for any region.
         * If the list is not specified, then the device is approved to be operated in any region.
         */
        const boost::optional<InstanceIdentifiers>& approvedJurisdictions() const;

    private:
        boost::optional<MetaData> m_metaData;
        boost::optional<InstanceIdentifiers> m_approvedJurisdictions;
};

inline MdsDescriptor::MdsDescriptor(SafetyClassification safetyClassification,
                                    boost::optional<CodedValue>&& type,
                                    ProductionSpecifications productionSpecifications,
                                    boost::optional<MetaData>&& metaData,
                                    boost::optional<InstanceIdentifiers> approvedJurisdictions,
                                    ExtensionTypes extensions) :
        AbstractDeviceComponentDescriptor(safetyClassification, std::move(type), std::move(productionSpecifications), std::move(extensions)),
        m_metaData(std::move(metaData)),
        m_approvedJurisdictions(std::move(approvedJurisdictions))
{
}

inline MdsDescriptor::MdsDescriptor(SafetyClassification safetyClassification,
                                    boost::optional<CodedValue>&& type,
                                    ProductionSpecifications productionSpecifications,
                                    const boost::optional<MetaData>& metaData, // NOLINT(modernize-pass-by-value)
                                    boost::optional<InstanceIdentifiers> approvedJurisdictions,
                                    ExtensionTypes extensions) :
        AbstractDeviceComponentDescriptor(safetyClassification, std::move(type), std::move(productionSpecifications), std::move(extensions)),
        m_metaData(metaData),
        m_approvedJurisdictions(std::move(approvedJurisdictions))
{
}

inline MdsDescriptor::MdsDescriptor(SafetyClassification safetyClassification,
                                    const boost::optional<CodedValue>& type,
                                    ProductionSpecifications productionSpecifications,
                                    boost::optional<MetaData>&& metaData,
                                    boost::optional<InstanceIdentifiers> approvedJurisdictions,
                                    ExtensionTypes extensions) :
        AbstractDeviceComponentDescriptor(safetyClassification, type, std::move(productionSpecifications), std::move(extensions)),
        m_metaData(std::move(metaData)),
        m_approvedJurisdictions(std::move(approvedJurisdictions))
{
}

inline MdsDescriptor::MdsDescriptor(SafetyClassification safetyClassification,
                                    const boost::optional<CodedValue>& type,
                                    ProductionSpecifications productionSpecifications,
                                    const boost::optional<MetaData>& metaData, // NOLINT(modernize-pass-by-value)
                                    boost::optional<InstanceIdentifiers> approvedJurisdictions,
                                    ExtensionTypes extensions) :
        AbstractDeviceComponentDescriptor(safetyClassification, type, std::move(productionSpecifications), std::move(extensions)),
        m_metaData(metaData),
        m_approvedJurisdictions(std::move(approvedJurisdictions))
{
}

inline const boost::optional<MetaData>& MdsDescriptor::metaData() const
{
    return m_metaData;
}

inline const boost::optional<InstanceIdentifiers>& MdsDescriptor::approvedJurisdictions() const
{
    return m_approvedJurisdictions;
}

/**
 * @brief Definition of shared pointer type \ref MdsDescriptorSharedPtr for descriptor \ref MdsDescriptor.
 * @ingroup Mdib
 */
using MdsDescriptorSharedPtr = SharedPtr<MdsDescriptor>;


} /* namespace Mdib */
} /* namespace DFL */
