#pragma once

#include <boost/optional/optional.hpp>
#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/CodeId.h>

namespace DFL
{
namespace Mdib
{
class CodedValue;

namespace Convert
{

/**
 * @brief Convert a CodedValue to the context free code of ISO/IEEE 11073-10101.
 * @param code Code to convert.
 * @return context free ISO/IEEE 11073-10101 code (if available) or <tt>boost::none</tt>
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP boost::optional<CodeId> toOptionalIeeeCfCodeString(CodedValue const& code);

} /* namespace Convert */
} /* namespace Mdib */
} /* namespace DFL */
