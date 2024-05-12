#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibChangeType.h>

/// Things from here shall not end up in production code.
namespace S31::Sdc::Experimental
{

/**
 * @brief Make (xml-) reports from Mdib + change set.
 */
S31_CORE_EXPIMP std::string makeReport(const DFL::Mdib::MdibChangeSet& changes, const DFL::Mdib::Mdib& mdib, DFL::Mdib::MdibChangeType changeType);
}
