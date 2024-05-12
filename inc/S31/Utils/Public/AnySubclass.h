#pragma once

#include <any>
#include <type_traits>

namespace S31::Utils
{

/**
 * @brief Class that wraps std::any in a restrictive manner
 *
 * @details
 * The ctor accepts only types that inherit from T_Superclass.
 * The underlying std::any variable can be obtained by the get() function.
 *
 * @ingroup S31Utils
 */
template <typename T_Superclass>
class AnySubclass
{
public:
    template<typename T_Elem>
    // NOLINTNEXTLINE(google-explicit-constructor)
    AnySubclass(T_Elem containedElement);

    const std::any& get() const;
private:
    std::any m_containedElement;
};

template<typename T_Superclass>
template<typename T_Elem>
AnySubclass<T_Superclass>::AnySubclass(T_Elem containedElement): m_containedElement(containedElement)
{
    static_assert(
            std::is_base_of_v<T_Superclass, T_Elem>,
            "Class T_Elem must be derived from T_Superclass");
}

template<typename T_Superclass>
const std::any& AnySubclass<T_Superclass>::get() const
{
    return m_containedElement;
}

} /* Namespace S31::Utils */
