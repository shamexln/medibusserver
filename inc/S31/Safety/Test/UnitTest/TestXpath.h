#pragma once

#include <gtest/gtest.h>

namespace S31Test::Safety::UnitTest
{

class TestXpath: public ::testing::Test
{
    protected:
        void testEncode();
};

}
