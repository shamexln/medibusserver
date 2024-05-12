#pragma once

#include <gtest/gtest.h>

namespace S31Test::Sdc::UnitTest
{

class TestLocationDetailUriMapper: public ::testing::Test
{
    protected:
        void testRoundTripMapping();
        void testUriParsing();
};

}
