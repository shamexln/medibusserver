#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Interface for SOAP web services.
 *
 * Interface must be implemented by all web services that the DPWS
 * stack should handle. Typically this interface should be
 * generated from \ref gSOAP in the \<name\>Service.h files.
 *
 * Currently (2.8.8) \ref gSOAP does not include the interface in the
 * class definition. That is why this interface must be implemented by
 * the application developer.
 *
 * \ingroup S31SdcDevice
 */
class IWebService
{
    public:
        virtual ~IWebService() noexcept = default;

        /// function get called to dispatch a web service request
        /// for a specific context (soap handle) after parsing the SOAP header
        /// \param[in] soapHandle soap context for incoming web service request
        /// \return Should return 0 (SOAP_OK) if the request was handled.
        ///         Otherwise \ref gSOAP error code.
        virtual int dispatch(struct soap* soapHandle) = 0;

};

}
