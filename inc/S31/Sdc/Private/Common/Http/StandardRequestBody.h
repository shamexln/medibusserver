#pragma once

#include <S31/Sdc/Private/Common/Http/CreateRequestBody.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Standard function to create a Http Request Body, simply returns the body as is.
 * @details
 * Used in Http Request messages where the content of the body does not depend on details
 * of the connection itself (which is typically the case).
 * @ingroup S31SdcCommon
 */
inline CreateRequestBody StandardBody(std::string body)
{
    return [body = std::move(body)](const ConnectionContext& /* cc */) { return body; };
}

}
