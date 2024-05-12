
#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/Timestamp.h>

#include <Framework/Chrono/Public/ChronoIo.h>

#include <iosfwd>

namespace DFL
{
namespace Format
{
class Stream;
}
}

namespace boost
{
namespace chrono
{

/**
 * @brief Stream data to given stream.
 *
 * This operator is in boost::chrono. That's because DFL::Mdib::Timestamp is typedefed to a
 * boost::chrono type. Argument-dependent lookup ignores namespaces introduced by typedef.
 * The operator needs to be in the namespace of the underlying type. There is no stream operator
 * for timepoint in boost::chrono, so we need to define our own.
 *
 * Making Mdib::Timestamp a strong type will probably allow to define this operators in DFL::Mdib
 * if desired.
 *
 * @param out Sink stream
 * @param data Data to stream
 * @return Passed stream
 */
///@{
DFL_MDIB_EXPIMP std::ostream& operator<<(std::ostream& out, const DFL::Mdib::Timestamp& data);
DFL_MDIB_EXPIMP DFL::Format::Stream& operator<<(DFL::Format::Stream& out, const DFL::Mdib::Timestamp& data);
///@}

}
}
