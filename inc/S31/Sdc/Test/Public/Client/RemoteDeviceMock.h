#pragma once

#include <S31/Sdc/Private/Client/RemoteMdibAccess.h>
#include <S31/Sdc/Public/Client/RemoteDevice.h>
#include <S31/Sdc/Public/Client/RemoteDeviceMdibObserver.h>
#include <S31/Sdc/Public/Common/DpwsDeviceMetadata.h>
#include <S31/Sdc/Public/Common/MdibAccessSmartPtrTypes.h>
#include <S31/Sdc/Test/Public/Common/MdibAccessMock.h>
#include <S31/SetService/Public/Client/OperationInvoker.h>
#include <S31/SetService/Test/Public/Client/OperationInvokerMock.h>
#include <S31/Utils/Public/ObservableSubject.h>

#include <Framework/Mdib/Public/MdibObserver.h>
#include <Framework/Mdib/Test/Public/TestFactory.h>

#include <string>
#include <utility>

namespace S31::Sdc::Test
{

/**
 * @brief Mock implementation for \ref S31::Sdc::RemoteDevice.
 * @ingroup S31SdcClient
 */
class RemoteDeviceMock: public S31::Sdc::RemoteDevice, public std::enable_shared_from_this<RemoteDeviceMock>
{
        DFL_NOT_COPYABLE(RemoteDeviceMock)

    public:
        RemoteDeviceMock();

        explicit RemoteDeviceMock(EndpointReference urn);

        RemoteDeviceMock(DFL::NotNull<S31::Sdc::MdibAccessSharedPtr> mdibAccess, EndpointReference urn);

        RemoteDeviceMock(DFL::NotNull<S31::Sdc::MdibAccessSharedPtr> mdibAccess,
                         EndpointReference urn,
                         const DFL::NotNull<std::shared_ptr<S31::SetService::OperationInvoker>>& operationInvoker);

        const EndpointReference& endpointReference() const override;

        DFL::NotNull<DFL::Mdib::MdibAccessSharedPtr> getMdibAccess() const override;

        std::shared_ptr<SetService::OperationInvoker> operationInvoker() const override;
        DFL::NotNull<std::shared_ptr<SetService::Test::OperationInvokerMock>> operationInvokerMock() const;

        DFL::NotNull<S31::Sdc::MdibAccessSharedPtr> mdibAccess() const override;

        Sdc::DpwsDeviceMetadata dpwsDeviceMetadata() const override;

        void registerObserver(const std::weak_ptr<S31::Sdc::RemoteDeviceMdibObserver>& observer) override;

        void unregisterObserver(const std::weak_ptr<S31::Sdc::RemoteDeviceMdibObserver>& observer) override;

        LocalizationClientPtr localization() const override;

    private:
        /**
         * @ingroup S31SdcClient
         */
        class MdibChangesBroker: public DFL::Mdib::MdibObserver
        {
            public:
                explicit MdibChangesBroker(const std::shared_ptr<S31::Sdc::RemoteDevice>& node);
                void onChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib,
                              const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes,
                              DFL::Mdib::MdibChangeType changeType) override;
                void registerObserver(const std::weak_ptr<S31::Sdc::RemoteDeviceMdibObserver>& observer);
                void unregisterObserver(const std::weak_ptr<S31::Sdc::RemoteDeviceMdibObserver>& observer);

            private:
                std::weak_ptr<S31::Sdc::RemoteDevice> m_node;
                S31::Utils::ObservableSubjectDelegate<S31::Sdc::RemoteDeviceMdibObserver> m_mdibChangesObservable;
        };

        EndpointReference m_urn;
        DFL::NotNull<S31::Sdc::MdibAccessSharedPtr> m_mdibAccess;
        DFL::NotNull<std::shared_ptr<SetService::Test::OperationInvokerMock>> m_operationInvoker;
        std::shared_ptr<MdibChangesBroker> m_mdibObserver;

        static DFL::NotNull<std::shared_ptr<S31::Sdc::MdibAccess>> createMdibAccess() ;
};

inline RemoteDeviceMock::RemoteDeviceMock() :
        m_urn(EndpointReference(DFL::Net::Uri("urn:uuid:ba5dc263-3f74-4dca-bd2b-afcae5999490"))), // random, but fixed UUID if none is defined on construction
        m_mdibAccess(createMdibAccess()),
        m_operationInvoker(DFL::asNotNull(std::make_shared<S31::SetService::Test::OperationInvokerMock>()))
{
}

inline RemoteDeviceMock::RemoteDeviceMock(EndpointReference urn) :
        m_urn(std::move(urn)),
        m_mdibAccess(createMdibAccess()),
        m_operationInvoker(DFL::asNotNull(std::make_shared<S31::SetService::Test::OperationInvokerMock>()))
{
}

inline RemoteDeviceMock::RemoteDeviceMock(DFL::NotNull<S31::Sdc::MdibAccessSharedPtr> mdibAccess, EndpointReference urn) :
        m_urn(std::move(urn)),
        m_mdibAccess(std::move(mdibAccess)),
        m_operationInvoker(DFL::asNotNull(std::make_shared<S31::SetService::Test::OperationInvokerMock>()))
{
}

inline RemoteDeviceMock::RemoteDeviceMock(DFL::NotNull<S31::Sdc::MdibAccessSharedPtr> mdibAccess,
                                          EndpointReference urn,
                                          const DFL::NotNull<std::shared_ptr<S31::SetService::OperationInvoker>>& operationInvoker) :
        m_urn(std::move(urn)),
        m_mdibAccess(std::move(mdibAccess)),
        m_operationInvoker(DFL::asNotNull(std::dynamic_pointer_cast<S31::SetService::Test::OperationInvokerMock>(operationInvoker.get())))
{
}

inline const EndpointReference& RemoteDeviceMock::endpointReference() const
{
    return m_urn;
}

inline DFL::NotNull<DFL::Mdib::MdibAccessSharedPtr> RemoteDeviceMock::getMdibAccess() const
{
    return m_mdibAccess;
}

inline DFL::NotNull<S31::Sdc::MdibAccessSharedPtr> RemoteDeviceMock::mdibAccess() const
{
    return m_mdibAccess;
}

inline DFL::NotNull<std::shared_ptr<SetService::Test::OperationInvokerMock>> RemoteDeviceMock::operationInvokerMock() const
{
    return m_operationInvoker;
}

inline std::shared_ptr<SetService::OperationInvoker> RemoteDeviceMock::operationInvoker() const
{
    return m_operationInvoker.get();
}

inline Sdc::DpwsDeviceMetadata RemoteDeviceMock::dpwsDeviceMetadata() const
{
    return {};
}

inline void RemoteDeviceMock::registerObserver(const std::weak_ptr<S31::Sdc::RemoteDeviceMdibObserver>& observer)
{
    if (!m_mdibObserver)
    {
        m_mdibObserver = std::make_shared<MdibChangesBroker>(shared_from_this());
        m_mdibAccess->registerObserver(m_mdibObserver);
    }
    m_mdibObserver->registerObserver(observer);
}

inline void RemoteDeviceMock::unregisterObserver(const std::weak_ptr<S31::Sdc::RemoteDeviceMdibObserver>& observer)
{
    m_mdibObserver->unregisterObserver(observer);
}

inline LocalizationClientPtr RemoteDeviceMock::localization() const
{
    return nullptr;
}

inline RemoteDeviceMock::MdibChangesBroker::MdibChangesBroker(const std::shared_ptr<S31::Sdc::RemoteDevice>& node) :
        m_node(node)
{
}

inline void RemoteDeviceMock::MdibChangesBroker::onChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib,
                                                          const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes,
                                                          DFL::Mdib::MdibChangeType changeType)
{
    if (auto node = m_node.lock())
    {
        m_mdibChangesObservable.notify([&](S31::Sdc::RemoteDeviceMdibObserver& observer)
        {
            observer.onChange(node, mdib, changes, changeType);
        });
    }
}

inline void RemoteDeviceMock::MdibChangesBroker::registerObserver(const std::weak_ptr<S31::Sdc::RemoteDeviceMdibObserver>& observer)
{
    m_mdibChangesObservable.registerObserver(observer);
}

inline void RemoteDeviceMock::MdibChangesBroker::unregisterObserver(const std::weak_ptr<S31::Sdc::RemoteDeviceMdibObserver>& observer)
{
    m_mdibChangesObservable.unregisterObserver(observer);
}

inline DFL::NotNull<std::shared_ptr<S31::Sdc::MdibAccess>> RemoteDeviceMock::createMdibAccess()
{
    return DFL::asNotNull(std::make_shared<S31::Sdc::Test::MdibAccessMock>());
}

}
