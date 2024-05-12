#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/NotNull.h>

#include <map>
#include <memory>
#include <mutex>

namespace S31::Sdc::Impl
{
class DpwsDevice;

/**
 * @brief Stores shared_ptr to all local DPWS Devices of a dSOAP instance.
 *
 * \ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP LocalDeviceRegistry
{
    public:
        using DpwsDevicePtr = DFL::NotNull<std::shared_ptr<DpwsDevice>>;
        using DpwsDevicePtrMap = std::map<std::string, DpwsDevicePtr>;

        LocalDeviceRegistry();
        ~LocalDeviceRegistry();

        void insertDevice(DpwsDevicePtr device);
        void removeDevice(const std::string& epr);

        /// \returns A DpwsDevice object or an empty shared_ptr if no local device was found.
        std::shared_ptr<DpwsDevice> getDeviceForEpr(const std::string& epr) const;
        DpwsDevicePtrMap getDevicesMap() const;

    private:
        mutable std::mutex m_mutex;
        DpwsDevicePtrMap m_localDevices;
};

}
