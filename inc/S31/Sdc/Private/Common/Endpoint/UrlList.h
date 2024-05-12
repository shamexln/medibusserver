#pragma once

#include <S31/Sdc/Private/Common/Endpoint/EndpointUrl.h>

#include <boost/optional/optional.hpp>

namespace S31::Sdc::Impl::Endpoint
{

/**
 * @brief Provides a prioritized URL list interface.
 * @ingroup S31SdcCommon
 */
class UrlList
{
    public:
        virtual ~UrlList() = default;

        /**
         * @brief Removes the URL from the list.
         */
        virtual void removeUrl(const Url& url) = 0;

        /**
         * @brief Resolves the next available URL with the highest priority.
         * @return The URL with the highest priority from the list or \c boost::none if the list is empty.
         */
        virtual boost::optional<Url> nextAvailableUrl() const = 0;

        /**
         * @brief Clears the URL list.
         */
        virtual void clear() = 0;
};

}
