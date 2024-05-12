#pragma once

#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Public/Model/Uri.h>
#include <Framework/Utils/Public/Uri.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Maps \ref DFL::Mdib::CodedValue from CodedValue (e.g., Mds Types) to URN and vice versa.
 * @details The URNs are used for type-based discovery with WS-Discovery scopes.
 * @ingroup S31SdcCommon
 */
class TypeUriMapper
{
    public:
        /**
         * @brief Maps one CodedValue.
         * @details May be used for coded value to type discovery URI.
         * IEEE 11073-10101 coding system OIDs and version are ommited in the resulting URI.
         */
        static DFL::Mdib::Uri toUri(const DFL::Mdib::CodedValue& codedValue);

        /**
         * @brief Extracts a coded Value from a type discovery Uri.
         * @details Can handle if the IEEE 11073-10101 coding system OIDs and version are ommited in the URI.
         */
        static boost::optional<DFL::Mdib::CodedValue> typeUriToCodedValue(const DFL::Net::Uri& typeUri);


};

}
