#pragma once

#include <S31/Comp/S31Only/Deflate.h>
#include <S31/History/Public/ResultImpl.h>
#include <S31/History/Public/Service.h>

#include <Framework/Encoding/Public/Convert.h>

namespace S31::History::Test
{

enum class Payload
{
    NoCompression,
    Compress
};

class DummyResult;

class DummyIt : public ResultItImpl, public std::enable_shared_from_this<DummyIt>
{
public:
    explicit DummyIt(std::shared_ptr<const DummyResult> result)
        : m_result{std::move(result)}
    {
        m_report.report = createReport(1);
    }
    std::shared_ptr<ResultItImpl> next() override;
    ChangeSequenceReport&         data() override
    {
        return m_report;
    }

    bool equals(const ResultItImpl& rhs) const override
    {
        if (const auto* r = dynamic_cast<const DummyIt*>(&rhs))
        {
            return m_currentPos == r->m_currentPos;
        }
        return false;
    }

private:
    std::string createReport(int pos);

    std::shared_ptr<const DummyResult> m_result;
    int                                m_currentPos{};
    ChangeSequenceReport               m_report;
};

class DummyResult : public ResultImpl, public std::enable_shared_from_this<DummyResult>
{
public:
    DummyResult(int numberOfReports, Payload payload)
        : m_numberOfReports{numberOfReports}
        , m_payload{payload}
    {
    }
    ResultIt begin() const override
    {
        if (m_numberOfReports)
        {
            return ResultIt{shared_from_this(), std::make_shared<DummyIt>(shared_from_this())};
        }
        return {};
    }
    int numberOfReports() const noexcept
    {
        return m_numberOfReports;
    }

    bool compressPayload() const
    {
        return m_payload == Payload::Compress;
    }

private:
    int     m_numberOfReports;
    Payload m_payload;
};

inline std::string DummyIt::createReport(int pos)
{
    auto payload = "<d:a xmlns:d=\"urn:abc\">" + std::to_string(pos) + "</d:a>";
    if (m_result->compressPayload())
    {
        return DFL::Encoding::Convert::Bytes::asString(Comp::Deflate::compress(payload).gzipBytes());
    }
    return payload;
}


inline std::shared_ptr<ResultItImpl> DummyIt::next()
{
    ++m_currentPos;
    if (m_currentPos >= m_result->numberOfReports())
    {
        // last report already provided, end()
        return {};
    }
    m_report.report = createReport(m_currentPos + 1);
    return shared_from_this();
}
/**
 * @brief Dummy for test purposes.
 */
class DummyService : public Service
{
public:
    explicit DummyService(int numberOfReports, Payload payload = Payload::NoCompression)
        : m_numberOfReports{numberOfReports}
        , m_payload{payload}
    {
    }

    Result request(const Query& /*query*/) const override
    {
        return Result{std::make_shared<DummyResult>(m_numberOfReports, m_payload)};
    }

    void
    store(const DFL::Mdib::Mdib& /*mdib*/,
          const DFL::Mdib::MdibChangeSet& /*changes*/,
          DFL::Mdib::MdibChangeType /*changeType*/,
          std::string_view /*bicepsXmlReportMessage*/) override
    {
        // dummy service has its own data
    }

    std::string currentInternalStatus() const override
    {
        return "The dummy service has no stored data. It generated dummy data.";
    }

private:
    int     m_numberOfReports;
    Payload m_payload;
};

}  // namespace S31::History::Test
