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
class PatientDemographicsCoreData;

/**
 * @brief DFL Format Stream operator for \ref PatientDemographicsCoreData.
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Format::Stream& operator<<(Format::Stream& out, const PatientDemographicsCoreData& data);

/**
 * @brief Stream operator for \ref PatientDemographicsCoreData.
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& out, const PatientDemographicsCoreData& data);

}
}
