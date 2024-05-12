#pragma once

#include <boost/type_traits/has_not_equal_to.hpp>

#include <type_traits>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace DFL
{
namespace Utils
{
namespace Test
{
/**
 * @brief Modifies given object.
 *
 * Used inside the @ref DFL::Utils::Test::isRegularType to create modified objects. 
 * @ref DFL::Utils::Test::Zapper can be specialized to customize what zap does.
 * Check @ref DFL::Utils::Test::Zapper for an example.
 *
 * @ingroup Utils
 */
template<class T>
void zap(T& zapMe);
/**
 * @brief Customization point for implementing a zapper for your own type.
 *
 * Example:
 * @snippet Framework/Utils/Test/UnitTest/TestIsRegularType.cpp ZapperExample
 * The default behaviour just assigns a default constructed instance to the
 * given object.
 *
 * @ingroup Utils
 */
template<class T>
class Zapper
{
public:
    /**
     * @brief Assigns default constructed instance to given object.
     */
    void operator()(T& zapMe);
};

template <class T>
inline void Zapper<T>::operator()(T& zapMe)
{
    // consider specializing Zapper for your type if you get a compile error
    // here see Zapper<ns::RegularType> in TestIsRegular.cpp for an example
    static_assert(std::is_default_constructible<T>::value,
                  "T shall be default constructible");
    static_assert(std::is_copy_assignable<T>::value,
                  "T shall be copy assignable");
    static_assert(boost::has_not_equal_to<T>::value,
                  "T shall be eq/ne comparable");

    const T a{};
    ASSERT_THAT(zapMe, testing::Ne(a));
    zapMe = a;
}

template<class T>
inline void zap(T& zapMe)
{
    // if you get a compile-error here
    // you probably forgot to specialize Zapper for your type
    // see Zapper<ns::RegularType> in TestIsRegular.cpp for an example
    Zapper<T>{}(zapMe);
}
}
}
}
