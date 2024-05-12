#pragma once

#include <S31/History/Private/Bundle.h>
#include <S31/History/Private/MdibSequence.h>
#include <S31/History/Public/Configuration.h>
#include <S31/History/Public/InMemoryHistoryService.h>

#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibSmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Timestamp.h>
#include <Framework/Utils/Public/NotNull.h>

#include <boost/circular_buffer.hpp>

#include <deque>
#include <memory>
#include <mutex>
#include <optional>
#include <tuple>
#include <vector>

namespace S31::History::Impl
{

/**
 * @brief Container type for bundles.
 */
using BundleContainerType = boost::circular_buffer<Bundle>;

/**
 * @brief Sequence information for the bundle container.
 * @details
 * To avoid storing the same MDIB sequence information with all bundles they are stored in this class.
 * Furthermore it provides faster access to specific MDIB sequences.
 */
class SeqData
{
public:
    SeqData(MdibSequence seq, BundleContainerType::iterator first);

    BundleContainerType::const_iterator begin() const
    {
        return m_first;
    }
    BundleContainerType::const_iterator end() const
    {
        auto end = m_last;
        return ++end;
    }

    Bundle& last()
    {
        return *m_last;
    }
    const Bundle& last() const
    {
        return *m_last;
    }
    Bundle& first()
    {
        return *m_first;
    }
    const Bundle& first() const
    {
        return *m_first;
    }

    bool empty() const
    {
        return !m_size;
    }

    std::size_t size() const
    {
        return m_size;
    }

    void moveFirst()
    {
        --m_size;
        ++m_first;
    }

    void moveLast()
    {
        ++m_last;
        ++m_size;
    }

    DFL::Mdib::Timestamp startTime() const
    {
        return m_first->firstTime();
    }

    const MdibSequence& sequence() const
    {
        return m_sequence;
    }

private:
    MdibSequence                  m_sequence;
    std::size_t                   m_size{1};
    BundleContainerType::iterator m_first;
    BundleContainerType::iterator m_last;
};

class InMemoryDataStore : public std::enable_shared_from_this<InMemoryDataStore>, public StoreInterface
{
public:
    explicit InMemoryDataStore(Configuration configuration);

    void
    store(const DFL::Mdib::Mdib&          mdib,
          const DFL::Mdib::MdibChangeSet& changes,
          DFL::Mdib::MdibChangeType       changeType,
          std::string_view                bicepsXmlReportMessage) override;

    const CompressionLevel m_compressionLevel;
    std::deque<SeqData>    m_data{};
    const std::size_t      m_maxNumberOfBundles{};
    const std::size_t      m_reportBundleSize{1};
    const unsigned int     m_mdibSnapshotPeriod{1};

    BundleContainerType m_bundles;

    struct Iterator
    {
        inline Iterator(std::deque<SeqData>::const_iterator seqIt, BundleContainerType::const_iterator versionIt)
            : seqIt{std::move(seqIt)}
            , versionIt{versionIt}
        {
        }

        inline bool operator== (const Iterator& rhs) const
        {
            return seqIt == rhs.seqIt && versionIt == rhs.versionIt;
        }

        inline bool operator!= (const Iterator& rhs) const
        {
            return !(*this == rhs);
        }

        std::deque<SeqData>::const_iterator seqIt;
        BundleContainerType::const_iterator versionIt;
    };

    Iterator begin() const; // test only
    Iterator end() const;

    Iterator lowerBound(const MdibSequence& seq, DFL::Mdib::VersionCounter version, InitialMdib initialMdib) const;
    Iterator upperBound(const MdibSequence& seq, DFL::Mdib::VersionCounter version) const;

    Iterator lowerBound(DFL::Mdib::Timestamp time, InitialMdib initialMdib) const;
    Iterator upperBound(DFL::Mdib::Timestamp time) const;

    /**
     * @brief Creates a hm:ChangeSequenceReport string.
     */
    std::string createChangeSequenceReport(const Iterator& it, InitialMdib initialMdib) const;

    MdibSequence sequence(const Iterator& it) const;
    Iterator next(Iterator it) const;

    /**
     * @brief Number of MDIB report chunks across MDIB sequences.
     */
    std::size_t countReportChunks() const;

    /**
     * @brief Debug string.
     */
    std::string currentInternalStatus() const override;

private:
    void compressLastDataBlockIfRequired();

    struct Statistics
    {
        std::size_t uncompressedMdibSize{};
        std::size_t compressedMdibSize{};
        std::size_t numberOfMdibs{};
        std::size_t uncompressedReportSize{};
        std::size_t compressedReportSize{};
        std::size_t numberOfReportBundles{};
    };

    Statistics extractStatisticsNoLock() const;

    mutable std::mutex m_mutex;
};

}  // namespace S31::History::Impl
