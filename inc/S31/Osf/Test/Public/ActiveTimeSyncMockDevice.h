#pragma once

#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/Sdc/Public/Device/MdibFactory.h>
#include <S31/Sdc/Test/Public/Client/RemoteDeviceMock.h>
#include <S31/Sdc/Test/Public/Client/RemoteDevicesProviderMock.h>
#include <S31/Test/S31Only/Exception.h>

#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Crypto/Public/RandomUuidGenerator.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/Model/CodedValueConstants.h>
#include <Framework/Mdib/Test/Public/TestFactory.h>
#include <Framework/Mdib/Test/Public/MdibWriter.h>

#include <gtest/gtest.h>

#include <boost/optional/optional.hpp>

namespace S31::Osf::Test
{
namespace Handles
{
static const DFL::Mdib::MdsHandle Mds("mds");
static const DFL::Mdib::ClockHandle Clock("clock");
}

/**
 * @brief Helper class for testing to maintain a mock device with a clock
 */
class ActiveTimeSyncMockDevice
{
    public:
        /// Construct device mock
        ActiveTimeSyncMockDevice();

        /// Set or clear the activeSyncProtocol of the clock
        void activeTimeSyncProtocol(boost::optional<DFL::Mdib::CodedValue> activeSyncProtocol);

        /// Register the mock device with a node provider mock
        void registerConnectable(Sdc::Test::RemoteDevicesProviderMock& mockProvider);

        /// The endpoint reference of the mock device
        [[nodiscard]] const Sdc::EndpointReference& endpointReference() const;

    private:
        static void initializeMdib(Sdc::LocalMdibAccess& mdibAccess);
        [[nodiscard]] static Sdc::EndpointReference randomEpr();

        DFL::NotNull<Sdc::LocalMdibAccessSharedPtr> m_mdibAccess;
        DFL::NotNull<std::shared_ptr<Sdc::Test::RemoteDeviceMock>> m_deviceMock;
};

inline ActiveTimeSyncMockDevice::ActiveTimeSyncMockDevice() :
    m_mdibAccess(Sdc::MdibFactory::createLocalSdcMdibAccess(DFL::Mdib::MdibConstraints::allConstraints())),
    m_deviceMock(std::make_shared<Sdc::Test::RemoteDeviceMock>(m_mdibAccess, randomEpr()))
{
    initializeMdib(*m_mdibAccess);
}

void ActiveTimeSyncMockDevice::activeTimeSyncProtocol(boost::optional<DFL::Mdib::CodedValue> activeSyncProtocol)
{
    auto mdib = m_mdibAccess->latestMdib();
    auto clockEntity = mdib->entity(Handles::Clock);
    THROW_IF_NOT(clockEntity);

    auto clockState = DFL::Mdib::getBuilder(clockEntity->state());
    clockState.activeSyncProtocol(std::move(activeSyncProtocol));

    DFL::Mdib::MdibChangeSet changeset;
    changeset.addOneToUpdate(DFL::Mdib::EntityFactory::create(DFL::asNotNull(clockEntity), clockState));

    auto result = m_mdibAccess->writeComponentStates(changeset);
    ASSERT_MDIB_WRITE_SUCCESS(result);
}

inline void ActiveTimeSyncMockDevice::registerConnectable(Sdc::Test::RemoteDevicesProviderMock& mockProvider)
{
    mockProvider.connectableRemoteDevice(m_deviceMock.get());
}

const Sdc::EndpointReference& ActiveTimeSyncMockDevice::endpointReference() const
{
    return m_deviceMock->endpointReference();
}

inline void ActiveTimeSyncMockDevice::initializeMdib(Sdc::LocalMdibAccess& mdibAccess)
{
    DFL::Mdib::MdibChangeSet changeSet;
    changeSet.addOneToInsert(DFL::Mdib::Test::TestFactory::createEntity(Handles::Mds));

    DFL::Mdib::ClockDescriptorBuilder clockDesc;
    clockDesc.type(DFL::Mdib::Test::TestFactory::hashCodedValue(Handles::Clock.string()));
    clockDesc.timeProtocol({DFL::Mdib::CodedValueConstants::MDC_TIME_SYNC_EBWW,
                            DFL::Mdib::CodedValueConstants::MDC_TIME_SYNC_NTPV3,
                            DFL::Mdib::CodedValueConstants::MDC_TIME_SYNC_NTPV4});

    changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(Handles::Clock, clockDesc, Handles::Mds));

    auto result = mdibAccess.writeDescription(changeSet);
    ASSERT_MDIB_WRITE_SUCCESS(result);
}

inline Sdc::EndpointReference ActiveTimeSyncMockDevice::randomEpr()
{
    return Sdc::EndpointReference(DFL::Net::Uri("urn:uuid:" + DFL::Crypto::generateRandomUuidString()));
}

}
