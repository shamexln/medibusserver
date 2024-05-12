#pragma once

#include <S31/Sdc/Private/Common/IWebService.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::Sdc::Impl
{
class DpwsDevice;

/**
 * @brief The Host (also known as Hosting Service) is running under the devices XAddress.
 * @details
 * It supports WS-Discovery Probe request via HTTP (directed probe) as well as
 * WS-Transfer Get to retrieve metadata about all running Hosted Services (e.g., Localization service)
 */
class HostService : public IWebService
{
public:
    explicit HostService(DFL::NotNull<std::shared_ptr<DpwsDevice>> device)
        : m_device{std::move(device)}
    {
    }

    int dispatch(struct soap* soapHandle) override;

private:
    DFL::NotNull<std::shared_ptr<DpwsDevice>> m_device;
};
}  // namespace S31::Sdc::Impl
