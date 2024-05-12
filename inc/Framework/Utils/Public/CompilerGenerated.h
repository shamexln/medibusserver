#pragma once

#include <boost/config.hpp>

/**
 * @file
 * @brief Easy creation of copyable/noncopyable types where you
 * do not need to know if the old declare-stuff-private approach
 * has to be used or if default/delete functions are available.
 *
 *
 * @warning The macros open public/private sections.
 * It is best to use these macros at the top of the class declaration
 * and then open the appropriate sections.
 *
 * @snippet Utils/Test/UnitTest/TestCompilerGenerated.cpp Usage
 *
 * @ingroup Utils
 *
 * @def DFL_NOT_COPYCONSTRUCTABLE
 * @brief Makes Type not copy constructable.
 * @ingroup Utils
 *
 * @def DFL_NOT_COPYASSIGNABLE
 * @brief Makes Type not copy assignable.
 * @ingroup Utils
 *
 * @def DFL_NOT_COPYABLE
 * @brief Type is neither copy constructable nor copy assignable.
 * @ingroup Utils
 *
 * @def DFL_DEFAULT_COPYCONSTRUCTABLE
 * @brief Type is default constructable.
 * @ingroup Utils
 *
 * @def DFL_DEFAULT_MOVECONSTRUCTABLE
 * @brief Type is default move constructable.
 * @ingroup Utils
 *
 * @def DFL_DEFAULT_COPYASSIGNABLE
 * @brief Type is default copy assignable.
 * @ingroup Utils
 *
 * @def DFL_DEFAULT_COPYABLE
 * @brief Type is default copyable.
 * @ingroup Utils
 *
 * @def DFL_NOT_DEFAULT_CONSTRUCTABLE
 * @brief Type is not default constructable.
 * @ingroup Utils
 *
 * @def DFL_DEFAULT_CONSTRUCTABLE
 * @brief Type is default constructable.
 * @ingroup Utils
 */
#define DFL_NOT_DEFAULT_CONSTRUCTABLE(Type) \
    public: Type() = delete;

#define DFL_NOT_COPYCONSTRUCTABLE(Type) \
    public: Type(Type const&) = delete;

#define DFL_NOT_COPYASSIGNABLE(Type) \
    public: Type& operator=(const Type&) = delete;

#define DFL_NOT_COPYABLE(Type)      \
    DFL_NOT_COPYCONSTRUCTABLE(Type) \
    DFL_NOT_COPYASSIGNABLE(Type)

#define DFL_DEFAULT_CONSTRUCTABLE(Type) \
    public: Type() = default;

#define DFL_DEFAULT_COPYCONSTRUCTABLE(Type)     \
    public: Type(const Type&) = default;

#define DFL_DEFAULT_MOVECONSTRUCTABLE(Type)     \
    public: Type(Type&&) = default;

#define DFL_DEFAULT_COPYASSIGNABLE(Type) \
    public: Type& operator=(const Type&) = default;

#define DFL_DEFAULT_COPYABLE(Type) \
  DFL_DEFAULT_COPYCONSTRUCTABLE(Type) \
  DFL_DEFAULT_COPYASSIGNABLE(Type)
