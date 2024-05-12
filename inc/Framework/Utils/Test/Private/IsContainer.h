#pragma once

#include <Framework/Utils/Test/Public/IsRegularType.h>

#include <gtest/gtest.h>

#include <algorithm>
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
template <class Container>
struct IterConstruct
{
    template <class Init>
    Container operator()(const Init& init) const
    {
        using std::begin;
        using std::end;
        return Container{begin(init), end(init)};
    }
};

template <class Container>
inline void checkTypes()
{
    static_assert(std::is_same<typename Container::reference,
                               typename Container::value_type&>::value,
                  "reference must be same as value_type&");
    static_assert(std::is_same<typename Container::const_reference,
                               const typename Container::value_type&>::value,
                  "const_reference must be same as const value_type&");

    static_assert(
        std::is_convertible<typename Container::iterator,
                            typename Container::const_iterator>::value,
        "iterator must be convertible to const_iterator");
    static_assert(
        std::is_base_of<
            std::forward_iterator_tag,
            typename std::iterator_traits<
                typename Container::iterator>::iterator_category>::value,
        "iterator must be at least a forward iterator");
    static_assert(
        std::is_base_of<
            std::forward_iterator_tag,
            typename std::iterator_traits<
                typename Container::const_iterator>::iterator_category>::value,
        "const_iterator must be at least a forward iterator");

    static_assert(std::is_signed<typename Container::difference_type>::value,
                  "difference_type must be signed");
    static_assert(
        std::is_same<typename Container::difference_type,
                     typename std::iterator_traits<
                         typename Container::iterator>::difference_type>::value,
        "difference_type must be the same as iterator_traits::difference_type "
        "for iterator");
    static_assert(
        std::is_same<
            typename Container::difference_type,
            typename std::iterator_traits<
                typename Container::const_iterator>::difference_type>::value,
        "difference_type must be the same as iterator_traits::difference_type "
        "for const_iterator");

    static_assert(std::is_unsigned<typename Container::size_type>::value,
                  "size_type must be unsigned");
}

template <class Container, class InputIt>
inline void checkConsistency(const Container& c,
                             const InputIt& first,
                             const InputIt& last)
{
    const auto dist = std::distance(first, last);
    ASSERT_EQ(dist, std::distance(c.begin(), c.end()));
    ASSERT_EQ(dist, std::distance(c.cbegin(), c.cend()));
    ASSERT_EQ(static_cast<typename Container::size_type>(dist), c.size());
    ASSERT_LE(c.size(), c.max_size());
    ASSERT_EQ(dist == 0, c.empty());
    ASSERT_TRUE(std::equal(c.begin(), c.end(), first));
    ASSERT_TRUE(std::equal(c.cbegin(), c.cend(), first));
}

template <class Container>
inline void checkDefaultContainerConsistency()
{
    const std::vector<typename Container::value_type> vec{};
    checkConsistency(Container{}, vec.cbegin(), vec.cend());
}

template <class Container, class InputIt>
inline void checkNonDefaultContainerConsistency(const Container& c,
                                                const InputIt& first,
                                                const InputIt& last)
{
    checkConsistency(c, first, last);
}

template <class Container>
inline void checkSwapMethod(const Container& a, const Container& b)
{
    ASSERT_NE(a, b);
    Container c1{a};
    Container c2{b};
    c1.swap(c2);
    ASSERT_EQ(c1, b);
    ASSERT_EQ(c2, a);
}

template <class Container, class Init>
inline void isContainer(const Container& a,
                        const Container& b,
                        const Init& initA)
{
    ASSERT_NE(a, b) << "prototypes must be different";
    ASSERT_NE(a, Container{}) << "prototype must not be default constructed";
    ASSERT_NE(b, Container{}) << "prototype must not be default constructed";

    checkTypes<Container>();
    checkDefaultContainerConsistency<Container>();
    checkNonDefaultContainerConsistency(a, initA.begin(), initA.end());
    checkSwapMethod(a, b);
    isRegularType(a, b);
}
}
}
}
}
