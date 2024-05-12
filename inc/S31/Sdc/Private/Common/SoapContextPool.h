#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>
#include <S31/Sdc/Private/Common/ISoapContextPool.h>
#include <S31/Sdc/Private/Common/SdcMessageObserverRegistry.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/CompilerGenerated.h>
#include <Framework/Utils/Public/NotNull.h>

#include <mutex>
#include <utility>
#include <vector>

namespace S31
{
class CoreConfiguration;
namespace Sdc::Impl
{

class LocalDeviceRegistry;
class ISslHandshakeSemaphore;

/**
 * \brief Pool for struct soap contexts that are used for incoming and outgoing request / SOAP messaging.
 *
 * \ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP SoapContextPool: public ISoapContextPool, public S31::Utils::ObservableSubject<SdcMessageObserver>
{
        DFL_NOT_COPYABLE(SoapContextPool)
    public:
        SoapContextPool();
        explicit SoapContextPool(const DFL::NotNull<std::shared_ptr<CoreConfiguration>>& config);
        ~SoapContextPool() override;

        DFL::NotNull<SoapPtr> getSoapPtr() override;
        DFL::NotNull<SoapPtr> getUdpSoapPtr() override;

        static void returnHandle(DFL::NotNull<struct soap*> nnsoapHandle);

        void setDeviceRegistry(std::weak_ptr<LocalDeviceRegistry> deviceRegistry);

        void setConfiguration(const DFL::NotNull<std::shared_ptr<CoreConfiguration>>& config);

        /// Only for testing.
        void setPeerAuthorizationCallback(const PeerAuthorizationCallback& callback) override;

        void registerObserver(const std::weak_ptr<SdcMessageObserver>& observer) override;
        void unregisterObserver(const std::weak_ptr<SdcMessageObserver>& observer) override;


    private:
        /// \returns an initialized soap handle or throws std::bad_alloc.
        /// All values should be reset to default values as \ref gSOAP's soap_init() does.
        DFL::NotNull<struct soap*> getFreeHandle();
        DFL::NotNull<struct soap*> getFreeUdpHandle();

        static DFL::NotNull<struct soap*> createNewHandle();

        static void freeHandle(struct soap* soapHandle);

        std::weak_ptr<LocalDeviceRegistry> m_deviceRegistry;
        mutable std::mutex m_mutex;

        /// stores all soap handles (free and currently used)
        std::vector<struct soap*> m_handles;
        std::shared_ptr<CoreConfiguration> m_configuration;
        std::shared_ptr<ISslHandshakeSemaphore> m_sslHandshakeSemaphore;
        PeerAuthorizationCallback m_authorizationCallback;
        std::shared_ptr<SdcMessageObserverRegistry> m_sdcMessageObserverRegistry;
};

}
}
