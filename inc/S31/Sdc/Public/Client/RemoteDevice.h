#pragma once

#include <S31/Nomenclature/Public/Credentials.h>
#include <S31/Sdc/Public/Client/LocalizationClient.h>
#include <S31/Sdc/Public/Client/RemoteDeviceMdibSubject.h>
#include <S31/Sdc/Public/Common/DpwsDeviceMetadata.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/Sdc/Public/Common/MdibAccessSmartPtrTypes.h>
#include <S31/SetService/Public/Client/OperationInvoker.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Config/Public/Attributes.h>
#include <Framework/Mdib/Public/MdibAccess.h>
#include <Framework/Mdib/Public/RemoteMdibAccessSmartPtrTypes.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::Sdc
{

/**
 * @brief %RemoteDevice interface provides access to a remote SDC device.
 * @details Use \ref S31::Sdc::RemoteDevicesProvider to obtain %RemoteDevice instances.
 *
 * The %RemoteDevice interface can be used to e.g. \ref RemoteDevice::mdibAccess() "access MDIB data" that has been received from remote,
 * \ref RemoteDevice::operationInvoker() "invoke set operations" or \ref RemoteDevice::dpwsDeviceMetadata() "receive DPWS metadata".
 * @ingroup S31SdcClient
 */
class S31_CORE_EXPIMP RemoteDevice: public RemoteDeviceMdibSubject
{
    public:
        ~RemoteDevice() override = default;

        /**
         * @brief Returns information item that uniquely identifies the remote device.
         * @details As of DPWS this identifier is a UUID (R0004: A DEVICE SHOULD use a urn:uuid scheme IRI as the [address] property of its Endpoint Reference.)
         */
        virtual const EndpointReference& endpointReference() const = 0;

        /**
         * @deprecated Use \ref S31::Sdc::RemoteDevice::mdibAccess() instead.
         */
        DFL_ATTRIBUTE_DEPRECATED("Use S31::Sdc::RemoteDevice::mdibAccess() instead.")
        virtual DFL::NotNull<DFL::Mdib::MdibAccessSharedPtr> getMdibAccess() const = 0;

        /**
         * @brief Access to trigger remote set operations.
         * @details
         * The SET service is an optional service. In case the the remote device does not provide a SET service a
         * nullptr is returned.
         *
         * See \ref SetService::OperationInvoker.
         * @returns Empty (nullptr) shared pointer in case no SET service is provided.
         */
        [[nodiscard]] virtual std::shared_ptr<SetService::OperationInvoker> operationInvoker() const = 0;

        /**
         * @brief Retrieves the readable remote MDIB.
         */
        virtual DFL::NotNull<S31::Sdc::MdibAccessSharedPtr> mdibAccess() const = 0;

        /**
         * @brief Provides information about the remote device such as model name, manufacturer, serial number, etc.
         */
        virtual Sdc::DpwsDeviceMetadata dpwsDeviceMetadata() const = 0;

        /**
         * @brief Provides information about the remote device certificate such as EKU role information, etc.
         */
        virtual S31::Nomenclature::Credentials credentials() const
        {
            return {};
        }

        /**
         * @brief Provides access to the @ref S31::Sdc::LocalizationClient.
         * @returns Empty (nullptr) shared pointer in case no localization service is provided.
         */
        virtual LocalizationClientPtr localization() const = 0;
};

}
