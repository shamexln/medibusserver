#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/NotNull.h>

#include <boost/optional/optional.hpp>

#include <memory>
#include <functional>

namespace DFL::Mdib
{
class CodedValue;
class Mdib;
}

namespace S31
{
namespace Sdc
{
class EndpointReference;
class RemoteDevicesSubject;
}

namespace Osf
{
/**
 * @brief Monitor @ref DFL::Mdib::ClockState::activeSyncProtocol() "active time sync protocol" of connected devices
 * @details This utility class provides support for detecting that the active time sync protocol of a
 * connected device is not MDC_TIME_SYNC_NTPV3 or MDC_TIME_SYNC_NTPV4.
 * @ingroup S31OsfClient
 */
class S31_CORE_EXPIMP ActiveTimeSyncProtocolWatcher
{
    public:
        /**
         * @brief Notification that a connected device's active time sync protocol is not MDC_TIME_SYNC_NTPV3 or MDC_TIME_SYNC_NTPV4.
         * @details Caller provides @ref S31::Sdc::EndpointReference that identifies the connected device, the optional @ref DFL::Mdib::CodedValue
         * that identifies the %activeSyncProtocol, (or none if %activeSyncProtocol is not set, or the clock is not unique), and the
         * @ref DFL::Mdib::Mdib from the remote device.
         */
        using ErrorCallback = std::function<void(const Sdc::EndpointReference&,
                                                 const boost::optional<DFL::Mdib::CodedValue>&,
                                                 const DFL::Mdib::Mdib&)>;

        /**
         * @brief Constructor
         */
        ActiveTimeSyncProtocolWatcher(Sdc::RemoteDevicesSubject& nodeProvider,
                                      ErrorCallback errorHandler);

    private:
        class ObserverImpl;
        DFL::NotNull<std::shared_ptr<ObserverImpl>> m_observer;
};

}
}
