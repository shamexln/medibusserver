#pragma once

#include <S31/History/Public/Result.h>
#include <S31/History/Public/Query.h>

#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibChangeType.h>

#include <string_view>

namespace S31::History
{

/**
 * @brief Request interface for a history service implementation.
 * @details
 * Depend on this interface in case read/request is only required from an instance. Otherwise, use the combined service
 * interface \ref S31::History::Service.
 * @ingroup S31CoreHistory
 */
class RequestInterface
{
public:
    virtual ~RequestInterface() noexcept = default;

    /**
     * @brief Request MDIB data from history service.
     * @details
     * The historic data might be in different MDIB sequences depending on the request.
     * @return Relevant historic data.
     */
    virtual Result request(const Query& query) const = 0;
};

/**
 * @brief Insert/write interface for a history service implementation.
 * @details
 * Depend on this interface in case inserting MDIB data is only required function from a history service instance.
 * Otherwise, use the combined service interface \ref S31::History::Service.
 * @ingroup S31CoreHistory
 */
class StoreInterface
{
public:
    virtual ~StoreInterface() noexcept = default;

    /**
     * @brief Store MDIB data in history service.
     * @details
     * The historic data that shall be stored in the history service.
     */
    virtual void
    store(const DFL::Mdib::Mdib&          mdib,
          const DFL::Mdib::MdibChangeSet& changes,
          DFL::Mdib::MdibChangeType       changeType,
          std::string_view                bicepsXmlReportMessage) = 0;

    /**
     * @brief Debug string with the internal status of the store.
     * @details
     * Should contain information how much data is stored with compression rate etc.
     */
    virtual std::string currentInternalStatus() const = 0;
};


/**
 * @brief Abstract interface of the history service.
 * @details
 * Different implementations are possible, from volatile in memory storage up to persistence on the SD card.
 * @ingroup S31CoreHistory
 */
class Service : public RequestInterface, public StoreInterface
{
};

}  // namespace S31::History
