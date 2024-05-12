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
class BaseDemographics;

/**
 * @brief Stream operator for output.
 *
 * @param out returned output stream
 * @param baseDemographics @ref DFL::Mdib::BaseDemographics value to stream
 * @return the passed stream (first argument)
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& out, const BaseDemographics& baseDemographics);

/**
 * @brief Stream operator for output.
 *
 * @param out returned output stream
 * @param baseDemographics @ref DFL::Mdib::BaseDemographics value to stream
 * @return the passed stream (first argument)
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Format::Stream& operator<<(Format::Stream& out, const BaseDemographics& baseDemographics);

}
}
