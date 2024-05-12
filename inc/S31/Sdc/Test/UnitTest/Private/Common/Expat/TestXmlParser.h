#pragma once

#include <gtest/gtest.h>

namespace S31Test::Sdc::Impl::Expat::UnitTest
{

class TestXmlParser: public ::testing::Test
{
    protected:
        void testParse();
        void testParseText();
        void testCdata();
};

}
