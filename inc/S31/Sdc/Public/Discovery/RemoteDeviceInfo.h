#pragma once

#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Model/Component/ProductionSpecification.h>
#include <Framework/Mdib/Public/Model/Context/LocationDetail.h>
#include <Framework/Mdib/Public/Model/ExtensionKnown/CodedStringAttribute.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>

#include <boost/optional/optional.hpp>

#include <string>

namespace S31::Sdc
{

/**
 * @brief %RemoteDeviceInfo holds any accessible information of a certain device that has been discovered on the network.
 * @details Discovery messages in SDC provide unique endpoint references as well as device types and scopes. The endpoint
 * reference and scope information are retrievable from %RemoteDeviceInfo.
 *
 * This class is used in the @ref DiscoveryProvider to notify observers about devices found on the SDC network.
 * @ingroup S31SdcDiscovery
 */
class S31_CORE_EXPIMP RemoteDeviceInfo
{
    public:
        /**
         * @brief Reflects an associated location extracted from the discovery scopes URI list.
         * @ingroup S31SdcClient
         */
        class S31_CORE_EXPIMP AssociatedLocation
        {
            public:
                /**
                 * @brief Constructor that does not contain location detail.
                 */
                explicit AssociatedLocation(const DFL::Mdib::InstanceIdentifier& identification); // NOLINT(modernize-pass-by-value)

                /**
                 * @brief Full constructor.
                 */
                AssociatedLocation(const DFL::Mdib::InstanceIdentifier& identification, // NOLINT(modernize-pass-by-value)
                                   const boost::optional<DFL::Mdib::LocationDetail>& locationDetail); // NOLINT(modernize-pass-by-value)

                /**
                 * @brief Returns the location's identification.
                 */
                const DFL::Mdib::InstanceIdentifier& identification() const noexcept;
                /**
                 * @brief Returns the location's human-readable details if available.
                 */
                const boost::optional<DFL::Mdib::LocationDetail>& locationDetail() const noexcept;

            private:
                DFL::Mdib::InstanceIdentifier m_identification;
                boost::optional<DFL::Mdib::LocationDetail> m_locationDetail;
        };

        /**
         * @brief Sequence of @ref AssociatedLocation objects.
         */
        using AssociatedLocations = std::vector<AssociatedLocation>;

        /**
         * @brief Constructor.
         */
        RemoteDeviceInfo(const EndpointReference& endpointReference, // NOLINT(modernize-pass-by-value)
                         AssociatedLocations locations,
                         DFL::Mdib::CodedValues mdsTypes = {},
                         DFL::Mdib::ProductionSpecifications productionSpecifications = {},
                         DFL::Mdib::Ext::CodedStringAttributes codedStringAttributes = {},
                         std::vector<DFL::Locale::Utf8> rawDiscoveryScopes = {});

        /**
         * @brief Constructor.
         */
        RemoteDeviceInfo(EndpointReference&& endpointReference,
                         AssociatedLocations locations,
                         DFL::Mdib::CodedValues mdsTypes = {},
                         DFL::Mdib::ProductionSpecifications productionSpecifications = {},
                         DFL::Mdib::Ext::CodedStringAttributes codedStringAttributes = {},
                         std::vector<DFL::Locale::Utf8> rawDiscoveryScopes = {});

        /**
         * @brief Returns the endpoint reference of the remote device as received from discovery.
         */
        const EndpointReference& endpointReference() const noexcept;

        /**
         * @brief Returns all associated locations as received from discovery.
         */
        const AssociatedLocations& locations() const noexcept;

        /**
         * @brief Returns Component type received from discovery.
         * @details These are types added to Discovery Scopes according to 11073-20701-2018 Section 9.2.
         *
         *  9.2 states that Mds and Vmd types can be added to Discovery Scopes. However, BICEPS R0134 specifies
         *  that Mds types shall always be made available for discovery. Vmd types are optional.
         *  Currently, S31 only sends Mds types.
         */
        const DFL::Mdib::CodedValues& types() const noexcept;

        /**
         * @brief Returns production specifications received from Discovery
         * @details Includes Mds MetaData information such as ModelName and Manufacturer
         */
        const DFL::Mdib::ProductionSpecifications& productionSpecifications() const noexcept;

        /**
         * @brief Returns device coded string attributes received from Discovery
         * @details Includes device identifiers like Soft Id, aka device name or friendly name.
         */
        const DFL::Mdib::Ext::CodedStringAttributes& codedStringAttributes() const noexcept;

        /**
         * @brief List of WS-Discovery scopes as received in the UDP datagram.
         * @details
         * To access MDS type information or the locations from the scopes
         * it is recommended to use the member functions @ref types() and
         * @ref locations().
         */
        const std::vector<DFL::Locale::Utf8>& rawDiscoveryScopes() const noexcept;

        /**
         * @brief The manufacturer from the @ref productionSpecifications() if there is one.
         */
        DFL::Locale::Utf8 manufacturer() const;

        /**
         * @brief The model name from the @ref productionSpecifications() if there is one.
         */
        DFL::Locale::Utf8 modelName() const;

        /**
         * @brief The device name (aka friendly name) from the coded attributes (@ref codedStringAttributes()) if there is one.
         */
        DFL::Locale::Utf8 deviceName() const;

    private:
        DFL::Locale::Utf8 productionSpecification(const DFL::Mdib::CodedValue& code) const;

        EndpointReference m_endpointReference;
        AssociatedLocations m_locations;
        DFL::Mdib::CodedValues m_mdsTypes;
        DFL::Mdib::ProductionSpecifications m_productionSpecifications;
        DFL::Mdib::Ext::CodedStringAttributes m_codedStringAttributes;

        std::vector<DFL::Locale::Utf8> m_rawDiscoveryScopes;
};

}
