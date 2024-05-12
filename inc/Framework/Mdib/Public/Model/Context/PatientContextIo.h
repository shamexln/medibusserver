#pragma once

#include <Framework/Mdib/Private/ExpImp.h>

#include <iosfwd>

namespace DFL
{
namespace Format
{
class Stream;
}
namespace Mdib
{

class PatientContext;

/**
 * @brief Generates a human readable representation of \ref PatientContext.
 */
DFL_MDIB_EXPIMP Format::Stream& operator<<(Format::Stream& out, PatientContext const& data);

/**
 * @brief Stream operator for \ref PatientContext.
 */
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& out, PatientContext const& data);

}
}
