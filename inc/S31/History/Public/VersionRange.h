#pragma once

#include <S31/History/Private/S31HistoryExImp.h>

#include <Framework/Mdib/Public/Model/MdibVersion.h>

namespace S31::History
{
/**
 * @brief Request filter for historic MDIB data based on a version range.
 * @details
 * Such a request contains one MDIB sequence.
 * @ingroup S31CoreHistory
 */
class S31_HISTORY_EXPIMP VersionRange
{
public:
    VersionRange(DFL::Mdib::MdibVersion start, DFL::Mdib::VersionCounter end);

    const DFL::Mdib::MdibVersion& startVersion() const noexcept;
    DFL::Mdib::VersionCounter endVersion() const noexcept;

private:
    /**
     * @brief Start version with sequence and instance ID.
     */
    DFL::Mdib::MdibVersion m_startVersion;

    /**
     * @brief End version for same sequence and instance ID as in start version.
     */
    DFL::Mdib::VersionCounter m_endVersion;
};
}
