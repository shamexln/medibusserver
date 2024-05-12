#pragma once

#include <Framework/Utils/Test/Private/IsRegularType.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace DFL
{
namespace Utils
{
namespace Test
{
/**
 * @brief Tests if type of given objects conforms to the regular concept.
 *
 * The regular type concept basically states that a given type behaves like an int.
 * Checking if your own type conforms this concept is useful for pod-like types but extremely
 * interesting for resource handling types. To make such types conforming the regular concept
 * several idioms need to be obeyed. We have provided an example of such a type for testing this
 * utility. It can be found in the following file:
 * Framework/Utils/Test/UnitTest/TestIsRegularType.cpp
 *
 * To be able to not only verify the compile time requirements but also the runtime semantics
 * this test needs to be given two objects which are not equal and not default constructed.
 *
 * The concept check is done statically at compiletime.
 * It asserts that the requirements of the std concept regular which are described here:
 * https://en.cppreference.com/w/cpp/concepts/regular are met.
 * That means that the following operations/functions have to be available:
 * - copy_constructible
 * - copy_assingable
 * - move_constructible
 * - move_assignable
 * - swappable
 * - default_constructible
 * - equality_comparable
 *
 * The second part checks at runtime if the copy-ctor, copy-assignment and equality operator
 * implement the correct semantics. The according axioms have been described here
 * http://stepanovpapers.com/DeSt98.pdf by Alexander Stepanov. In short they are:
 * 1. T a = b; assert(a==b);
 * 2. T a; a = b; <=> T a = b;
 * 3. T a = c; T b = c; a = d; assert(b==c);
 * 4. T a = c; T b = c; zap(a); assert(b==c && a!=b);
 *
 * Please read the documentation of what @ref DFL::Utils::Test::zap() does by default and how you can
 * customize it for your type. In any case this test is not a complete replacement for the tested operations.
 * For example it does not tell you if all members of your type are honored in the implementation of the
 * equality operations.
 *
 * @snippet Utils/Test/UnitTest/TestIsRegularType.cpp isRegularType
 *
 * @ingroup Utils
 */
template <class RegularType>
void isRegularType(const RegularType&, const RegularType&);
/**
 * @brief Tests if type of given objects leaves a default constructed object after move.
 *
 * @snippet Utils/Test/UnitTest/TestIsRegularType.cpp isRegularType
 *
 * @ingroup Utils
 */
template <class T>
void isDefaultAfterMove(const T&, const T&);

template <class RegularType>
inline void isRegularType(const RegularType& a, const RegularType& b)
{
    ASSERT_NE(a, b) << "prototypes must be different";
    ASSERT_NE(a, RegularType{}) << "prototype must not be default constructed";
    ASSERT_NE(b, RegularType{}) << "prototype must not be default constructed";

    Impl::IsRegularType<RegularType>{a, b}.run();
}

template <class T>
inline void isDefaultAfterMove(const T& a, const T& b)
{
    ASSERT_EQ(T{}, T{}) << "default constructed objects must be equal";
    ASSERT_NE(a, b) << "prototypes must be different";
    ASSERT_NE(a, T{}) << "prototype must not be default constructed";
    ASSERT_NE(b, T{}) << "prototype must not be default constructed";

    {
        T movedFrom{a};
        const T movedTo{std::move(movedFrom)};
        // NOLINTNEXTLINE(clang-analyzer-cplusplus.Move,bugprone-use-after-move)
        ASSERT_EQ(T{}, movedFrom);
    }
    {
        T movedFrom{};
        const T movedTo{std::move(movedFrom)};
        // NOLINTNEXTLINE(clang-analyzer-cplusplus.Move,bugprone-use-after-move)
        ASSERT_EQ(T{}, movedFrom);
    }
    {
        T movedFrom{a};
        T movedTo{b};
        movedTo = std::move(movedFrom);
        // NOLINTNEXTLINE(clang-analyzer-cplusplus.Move,bugprone-use-after-move)
        ASSERT_EQ(T{}, movedFrom);
    }
    {
        T movedFrom{};
        T movedTo{b};
        movedTo = std::move(movedFrom);
        // NOLINTNEXTLINE(clang-analyzer-cplusplus.Move,bugprone-use-after-move)
        ASSERT_EQ(T{}, movedFrom);
    }
}

}
}
}
