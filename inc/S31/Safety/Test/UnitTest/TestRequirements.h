#pragma once

#include <gtest/gtest.h>

namespace S31Test::Safety::UnitTest
{

/**
 * @brief Unit tests for \ref S31::Safety::Requirements.
 */
class TestRequirements: public ::testing::Test
{
    protected:
        void testDuplicates();
};

}
