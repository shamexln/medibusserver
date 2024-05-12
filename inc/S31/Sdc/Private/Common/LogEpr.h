#pragma once

#include <S31/Sdc/Public/Common/EndpointReference.h>

#include <string>

namespace S31::Sdc::Impl
{

/**
 * @brief Helper function to create an endpoint reference prefix string.
 * @details To be used to prefix log messages that belong to a specific endpoint.
 * @ingroup S31SdcCommon
 */

inline std::string logEpr(const EndpointReference& epr)
{
    return "(" + epr.address().str() + ") ";
}

}
