#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>
#include <S31/SetService/Public/Device/ClientInformation.h>
#include <S31/Sdc/Private/Common/SoapPtr.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/Uri.h>
#include <Framework/Utils/Public/Oids.h>

#include <boost/optional/optional.hpp>

#include <string>
#include <vector>

namespace S31::Sdc::Impl
{

/**
 * \brief General helper functions for soap handling.
 *
 * \ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP SoapUtils
{
    public:
        /**
         * @name soapFault
         * @brief Create are text message for the given fault.
         * @param soapHandle `soap` handle containing a SOAP fault. Cannot be `const` due to gSOAP API limitations. Can be modified.
         * @return text message for logging purposes.
         */
        ///@{
        static std::string soapFault(soap* soapHandle);
        static std::string soapFault(soap& soapHandle);
        static std::string soapFault(DFL::NotNull<soap*> soapHandle);
        ///@}

        /**
         * @brief Checks that the peer has the specified roles.
         * @details If peer has not the required roles then a soap fault is set and a log entry is written.
         * @return SOAP_OK if each role is ok or the given roles container is empty, an error code otherwise.
         */
        static int checkThatPeerHasRoles(soap* soapHandle, const DFL::Oids& roles);

        /**
         * @brief Converts the client information from gSOAP soap context to
         * domain model.
         */
        static SetService::ClientInformation clientInformation(const soap* soapHandle);

        /**
         * @brief Get the a part of @e buf around bufidx from the soap handle (for logging).
         *
         * @details Returns e.g. "buflen: 5 bufidx: 0 data: 12345" (with buf = "12345"),
         */
        static std::string bufSnippet(const soap* soapHandle, size_t maxLength = 500);

        /**
         * @brief Get the start segment of @e buf from the soap handle (for logging).
         */
        static std::string bufStart(const soap* soapHandle, std::size_t maxLength = 500);

        /**
         * @brief Returns the message ID from the header or '@<no message ID@>'.
         */
        static std::string messageID(const soap* soapHandle);

        /**
         * @brief Returns the To EPR Address from the header or boost::none.
         */
        static boost::optional<DFL::Net::Uri> toUri(const soap* soapHandle);

};

}
