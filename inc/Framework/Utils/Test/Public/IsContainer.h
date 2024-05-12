#pragma once

#include <Framework/Utils/Test/Private/IsContainer.h>

#include <utility>

namespace DFL
{
namespace Utils
{
namespace Test
{
/**
 * @brief Tests if given type meets the container requirements.
 *
 * @details
 * The method needs two different prototypes of type Container.
 * These two prototypes will be constructed from initA and initB using the
 * callable construct.
 *
 * For details on the C++ Container requirement,
 * see https://en.cppreference.com/w/cpp/named_req/Container.
 *
 * @snippet Utils/Test/UnitTest/TestIsContainer.cpp GoodContainerType
 * @snippet Utils/Test/UnitTest/TestIsContainer.cpp constructFunc
 *
 * @tparam Container Type to be tested
 * @tparam InitContainer Type of a container used for constructing the
 * prototypes. It should provide the begin()/end() memberfunctions.
 * @tparam ConstructFunc
 * Callable with an Init argument that returns a Container.
 * @param initA
 * elements to be used for constructing the first prototype
 * @param initB
 * elements to be used for constructing the second prototype
 * @param construct
 * callable to be used for Container construction
 *
 * @ingroup Utils
 */
template <class Container,
          class InitContainer,
          class ConstructFunc = Impl::IterConstruct<Container>>
inline void isContainer(InitContainer&& initA,
                        InitContainer&& initB,
                        ConstructFunc construct = ConstructFunc{})
{
    // This ensures that we do not short circuit our tests.
    // The init-value is used to check if it is consistent with the constructed
    // container. If both are from the same type we would essential use the copy
    // constructor of the to be tested container and verify its implementation.
    static_assert(
        !std::is_same<std::decay<Container>, std::decay<InitContainer>>::value,
        "init-container-type shall differ from container type");
    Impl::isContainer(construct(std::forward<InitContainer>(initA)),
                      construct(std::forward<InitContainer>(initB)),
                      initA);
}
}
}
}
