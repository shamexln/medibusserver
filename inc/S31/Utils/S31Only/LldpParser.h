#pragma once

#include <S31/Utils/Private/S31UtilsExImp.h>

#include <Framework/Mdib/Public/Model/Context/LocationDetail.h>

#include <map>

namespace S31
{
/**
 * @brief Helper class to dissect LLDP Ethernet packets.
 * @details
 * More details about LLDP are available at https://wiki.wireshark.org/LinkLayerDiscoveryProtocol
 * \ingroup S31Utils
 */
class S31_UTILS_EXPIMP LldpParser
{
    public:
        /**
         * Create this class with the received LLDP packet as a parameter, will be parsed and made accessible.
         */
        LldpParser(const unsigned char* rawData, unsigned int size);
        virtual ~LldpParser() = default;

        /**
         * @brief Returns the value of the given Location Field (civic part).
         * return empty string when not set
         */
        std::string getLocationField (unsigned int number);

        /**
         * @brief Interprets the received LLDP information as location.
         */
       DFL::Mdib::LocationDetail asLocation();
       /** @brief Returns true if valid in general (syntax). */
       bool isValidPacket() const;
       /** @brief Returns true if this is usable (content sufficient for our location needs). */
       bool hasLocation() const;
    private:
       bool m_valid{false};
       bool m_usable{false};
       std::map<unsigned int, std::string> m_fields;
       bool checkOneEntry (const unsigned char* data, unsigned char tlv_type, unsigned short tlv_length);
       bool checkMED      (const unsigned char* data, unsigned short length);
       bool parseLocation (const unsigned char* data, unsigned short length);

};

} /* namespace S31 */
