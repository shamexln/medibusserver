#pragma once

#include <S31/Osf/Public/Device/ColorScheme.h>
#include <S31/SetService/Public/Device/InvocationCallbackRegistry.h>

#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>

namespace S31::Osf
{
/**
 * @brief Function wrapper for the setting the color scheme callback.
 *
 * @ingroup S31OsfDevice
 */
using ColorSchemeCallbackFunction = std::function<void(SetService::SynchronousDeviceTransaction&, const DFL::Mdib::Handle& operationHandle, S31::Osf::ColorScheme)>;

/**
 * @brief Device side interface that is responsible for registering callbacks for setting the color scheme.
 *
 * @ingroup S31OsfDevice
 */
class S31_CORE_EXPIMP ColorSchemeDevice
{
        DFL_NOT_COPYABLE(ColorSchemeDevice)

    public:

        ColorSchemeDevice(ColorSchemeDevice&&) = delete;
        ColorSchemeDevice& operator=(ColorSchemeDevice&&) = delete;

        /**
         * @brief Instantiates the ColorSchemeDevice object with callback, invocationCallbackRegistry and local mdib access.
         *
         * @param colorSchemeCallbackFunction The callback function of the set operation for the color scheme.
         * @param invocationCallbackRegistry The registry to register the device side call back for the set string operation.
         * @param localMdibAccess local Mdib access
         */
        ColorSchemeDevice(ColorSchemeCallbackFunction colorSchemeCallbackFunction,
                          const DFL::NotNull<std::shared_ptr<SetService::InvocationCallbackRegistry>>& invocationCallbackRegistry,
                          const DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr>& localMdibAccess);

        /**
         * @brief The destructor unregisters the color scheme mode callback and
         * sets the \ref DFL::Mdib::OperatingMode of the set operation for the color scheme mode to Disabled.
         */
        ~ColorSchemeDevice() noexcept = default;

    private:

        class ColorSchemeDeviceImpl;
        DFL::NotNull<std::shared_ptr<ColorSchemeDeviceImpl>> m_impl;
};

}
