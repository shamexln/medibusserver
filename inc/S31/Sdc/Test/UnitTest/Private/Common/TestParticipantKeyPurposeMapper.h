#pragma once

#include <gtest/gtest.h>

namespace S31Test::Sdc::UnitTest
{

class TestParticipantKeyPurposeMapper: public ::testing::Test
{
    protected:

        void testOidToUri();
        void testUriToOid();
        void testRoundTrip();
};

}
