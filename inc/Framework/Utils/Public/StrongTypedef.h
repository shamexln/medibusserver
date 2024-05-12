#pragma once

#include <Framework/Utils/Private/StrongTypedefHelper.h>

#include <iosfwd>
#include <type_traits>
#include <utility>

namespace DFL
{
namespace Format
{
class Stream;
}
}
namespace DFL
{
namespace Skill
{
/**
 * @brief Requires == from the underlying type and provides == and !=.
 *
 * @ingroup Utils
 */
template<class T>
struct EqualityComparable : Impl::CrtpHelper<T, EqualityComparable>
{
    /**
     * @brief ==
     */
    bool operator==(const T& other) const
    {
        return other.get() == this->underlying().get();
    }
    /**
     * @brief !=
     */
    bool operator!=(const T& other) const
    {
        return !(*this == other);
    }
};
/**
 * @brief Requires < from the underlying type and provides <, >, <=, >=.
 *
 * @ingroup Utils
 */
template<class T>
struct LessThanComparable : Impl::CrtpHelper<T, LessThanComparable>
{
    /**
     * @brief <
     */
    bool operator<(const T& other) const
    {
        return this->underlying().get() < other.get();
    }
    /**
     * @brief >
     */
    bool operator>(const T& other) const
    {
        return other.get() < this->underlying().get();
    }
    /**
     * @brief <=
     */
    bool operator<=(const T& other) const
    {
        return !(other.get() < this->underlying().get());
    }
    /**
     * @brief >=
     */
    bool operator>=(const T& other) const
    {
        return !(*this < other);
    }
};
/**
 * @brief Provides ==, !=, <, >, <=, >=.
 *
 * Require that the underlying type is totally ordered. That means every value is either
 * before or after another value. Otherwise these two values are considered equal.
 * This is the case for int but not for float since it has NaN.
 *
 * @ingroup Utils
 */
template<class T>
struct TotallyOrdered
    : EqualityComparable<T>
    , LessThanComparable<T>
{};
/**
 * @brief Requires +, += from the underlying type and provides +, +=.
 *
 * @ingroup Utils
 */
template<class T>
struct Addable : Impl::CrtpHelper<T, Addable>
{
    /**
     * @brief +
     */
    T operator+(const T& other) const
    {
        return T(this->underlying().get() + other.get());
    }
    /**
     * @brief +=
     */
    T& operator+=(const T& other)
    {
        this->underlying().get() += other.get();
        return this->underlying();
    }
};
/**
 * @brief Requires -, -= from the underlying type and provides -, -=.
 *
 * @ingroup Utils
 */
template<class T>
struct Subtractable : Impl::CrtpHelper<T, Subtractable>
{
    /**
     * @brief -
     */
    T operator-(const T& other) const
    {
        return T(this->underlying().get() - other.get());
    }
    /**
     * @brief -=
     */
    T& operator-=(const T& other)
    {
        this->underlying().get() -= other.get();
        return this->underlying();
    }
};
/**
 * @brief Groups @ref DFL::Skill::Addable and @ref DFL::Skill::Subtractable to one skill.
 *
 * @ingroup Utils
 */
template<class T>
struct Additive
    : Addable<T>
    , Subtractable<T>
{};
/**
 * @brief Requires * from the underlying type and provides *.
 *
 * @ingroup Utils
 */
template<class T>
struct Multipliable : Impl::CrtpHelper<T, Multipliable>
{
    /**
     * @brief *
     */
    T operator*(const T& other) const
    {
        return T(this->underlying().get() * other.get());
    }
};
/**
 * @brief Requires / from the underlying type and provides /.
 *
 * @ingroup Utils
 */
template<class T>
struct Dividable : Impl::CrtpHelper<T, Dividable>
{
    /**
     * @brief /
     */
    T operator/(const T& other) const
    {
        return T(this->underlying().get() / other.get());
    }
};
/**
 * @brief Groups @ref DFL::Skill::Multipliable and @ref DFL::Skill::Dividable to one skill.
 *
 * @ingroup Utils
 */
template<class T>
struct Multiplicative
    : Multipliable<T>
    , Dividable<T>
{};
/**
 * @brief Groups @ref DFL::Skill::Additive and @ref DFL::Skill::Multiplicative to one skill.
 *
 * @ingroup Utils
 */
template<class T>
struct Arithmetic
    : Additive<T>
    , Multiplicative<T>
{};
/**
 * @brief Requires ++i from the underlying type and provides ++i, i++.
 *
 * @ingroup Utils
 */
template<class T>
struct Incrementable : Impl::CrtpHelper<T, Incrementable>
{
    /**
     * @brief ++
     */
    T& operator++()
    {
        ++(this->underlying().get());
        return this->underlying();
    }
    /**
     * @brief ++
     */
    T operator++(int)
    {
        T temp(this->underlying());
        ++(this->underlying().get());
        return temp;
    }
};
/**
 * @brief Requires --i from the underlying type and provides --i, i--.
 *
 * @ingroup Utils
 */
template<class T>
struct Decrementable : Impl::CrtpHelper<T, Decrementable>
{
    /**
     * @brief --
     */
    T& operator--()
    {
        --(this->underlying().get());
        return this->underlying();
    }
    /**
     * @brief --
     */
    T operator--(int)
    {
        T temp(this->underlying());
        --(this->underlying().get());
        return temp;
    }
};
/**
 * @brief Groups @ref DFL::Skill::Incrementable and @ref DFL::Skill::Decrementable to one skill.
 *
 * @ingroup Utils
 */
template<class T>
struct UnitStepable
    : Incrementable<T>
    , Decrementable<T>
{};
/**
 * @brief Enables T to be streamed via std::ostream and @ref DFL::Format::Stream if the
 * underlying type supports both or one of these stream operators.
 *
 * @ingroup Utils
 */
template<class T>
struct Streamable : Impl::CrtpHelper<T, Streamable>
{
    /**
     * @brief Requires std::ostream << operator
     */
    void streamInto(std::ostream& str) const
    {
        str << this->underlying().get();
    }
    /**
     * @brief Requires @ref DFL::Format::Stream << operator
     */
    void streamInto(::DFL::Format::Stream& str) const
    {
        str << this->underlying().get();
    }
};
}
/**
 * @brief Prevent bugs at compile time by providing strongly-typed and expressive interfaces with zero overhead.
 *
 * This type is directly derived from this proposal called
 * [Opaque Typedefs](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/p0109r0.pdf).
 *
 * @par Motivation
 * Consider these API calls:
 * @snippet Utils/Sample/Sample.cpp PoorLocationCtor
 * It may seem funny when you read it in a documentation like this but if you see it in real code
 * it is just frustrating. Compare that to this API calls:
 * @snippet Utils/Sample/Sample.cpp AwesomeLocationCtor
 * What we have gained now is the ability to reason about the code locally.
 * We do not have to jump to the according header file each time we have to use that API and
 * we can no longer introduce bugs by mixing the parameters as this would trigger a compile error.
 * And as you can see in the first example some parameters have been mixed up.
 * This bug could slip through verification and the later a bug is detected the more expensive it is.
 * Strong types can detect such misuses at compile time. So they should be used often.
 * And the best thing they are for free. No memory or runtime overhead is introduced since this
 * is a transparent type. This is how the parameters are defined:
 * @snippet Utils/Sample/Sample.cpp LocationStrongParams
 * Since these types are completely new types non of the functionality of the underlying type is available.
 * For example this code does not compile:
 * @snippet Utils/Sample/Sample.cpp FloorNotCompile
 * But some skills of the underlying type might totally make sense for the strong type. Thus it is possible
 * to pick and mix the skills of the underlying type into the strong type.
 * @snippet Utils/Sample/Sample.cpp CompareableFloor
 * @snippet Utils/Sample/Sample.cpp CompareFloors
 * See @ref DFL::Skill namespace for more skills that are available.
 *
 * @par Inspiration
 * This type and the different skill types are basically a mixture of these libraries:
 * - [NamedType](https://github.com/joboccara/NamedType)
 * - [type_safe](https://github.com/foonathan/type_safe)
 * - [boost.operators](http://www.boost.org/doc/libs/1_66_0/libs/utility/operators.htm)
 *
 * They all lack C++03 support and we picked the best APIs from all of them and merged them
 * into this one.
 *
 * @par Articles
 * - [Strong Types Series](https://www.fluentcpp.com/2016/12/05/named-constructors/)
 * - [Emulating strong/opaque typedefs](http://foonathan.net/blog/2016/10/19/strong-typedefs.html)
 *
 * @par Presentations
 * - [Strong Types For Strong Interfaces](https://www.youtube.com/watch?v=WVleZqzTw2k)
 * - [Typesafe Programming](https://www.youtube.com/watch?v=iihlo9A2Ezw)
 *
 * @tparam T Underlying type that is wrapped by this strong type.
 * @tparam TagType Used to disambiguate strong types which encapsulate the same underlying type.
 * Typically a [phantom type](https://www.fluentcpp.com/2016/12/08/strong-types-for-strong-interfaces/)
 * is sufficient. The recommendation is just to append 'Tag' to the name of the strong type and use that
 * symbol as the name for the tag-type.
 * @tparam Skill1 List of skills that the strong type should inherit from the underlying type.
 * Since the number of skills which can be applied is limited consider using grouped skills.
 * For example all of these strong types have the same set of skills.
 * @snippet Utils/Test/UnitTest/TestStrongTypedef.cpp SameSkills
 *
 * @ingroup Utils
 */
template<class T
         , class TagType
         , template<class> class Skill1 = Impl::Ignore1
         , template<class> class Skill2 = Impl::Ignore2
         , template<class> class Skill3 = Impl::Ignore3
         , template<class> class Skill4 = Impl::Ignore4
         , template<class> class Skill5 = Impl::Ignore5
         , template<class> class Skill6 = Impl::Ignore6
         , template<class> class Skill7 = Impl::Ignore7
         , template<class> class Skill8 = Impl::Ignore8
         , template<class> class Skill9 = Impl::Ignore9
         , template<class> class Skill10 = Impl::Ignore10>
class StrongTypedef
    : public Skill1<StrongTypedef<T, TagType, Skill1, Skill2, Skill3, Skill4, Skill5, Skill6, Skill7, Skill8, Skill9, Skill10> >
    , public Skill2<StrongTypedef<T, TagType, Skill1, Skill2, Skill3, Skill4, Skill5, Skill6, Skill7, Skill8, Skill9, Skill10> >
    , public Skill3<StrongTypedef<T, TagType, Skill1, Skill2, Skill3, Skill4, Skill5, Skill6, Skill7, Skill8, Skill9, Skill10> >
    , public Skill4<StrongTypedef<T, TagType, Skill1, Skill2, Skill3, Skill4, Skill5, Skill6, Skill7, Skill8, Skill9, Skill10> >
    , public Skill5<StrongTypedef<T, TagType, Skill1, Skill2, Skill3, Skill4, Skill5, Skill6, Skill7, Skill8, Skill9, Skill10> >
    , public Skill6<StrongTypedef<T, TagType, Skill1, Skill2, Skill3, Skill4, Skill5, Skill6, Skill7, Skill8, Skill9, Skill10> >
    , public Skill7<StrongTypedef<T, TagType, Skill1, Skill2, Skill3, Skill4, Skill5, Skill6, Skill7, Skill8, Skill9, Skill10> >
    , public Skill8<StrongTypedef<T, TagType, Skill1, Skill2, Skill3, Skill4, Skill5, Skill6, Skill7, Skill8, Skill9, Skill10> >
    , public Skill9<StrongTypedef<T, TagType, Skill1, Skill2, Skill3, Skill4, Skill5, Skill6, Skill7, Skill8, Skill9, Skill10> >
    , public Skill10<StrongTypedef<T, TagType, Skill1, Skill2, Skill3, Skill4, Skill5, Skill6, Skill7, Skill8, Skill9, Skill10> >
{
public:
    /**
     * @brief Value-Initializes underlying value.
     */
    constexpr StrongTypedef() noexcept(std::is_nothrow_default_constructible<T>::value)
        : m_value()
    {}
    /**
     * @brief Initializes this with given value.
     */
    // NOLINTNEXTLINE(modernize-pass-by-value)
    explicit constexpr StrongTypedef(const T& value) noexcept(std::is_nothrow_copy_constructible<T>::value)
        : m_value(value)
    {}
    /**
     * @brief Moves given value into this.
     */
    explicit constexpr StrongTypedef(T&& value) noexcept(std::is_nothrow_move_constructible<T>::value)
        : m_value(std::move(value))
    {}
    /**
     * @brief Returns writeable reference to held value.
     */
    T& get() noexcept
    {
        return m_value;
    }
    /**
     * @brief Returns read-only reference to held value.
     */
    const T& get() const noexcept
    {
        return m_value;
    }
private:
    T m_value;
};
/**
 * @brief Provides ostream operator if strong type has the @ref ::DFL::Skill::Streamable.
 *
 * @ingroup Utils
 */
template<class T
         , class TagType
         , template<class> class Skill1
         , template<class> class Skill2
         , template<class> class Skill3
         , template<class> class Skill4
         , template<class> class Skill5
         , template<class> class Skill6
         , template<class> class Skill7
         , template<class> class Skill8
         , template<class> class Skill9
         , template<class> class Skill10>
std::ostream& operator<<(std::ostream& str, const StrongTypedef<T, TagType, Skill1, Skill2, Skill3, Skill4, Skill5, Skill6, Skill7, Skill8, Skill9, Skill10>& t)
{
    t.streamInto(str);
    return str;
}
/**
 * @brief Provides @ref ::DFL::Format::Stream operator if strong type has the @ref ::DFL::Skill::Streamable.
 *
 * @ingroup Utils
 */
template<class T
         , class TagType
         , template<class> class Skill1
         , template<class> class Skill2
         , template<class> class Skill3
         , template<class> class Skill4
         , template<class> class Skill5
         , template<class> class Skill6
         , template<class> class Skill7
         , template<class> class Skill8
         , template<class> class Skill9
         , template<class> class Skill10>
::DFL::Format::Stream& operator<<(::DFL::Format::Stream& str, const StrongTypedef<T, TagType, Skill1, Skill2, Skill3, Skill4, Skill5, Skill6, Skill7, Skill8, Skill9, Skill10>& t)
{
    t.streamInto(str);
    return str;
}
}
