#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <boost/type_traits/remove_pointer.hpp>
#include <typeinfo>
#include <string>

/**
 * @ingroup Utils
 * @{
 *
 * @file
 * @brief Provides useful cast functions.
 *
 * Some of these cast functions are provided as a replacement for existing c++
 * cast functions. exact_cast is a replacement for \c dynamic_cast.
 * @c dynamic_cast is able to do downcasts aswell as crosscasts. It does so by
 * using the typeid and traversing the inheritance structure. In cases where the
 * exact target type is known a more efficient implementation can be used. This
 * is provided by the exact_cast. It performs one typeid comparison and a
 * static_cast. Given this class hierachy:
 *
 * @code
 * class Base
 * {
 * public:
 *     virtual ~Base(){}
 * };
 *
 * class Sub_1 : public Base
 * {};
 *
 * class Sub_1_1 : public Sub_1
 * {};
 * @endcode
 * An exact_cast can perform the following conversions.
 * @code
 * Base* baseToSub_1 = new Sub_1();
 * Sub_1* sub_1 = exact_cast<Sub_1*>(baseToSub_1);
 *
 * Base* baseToSub_1_1 = new Sub_1_1();
 * Sub_1_1* sub_1_1 = exact_cast<Sub_1_1*>(baseToSub_1_1);
 * @endcode
 * This conversion does not work and throws an exception:
 * @code
 * Base* baseToSub_1_1 = new Sub_1_1();
 * exact_cast<Sub_1*>(baseToSub_1_1); // throws
 * @endcode
 */
namespace DFL
{

/**
 * @brief Exception which is thrown if casting did not work.
 */
class BadCast: public std::bad_cast
{
public:
    /**
     * @brief Constructs a bad cast exception.
     * @param what The text attached to this exception.
     */
    BadCast(char const* what);
    BadCast& operator=(BadCast const&) = delete;

    /**
     * @brief Returns text of this exception.
     * @return Text of this exception.
     */
    char const* what() const noexcept override;

private:
    std::string m_what;
};

inline BadCast::BadCast(char const* what) :
    std::bad_cast(),
    m_what(what)
{
}

inline char const* BadCast::what() const noexcept
{
    return m_what.c_str();
}

/**
 * @brief Casts pointer from source type to target type.
 * @param s Pointer to source object to be casted.
 * @return Pointer to target type.
 * @exception BadCast
 * Thrown if pointer to source type is NULL or
 * typeid of target and source type do not match.
 * @ingroup Utils
 */
template<typename Target, typename Source>
Target exact_cast(Source* s);

template<typename Target, typename Source>
inline Target exact_cast(Source* s)
{
    // check s for NULL
    // otherwise std::bad_typeid would be thrown
    if (s && (typeid(*s) == typeid(typename boost::remove_pointer<Target>::type)))
    {
        return static_cast<Target>(s);
    }
    throw BadCast((std::string("cannot convert from ")
        + typeid(Source).name()
        + " to "
        + typeid(Target).name()).c_str());
}
}
/** @} */
