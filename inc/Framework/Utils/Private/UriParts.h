#pragma once

#include <Framework/Utils/Private/ExpImp.h>

#include <boost/optional.hpp>
#include <boost/range/iterator_range.hpp>

namespace DFL
{
namespace Net
{
namespace Impl
{

/**
 * @brief   Container for iterator ranges of an URIs hierarchical part.
 * @details These ranges are filled during parsing in @ref DFL::Net::Uri.
 *          They provide lightweight access to the respective part of the URI via begin() and end().
 * @ingroup Utils
 */
template <class FwdIter>
class DFL_UTILS_EXPIMP HierarchicalPart
{
    public:
        /**@brief Iterator range for user info part of URI.
         */
        boost::optional<boost::iterator_range<FwdIter> > userInfo;

        /**@brief Iterator range for host part of URI.
         */
        boost::optional<boost::iterator_range<FwdIter> > host;

        /**@brief Iterator range for port part of URI.
         */
        boost::optional<boost::iterator_range<FwdIter> > port;

        /**@brief Iterator range for path part of URI.
         */
        boost::optional<boost::iterator_range<FwdIter> > path;

        /**
         * @return Iterator to the beginning of the URIs hierarchical part.
         */
        FwdIter begin() const
        {
            return userInfo.get().begin();
        }

        /**
         * @return Iterator to the end of the URIs hierarchical part.
         */
        FwdIter end() const
        {
            return path.get().end();
        }

        /**@brief Replaces all \c boost::none objects with empty ranges at the sensible position in the URI.
         * @details E.g. the URI "http://localhost/" has no user info component.
         *          During parsing in @ref DFL::Net::Uri, the user info range will be filled with \c boost::none.
         *          Update() is then invoked to have both begin() and end() of the user info range point
         *          to the "l" in "localhost" as this is where the user info component would be.
         */
        void update()
        {
            if (!userInfo)
            {
                if (host)
                {
                    userInfo = boost::iterator_range<FwdIter>(host.get().begin(), host.get().begin());
                }
                else if (path)
                {
                    userInfo = boost::iterator_range<FwdIter>(path.get().begin(), path.get().begin());
                }
            }

            if (!host)
            {
                host = boost::iterator_range<FwdIter>(path.get().begin(), path.get().begin());
            }

            if (!port)
            {
                port = boost::iterator_range<FwdIter>(path.get().begin(), path.get().begin());
            }
        }

        /** @brief Replaces all objects with empty ranges.
         *  @details This is called in @ref DFL::Net::Uri via UriParts::empty() when the parser determines
         *           that the given URI is invalid.
         */
        void empty(FwdIter it)
        {
            userInfo = boost::iterator_range<FwdIter>(it, it);
            host = boost::iterator_range<FwdIter>(it, it);
            port = boost::iterator_range<FwdIter>(it, it);
            path = boost::iterator_range<FwdIter>(it, it);
        }
};

/**
 * @brief   Container for iterator ranges of an URI.
 * @details These ranges are filled during parsing in @ref DFL::Net::Uri.
 *          They provide lightweight access to the respective part of the URI via begin() and end().
 * @ingroup Utils
 */
template <class FwdIter>
class DFL_UTILS_EXPIMP UriParts
{
    public:
        /**@brief Iterator range for scheme part of URI.
         */
        boost::iterator_range<FwdIter> scheme;

        /**@brief Iterator range for hierarchical part of URI.
         */
        HierarchicalPart<FwdIter> hierarchicalPart;

        /**@brief Iterator range for query part of URI.
         */
        boost::optional<boost::iterator_range<FwdIter> > query;

        /**@brief Iterator range for fragment part of URI.
         */
        boost::optional<boost::iterator_range<FwdIter> > fragment;

        /**@brief Replaces all \c boost::none objects with empty ranges at the sensible position in the URI.
         * @details E.g. the URI "http://localhost/path?foo" has no fragment component.
         *          During parsing in @ref DFL::Net::Uri, the fragment range will be filled with \c boost::none.
         *          Update() is then invoked to have both begin() and end() of the fragment range point to the URIs end.
         */
        void update()
        {
            hierarchicalPart.update();

            if (!query)
            {
                query = boost::iterator_range<FwdIter>(hierarchicalPart.end(), hierarchicalPart.end());
            }
            if (!fragment)
            {
                fragment = boost::iterator_range<FwdIter>(query.get().end(), query.get().end());
            }
        }

        /** @brief Replaces all objects with empty ranges.
         *  @details This is called in @ref DFL::Net::Uri when the parser determines that the given URI is invalid.
         */
        void empty()
        {
            scheme = boost::iterator_range<FwdIter>(scheme.begin(), scheme.begin());
            hierarchicalPart.empty(scheme.begin());
            query = boost::iterator_range<FwdIter>(scheme.begin(), scheme.begin());
            fragment = boost::iterator_range<FwdIter>(scheme.begin(), scheme.begin());
        }

};

}
}
}
