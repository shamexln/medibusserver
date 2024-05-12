#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <Framework/Format/Public/Stream.h>
#include <Framework/Utils/Private/EnumClassHelper.h>
#include <boost/core/scoped_enum.hpp>
#include <iostream>
/**
 * @file Utils/Public/EnumClass.h
 * @brief The macros defined here either emulate scoped enums as introduced in c++11
 * with the help of boost.scoped_enums or resolve directly to enum class depending
 * on the used compiler.
 *
 * @ingroup Utils
 */
/**
 * @brief Begin the declaration of an enum class.
 * @details
 * This macro begins the declaration on an enum class (C++11) with backwards
 * compatibility for C++03 compiler. For C++03 the scoping will be simulated.
 *
 * ## Usage
 * The following snippet shows the usage.
 * @snippet Utils/Test/UnitTest/TestEnumClass.cpp EnumClassCreation
 * It can be enriched with doxygen comments and appears in the enumerations section
 * just like standard \c enum \c class definitions.
 *
 * The underlying implementation is boost scoped_enum for C++03 compiler.
 * Thus, for \c switch \c case statements it has to look like
 * @snippet Utils/Test/UnitTest/TestEnumClass.cpp EnumClassSwitch
 * For equal comparison in unit tests it looks like
 * @snippet Utils/Test/UnitTest/TestEnumClass.cpp EnumClassEqual
 *
 * @ingroup Utils
 */
#define DFL_ENUM_CLASS(x) BOOST_SCOPED_ENUM_DECLARE_BEGIN(x)

/**
 * @brief Ends the declaration of an enum class.
 * @ingroup Utils
 */
#define DFL_ENUM_CLASS_END(x) BOOST_SCOPED_ENUM_DECLARE_END(x)

/**
 * @brief Generates stream operator for std::ostream and DFL::Format::Stream.
 *
 * ## Usage
 * For streaming support use this macro in your \c XyzIo.cpp file
 * @snippet Utils/Test/UnitTest/TestEnumClass.cpp EnumClassStream
 * It will generate the definitions for
 * \verbatim
const char* cStr(name v);
std::ostream& operator<<(std::ostream& out, MySwitch data);
DFL::Format::Stream& operator<<(DFL::Format::Stream& out, MySwitch data);
\endverbatim
 *
 * @ingroup Utils
 */
#define DFL_ENUM_CLASS_STREAM_OPERATOR(name, enumerators)                 \
const char* cStr(name v);                                                 \
std::ostream& operator <<(std::ostream& out, name v);                     \
DFL::Format::Stream& operator <<(DFL::Format::Stream& out, name v);       \
                                                                          \
inline const char* cStr(name v)                                           \
{                                                                         \
    switch (boost::native_value(v))                                       \
    {                                                                     \
        BOOST_PP_SEQ_FOR_EACH(                                            \
            DFL_STREAM_VALUE_TO_CSTR,                                     \
            name,                                                         \
            enumerators                                                   \
        )                                                                 \
    }                                                                     \
    return "[Unknown " BOOST_PP_STRINGIZE(name) "]";                      \
}                                                                         \
inline std::ostream& operator <<(std::ostream& out, name v)               \
{                                                                         \
    out << cStr(v);                                                       \
    return out;                                                           \
}                                                                         \
inline DFL::Format::Stream& operator <<(DFL::Format::Stream& out, name v) \
{                                                                         \
    out << cStr(v);                                                       \
    return out;                                                           \
}

/**
 * @brief Generate \c load and \c save methods for boost serialization purposes.
 *
 * @details It has to be called outside of any namespaces.
 * Internally it opens the boost serialization namespaces for the \c load and \c save method.
 * It uses an \c int as serialization type as done in boost.serialization for enumerations.
 *
 * Furthermore the tuples provided with name and integer value are
 * used for static_assert to take care the integer value does not change.
 * This is required for boost.serialization for example, where reading and
 * integer must resolve to the same enum value name.
 *
 * @ingroup Utils
 */
#define DFL_ENUM_CLASS_SERIALIZATION(name, enumerators) \
DFL_ENUM_CLASS_SERIALIZATION_MAPPING_ASSERT(name, enumerators) \
DFL_ENUM_CLASS_SERIALIZATION_LOAD_SAVE_METHODS(name, enumerators)
