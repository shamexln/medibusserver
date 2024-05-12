#pragma once

namespace S31::Sdc::Impl::OutgoingBlockingHttpRequestHelper
{
inline void returnsVoid()
{
}
}

/**
  * @brief For checking the soap handle against nullptr in jobs.
  * @ingroup S31SdcCommon
  */
#define SET_ERROR_AND_RETURN_VALUE_ON_EMPTY_SOAPHANDLE(value) \
do { \
    if (!soapHandle) \
    { \
        this->setOutcomeError(::S31::Sdc::Impl::Errors::NoSoapHandle{}); \
        this->outcomeErrorStream() << "No soap handle (" << this->jobName() << ")"; \
        return value; \
    } \
} while(0) \

/**
  * @brief For checking the soap handle against nullptr in jobs.
  * @ingroup S31SdcCommon
  */
#define SET_ERROR_AND_RETURN_ON_EMPTY_SOAPHANDLE \
    SET_ERROR_AND_RETURN_VALUE_ON_EMPTY_SOAPHANDLE(S31::Sdc::Impl::OutgoingBlockingHttpRequestHelper::returnsVoid())

/**
  * @brief For checking the HttpClientRegistry
  * @ingroup S31SdcCommon
  */
#define SET_ERROR_AND_RETURN_VALUE_ON_EMPTY_HTTP_CLIENT_REGISTRY(value) \
do { \
    if (!clientRegistry) \
    { \
        this->setOutcomeError(::S31::Sdc::Impl::Errors::NoHttpClient{}); \
        this->outcomeErrorStream() << "No HttpClient (" << this->jobName() << ")"; \
        return value; \
    } \
} while(0) \



