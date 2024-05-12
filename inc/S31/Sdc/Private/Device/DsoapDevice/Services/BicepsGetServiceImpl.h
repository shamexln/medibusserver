#pragma once

#include <Framework/Mdib/Public/LatestMdibSmartPtrTypes.h>
#include <Framework/Utils/Public/CompilerGenerated.h>

#include <memory>

#include <S31/Gsoap/S31Only/generated/gsoap/soapGetServiceBindingService.h>

namespace DFL::Mdib
{
class Mdib;
}
namespace S31::Sdc::Impl
{

/**
 * @brief Implementation of BicepsGetService.
 *
 * @details It is required as a separate class for unit testing.
 *
 * @ingroup S31SdcDevice
 */
class BicepsGetServiceImpl: private GetServiceBindingService
{
        // gSOAP assign and copy do not work as expected (Coverity findings)
        DFL_NOT_COPYABLE(BicepsGetServiceImpl)
    public:
        BicepsGetServiceImpl(struct soap* soapHandle, DFL::Mdib::LatestMdibWeakPtr latestMdib);

        int GetMdState(_msg__GetMdState* request, _msg__GetMdStateResponse& response) override;

        int GetMdDescription(_msg__GetMdDescription* request, _msg__GetMdDescriptionResponse& response) override;

        int GetMdib(_msg__GetMdib* request, _msg__GetMdibResponse& response) override;

        int dispatch() override;
        int dispatch(struct soap* soapDispatch) override;

    private:
        DFL::Mdib::LatestMdibWeakPtr m_latestMdib;

};

}
