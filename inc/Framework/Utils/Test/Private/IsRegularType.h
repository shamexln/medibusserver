#pragma once

#include <Framework/Utils/Test/Public/Zap.h>

#include <Framework/Config/Public/Config.h>

#include <boost/type_traits/has_equal_to.hpp>
#include <boost/type_traits/has_not_equal_to.hpp>

#include <type_traits>
#include <utility>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace DFL
{
namespace Utils
{
namespace Test
{
namespace Impl
{
template <class RegularType>
class IsRegularType
{
public:
    explicit IsRegularType(
        RegularType,
        RegularType);
    void run();

private:
    void zap(RegularType&);

    // regular-concept
    void defaultConstructible();
    void equalityComparable();
    void moveConstructible();
    void moveAssignable();
    void swappable();
    // regular axioms
    void axiom1_copyConstructible();
    void axiom2_copyAssignable();
    void axiom3_copyDoesNotCreateAliases();
    void axiom4_copyIsDeep();
    // common edge-cases
    void selfAssignable();
    void selfMovable();
    void copyConstructibleWithDefaultCtor();

    const RegularType m_protoOne{};
    const RegularType m_protoTwo{};
};
}
}
}
}

namespace DFL
{
namespace Utils
{
namespace Test
{
namespace Impl
{
template <class RegularType>
inline IsRegularType<RegularType>::IsRegularType(
    RegularType protoOne,
    RegularType protoTwo)
    : m_protoOne{std::move(protoOne)}
    , m_protoTwo{std::move(protoTwo)}
{
    // we do not check on all operations for "nothrow"
    // guarantees since it is not demanded by the
    // regular type concept
    // for example std::list does not provide noexcept
    // move-operations
    static_assert(
        std::is_default_constructible<RegularType>::value,
        "regular types shall be default constructible");
    static_assert(
        std::is_nothrow_destructible<RegularType>::value,
        "regular types shall be nothrow-destructible");
    static_assert(
        std::is_copy_constructible<RegularType>::value,
        "regular types shall be copy-constructible");
    static_assert(
        std::is_move_constructible<RegularType>::value,
        "regular types shall be move-constructible");
    static_assert(
        std::is_copy_assignable<RegularType>::value,
        "regular types shall be copy-assignable");
    static_assert(
        std::is_move_assignable<RegularType>::value,
        "regular types shall be move-assignable");
    static_assert(
        boost::has_equal_to<RegularType>::value,
        "regular types shall be equality-compareable");
    static_assert(
        boost::has_not_equal_to<RegularType>::value,
        "regular types shall be inequality-compareable");
}
template <class RegularType>
inline void IsRegularType<RegularType>::run()
{
    // order is based on required operations of checks
    defaultConstructible();
    equalityComparable();

    axiom1_copyConstructible();
    axiom2_copyAssignable();
    axiom3_copyDoesNotCreateAliases();
    axiom4_copyIsDeep();

    moveConstructible();
    moveAssignable();
    swappable();

    selfAssignable();
    selfMovable();
    copyConstructibleWithDefaultCtor();
}
template <class RegularType>
inline void IsRegularType<RegularType>::zap(RegularType& a)
{
    DFL::Utils::Test::zap(a);
}
template <class RegularType>
inline void IsRegularType<RegularType>::defaultConstructible()
{
    RegularType a{};
    static_cast<void>(a);
}
template <class RegularType>
inline void IsRegularType<RegularType>::equalityComparable()
{
    ASSERT_EQ(m_protoOne, m_protoOne);

    ASSERT_NE(RegularType{}, m_protoOne);
    ASSERT_NE(m_protoOne, RegularType{});

    ASSERT_NE(m_protoTwo, m_protoOne);
    ASSERT_NE(m_protoOne, m_protoTwo);
}
template <class RegularType>
inline void IsRegularType<RegularType>::moveConstructible()
{
    RegularType a{m_protoOne};
#if defined(DFL_CONFIG_COMPILER_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
    ASSERT_NO_THROW(const RegularType b{std::move(a)};); // NOLINT
#if defined(DFL_CONFIG_COMPILER_CLANG)
#pragma clang diagnostic pop
#endif
}
template <class RegularType>
inline void IsRegularType<RegularType>::moveAssignable()
{
    RegularType a{m_protoOne};
    RegularType b{};
    ASSERT_NO_THROW(b = std::move(a);); // NOLINT(cppcoreguidelines-avoid-goto)
}
template <class RegularType>
inline void IsRegularType<RegularType>::swappable()
{
    RegularType a{m_protoOne};
    RegularType b{m_protoTwo};
    using std::swap;
    swap(a, b);
    ASSERT_EQ(a, m_protoTwo);
    ASSERT_EQ(b, m_protoOne);
}
template <class RegularType>
inline void IsRegularType<RegularType>::axiom1_copyConstructible()
{
    // Our first axiom simply says that after constructing a new object a of
    // type T, with an initial value copied from object b, we
    // expect objects a and b to be equal.

    const RegularType b{m_protoOne};

    // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
    const RegularType a{b};
    ASSERT_EQ(a, b);
}
template <class RegularType>
inline void IsRegularType<RegularType>::axiom2_copyAssignable()
{
    // Furthermore, we expect this construction to be equivalent to
    // constructing a with a default constructor and then assigning the
    // value of b to it.

    const RegularType b{m_protoOne};

    RegularType a1{};
    a1 = b;
    // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
    RegularType a2{b};
    ASSERT_EQ(a1, a2);

    // So far, our axioms would be satisfied equally well by a language like
    // C++ which copies values on assignment, or by a language like Lisp
    // which simply copies addresses leaving both names pointing to the same
    // copy of the value.
}
template <class RegularType>
inline void IsRegularType<RegularType>::axiom3_copyDoesNotCreateAliases()
{
    // Our next axiom says that we intend the C++ copy semantics.
    // Here, after assigning the same value to both a and b, we expect to be
    // able to modify a without changing the value of b.

    const RegularType c{m_protoOne};
    const RegularType d{m_protoTwo};

    RegularType a{c};
    // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
    const RegularType b{c};
    a = d;
    ASSERT_EQ(b, c);
}
template <class RegularType>
inline void IsRegularType<RegularType>::axiom4_copyIsDeep()
{
    // In fact, we want an even stronger condition. If zap is an operation
    // which always changes the value of its operand, we expect the
    // following to hold. That is, b and c do not continue to be equal
    // simply because their values were changed along with a’s, but rather
    // because changing a’s value did not change theirs.

    const RegularType c{m_protoOne};

    RegularType a{c};
    // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
    const RegularType b{c};
    zap(a);
    ASSERT_EQ(b, c);
    ASSERT_NE(a, b);
}
template <class RegularType>
inline void IsRegularType<RegularType>::selfAssignable()
{
    RegularType a{m_protoOne};
#if defined(DFL_CONFIG_COMPILER_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wself-assign-overloaded"
#endif
    // NOLINTNEXTLINE(misc-redundant-expression)
    a = a;
#if defined(DFL_CONFIG_COMPILER_CLANG)
#pragma clang diagnostic pop
#endif
    ASSERT_EQ(a, m_protoOne);
}
template <class RegularType>
inline void IsRegularType<RegularType>::selfMovable()
{
    // We had to remove this check.
    // According to ...
    // https://stackoverflow.com/questions/13127455/what-does-the-standard-library-guarantee-about-self-move-assignment
    // the right side maybe in a valid but unspecified state.
    // So selfMoveAssign is not UB but it is definetly not a NOOP as was written
    // here.

    // RegularType a{m_protoOne};
    // a = std::move(a);
    // // NOLINTNEXTLINE(clang-analyzer-cplusplus.Move,bugprone-use-after-move)
    // ASSERT_EQ(a, m_protoOne);
}
template <class RegularType>
inline void IsRegularType<RegularType>::copyConstructibleWithDefaultCtor()
{
    RegularType a{};
    // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
    const RegularType b{a};
    ASSERT_EQ(a, b);
}
}
}
}
}
