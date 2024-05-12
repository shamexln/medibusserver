#pragma once

#include <Framework/Utils/Public/TypesafeEnum.h>

/**
 * @file
 * @brief Declares and defines typesafe gas kind enum values by using the
 * DFL_TYPESAFE_ENUM macro from TypesafeEnum.h.
 *
 * @ingroup Utils
 */
namespace DFL
{

DFL_TYPESAFE_ENUM(GasKind,
                  (Undefined)
                  (Air)
                  (O2)
                  (CO2)
                  (N2O)
                  (NO)
                  (Xenon)
                  (Heliox)
                  (Halothane)
                  (Enflurane)
                  (Isoflurane)
                  (Desflurane)
                  (Sevoflurane)
                 )
}

namespace DFL
{
namespace GasKind
{
/**
 * @brief Checks if gas is a ventilation gas.
 *
 * @param gasKind The gas to be checked.
 * @return True if gas is a ventilation gas otherwise false.
 *
 * @ingroup Utils
 */
inline bool isVentilationGas(Type gasKind)
{
    return ((Air    == gasKind) ||
            (O2     == gasKind) ||
            (Heliox == gasKind)
           );
}
/**
 * @brief Checks if gas is an agent gas.
 *
 * @param gasKind The gas to be checked.
 * @return True if gas is a agent gas otherwise false.
 *
 * @ingroup Utils
 */
inline bool isAgent(Type gasKind)
{
    return ((Halothane   == gasKind) ||
            (Enflurane   == gasKind) ||
            (Isoflurane  == gasKind) ||
            (Desflurane  == gasKind) ||
            (Sevoflurane == gasKind)
           );
}
}
}
