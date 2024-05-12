#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>
#include <S31/S31CoreExImp.h>

#include <cstddef>

namespace S31::Sdc::Impl
{

/**
 * Function to process inbound messages before passing on to gsoap
 * This includes:
 *   - crop inbound SOAP messages to avoid out of memory situations.
 *
 * \ingroup S31SdcCommonWebServices
 */
class S31_CORE_EXPIMP InboundPreFilter
{
    public:

        /**
         * Callback method for \c fpreparerecv member of <tt>struct soap</tt>.
         */
        static int checkInboundBytes(struct soap* soapHandle, const char* buf, std::size_t inputSize);

};

}
