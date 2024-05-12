#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <Framework/Utils/Private/UriParts.h>

#include <boost/range/iterator_range.hpp>

#include <iterator>
#include <string>
#include <utility>
#include <vector>

namespace DFL
{
namespace Net
{

/**
 * @brief   Container for Uniform Resource Identifier (URI).
 * @details The class acts as a lightweight wrapper for a URI string and provides access to an URI's individual parts.
 *          See <a href="https://tools.ietf.org/html/rfc3986">RFC3986</a> for reference.
 *          The string provided is parsed on construction and throws a runtime error if the string is not a valid URI.
 *          Relative URIs are treated as invalid.
 *          Here are examples of valid URIs and their individual parts.
 * @snippet Utils/Test/UnitTest/TestUri.cpp ValidUris
 *          On the contrary, here are examples of invalid URIs.
 * @snippet Utils/Test/UnitTest/TestUri.cpp InvalidUris
 * @ingroup Utils
 */
class DFL_UTILS_EXPIMP Uri
{
    public:

        /** @brief String type used. */
        using string_type = std::string;

        /** @brief Constant iterator type used. */
        using const_iterator = string_type::const_iterator;

        /** @brief Constant range type used. */
        using const_range_type = boost::iterator_range<const_iterator>;

        /**
         * @brief Ctor.
         */
        explicit Uri(string_type uri);

        /**
         * @brief Equality method checking whether two URIs have the same underlying string representation.
         * @return True if underlying strings are the same.
         */
        bool equals(const Uri& other) const;

        /**
         * @brief Provides access to the underlying URI string.
         * @return String representation of URI string.
         */
        const string_type& str() const;

        /**
         * @brief Provides iterator to the underlying URI string.
         * @return Iterator to the beginning of the URI string.
         */
        const_iterator begin() const;

        /**
         * @brief Provides iterator to the underlying URI string.
         * @return Iterator to the end of the URI string.
         */
        const_iterator end() const;

        /**
         * @brief Provides iterator to the underlying const URI string.
         * @return Iterator to the beginning of the URI string.
         */
        const_iterator cbegin() const;

        /**
         * @brief Provides iterator to the underlying const URI string.
         * @return Iterator to the end of the URI string.
         */
        const_iterator cend() const;

        /**
         * @brief Provide iterator range to the URI's scheme.
         * @return Iterator range for scheme part
         */
        const_range_type schemeRange() const;

        /**
         * @brief Provide iterator range to the URI's authority.
         * @return Iterator range for authority part
         */
        const_range_type authorityRange() const;

        /**
         * @brief Provide iterator range to the URI's user info.
         * @return Iterator range for user info part
         */
        const_range_type userInfoRange() const;

        /**
         * @brief Provide iterator range to the URI's host.
         * @return Iterator range for host part
         */
        const_range_type hostRange() const;

        /**
         * @brief Provide iterator range to the URI's port.
         * @return Iterator range for port part
         */
        const_range_type portRange() const;

        /**
         * @brief Provide iterator range to the URI's path.
         * @return Iterator range for path part
         */
        const_range_type pathRange() const;

        /**
         * @brief Provide iterator range to the URI's query.
         * @return Iterator range for query part
         */
        const_range_type queryRange() const;

        /**
         * @brief Provide iterator range to the URI's fragment.
         * @return Iterator range for fragment part
         */
        const_range_type fragmentRange() const;

        /**
         * @brief String representation of scheme.
         * @return String containing the scheme of the URI.
         */
        string_type scheme() const;

        /**
         * @brief string representation of authority.
         * @return String containing the authority of the URI.
         */
        string_type authority() const;

        /**
         * @brief string representation of user info.
         * @return String containing the user info of the URI.
         */
        string_type userInfo() const;

        /**
         * @brief string representation of host.
         * @return String containing the host of the URI.
         */
        string_type host() const;

        /**
         * @brief string representation of port.
         * @return String containing the port of the URI.
         */
        string_type port() const;

        /**
         * @brief string representation of path.
         * @return String containing the path of the URI.
         */
        string_type path() const;

        /**
         * @brief string representation of query.
         * @return String containing the query of the URI.
         */
        string_type query() const;

        /**
         * @brief string representation of fragment.
         * @return String containing the fragment of the URI.
         */
        string_type fragment() const;

        /**
         * @brief Method to extract the query parameter to a certain key.
         * @details Here are examples of Key-Value Pairs for certain URIs.
         * @snippet Utils/Test/UnitTest/TestUri.cpp KeyValue
         * @return Parameter associated with key, @c none if "key=" is not found in query part of URI.
         */
        boost::optional<string_type> queryParam(const string_type& key) const;

        /**
         * @brief Method to extract path segments.
         * @details Here are examples of URIs and their extracted path segments.
         * @snippet Utils/Test/UnitTest/TestUri.cpp PathSegments
         * @return Vector containing all path segments.
         */
        std::vector<string_type> pathSegments() const;

    private:
        string_type m_uri;

        using Offset = std::iterator_traits<string_type::iterator>::difference_type;
        Offset m_schemeEndOffset{}; // Scheme must always start at the beginning of the uri
        std::pair<Offset, Offset> m_userInfoOffsets;
        std::pair<Offset, Offset> m_hostOffsets;
        std::pair<Offset, Offset> m_portOffsets;
        std::pair<Offset, Offset> m_pathOffsets;
        std::pair<Offset, Offset> m_queryOffsets;
        Offset m_fragmentBeginOffset{}; // Fragment end is always the end of the uri

        void parse();
        void initOffsets(const Impl::UriParts<string_type::iterator>& uriParts);

};

/**
 * @brief Equal and unequal operators compare underlying string.
 * @ingroup Utils
 */
///@{
bool DFL_UTILS_EXPIMP operator==(const Uri& lhs, const Uri& rhs);
bool DFL_UTILS_EXPIMP operator!=(const Uri& lhs, const Uri& rhs);
///@}

/**
 * @brief Converts given string to a URI.
 * @return @c none in case an invalid URI string is provided, otherwise @c optional<Uri>.
 * @ingroup Utils
 */
boost::optional<Uri> DFL_UTILS_EXPIMP toUri(const Uri::string_type& uriString);

}
}

