#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Defines an association between an arbitrary context and the system.
 * @details E.g., a context might be a specific location or patient that is associated
 * to a medical device (or the %Mdib of that device).
 * @ingroup Mdib
 */
enum class ContextAssociation
{
    /// There is no sensible context association derivable
    NotAssociated,

    /// Context information is in a pre-association state.
    PreAssociated,

    /// Context information is associated.
    Associated,

    /// Context information is no longer associated.
    Disassociated
};
DFL_ENUM_CLASS_STREAM_OPERATOR(ContextAssociation, (NotAssociated)(PreAssociated)(Associated)(Disassociated))

}
}

// Do not change the enum value integer mapping.
// It is used for serialization and might be persisted.
DFL_ENUM_CLASS_SERIALIZATION(::DFL::Mdib::ContextAssociation, ((NotAssociated,0))((PreAssociated,1))((Associated,2))((Disassociated,3)))
