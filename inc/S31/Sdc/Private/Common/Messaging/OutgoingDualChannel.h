#pragma once

#include <S31/Safety/Public/DualChannelHash.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/CompilerGenerated.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapStub.h>

#include <memory>

namespace S31::Sdc::Impl
{

/**
 * @brief Appends dual-channel information to outgoing SOAP header
 *
 * @details
 * General usage
 * =============
 *
 * - Create an instance with valid soap handle
 * - Use OutgoingDualChannel::addDcValue() to append dual-channel values to the header
 *
 * Please note that dual-channel values are added as Base64 encoded SHA1 values. Other formats are not supported!
 *
 * \ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP OutgoingDualChannel
{
        DFL_NOT_COPYABLE(OutgoingDualChannel)
    public:
        /*!
         * \brief Constructor.
         *
         * - Checks existence of a safety SOAP header element and creates one if necessary
         * - Checks existence of dual-channel SOAP header element and creates one if necessary
         *
         * @param soapHandle Required to get access to SOAP header
         */
        explicit OutgoingDualChannel(struct soap* soapHandle);

        /*!
         * \brief Appends dual-channel values to the SOAP header.
         *
         * The dual-channel value must already be encoded in the target format (e.g., hex representation of SHA1 hash).
         *
         * @param referencedSelector The selector that points to the corresponding dual-channel XPath expression.
         * @param dcRepresentation The dual channel representation that is already encoded.
         */
        void addDcValue(const std::string& referencedSelector, const Safety::DualChannelHash& dcRepresentation);

    private:
        struct soap* m_soapHandle;
        std::shared_ptr<si__T_USCOREDualChannel> m_dualChannel;

};

}
