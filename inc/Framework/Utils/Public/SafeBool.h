#pragma once

#include <Framework/Utils/Private/ExpImp.h>

#include <boost/config.hpp>

namespace DFL
{
/**
 * @brief Class for implementing the safe bool idiom.
 *
 * The naive approach on converting a handcrafted type to a bool would be the
 * usage of a conversion operator:
 * @code
 * class ToBool
 * {
 * public:
 *     ToBool(int value) : m_value(value) {}
 *     int m_value;
 *     operator bool() const
 *     {
 *         return m_value > 0;
 *     }
 * };
 * @endcode
 * Now you can use instances of this type in an if expression:
 * @code
 * ToBool const isTrue(1);
 * ToBool const isFalse(-1);
 * if(isTrue) { assert(true); }
 * else { assert(false); }
 * if(isFalse) { assert(false); }
 * else { assert(true); }
 * @endcode
 * But there are a lot of more expressions available:
 * @code
 * isTrue < isFalse;
 * isTrue + isFalse;
 * @endcode
 * All kinds of relational- and arithmetic operators work with this type.
 * The reason is that bool is implicitly convertible to int and since ToBool is
 * implicit convertible to bool the conversion to int works aswell.
 * A version of ToBool which turns these experssions into a compiletime errors
 * looks like this:
 * @code
 * class ToBool
 * {
 * public:
 *     ToBool(int value) : m_value(value) {}
 *     int m_value;
 *     operator SafeBool::Type() const
 *     {
 *         return SafeBool::isTrue(m_value > 0);
 *     }
 * };
 * @endcode
 * Since this idiom is very useful it has direct support from the language since
 * c++11. The feature is called explicit conversion operator and looks like
 * this:
 * @code
 * class ToBool
 * {
 * public:
 *     ToBool(int value) : m_value(value) {}
 *     int m_value;
 *     explicit operator bool() const
 *     {
 *         return m_value > 0;
 *     }
 * };
 * @endcode
 * To take advantage of this two macros are provided. On pre c++11 compiler the
 * SafeBool class is used and on c++11 compilers the explicit conversion
 * operator is used:
 * @code
 * // ToBool.h
 * class ToBool
 * {
 *     DFL_SAFEBOOL_DECL();
 * };
 *
 * // ToBool.cpp
 * DFL_SAFEBOOL_IMPL(ToBool, (m_value > 0))
 * @endcode
 * @warning If one has to write code written with and without c++11 support take
 * into account that explicit conversion operators only work in direct
 * initialization context whilst the safe bool idiom also works in copy
 * initialization contexts.
 * @code
 * ToBool const isTrue(1);
 * bool a(isTrue); // direct initialization
 * bool b = isTrue; // copy initialization
 * @endcode
 *
 * @ingroup Utils
 */
class DFL_UTILS_EXPIMP SafeBool
{
public:
    /**
     * @brief Represents a type which is valid in a boolean context and not
     * further convertible.
     */
    using Type = void (SafeBool::*)() const;

    /**
     * @brief Determines whether the value is true in a boolean context or not.
     * @param value Experssion to be tested true.
     * @return Value which is true or false in boolean context depending on the
     * given value.
     */
    static Type isTrue(bool value);

private:
    void thisIsTrue() const;
};
/**
 * @brief Provokes a compiler error in order to prohibit comparison of SafeBool.
 *
 * @ingroup Utils
 */
template <typename T>
bool operator==(SafeBool const&, T const&) = delete;
/**
 * @brief Provokes a compiler error in order to prohibit comparison of SafeBool.
 *
 * @ingroup Utils
 */
template <typename T>
bool operator!=(SafeBool const&, T const&) = delete;
}

#if !defined(BOOST_NO_EXPLICIT_CONVERSION_OPERATORS)
/** @brief Declares the conversion function. */
#define DFL_SAFEBOOL_DECL() explicit operator bool() const

/** @brief Implements the conversion function. */
#define DFL_SAFEBOOL_IMPL(className, boolExpr)                                 \
    className::operator bool() const                                           \
    {                                                                          \
        return ((boolExpr));                                                   \
    }
#else
#define DFL_SAFEBOOL_DECL() operator DFL::SafeBool::Type() const

#define DFL_SAFEBOOL_IMPL(className, boolExpr)                                 \
    className::operator DFL::SafeBool::Type() const                            \
    {                                                                          \
        return DFL::SafeBool::isTrue((boolExpr));                              \
    }
#endif
