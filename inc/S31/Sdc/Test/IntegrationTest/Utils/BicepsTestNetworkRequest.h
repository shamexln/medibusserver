#pragma once

#include <S31/Sdc/Private/Common/MessageLayer/IncomingNetworkRequest.h>

namespace S31::Sdc
{
namespace Impl
{
class IWebService;
}

namespace Test
{

/**
 * @brief Thin wrapper implementation of \ref S31::Sdc::Impl::IncomingNetworkRequest for test
 */
class BicepsTestNetworkRequest: public S31::Sdc::Impl::IncomingNetworkRequest
{
    public:
        BicepsTestNetworkRequest(DFL::NotNull<S31::Sdc::Impl::SoapPtr> soapPtrIn, S31::Sdc::Impl::IWebService& service);
};

}
}
