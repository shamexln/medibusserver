#pragma once

#include <S31/S31CoreExImp.h>

#include <string>
#include <vector>

namespace S31::Sdc::Impl
{

/**
 * General helper functions for Uri (Url and Urn) handling.
 *
 * \ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP UriUtils
{
    public:

        /**
         * @brief Normalizes any UUID URNs.
         *
         * @details
         * In old version the EPR of a DPWS device was uuid:836ccf70-e3c6-420a-91db-b6214f6368aa.
         * The correct EPR (as specified later) is urn:uuid:836ccf70-e3c6-420a-91db-b6214f6368aa.
         * Furthermore it is case insensitive (all lower case).
         */
        static std::string normalizeUrnUuidPrefix(const std::string& uuid);

        /**
         * Returns the (lowercase) scheme of an URI.
         */
        static std::string getSchemeFromUri(const std::string& uri);

        /**
         * Returns the Authority (user info @ host : port) of an URL.
         *
         * If an URN is given, it will be an empty string.
         */
        static std::string getAuthorityFromUrl(const std::string& url);

        /**
         * Splits a path into url-decoded segments.
         *
         * E.g., "/abc/a%20b" into "abc" and "a b".
         */
        static std::vector<std::string> splitPathToDecodedSegments(const std::string& path);

        static std::string extractPath(const std::string& uri);

        /**
         * Extracts the query part of an URL.
         *
         * E.g., "foo=bar" from "http://example.com/abc?foo=bar#top".
         */
        static std::string extractQuery(const std::string& url);

        /**
         * Get the parameter value of a given key from a query (parts of URL).
         *
         * E.g. for "bar" in "bar=foo&what=all" it is "foo".
         */
        static std::string getParamValueFromQuery(const std::string& key, const std::string& query);

        static std::string getParamValueFromUrl(const std::string& key, const std::string& url);

        static std::string urlEncode(const std::string& raw);
        static std::string urlDecode(const std::string& percentEncoded);

        /**
         * Converts a two byte hex string to the corresponding character.
         */
        static unsigned char hexToChar(const std::string& str);

        static void split(std::vector<std::string>& parts, const std::string& uri, const std::string& delimiters);

        static bool endsWith(const std::string& uri, const char character);
};

}
