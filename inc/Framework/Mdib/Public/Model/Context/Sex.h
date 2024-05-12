#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief ISO/IEC 5218 conform sex of a human.
 * @details "%Sex" refers to the biological and physiological characteristics that define men and women,
 * while "Gender" refers to the socially constructed roles, behaviors, activities, and attributes
 * that a given society considers appropriate for men and women.
 * @ingroup Mdib
 */
enum class Sex
{
    /// Indicates that the sex is unknown for different reasons
    Unknown,

    /// Indicates a male patient
    Male,

    /// Indicates a female patient
    Female,

    /// Sex is not designated
    Unspecified
};
DFL_ENUM_CLASS_STREAM_OPERATOR(Sex, (Unknown)(Male)(Female)(Unspecified))

}
}

// Do not change the enum value integer mapping.
// It is used for serialization and might be persisted.
DFL_ENUM_CLASS_SERIALIZATION(::DFL::Mdib::Sex, ((Unknown,0))((Male,1))((Female,2))((Unspecified,3)))
