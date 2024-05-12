#pragma once

#include <string>

namespace S31::Sdc::Impl
{

/**
 * \brief RFC 3986 matching rule for string comparison.
 *
 * \ingroup S31SdcCommon
 */
class RFC3986Rule
{
    public:

        /// RFC 3986 matching rule according to Section 5.1 of WS-Discovery:
        /// http://docs.oasis-open.org/ws-dd/discovery/1.1/os/wsdd-discovery-1.1-spec-os.html#_Toc234231830
        /// For example, S1 = "http://example.com/abc" matches S2 = "http://example.com/abc/def" using this rule
        /// but S1 = "http://example.com/a" does not matches S2.
        static bool match(const std::string& s1, const std::string& s2);

    private:
        static bool isDotSegment(const std::string& segment);
};

}
