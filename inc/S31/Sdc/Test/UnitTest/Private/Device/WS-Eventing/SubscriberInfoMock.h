#pragma once

#include <S31/Sdc/Private/Device/WS-Eventing/SubscriberInfo.h>

namespace S31::Sdc::Impl::Test
{

/**
 * @brief Mock that always has a subscription for a distinguished name.
 * @ingroup S31SdcDevice
 */
class SubscriberInfoMock: public SubscriberInfo
{
    public:
        bool hasSubscriber(const DFL::Crypto::DistinguishedName&) override
        {
            return true;
        }
};

}
