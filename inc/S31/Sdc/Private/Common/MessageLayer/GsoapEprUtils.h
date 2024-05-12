#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>
#include <S31/S31CoreExImp.h>

#include <string>
#include <string_view>

namespace S31::Sdc::Impl
{
class GsoapEpr;

/**
 * \brief Utility functions for \ref S31::Sdc::Impl::GsoapEpr.
 *
 * \ingroup S31SdcCommonWebServices
 */
class S31_CORE_EXPIMP GsoapEprUtils
{
    public:
        static void prepareRequest(soap* soap, const S31::Sdc::Impl::GsoapEpr& remoteEpr, std::string_view action);

        /**
         * @brief Version for one-way messages only.
         * @details
         *
         * Background for MessageID in SOAP header:
         *
         * [WS-Addressing](https://www.w3.org/TR/ws-addr-core/) section [3.2](https://www.w3.org/TR/ws-addr-core/#msgaddrpropsinfoset)
         * specifies the /wsa:MessageID Message Addressing Property:
         * > This OPTIONAL element (whose content is of type xs:anyURI) conveys the [message id] property.
         *
         * Section [3.4](https://www.w3.org/TR/ws-addr-core/#formreplymsg) (Formulating a Reply Message):
         * > This section specifies the WS-Addressing-specific
         * > rules for creating a reply or fault message related to another message.
         *
         * Depending on the case (reply or fault) different rules apply to select the EPR.
         * > In either of the above cases, if the related message lacks a [message id] property, the processor MUST fault.
         *
         * The response message must include
         * > [relationship]: this property MUST include a pair of IRIs as follows;
         * > the relationship type is the predefined reply URI "http://www.w3.org/2005/08/addressing/reply"
         * > and the related message's identifier is the [message id] property value from the message being replied to;
         * > other relationships MAY be expressed in this property
         *
         * The same is stated in [Basic Profile 2.0](http://ws-i.org/profiles/BasicProfile-2.0-2010-11-09.html):
         * > [3.7.11](http://ws-i.org/profiles/BasicProfile-2.0-2010-11-09.html#[message_id]_and_One-Way_Operations) [message id] and One-Way Operations
         * >
         * > When sending a one-way message the SENDER could choose to ignore any possible response - for example, a fault.
         * > However, if the SENDER is interested in receiving those messages,
         * > the SENDER will need to include a [message id] property in the one-way message to ensure
         * > that the response can be successfully transmitted (see
         * > [WS-Addressing 1.0 - %Core](https://www.w3.org/TR/ws-addr-core/),
         * > [Section 3.4](https://www.w3.org/TR/ws-addr-core/#formreplymsg) ).
         *
         * For one-way HTTP messages (WS-Eventing reports for example) there is no requirement
         * for duplicate message detection or reply messages with a wsa:RelatesTo SOAP header block.
         */
        static void prepareHttpOnewayRequest(soap* soap, const S31::Sdc::Impl::GsoapEpr& remoteEpr, std::string_view action);
};

}
