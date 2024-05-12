#pragma once

#include <S31/Localization/Public/Common/LocalizedText.h>
#include <S31/Localization/Public/Common/LocalizedTextReference.h>
#include <S31/Sdc/Public/Client/LocalizationClientRequestComplete.h>

#include <Framework/Mdib/Public/Model/LocalizedText.h>
#include <Framework/Utils/Public/LanguageTag.h>

#include <memory>

namespace S31::Sdc
{

/**
 * @brief Interface to access the localization service of a (remote) device.
 * @details
 * ### Concepts
 *
 * The localization client loads texts from the remote device and holds a cache of already loaded
 * texts. The user triggers a request for texts he is interested in. The client notifies the
 * user when the requested texts are loaded into the client cache. The user can then lookup
 * single texts from the client (cache).
 *
 * ### Error handling
 * Non handleable errors (see @ref Utils::Error) are routed to connection handling. So, an
 * error leads to disconnect.
 *
 * ### Workflow
 * 1. express interest in certain texts by *fetching* them
 * 2. wait for completion
 * 3. use *lookup* from cache to use the texts. If *lookup* cannot provide a text that was triggered
 *    to *fetch* before then the device cannot provide a text for this reference.
 *
 * Notes:
 * - Do @b not first lookup and then fetch texts that are not found through lookup. The client's *fetch* does this already.
 * - *fetch* returns immediately with a completed notifier if the requested texts are in the cache already.
 *
 * @ingroup S31SdcClient
 */
class LocalizationClient
{
    public:
        /// @brief Shortcut for LocalizationClientRequestCompletePtr.
        using Notifier = LocalizationClientRequestCompletePtr;

        using Language = DFL::Locale::LanguageTag;
        using Languages = std::vector<Language>;

        virtual ~LocalizationClient() = default;

        /**
         * @name Fetch to cache
         * @brief Trigger an operation that fetches data from the remote device.
         * @details These functions work asynchronous. The caller can check the status of the fetch
         * operation with the returned notifier object.
         */
        ///@{
        /**
         * @brief Fetch the list of supported languages from the remote device.
         * @details If a *fetch languages* is already running, then no new request started. The already
         * existing notifier will be returned.
         */
        virtual Notifier fetchSupportedLanguages() = 0;

        /**
         * @brief Fetch the the texts for the given references from the devices.
         * @details As texts are invariant the given references are filtered before. References
         * which were fetched already are removed from the list. Because of this there is the
         * case that all given references are already requested before. In this case no network request
         * is triggered at all. The notifier returns in status *completed* immediately.
         */
        virtual Notifier fetch(S31::Localization::LocalizedTextReferences&& references) = 0;
        ///@}

        /**
         * @name Text lookup
         * @brief Getting texts from the cache
         */
        ///@{

        /**
         * @brief Provides the best fitting text if there are matching texts.
         * @details If no such text can be found, then *none* is returned. The active language has to be set before - otherwise an error is raised and *none* is
         * returned.
         */
        virtual boost::optional<Localization::LocalizedText> text(
                const DFL::Mdib::LocalizedTextRef& ref,
                const DFL::Mdib::VersionCounter& version,
                const boost::optional<DFL::Mdib::LocalizedTextWidth>& textWidth = boost::none,
                const boost::optional<Localization::NumberOfLines>& numberOfLines = boost::none) const = 0;

        /**
         * @brief Lookup from a text (containing a reference and version)
         */
        boost::optional<Localization::LocalizedText> text(
                        const DFL::Mdib::LocalizedText& ltext,
                        const boost::optional<DFL::Mdib::LocalizedTextWidth>& textWidth = boost::none,
                        const boost::optional<Localization::NumberOfLines>& numberOfLines = boost::none) const
        {
            if (!ltext.reference().get().empty() && ltext.version())
            {
                return text(ltext.reference(), *ltext.version(), textWidth, numberOfLines);
            }
            return boost::none;
        }

        /**
         * @brief Provides all texts of the given reference (and maybe restricted to a version) from the cache.
         * @details Texts are in the active language. Result may be empty if there are no texts for this reference and version in the cache.
         * @param reference The reference of the text.
         * @param version Version of the text. If this is not set then all versions of the text in the cache are returned.
         */
        virtual Localization::LocalizedTexts texts(
                const DFL::Mdib::LocalizedTextRef& reference,
                const boost::optional<DFL::Mdib::VersionCounter>& version = boost::none) const = 0;
        ///@}

        /**
         * @brief Get the supported languages of the remote device from a previous successful
         * call of @ref fetchSupportedLanguages(). If there was no such call then the returned
         * container is empty.
         */
        virtual Languages supportedLanguages() const = 0;

        /**
         * @brief Sets the active language to the given value.
         * @details The active language represents the language in use on the client (e.g. the
         * language used in the UI). It will be used in fetch or lookup of texts.
         * Changing the active language actually clears the client's cache and reference store. Running text fetch requests will
         * be notified as completed immediately.
         */
        virtual void setActiveLanguage(const Language& lang) = 0;

};

using LocalizationClientPtr = std::shared_ptr<LocalizationClient>;

}
