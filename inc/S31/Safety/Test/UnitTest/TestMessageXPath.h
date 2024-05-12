#pragma once

#include <gtest/gtest.h>

namespace S31Test::Safety::UnitTest
{

class TestMessageXPath: public ::testing::Test
{
    protected:
        void testConversionToArgumentIndex();
        void testConversionToUtf8();
        void testConversionToMessageXPathExpression();
        void testConversionFromArgumentIndexToMessageXPathExpression();
        void testMismatchedNamespace();
};

}
