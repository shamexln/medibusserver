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
class OperationGroup;

/**
 * @brief Stream operator for output.
 *
 * @param out returned output stream
 * @param operationGroup to stream
 * @return the passed stream (first argument)
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& out, OperationGroup const& operationGroup);

/**
 * @brief Stream operator for debug output.
 * @param out returned output stream
 * @param operationGroup to stream
 * @return the passed stream (first argument)
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Format::Stream& operator<<(Format::Stream& out, OperationGroup const& operationGroup);

} /* namespace Mdib */
} /* namespace DFL */
