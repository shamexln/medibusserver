#pragma once

#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/Model/Timestamp.h>
#include <Framework/Utils/Public/EnumClass.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <string>

namespace S31::History::Impl
{

struct CompressionLevelTag;
using CompressionLevel =
        DFL::StrongTypedef<int, struct CompressionLevelTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

enum class MdibSnippet
{
    Include,
    Skip
};

class Bundle
{
public:
    Bundle(CompressionLevel       compressionLevel,
           MdibSnippet            mdibSnippet,
           const DFL::Mdib::Mdib& mdib,
           std::string_view       bicepsXmlReportMessage,
           DFL::Mdib::Timestamp   time);

    /**
     * @brief Optional MDIB as XML string.
     * @details
     * To save memory not for all MDIB report bundles an MDIB snapshot is stored.
     * From this it follows that this field might be empty if no such MDIB snapshot is available.
     * To find a sync point previous data entries must be evaluated.
     */
    const std::string& mdib() const;

    /**
     * @brief (Calculates) the version of the first MDIB report.
     */
    DFL::Mdib::VersionCounter firstVersion() const noexcept;

    DFL::Mdib::VersionCounter lastVersion() const;

    /**
     * @brief Concatenation of all MDIB reports (raw XML or gzip compressed).
     * @details
     * It include the \c HistoricReport xml tag so that it can be used afterwards without further analysis.
     * As long as additional reports might be added the XML data is uncompressed. Afterwards it will be gzip
     * compressed with sync end to allow concatenating it with other gzip compressed chunks.
     */
    const std::string& bicepsXmlReportMessage() const;

    /**
     * @brief Timestamp of the first MDIB report.
     * @details
     * If there is only one report \c firstTime() and \c lastTime() will have the same timestamp.
     */
    DFL::Mdib::Timestamp firstTime() const;

    DFL::Mdib::Timestamp lastTime() const;

    /**
     * @brief Current number of MDIB reports in this instance.
     * @details
     * This data structure collects MDIB reports and store in this variable the current number.
     * It could be used to check if the bucket is full based on current configuration.
     */
    std::size_t numberOfBicepsReportMessages() const;

    /**
     * @brief Adds another report to the existing ones.
     */
    void appendReport(DFL::Mdib::VersionCounter version, std::string_view report, DFL::Mdib::Timestamp time);

    /**
     * @brief Compresses the reports string.
     * @details
     * Afterwards no more reports can be appended.
     */
    void compressReports(CompressionLevel level);

private:
    std::string               m_mdib;
    DFL::Mdib::VersionCounter m_lastVersionCounter;
    std::string               m_bicepsXmlReportMessage;
    DFL::Mdib::Timestamp      m_firstTime;
    DFL::Mdib::Timestamp      m_lastTime;
    std::size_t               m_numberOfBicepsReportMessages{1};
};
}  // namespace S31::History::Impl
