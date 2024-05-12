#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Patient type as defined in ISO/IEEE 11073-10201 section 7.10.1.1.
 * @details It is not specified whether a patient is a neonatal, pediatric, or adult.
 * E.g., there are no ages or weights specified to distinguish between them.
 * @ingroup Mdib
 */
enum class PatientType
{
    /// Unspecified type
    Unspecified,

    /// Indicates an adult patient
    Adult,

    /// Indicates an adolescent patient with approximate age range of 12 years to 21 years
    Adolescent,

    /// Pediatric. Indicates a pediatric patient with approximate age range of 2 years to 12 years
    Pediatric,

    /// Indicates an infant patient with approximate age range of 1 month to 2 years
    Infant,

    /// Indicates a neonatal patient with approximate age range of birth to 1 month
    Neonatal,

    /// The patient type is designated by some other means
    Other
};
DFL_ENUM_CLASS_STREAM_OPERATOR(PatientType, (Unspecified)(Adult)(Adolescent)(Pediatric)(Infant)(Neonatal)(Other))

}
}

// Do not change the enum value integer mapping.
// It is used for serialization and might be persisted.
DFL_ENUM_CLASS_SERIALIZATION(::DFL::Mdib::PatientType, ((Unspecified,0))((Adult,1))((Adolescent,2))((Pediatric,3))((Infant,4))((Neonatal,5))((Other,6)))
