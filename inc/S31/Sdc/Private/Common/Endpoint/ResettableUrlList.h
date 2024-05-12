#pragma once

#include <S31/Sdc/Private/Common/Endpoint/UrlList.h>
#include <S31/S31CoreExImp.h>

#include <mutex>
#include <vector>

namespace S31::Sdc::Impl::Endpoint
{

/**
 * @brief Provides a prioritized URL list implementation with resettable URL lists.
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP ResettableUrlList: public UrlList
{
    public:
        /**
          * @brief Creates a list with no enclosed URLs.
          */
        ResettableUrlList();

        /**
         * @brief Creates a list with the given ordered sequence of URLs.
         * @param urls For all indices i, j with j > i: the vector entry at index i has a higher priority than the entry at index j
         */
        explicit ResettableUrlList(const std::vector<Url>& urls); // NOLINT(modernize-pass-by-value)

        void removeUrl(const Url& url) override;

        boost::optional<Url> nextAvailableUrl() const override;

        void clear() override;

        /**
         * @brief Resets list with the given one.
         */
        void resetUrls(const std::vector<Url>& urls);

    private:
        mutable std::mutex m_urlsMutex;
        std::vector<Url> m_urls;
};

}
