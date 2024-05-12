#pragma once

#include <boost/static_assert.hpp>

/**
 * @file
 * @brief Contains utilities for making assertion which fail at compile time.
 *
 * These assert macros take compile time expression which lead to either
 * "true" or "false". If a message is provided it can be found in the
 * compiler output if the given expression leads to a compile time "false".
 *
 * The assert macros can be used in various scopes (namespaces, private sections, functions, ...).
 * @snippet Utils/Test/UnitTest/TestStaticAssert.cpp Scopes
 *
 * For being able to compare enum values of different enum types
 * without generating warnings a special macro has been implemented
 * which casts boths values to int and then make the comparison.
 * @snippet Utils/Test/UnitTest/TestStaticAssert.cpp Enums
 *
 * @ingroup Utils
 */
/**
 * @brief Leads to a compile error if given expression leads to a compile time "false"
 * @ingroup Utils
 */
#define DFL_STATIC_ASSERT(expression)           \
    BOOST_STATIC_ASSERT(expression)
/**
 * @brief Same as @ref DFL_STATIC_ASSERT but given msg is included in compiler error message
 * if expression is "false" at compile time.
 * @ingroup Utils
 */
#define DFL_STATIC_ASSERT_MSG(expression, msg)  \
    BOOST_STATIC_ASSERT_MSG(expression, msg)
/**
 * @brief Compares given values with given operator by casting both to int
 * before performing the comparision.
 *
 * This supresses the "incompatible enum values" warning so be sure to use it accordingly.
 *
 * @ingroup Utils
 */
#define DFL_STATIC_ASSERT_INCOMPATIBLE_ENUMS_OP(lhs, op, rhs)   \
    BOOST_STATIC_ASSERT(static_cast<int>(lhs) op static_cast<int>(rhs))
/**
 * @brief See @ref DFL_STATIC_ASSERT_INCOMPATIBLE_ENUMS_OP
 * @ingroup Utils
 */
#define DFL_STATIC_ASSERT_INCOMPATIBLE_ENUMS_EQ(lhs, rhs)   \
    DFL_STATIC_ASSERT_INCOMPATIBLE_ENUMS_OP((lhs), ==, (rhs))
