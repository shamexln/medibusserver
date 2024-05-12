#pragma once

#include <S31/Utils/Public/Errors.h>

namespace S31::Sdc::Errors
{

/**
 * @brief User disconnected without specified reason.
 * @ingroup S31SdcCommon
 */
struct UserDisconnected: Utils::SpecificError
{
};

/**
 * @brief The relevant part of S31 is about to be destroyed.
 * @details Typically this is caused by shutdown of the process using S31. Users have to ensure that
 * in this case no new 'connection repair' attempts are started.
 * @ingroup S31SdcCommon
 */
struct Shutdown: Utils::SpecificError
{
};

/**
 * @brief There was a problem in communication between SDC communication partners.
 * @details E.g., failed HTTP/S requests.
 * @ingroup S31SdcCommon
 */
struct CommunicationFailure: Utils::SpecificError
{
};

/**
 * @brief Specific (communication) errors from the SSL layer.
 * @ingroup S31SdcCommon
 */
struct SslFailure: Utils::SpecificError
{
};

/**
 * @brief Processing of the data received from the SDC communication partner failed.
 * @details E.g., a metric report content that violates the BICEPS standard.
 * @ingroup S31SdcCommon
 */
struct DataInvalid: Utils::SpecificError
{
};

/**
 * @brief A report from network has a Mdib version with a new sequence.
 * @details In BICEPS this is legal - but this condition cannot be handled by S31. A product
 * using S31 has to handle this in a domain specific way.
 * @ingroup S31SdcCommon
 */
struct MdibSequenceChanged: Utils::SpecificError
{
};

/**
 * @brief An error that does not fall in one of the other categories.
 * @ingroup S31SdcCommon
 */
struct Generic: Utils::SpecificError
{
};


}
