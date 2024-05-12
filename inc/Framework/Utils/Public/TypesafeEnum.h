#pragma once

#include <Framework/Utils/Private/TypesafeEnumHelper.h>
#include <Framework/Config/Public/Attributes.h>
#include <boost/preprocessor.hpp>
#include <sstream>
#include <stdexcept>

DFL_HEADER_DEPRECATED("use C++11 scoped enunms instead")

/**
@ingroup Utils
@{

@deprecated Use EnumClass.h instead.

@file
@brief DEPRECATED - Define enums in a typesafe way.

## Motivation

The classical enums are implicit convertible to int. This is a source of many
bugs:
@code
struct Switch
{
    typedef enum {On, Off} Type;
};

Switch::Type s = Switch::On;
if(s) { cout << "On"; }
else { cout << "Off"; }
@endcode
Of course this example prints "Off" to the console.
@code
struct State
{
    typedef enum {Off, On} Type;
};

State::Type t(State::On);
switch(t)
{
    case State::On: cout << "On"; break;
    case State::Off: cout << "Off"; break;
    default: break;
}
@endcode
And it is clear that this example prints "Off" to the console, too.

There are many more scenarios where the implicit conversion of enums to int is at
least confusing. The solution is to wrap an enum in a class. This way the implicit
conversion is no longer available.

## Usage
@snippet Utils/Test/UnitTest/TestTypesafeEnum.cpp TypesafeEnumCreation
This generates a type where the enum-values are instances of that type.
This macro can only be used at namespace-level.

## API
### Copyable
@snippet Utils/Test/UnitTest/TestTypesafeEnum.cpp copyable

### Assignable
@snippet Utils/Test/UnitTest/TestTypesafeEnum.cpp assignable

### operator==
@snippet Utils/Test/UnitTest/TestTypesafeEnum.cpp operator==

### operator!=
@snippet Utils/Test/UnitTest/TestTypesafeEnum.cpp operator!=

### cStr
@snippet Utils/Test/UnitTest/TestTypesafeEnum.cpp toString

### value
@snippet Utils/Test/UnitTest/TestTypesafeEnum.cpp toNative
To make interfacing with non typesafe components possible, a typesafe enum
value can be converted to a native value.
\warning The only guarantee this function makes is that each value has a unique number different
to the other enum-values. There is especially no guarantee that the first enum-value starts with 0
nor that the others have any order.

### fromValue
@snippet Utils/Test/UnitTest/TestTypesafeEnum.cpp fromNative
@snippet Utils/Test/UnitTest/TestTypesafeEnum.cpp fromNativeThrows
A typesafe enum value can also be created from a native value. If the native
value does not fit to a typesafe enum value an exception is thrown.

### Count (compile time)
@snippet Utils/Test/UnitTest/TestTypesafeEnum.cpp countAtCompiletime
Number of enum-values is accessible at compiletime.

### Value (compile time)
@snippet Utils/Test/UnitTest/TestTypesafeEnum.cpp nativeValuesAtCompiletime
Native value of a typesafe enum value is accessible at compiletime.
This allows the usage of typesafe enum values e.g. in switch-cases and
as template parameters.

### Overloads
@snippet Utils/Test/UnitTest/TestTypesafeEnum.cpp OverloadOnEnumType
Since each enum value exposes its own type one can use function overloading
instead of if-else if-else implementations.
*/

/**
 * @brief DEPRECATED - Defines a typesafe enum.
 * @param Scope The name of the scope in which enum values are defined.
 * @param Seq Sequence of enum values. Have to be surrounded by "()".
 * @deprecated use EnumClass.h instead.
 */
#define DFL_TYPESAFE_ENUM(Scope, Seq)                                   \
  namespace Scope                                                       \
  {                                                                     \
    class Type                                                          \
    {                                                                   \
    public:                                                             \
      Type();                                                           \
      typedef int Native;                                               \
      static Type fromValue(Native nativeValue);                        \
      char const* cStr() const;                                         \
      Native value() const;                                             \
      bool operator==(Type const& other) const;                         \
      bool operator!=(Type const& other) const;                         \
    protected:                                                          \
      typedef enum                                                      \
      {                                                                 \
        BOOST_PP_SEQ_ENUM(Seq)                                          \
      } Kind;                                                           \
      explicit Type(Native nativeValue);                                \
    private:                                                            \
      Kind m_kind;                                                      \
    };                                                                  \
    static const Type::Native Count = BOOST_PP_SEQ_SIZE(Seq);           \
    inline Type Type::fromValue(Native nativeValue)                     \
    {                                                                   \
      return Type(nativeValue);                                         \
    }                                                                   \
    inline Type::Type()                                                 \
      : m_kind(static_cast<Kind>(0))                                    \
    {                                                                   \
    }                                                                   \
    inline Type::Type(Native nativeValue)                               \
      : m_kind(static_cast<Kind>(nativeValue))                          \
    {                                                                   \
      switch(m_kind)                                                    \
      {                                                                 \
        BOOST_PP_SEQ_FOR_EACH(DFL_IMPL_CHECK_VAL, Unused, Seq)          \
      default:                                                          \
        {                                                               \
          std::ostringstream txt;                                       \
          txt << "enum can not be constructed from native value " << nativeValue; \
          throw std::runtime_error(txt.str());                          \
        }                                                               \
      }                                                                 \
    }                                                                   \
    inline char const* Type::cStr() const                               \
    {                                                                   \
      switch(m_kind)                                                    \
      {                                                                 \
        BOOST_PP_SEQ_FOR_EACH(DFL_IMPL_VAL_TO_STR, Unused, Seq)         \
      default:                                                          \
        return "";                                                      \
      }                                                                 \
    }                                                                   \
    inline Type::Native Type::value() const                             \
    {                                                                   \
      return m_kind;                                                    \
    }                                                                   \
    inline bool Type::operator==(Type const& other) const               \
    {                                                                   \
      return m_kind == other.m_kind;                                    \
    }                                                                   \
    inline bool Type::operator!=(Type const& other) const               \
    {                                                                   \
      return !(this->operator==(other));                                \
    }                                                                   \
    BOOST_PP_SEQ_FOR_EACH(DFL_IMPL_TYPESAFE_ENUM_VALUE, Unused, Seq)    \
  }

/** @} */
