#pragma once

#include <gtest/gtest.h>

#include <memory>

namespace S31Test::Sdc::UnitTest
{

/**
 * @brief Performs traversal tests for SDC's SET operation invocation states.
 */
class TestSetOperationStateMachine: public ::testing::Test
{
    protected:
        void testValidCombinations();
        void testInvalidCombinations();
        void testReset();
};

}
