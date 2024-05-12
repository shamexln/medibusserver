#pragma once

// static compiler check if expression is true
namespace DFL
{
namespace Global
{
namespace Impl
{
template<bool> struct CompileTimeCheck;
template<> struct CompileTimeCheck<true>
{
};
}
}
}

// For check during compile time. Message enables output of error description in compiler output. Message must be a valid C++ name.
#define STATIC_CHECK(expression) (::DFL::Global::Impl::CompileTimeCheck<(expression)!=0>())
#define STATIC_CHECK_MSG(expression, msg) {::DFL::Global::Impl::CompileTimeCheck<(expression)!=0>\
    ERROR_##msg;\
    static_cast<void>(ERROR_##msg);}

/**
 * @brief Static compiler check if a class T is of type void
 * @ingroup Global
 */
template<class T> struct CompilerAssertVoid;
template<> struct CompilerAssertVoid<void>
{
};

/**
 * @see std::enable_if
 * @ingroup Global
 */
template<bool B, class T = void>
struct enable_if_c
{
    /**
     * type
     */
    using type = T;
};

/**
 * @see std::enable_if
 * @ingroup Global
 */
template<class T>
struct enable_if_c<false, T>
{
};

/**
 * @see std::enable_if
 * @ingroup Global
 */
template<bool B, class T = void>
struct enable_if: public enable_if_c<B, T>
{
};

/**
 * @see std::enable_if
 * @ingroup Global
 */
template<class CondType, class T = void>
struct enable_if_v
{
};

/**
 * @see std::enable_if
 * @ingroup Global
 */
template<class T>
struct enable_if_v<void, T>
{
    /**
     * type
     */
    using type = T;
};

/**
 * @see std::enable_if
 * @ingroup Global
 */
template<class CondType, class T = void>
struct enable_if_void: public enable_if_v<CondType, T>
{
};

/**
 * @see std::enable_if
 * @ingroup Global
 */
template<class CondType, class T = void>
struct enable_if_nv
{
    /**
     * type
     */
    using type = T;
};

/**
 * @see std::enable_if
 * @ingroup Global
 */
template<class T>
struct enable_if_nv<void, T>
{
};

/**
 * @see std::enable_if
 * @ingroup Global
 */
template<class CondType, class T = void>
struct enable_if_not_void: public enable_if_nv<CondType, T>
{
};

/**
 * @see std::enable_if
 * @ingroup Global
 */
template<class CondType, class T = void>
struct enable_if_ref
{
};

/**
 * @see std::enable_if
 * @ingroup Global
 */
template<class CondType, class T>
struct enable_if_ref<const CondType&, T>
{
    /**
     * type
     */
    using type = T;
};

/**
 * @see std::enable_if
 * @ingroup Global
 */
template<class CondType, class T = void>
struct enable_if_reference: public enable_if_ref<CondType, T>
{
};

/**
 * @see std::enable_if
 * @ingroup Global
 */
template<class CondType, class T = void>
struct enable_if_not_ref
{
    /**
     * type
     */
    using type = T;
};

/**
 * @see std::enable_if
 * @ingroup Global
 */
template<class CondType, class T>
struct enable_if_not_ref<CondType&, T>
{
};

/**
 * @see std::enable_if
 * @ingroup Global
 */
template<class CondType, class T = void>
struct enable_if_not_reference: public enable_if_not_ref<CondType, T>
{
};
