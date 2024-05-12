#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>

#include <cstddef>

namespace S31::Sdc::Impl::Expat
{
class XmlParser;

/**
 * @ingroup S31SdcCommon
 */
class GsoapIntegration
{
    public:
        /**
         * @brief Like gSOAP's function \c soap_get0 and \c soap_get1, but returns the whole buffer and
         * not only the next unicode code point.
         */
        static int getData(struct soap* soapHandle, const char** buffer, std::size_t& len);

        /**
         * @brief Uses custom parser to handle the soap body.
         * @details It has to be called after parsing the soap header before parsing the soap body.
         */
        static int handleExpat(struct soap* soapHandle, XmlParser& parser);


};

}
