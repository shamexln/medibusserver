#pragma once

namespace S31::Sdc::Impl
{

/**
 * S31-specific SOAP error codes.
 *
 * Unscoped enum to allow the error codes to be used in the same way as other gSOAP errors.
 *
 * @ingroup S31SdcCommon
 */
enum SoapError : int
{
    SOAP_INBOUND_MSG_TOO_LARGE = 600,
    SOAP_LZ4_DECOMPRESSION_EOM = 601,
};

/**
 * Return the string description of a given \ref SoapError
 *
 * @ingroup S31SdcCommon
 */
const char* getSoapErrorString(int error);

}
