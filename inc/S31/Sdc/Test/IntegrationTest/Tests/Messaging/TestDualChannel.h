#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>
#include <S31/Safety/Public/DualChannel.h>

#include <gtest/gtest.h>

#include <memory>

namespace S31::Sdc::Impl
{
class SoapContextPool;

namespace Test
{

class TestDualChannel: public ::testing::Test
{
    protected:

        void testDualChannelWithValidSha1();
        void testDualChannelWithInvalidSha1();
        void testDualChannelWithInvalidReferenceId();
        void testSerialization();

        void SetUp() override;
        void TearDown() override;
    private:
        void checkOutgoingDualChannel(const std::string& refId,
                                      const std::string& value,
                                      const std::string& expectedB64Sha1);
        void checkIncomingDualChannel(const std::string& refId,
                                      const std::string& value,
                                      const Safety::DualChannelId& expectedRefId,
                                      const std::string& b64Sha1,
                                      bool expectedCheckResult);

        void prepareOutgoingMessage(struct soap* sHandle, const std::string& refId, const std::string& value);
        void checkOutgoingMessageHeader(struct soap* sHandle,
                                        const std::string& refId,
                                        const std::string& expectedB64Sha1);

        void prepareIncomingMessageHeader(struct soap* sHandle, const std::string& refId, const std::string& b64Sha1);
        void checkIncomingMessage(struct soap* sHandle,
                                  const Safety::DualChannelId& refId,
                                  const std::string& value,
                                  bool expectedResult);
        std::shared_ptr<SoapContextPool> m_soapPool;
};

}

}
