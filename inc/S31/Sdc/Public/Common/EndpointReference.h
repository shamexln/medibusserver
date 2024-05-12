#pragma once

#include <Framework/Utils/Public/Uri.h>

namespace S31::Sdc
{

/**
 * @brief Endpoint reference as described in WS-Addressing.
 * @details Currently only support for the endpoint reference address.
 *          Reference parameters and metadata are not supported.
 * @ingroup S31SdcCommon
 */
class EndpointReference
{
    public:
        /**
         * @brief Constructor taking the address as first argument.
         */
        explicit EndpointReference(const DFL::Net::Uri& address); // NOLINT(modernize-pass-by-value)

        /**
         * @brief Move constructor taking the address as first argument.
         */
        explicit EndpointReference(DFL::Net::Uri&& address);

        /**
         * @brief Returns the endpoint reference address.
         */
        const DFL::Net::Uri& address() const;

    private:
        DFL::Net::Uri m_address;
};

/**
 * @brief Convenience function to create an \ref EndpointReference instance from \ref DFL::Net::Uri.
 * @ingroup S31SdcCommon
 */
EndpointReference toEpr(DFL::Net::Uri&& eprAddress);

/**
 * @brief Convenience function to create an \ref EndpointReference instance from \ref DFL::Net::Uri.
 * @ingroup S31SdcCommon
 */
EndpointReference toEpr(const DFL::Net::Uri& eprAddress);

/**
 * @brief Convenience function to create an \ref EndpointReference instance from an \c std::string.
 * @details \note As the string is parsed to an \ref DFL::Net::Uri "URI" internally, any
 * formatting issue results in a \c boost::none.
 * @ingroup S31SdcCommon
 */
boost::optional<EndpointReference> toEpr(const std::string& eprAddress);

inline EndpointReference::EndpointReference(const DFL::Net::Uri& address) : // NOLINT(modernize-pass-by-value)
    m_address(address)
{
}

inline EndpointReference::EndpointReference(DFL::Net::Uri&& address) :
    m_address(std::move(address))
{
}

inline const DFL::Net::Uri& EndpointReference::address() const
{
    return m_address;
}

/**
 * @brief Convenience function to create an \ref EndpointReference instance from \ref DFL::Net::Uri.
 * @ingroup S31SdcCommon
 */
inline EndpointReference toEpr(DFL::Net::Uri&& eprAddress)
{
    return EndpointReference{ std::move(eprAddress) };
}

/**
 * @brief Convenience function to create an \ref EndpointReference instance from \ref DFL::Net::Uri.
 * @ingroup S31SdcCommon
 */
inline EndpointReference toEpr(const DFL::Net::Uri& eprAddress)
{
    return EndpointReference{ eprAddress };
}

/**
 * @brief Convenience function to create an \ref EndpointReference instance from \ref DFL::Net::Uri.
 * @ingroup S31SdcCommon
 */
inline boost::optional<EndpointReference> toEpr(const std::string& eprAddress)
{
    if (auto optionalUri = DFL::Net::toUri(eprAddress))
    {
        return EndpointReference{ std::move(*optionalUri) };
    }

    return boost::none;
}

/**
 * @brief Check equality of \ref EndpointReference addresses.
 * @ingroup S31SdcCommon
 */
inline bool addressEquals(const EndpointReference& lhs, const EndpointReference& rhs)
{
    return lhs.address() == rhs.address();
}

/**
 * @brief Comparator to use EndpointReference as key in a std::map
 * @details Compares the strings of the addresses of the EndpointReferences (using <)
 * @ingroup S31SdcCommon
 */
class EprAddressLessCompare
{
public:
    bool operator()(const EndpointReference& lhs, const EndpointReference& rhs) const
    {
        return lhs.address().str() < rhs.address().str();
    }
};

}
