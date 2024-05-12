#pragma once

#include <S31/S31CoreExImp.h>

#include <S31/SetService/Public/Device/InvocationCallbackRegistry.h>

#include <Framework/Chrono/Public/TimeZone.h>
#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/Utf8.h>

#include <memory>

namespace S31::Osf
{

/**
 * @brief Callback type for set time zone.
 * @ingroup S31OsfDevice
 */
using TimeZoneCallback = std::function<void(const DFL::Chrono::TimeZone&,
                                            SetService::SynchronousDeviceTransaction&)>;
/**
 * @brief Callback type for set NTP server.
 * @ingroup S31OsfDevice
 */
using NtpServerCallback = std::function<void(const DFL::Locale::Utf8&,
                                             SetService::SynchronousDeviceTransaction&)>;


class S31_CORE_EXPIMP TimeConfigurationReceiver
{
    public:
        /**
         * @brief Registers the callback for time/clock configuration.
         * @details
         * It registers the given callback in the SetService for the set time zone and set NTP server operation and
         * enables the operation (\ref DFL::Mdib::OperatingMode::Enabled).
         * The operation has to be in the MDIB with correct type and target operation set to
         * \ref DFL::Mdib::ClockDescriptor "ClockDescriptor".
         *
         * @param timeZoneCallback Callback function for set time zone requests.
         * @param ntpServerCallback Callback for set NTP server.
         * @param invocationCallbackRegistry Source for incoming network operation.
         * @param mdibAccess Mdib with patient operation to use.
         */
        TimeConfigurationReceiver(const TimeZoneCallback& timeZoneCallback,
                                  const NtpServerCallback& ntpServerCallback,
                                  const DFL::NotNull<std::shared_ptr<SetService::InvocationCallbackRegistry>>& invocationCallbackRegistry,
                                  const DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr>& mdibAccess);

        TimeConfigurationReceiver(const TimeConfigurationReceiver&) = default;
        TimeConfigurationReceiver& operator=(const TimeConfigurationReceiver&) = default;

        /**
         * @brief Unregisters the callback from SetService and sets MDIB operation to \ref DFL::Mdib::OperatingMode::Disabled.
         */
        ~TimeConfigurationReceiver() noexcept;

    private:
        class Impl;
        DFL::NotNull<std::shared_ptr<Impl>> m_impl;

};

}
