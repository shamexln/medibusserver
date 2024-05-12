#pragma once

#include <S31/Sdc/Private/Common/IWebService.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::Sdc::Impl
{

class DpwsDevice;

/**
 * @brief Implementation of WS-Transfer Get operation to retrieve metadata of DPWS devices.
 * @details
 * The meta data of the device contain information about
 * - ThisModel,
 * - ThisDevice and
 * - Relationship with
 *    - Host (Hosting) and
 *    - Hosted service (e.g., localization service)
 *
 * @ingroup S31SdcCommonWebServices
 */
class S31_CORE_EXPIMP TransferService: public IWebService
{
    public:
        explicit TransferService(DFL::NotNull<std::shared_ptr<DpwsDevice>> device);

        int dispatch(struct soap* soapDispatch) override;

    private:
        DFL::NotNull<std::shared_ptr<DpwsDevice>> m_device;
};

}
