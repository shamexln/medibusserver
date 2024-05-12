#pragma once

#include <Framework/Log/Public/Message.h>

#include <algorithm>
#include <numeric>
#include <string>
#include <string_view>
#include <utility>

namespace S31::Sdc::Test
{
namespace TlsLogMessageStrings
{
inline constexpr std::string_view CertMsgIndicator{") Cert: "};
inline constexpr std::string_view BeginCert{"-----BEGIN CERTIFICATE-----"};
inline constexpr std::string_view EndCert{"-----END CERTIFICATE-----"};
}

/// @brief Helper function to find a chunked Pem string in a log.
/// @details A Pem string is generally too long to fit in a single log message,
/// so it is chunked into multiple messages.  This helper locates the log
/// messages containing the Pem string.
/// @param first Iterator to the begin of a Log message container
/// @param last Iterator to the end of a Log message container
template<class LogIterator>
std::pair<LogIterator, LogIterator> findPemStringInLogMessages(LogIterator first, LogIterator last)
{
    using namespace TlsLogMessageStrings;
    auto pemStringBegin = std::find_if(
            first,
            last,
            [](const DFL::Log::Message& m)
            {
                auto messageText = std::string_view{m.text().cStr()};
                return messageText.find(BeginCert) != std::string_view::npos;
            });

    auto pemStringEnd = std::find_if(
            first,
            last,
            [](const DFL::Log::Message& m)
            {
                auto messageText = std::string_view{m.text().cStr()};
                return messageText.find(EndCert) != std::string_view::npos;
            });

    return std::make_pair(pemStringBegin, pemStringEnd);
}


/// @brief Helper function to rebuild a Pem string from debug log messages.
/// @details A Pem string is generally too long to fit in a single log message,
/// so it is chunked into multiple messages.  This helper extracts the string from
/// multiple messages.
/// @param first Iterator to message containing BEGIN CERTIFICATE
/// @param last Iterator to message containing END CERTIFICATE
template<class LogIterator>
std::string reassemblePemStringFromLogMessages(LogIterator first, LogIterator last)
{
    using namespace TlsLogMessageStrings;
    return std::accumulate(
            first,
            last + 1,
            std::string{},
            [](std::string pemData, const DFL::Log::Message& m)
            {
                auto messageText = std::string_view{m.text().cStr()};
                auto chunkStart  = messageText.find(CertMsgIndicator);

                if (chunkStart != std::string_view::npos)
                {
                    auto pemChunk = std::string{messageText.substr(chunkStart + CertMsgIndicator.length())};

                    if (pemChunk.find(BeginCert) != std::string::npos)
                    {
                        // Need a newline after 'Begin'
                        pemChunk.insert(BeginCert.length(), "\r\n");
                    }

                    if (const auto endCertPos = pemChunk.find(EndCert); endCertPos != std::string::npos)
                    {
                        // Need a newline before 'End'
                        pemChunk.insert(endCertPos, "\r\n");
                    }

                    pemData += pemChunk;
                    pemData += "\r\n";
                }
                return pemData;
            });
}

}
