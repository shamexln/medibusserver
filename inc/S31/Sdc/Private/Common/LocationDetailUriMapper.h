#pragma once

#include <Framework/Mdib/Public/Model/Context/LocationDetail.h>

#include <boost/optional/optional.hpp>
#include <string>

namespace S31::Sdc::Impl
{

/**
 * @brief Convert between \ref DFL::Mdib::LocationDetail and URI query.
 * @details Implements the "Location Context Query Transformation" from section 9.3.1.2 of SDC (IEEE 11073-20701).
 * @ingroup S31SdcCommon
 */
class LocationDetailUriMapper
{
    public:
        /**
         * @brief Maps to the network URI query.
         */
        static std::string toUriQuery(const DFL::Mdib::LocationDetail& locationDetail);

        /**
         * @brief Extracts location detail from URI (if available).
         */
        static boost::optional<DFL::Mdib::LocationDetail> toLocationDetail(const std::string& locationUri);
};

}
