#pragma once

#include <Framework/Utils/Private/Iterator.h>
#include <Framework/Utils/Private/Tuple.h>

#include <boost/mp11/tuple.hpp>

#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include <iterator>
#include <type_traits>
#include <vector>

namespace DFL
{
namespace Utils
{
namespace Test
{
namespace Impl
{
template <class A, class Tuple>
inline auto createTestObjects(Tuple&& a, Tuple&& b) -> std::vector<A>
{
    using TT = typename std::remove_reference<Tuple>::type;
    constexpr std::size_t Size = StdExt::Impl::tuple_size<Tuple>::value;

    std::vector<TT> params{};
    params.reserve(Size);
    StdExt::Impl::slide(std::forward<Tuple>(a),
                        std::forward<Tuple>(b),
                        std::back_inserter(params));

    std::vector<A> as{};
    as.reserve(Size);
    std::copy(std::make_move_iterator(std::begin(params)),
              std::make_move_iterator(std::end(params)),
              StdExt::Impl::back_emplacer(as));

    return as;
}
}
/**
 * @brief Converts arguments into a tuple.
 *
 * @snippet Utils/Test/UnitTest/TestEqOpFor.cpp TestEqualityOp
 *
 * @ingroup Utils
 */
template <class A, class... Args>
inline constexpr auto ctorParamsFor(Args&&... args)
    -> decltype(std::make_tuple(std::forward<Args>(args)...))
{
    static_assert(
        std::is_constructible<A, Args&&...>::value,
        "class A shall be constructible from given ctor parameter types");
    return std::make_tuple(std::forward<Args>(args)...);
}
/**
 * @brief Tests if all members of a type are considered in the implementation of
 * == and != operator.
 *
 * ToBeTested is the class which == and != operators shall be tested and the
 * tuples given to 'with' are used to construct instances of that type. These
 * instances then are compared using the according operators and if an
 * unexpected result appears an according \::testing::AssertionResult is
 * returned.
 *
 * This utility assumes that all members which shall be checked in the operators
 * can be injected into the constructor. For example, suppose there is this
 * ctor:
 * @snippet Utils/Test/UnitTest/MoveOnlyType.h CtorMoveOnlyType
 * To verify that all members are honored in the equality operator one would
 * have to construct an origin instance and then construct N instances where
 * each of them differs in construction by only one parameter.
 * @snippet Utils/Test/UnitTest/TestEqOpFor.cpp MoveOnlyTypeInstances
 * Then one would loop over those instances and compare them against origin.
 * @snippet Utils/Test/UnitTest/TestEqOpFor.cpp MoveOnlyTypeComparisons
 * This is tedious and error prone. Thus with the usage of this utility
 * one just has to write this one-liner.
 * @snippet Utils/Test/UnitTest/TestEqOpFor.cpp TestEqualityOp
 * This will construct an origin from the first parameter and use the second one
 * to generate all further instances which will then be compared against the
 * origin instance. One important note though. This utility might also fail if
 * the constructor parameters are configured like this:
 * @snippet Utils/Test/UnitTest/TestEqOpFor.cpp IncorrectParams
 * Each value of the second parameter set has to be different from the first
 * one. This is not checked by this function because it would require all
 * parameter types to be equality comparable to compile and in case of reference
 * types (e.g. pointer) this semantic might be even wrong.
 *
 * @ingroup Utils
 */
template <class ToBeTested>
class EqOpFor
{
public:
    /**
     * @brief Takes two parameter tuples to construct test objects from and
     * returns either an testing::AssertionFailure or
     * testing::AssertionSuccess.
     */
    template <class Tuple>
    static auto with(Tuple ctorParamsOrigin, Tuple ctorParamsPermute)
        -> ::testing::AssertionResult
    {
        // all the algorithm used compile with move only types just fine
        // the problem is that creating the test objects requires copying
        // the given ctor parameters,
        // otherwise some test objects are created with a moved from parameter
        // value
        // possible solution for this problem could be PCSWORK-6333
        static_assert(std::is_copy_constructible<Tuple>::value,
                      "all parameters in tuple must be copyable");

        const auto& origin =
            boost::mp11::construct_from_tuple<ToBeTested>(ctorParamsOrigin);
        // NOLINTNEXTLINE(misc-redundant-expression)
        if (!(origin == origin))
        {
            return ::testing::AssertionFailure()
                   << origin << " was not equal to itself";
        }
        // NOLINTNEXTLINE(misc-redundant-expression)
        if (origin != origin)
        {
            return ::testing::AssertionFailure()
                   << origin << " was unequal to itself";
        }
        const auto& testObjs =
            ::DFL::Utils::Test::Impl::createTestObjects<ToBeTested>(
                ctorParamsOrigin,
                ctorParamsPermute);

        for (const auto& testObj : testObjs)
        {
            if (origin == testObj)
            {
                return ::testing::AssertionFailure()
                       << origin << " was equal to " << testObj;
            }
            if (!(origin != testObj))
            {
                return ::testing::AssertionFailure()
                       << origin << " was not unequal to " << testObj;
            }
        }
        return ::testing::AssertionSuccess();
    }
};
}
}
}
