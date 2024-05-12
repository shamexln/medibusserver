#pragma once

#include <S31/History/Private/S31HistoryExImp.h>
#include <S31/History/Public/Configuration.h>
#include <S31/History/Public/Service.h>

#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <memory>
#include <string>

namespace S31::History
{
namespace Impl
{
class InMemoryDataStore;
}  // namespace Impl


/**
 * @brief In memory (RAM) history service implementation.
 * @details
 * This history service implementation holds all required data in RAM.
 *
 * @ingroup S31CoreHistory
 */
class S31_HISTORY_EXPIMP InMemoryHistoryService : public Service
{
public:
    /**
     * @brief Construct with configuration.
     *
     * @param configuration Given configuration about storage.
     */
    explicit InMemoryHistoryService(Configuration configuration);

    /**
     * @name Service interface
     * @{
     */
    History::Result request(const Query& query) const override;

    void
    store(const DFL::Mdib::Mdib&          mdib,
          const DFL::Mdib::MdibChangeSet& changes,
          DFL::Mdib::MdibChangeType       changeType,
          std::string_view                bicepsXmlReportMessage) override;
    /// @}

    /**
     * @brief Debug string of current in memory data.
     */
    std::string currentInternalStatus() const override;

private:
    class Result;
    class ResultIt;

    DFL::NotNull<std::shared_ptr<Impl::InMemoryDataStore>> m_store;
};

}
