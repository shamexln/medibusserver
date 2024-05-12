#pragma once

#include <Framework/Crypto/Public/DistinguishedName.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Interface to check if a specific client has subscribed.
 * @ingroup S31SdcDevice
 */
class SubscriberInfo
{
    public:
        virtual ~SubscriberInfo() noexcept = default;

        virtual bool hasSubscriber(const DFL::Crypto::DistinguishedName& distinguishedName) = 0;
};

}
