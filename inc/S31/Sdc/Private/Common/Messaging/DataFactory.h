#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>
#include <S31/S31CoreExImp.h>

#include <memory>
#include <optional>
#include <string>

namespace S31::Sdc::Impl
{
/**
 * @brief Wraps \ref gSOAP soap_new_...() function with additional parameters.
 *
 * \ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP DataFactory
{
    public:

        /**
         * @name std::string allocation
         */
        ///@{
        static std::optional<std::string> stdStringIfNotEmpty(const std::string& data);
        static char* strdup(struct soap* soapHandle, const char* str);
        static char* strdup(struct soap* soapHandle, const std::string& data);
        ///@}

};

}
