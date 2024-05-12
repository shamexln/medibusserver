#pragma once

#include <Framework/Mdib/Public/Model/Component/ProductionSpecification.h>
#include <Framework/Mdib/Public/Model/ExtensionKnown/CodedStringAttribute.h>
#include <Framework/Utils/Public/Uri.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Maps device ProductionSpecifications (such as ModelName and Manufacturer) or CodedAttributes into URIs and vice versa
 * @details The URNs are used for discovery with WS-Discovery scopes.
 *
 * Production Specifications mapping conforms to the following Extended Backus-Naur Form:
 *  Scheme ::= 'sdc.mds.prodspec'
 *  Char ::= unreserved | escaped
 *  CharSequenceNz ::= Char { Char }
 *  CodingSystem ::= CharSequenceNz
 *  CodingSystemVersion ::= CharSequenceNz
 *  Code ::= CharSequenceNz
 *  CodedValue ::= Code [ ',' CodingSystem [ ',' CodingSystemVersion ] ]
 *  Root ::= CharSequenceNz
 *  Extension ::= CharSequenceNz
 *  InstanceIdentifier ::= Root [ ',' Extension ]
 *  ProductionSpec ::= { Char }
 *  SpecType ::= CodedValue
 *  ComponentId ::= InstanceIdentifier
 *  ProductionSpecification ::= ProductionSpec ':' SpecType [ ':' ComponentId ]
 *  MdsProductionSpecification ::= Scheme ':' ProductionSpecification
 *
 * Note: For ProductionSpecifications InstanceIdentifier mapping is added for completeness but currently not used.
 *
 *  CodedAttribute mapping conforms to the following Extended Backus-Naur Form:
 *  Scheme ::= 'sdc.mds.attr'
 *  Char ::= unreserved | escaped
 *  CharSequenceNz ::= Char { Char }
 *  CodingSystem ::= CharSequenceNz
 *  CodingSystemVersion ::= CharSequenceNz
 *  Code ::= CharSequenceNz
 *  CodedValue ::= Code [ ',' CodingSystem [ ',' CodingSystemVersion ] ]
 *  AttributeValue ::= { Char }
 *  AttributeCode ::= CodedValue
 *  Attribute ::=  AttributeValue ':'  AttributeCode
 *  MdsAttribute ::= Scheme ':' Attribute
 *
 * @ingroup S31SdcCommon
 */
class DeviceInfoUriMapper
{
    public:
        /**
         * @brief Maps ProductionSpecification to a uri
         * @details production specification currently pulled from Mds:Metadata, NOT Mds:ProductionSpecification
         */
        static DFL::Mdib::Uri toUri(const DFL::Mdib::CodedValue& codedVal, const DFL::Locale::Utf8& productionSpec);

        /**
         * @brief Maps a CodedAttribute extension to a uri
         */
        static DFL::Mdib::Uri toUri(const DFL::Mdib::Ext::CodedStringAttribute& codedAttribute);

        /**
         * @brief Extracts Mds ProductionSpecification information from the context-based discovery.
         */
        static boost::optional<DFL::Mdib::ProductionSpecification> uriToProductionSpec(const DFL::Net::Uri& productionSpecUri);

        /**
         * @brief Extracts a CodedAttribute from from the context-based discovery.
         */
        static boost::optional<DFL::Mdib::Ext::CodedStringAttribute> uriToCodedAttribute(const DFL::Net::Uri& codedAttributeUri);
};

}
