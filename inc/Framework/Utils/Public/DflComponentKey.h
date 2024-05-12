#pragma once

#include <Framework/Utils/Public/Instance.h>
#include <Framework/Utils/Public/Key.h>
#include <Framework/Utils/Public/Kind.h>

namespace DFL
{
/**
 * @brief Type of component kind used by DFL internally.
 */
using ComponentKindType =
   Component::StaticKind<0x0DF, Component::Static::string<'D', 'F', 'L'>>;
/**
 * @brief Type of component instance used by DFL internally.
 */
using ComponentInstanceType = Component::StaticInstance<0>;
/**
 * @brief Type of component key used by DFL internally.
 */
using ComponentKeyType =
    Component::StaticKey<ComponentKindType, ComponentInstanceType>;
/**
 * @brief Component key instance used by DFL internally.
 */
const ComponentKeyType componentKey{};
}
