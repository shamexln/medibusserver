#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Format/Public/Stream.h>
#include <ostream>
#include <string>

namespace DFL {
namespace Mdib {

class LocationDetail;

/**
 * @brief Generates a human readable representation.
 *
 * Format is not specified. It is typically used for debug log messages.
 * @param str Sink for the LocationDetail
 * @param locationDetail Input data structure to convert to string
 * @return human readable representation of the \ref LocationDetail.
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Format::Stream& operator<<(Format::Stream& str, LocationDetail const& locationDetail);

/**
 * @brief Stream operator for \ref LocationDetail.
 *
 * @param str Sink for the LocationDetail
 * @param locationDetail Data to stream
 * @return the referenced sink (first argument)
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& str, LocationDetail const& locationDetail);

} /* namespace Mdib */
} /* namespace DFL */
