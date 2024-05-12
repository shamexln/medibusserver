#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <cstddef>
#include <functional>
#include <memory>
#include <type_traits>
#include <utility>

namespace DFL
{
/**
 * @brief Indicates in a function interface that the passed pointer is assumed
 * to never be null.
 *
 * This type is directly derived from the cpp-core-guideline
 * [Declare a pointer that must not be null as
 * not_null](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Ri-nullptr).
 *
 * @par Motivation
 * It's often unclear if a pointer given to a function is allowed to be null.
 * @snippet Utils/Test/UnitTest/TestNotNull.cpp ProcessPointer
 * This leads to either missing null checks or unnecessary null checks which
 * cost performance and clutter the code. The alternative for a not-null-pointer
 * is a reference. But this is not always possible e.g. references cannot be
 * rebound. This file defines an alternative which can be used in cases where
 * references are not suitable.
 * @snippet Utils/Test/UnitTest/TestNotNull.cpp ProcessNotNull
 * This interface now explicitly states its contract. The given parameter is not
 * allowed to be null and thus is never checked. The client on the other hand
 * gets a compile error if a pointer is passed into the function.
 * @snippet Utils/Test/UnitTest/TestNotNull.cpp NoRawPointer
 * This reminds the client to obey the not-null-contract and this contract can
 * be signed like this:
 * @snippet Utils/Test/UnitTest/TestNotNull.cpp SigningContract
 * Of course a client can cheat by passing in a pointer which previously has
 * been assigned to null but assigning null directly does not compile/link.
 * @snippet Utils/Test/UnitTest/TestNotNull.cpp NoCtorFromNull
 * @snippet Utils/Test/UnitTest/TestNotNull.cpp NoNullToAsNotNull
 *
 * @par No Null-Checks
 * To be very clear here, the implementation never checks if the held pointer is
 * null. This is not the purpose of this type. Its purpose is state in the
 * interface that the caller is responsible for passing in a not-null pointer.
 *
 * @par Pointer Model
 * This type itself models a pointer.
 * @snippet Utils/Test/UnitTest/TestNotNull.cpp CopyNotNull
 * @snippet Utils/Test/UnitTest/TestNotNull.cpp CopyNotNullUnique
 * @snippet Utils/Test/UnitTest/TestNotNull.cpp MoveNotNull
 * This means, although all accessors from this type are const the element type
 * can be changed.
 * @snippet Utils/Test/UnitTest/TestNotNull.cpp NoConstContent
 * To prohibit modification of the element type declare the not-null-type like
 * this:
 * @snippet Utils/Test/UnitTest/TestNotNull.cpp ConstContent
 * This also means that not-null-types shall be passed by value.
 * @snippet Utils/Test/UnitTest/TestNotNull.cpp ProcessNotNull
 *
 * @par Smart or not?
 * The implementation is heavily inspired by the following libraries.
 * Reading their documentation is helpful too.
 * - [explicit](https://github.com/akrzemi1/explicit)
 * - [gsl](https://github.com/Microsoft/GSL)
 * -
 * [mozilla-NotNull](https://dxr.mozilla.org/mozilla-central/source/mfbt/NotNull.h)
 * @par
 * The major difference is that this implementation in the past also worked for
 * c++03 with the help of boost and that it explicitly allows smart-pointers to
 * be used as pointer types. gsl does not allow this. See
 * [issue](https://github.com/Microsoft/GSL/issues/89).
 *
 * @par Articles
 * - [Using the not_null Template for Pointers That Must Never Be
 * Null](https://visualstudiomagazine.com/articles/2016/06/01/using-the-not_null-template.aspx)
 * - [How not_null Can Improve Your
 * Code](https://dzone.com/articles/how-not-null-can-improve-your-code)
 *
 * @tparam PtrType Either a raw (int*) or smart pointer type
 *                 e.g. std::unique_ptr<int>, std::shared_ptr<int>, ...
 *
 * @ingroup Utils
 */
template <typename PtrType>
class NotNull
{
public:
    /** @brief Type being pointed to. */
    using element_type = typename std::pointer_traits<
        typename std::remove_const<PtrType>::type>::element_type;
    /** @brief Pointer type. */
    using pointer = PtrType;
    /** @brief Constant pointer type. */
    using const_pointer = const pointer;
    /**
     * @brief Moves given pointer into this class.
     *
     * @snippet Utils/Test/UnitTest/TestNotNull.cpp CtorFromUniquePtr
     * The easiest way to construct instances from this class is to use @ref
     * DFL::asNotNull.
     * @snippet Utils/Test/UnitTest/TestNotNull.cpp AsNotNullFromUniquePtr
     */
    template <class OtherPtrType>
    explicit NotNull(
        OtherPtrType other,
        typename std::enable_if<
            std::is_convertible<OtherPtrType, PtrType>::value>::type* = nullptr)
        : m_ptr(std::move(other))
    {
    }
    /**
     * @brief Construction from a not-null with different pointer type.
     *
     * @snippet Utils/Test/UnitTest/TestNotNull.cpp CtorFromUniquePtr
     */
    template <class OtherPtrType>
    /* implicit */ NotNull(
        NotNull<OtherPtrType> other,
        typename std::enable_if<
            std::is_convertible<OtherPtrType, PtrType>::value>::type* = nullptr)
        : m_ptr(std::move(other.get()))
    {
    }
    /**
     * @brief Returns reference to the held pointer.
     */
    const_pointer& get() const
    {
        return m_ptr;
    }
    /**
     * @brief Returns reference to the held pointer.
     */
    pointer& get()
    {
        return m_ptr;
    }
    /**
     * @brief Reference to the element being pointed to.
     */
    element_type& operator*() const
    {
        return *m_ptr;
    }
    /**
     * @brief Address of the element being pointed to.
     */
    element_type* operator->() const
    {
        return std::addressof(*m_ptr);
    }
    explicit NotNull(std::nullptr_t) = delete;
    NotNull& operator=(std::nullptr_t) = delete;
    explicit NotNull(int) = delete;
    NotNull& operator=(int) = delete;

private:
    PtrType m_ptr;
};
/**
 * @brief Encapsulates given pointer in a not-null type.
 *
 * Constructing a @ref DFL::NotNull with this function is more convenient than
 * calling the according constructor. It just saves a lot of typing and is more
 * expressive.
 * @snippet Utils/Test/UnitTest/TestNotNull.cpp AsNotNullFromUniquePtr
 *
 * @ingroup Utils
 */
template <typename Ptr>
NotNull<Ptr> asNotNull(Ptr p);

void asNotNull(std::nullptr_t) = delete;
void asNotNull(int) = delete;

template <typename Ptr>
inline NotNull<Ptr> asNotNull(Ptr p)
{
    return NotNull<Ptr>(std::move(p));
}

/**
 * @brief Comparison of not-null pointers that are convertible to each other.
 *
 * These operators compare addresses, not contents.
 * @snippet Utils/Test/UnitTest/TestNotNull.cpp NotNullSetKey
 *
 * @ingroup Utils
 * @{
 */
template <class Ptr, class OtherPtrType>
inline auto operator==(
    const NotNull<Ptr>& lhs,
    const NotNull<OtherPtrType>& rhs) noexcept(noexcept(lhs.get() == rhs.get()))
    -> decltype(lhs.get() == rhs.get())
{
    return lhs.get() == rhs.get();
}

template <class Ptr, class OtherPtrType>
inline auto operator!=(
    const NotNull<Ptr>& lhs,
    const NotNull<OtherPtrType>& rhs) noexcept(noexcept(lhs.get() != rhs.get()))
    -> decltype(lhs.get() != rhs.get())
{
    return lhs.get() != rhs.get();
}

// Why are std::less, std::less_equal, std::greater, std::greater_equal used to implement
// these comparisons?
// According to the c++ standard, the comparison of unrelated pointers (i.e. not pointing
// to elements of same array or struct) has an "unspecified" result, but the functor objects
// are specified to provide "total ordering" (possibly using some platform specific method).
// For more explaination see: https://stackoverflow.com/questions/9086372/how-to-compare-pointers
template <class Ptr, class OtherPtrType>
inline auto operator<(
    const NotNull<Ptr>& lhs,
    const NotNull<OtherPtrType>& rhs) noexcept(noexcept(std::less<>{}(lhs.get(), rhs.get())))
    -> decltype(std::less<>{}(lhs.get(), rhs.get()))
{
    return std::less<>{}(lhs.get(), rhs.get());
}

template <class Ptr, class OtherPtrType>
inline auto operator<=(
    const NotNull<Ptr>& lhs,
    const NotNull<OtherPtrType>& rhs) noexcept(noexcept(std::less_equal<>{}(lhs.get(), rhs.get())))
    -> decltype(std::less_equal<>{}(lhs.get(), rhs.get()))
{
    return std::less_equal<>{}(lhs.get(), rhs.get());
}

template <class Ptr, class OtherPtrType>
inline auto operator>(
    const NotNull<Ptr>& lhs,
    const NotNull<OtherPtrType>& rhs) noexcept(noexcept(std::greater<>{}(lhs.get(), rhs.get())))
    -> decltype(std::greater<>{}(lhs.get(), rhs.get()))
{
    return std::greater<>{}(lhs.get(), rhs.get());
}

template <class Ptr, class OtherPtrType>
inline auto operator>=(
    const NotNull<Ptr>& lhs,
    const NotNull<OtherPtrType>& rhs) noexcept(noexcept(std::greater_equal<>{}(lhs.get(), rhs.get())))
    -> decltype(std::greater_equal<>{}(lhs.get(), rhs.get()))
{
    return std::greater_equal<>{}(lhs.get(), rhs.get());
}
/** @} */
}
