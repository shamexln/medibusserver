#pragma once

#include <S31/Localization/Public/Client/LocalizedTextStore.h>
#include <S31/Localization/Public/Common/LocalizedTextReference.h>
#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Private/Client/Localization/ErrorDefinitions.h>
#include <S31/Sdc/Private/Client/Localization/GetLocalizedTextJob.h>
#include <S31/Sdc/Private/Client/Localization/GetSupportedLanguagesJob.h>
#include <S31/Sdc/Private/Client/Localization/LocalizationClientRequestCompleteImpl.h>
#include <S31/Sdc/Private/Client/Localization/LocalizedTextsExecutor.h>
#include <S31/Sdc/Private/Common/Endpoint/Executor.h>
#include <S31/Sdc/Public/Client/LocalizationClient.h>
#include <S31/Utils/Public/Errors.h>
#include <S31/Utils/Public/Outcome.h>

#include <Framework/Mdib/Public/Model/MdibVersionIo.h>
#include <Framework/Utils/Public/NotNull.h>

#include <algorithm>
#include <map>
#include <memory>
#include <mutex>


namespace S31::Sdc::Impl
{
namespace LocalizationImpl
{
class LocalizationClientRequestCompleteImpl;
}

/// Alias for the right LocalizedTextExecutor
using LocalizedTextExecutorPtr = std::shared_ptr<LocalizationImpl::LocalizedTextExecutor<GetLocalizedTextJob>>;

/**
 * @brief Implementation of the @ref S31::Sdc::LocalizationClient.
 *
 * @details
 * ### Text store and already requested references
 *
 * N.B. This section relates to the concept that we want to use a cache and want to avoid double requests.
 *
 * This class contains - beside the store of received localized texts - a container of the already requested references.
 * Rationale for this is: If the user wants to fetch a reference then it is not determinable whether the reference was looked
 * up before or not by only looking into the store(!). The store may have a match but the device may have - a still unrequested -
 * better fitting text. E.g. the user first requests a certain text with text width s and gets one (t_s). Later the user
 * wants the same text with text width xl. The text t_s would be a match for this, but there may be a better/larger text
 * on the device. Therefore we have to check whether a given reference was requested before or not.
 *
 * @ingroup S31SdcClient
 */
template<class SupportedLanguagesJob>
class LocalizationClientImpl:
        public LocalizationClient,
        public std::enable_shared_from_this<LocalizationClientImpl<SupportedLanguagesJob>>,
        public Utils::OutcomeConsumer<LocalizationClientImpl<SupportedLanguagesJob>, Sdc::Impl::GetSupportedLanguagesJobResult>
{
    public:
        using OutcomeType = typename Utils::OutcomeConsumer<LocalizationClientImpl<SupportedLanguagesJob>, Sdc::Impl::GetSupportedLanguagesJobResult>::OutcomeType;

        LocalizationClientImpl(const DFL::Mdib::MdibVersion& mdibVersion, // NOLINT(modernize-pass-by-value)
                               Endpoint::Executor executor,
                               Utils::WeakErrorHandler errorHandler);

        Notifier fetchSupportedLanguages() override;

        Notifier fetch(S31::Localization::LocalizedTextReferences&& references) override;

        boost::optional<S31::Localization::LocalizedText> text(
                const DFL::Mdib::LocalizedTextRef& ref,
                const DFL::Mdib::VersionCounter& version,
                const boost::optional<DFL::Mdib::LocalizedTextWidth>& textWidth,
                const boost::optional<S31::Localization::NumberOfLines>& numberOfLines) const override;

        S31::Localization::LocalizedTexts texts(
                const DFL::Mdib::LocalizedTextRef& reference,
                const boost::optional<DFL::Mdib::VersionCounter>& version) const override;

        Languages supportedLanguages() const override;

        void setActiveLanguage(const Language& lang) override;

    private:

        /// Get m_locLocalizedTextExecutorPtr, lazy creation, this cannot be done in ctor (due to callbacks).
        DFL::NotNull<LocalizedTextExecutorPtr> localizedTextExecutor();

        /// @name Callbacks from text request executor
        /// @{
        void gotResults(LocalizationImpl::Execution::TransactionId id, S31::Localization::LocalizedTextReferences&& refs, DFL::Mdib::LocalizedTexts&& texts);
        void completed(LocalizationImpl::Execution::TransactionId id, const boost::optional<S31::Utils::Error>& error);
        /// @}

        void raiseError(const Utils::Error& error) const;

        const DFL::Mdib::MdibVersion m_mdibVersion;
        Endpoint::Executor m_executor;
        mutable Utils::WeakErrorHandler m_errorHandler;
        LocalizedTextExecutorPtr m_localizedTextExecutor;

        mutable std::mutex m_mutex;
        Languages m_supportedLanguages;
        Language m_activeLanguage;
        S31::Localization::Client::LocalizedTextStore m_textStore;
        S31::Localization::LocalizedTextReferences m_alreadyRequestedReferences;

        using NotifierPtr = std::shared_ptr<LocalizationImpl::LocalizationClientRequestCompleteImpl>;

        struct FetchSupportLanguageData
        {
            S31::Utils::OutcomeTypes::UntypedHandlerPtr handler;
            NotifierPtr notifier;
        } m_fetchSupportLanguageData;

        using Notifiers = std::map<LocalizationImpl::Execution::TransactionId, NotifierPtr>;
        Notifiers m_notifiers;
};

template<class SupportedLanguagesJob>
inline LocalizationClientImpl<SupportedLanguagesJob>::LocalizationClientImpl(
        const DFL::Mdib::MdibVersion& mdibVersion, // NOLINT(modernize-pass-by-value)
        Endpoint::Executor executor,
        Utils::WeakErrorHandler errorHandler):
    m_mdibVersion(mdibVersion),
    m_executor(std::move(executor)),
    m_errorHandler(std::move(errorHandler))
{
}

template<class SupportedLanguagesJob>
inline LocalizationClient::Notifier LocalizationClientImpl<SupportedLanguagesJob>::fetchSupportedLanguages()
{
    auto outcomeHandler = this->makeOutcomeHandler([this](OutcomeType& outcome)
    {
        if (outcome.hasError())
        {
            raiseError(outcome.error());
        }
        else if (outcome.result()->mdibVersion.isOtherSequenceOf(m_mdibVersion))
        {
            auto error = S31::Utils::makeError(Errors::MdibSequenceIdMismatch{}, "MDIB SequenceId mismatch");
            error.messageStream() << ": previous MDIB version: " << m_mdibVersion << ", new MDIB version: " << outcome.result()->mdibVersion;
            raiseError(error);
        }
        else
        {
            std::lock_guard<std::mutex> const guard(m_mutex);
            m_supportedLanguages = outcome.result()->languages;
            S31_STREAM_TRACE_LOGGER("Localization", "GetSupportedLanguagesJob successfully completed");
        }

        if (m_fetchSupportLanguageData.notifier)
        {
            m_fetchSupportLanguageData.notifier->complete();
            m_fetchSupportLanguageData.notifier = nullptr;
        }
    });

    auto createJob = [](
            const S31::Sdc::Impl::Endpoint::Url& url,
            const S31::Utils::OutcomeTypes::HandlerPtr<Sdc::Impl::GetSupportedLanguagesJobResult>& handler)
    {
        return std::make_unique<SupportedLanguagesJob>(handler, url);
    };


    std::lock_guard<std::mutex> const guard(m_mutex);

    // is there a fetch running already?
    if (m_fetchSupportLanguageData.notifier)
    {
        return DFL::asNotNull(m_fetchSupportLanguageData.notifier);
    }

    m_fetchSupportLanguageData.handler = m_executor.submit<Sdc::Impl::GetSupportedLanguagesJobResult>(
                outcomeHandler, createJob);

    m_fetchSupportLanguageData.notifier = std::make_shared<LocalizationImpl::LocalizationClientRequestCompleteImpl>();
    return DFL::asNotNull(m_fetchSupportLanguageData.notifier);
}

template<class SupportedLanguagesJob>
inline LocalizationClient::Notifier LocalizationClientImpl<SupportedLanguagesJob>::fetch(S31::Localization::LocalizedTextReferences&& references)
{
    auto executor = localizedTextExecutor();
    auto notifier = DFL::asNotNull(std::make_shared<LocalizationImpl::LocalizationClientRequestCompleteImpl>());


    std::lock_guard<std::mutex> const guard(m_mutex);
    if (m_activeLanguage == Language())
    {
        auto error = Utils::makeError(LocalizationImpl::Errors::NoActiveLanguage{}, "Active language is not set in LocalizationClient");
        raiseError(error);
        notifier->complete();
        return notifier;
    }

    // filter out references which were already requested before
    S31::Localization::LocalizedTextReferences difference;
    std::set_difference(
                references.begin(), references.end(),
                m_alreadyRequestedReferences.begin(), m_alreadyRequestedReferences.end(),
                std::inserter(difference, difference.begin()));


    const auto id = executor->execute(std::move(difference), m_activeLanguage);
    if (!id)
    {
        notifier->complete();
        return notifier;
    }

    m_notifiers[*id] = notifier.get();

    return notifier;
}

template<class SupportedLanguagesJob>
inline boost::optional<S31::Localization::LocalizedText> LocalizationClientImpl<SupportedLanguagesJob>::text(
        const DFL::Mdib::LocalizedTextRef& ref,
        const DFL::Mdib::VersionCounter& version,
        const boost::optional<DFL::Mdib::LocalizedTextWidth>& textWidth,
        const boost::optional<S31::Localization::NumberOfLines>& numberOfLines) const
{
    std::lock_guard<std::mutex> const guard(m_mutex);
    if (m_activeLanguage == Language())
    {
        auto error = Utils::makeError(LocalizationImpl::Errors::NoActiveLanguage{}, "Active language is not set in LocalizationClient");
        raiseError(error);
        return boost::none;
    }
    S31::Localization::LocalizedTextReference const r(ref, version, textWidth, numberOfLines);
    auto t = m_textStore.text(r, m_activeLanguage);
    if (t.empty())
    {
        return boost::none;
    }
    return {std::move(t)};
}

template<class SupportedLanguagesJob>
inline S31::Localization::LocalizedTexts LocalizationClientImpl<SupportedLanguagesJob>::texts(const DFL::Mdib::LocalizedTextRef& reference, const boost::optional<DFL::Mdib::VersionCounter>& version) const
{
    std::lock_guard<std::mutex> const guard(m_mutex);
    if (m_activeLanguage == Language())
    {
        auto error = Utils::makeError(LocalizationImpl::Errors::NoActiveLanguage{}, "Active language is not set in LocalizationClient");
        raiseError(error);
        return {};
    }

    return m_textStore.texts(reference, version);
}

template<class SupportedLanguagesJob>
inline LocalizationClient::Languages LocalizationClientImpl<SupportedLanguagesJob>::supportedLanguages() const
{
    std::lock_guard<std::mutex> const guard(m_mutex);
    return m_supportedLanguages;
}

template<class SupportedLanguagesJob>
inline void LocalizationClientImpl<SupportedLanguagesJob>::setActiveLanguage(const LocalizationClient::Language& lang)
{
    Notifiers oldNotifieres;

    // note, that running fetchSupportedLanguages request are not affected from change of active language
    {
        std::lock_guard<std::mutex> const guard(m_mutex);

        if (lang == m_activeLanguage)
        {
            return;
        }

        oldNotifieres = m_notifiers;
        m_notifiers.clear();

        m_textStore.clear();
        m_alreadyRequestedReferences.clear();

        m_activeLanguage = lang;
    }

    for (auto&& n : oldNotifieres)
    {
        n.second->complete();
    }
}

template<class SupportedLanguagesJob>
inline DFL::NotNull<LocalizedTextExecutorPtr> LocalizationClientImpl<SupportedLanguagesJob>::localizedTextExecutor()
{
    std::lock_guard<std::mutex> const guard(m_mutex);
    if (!m_localizedTextExecutor)
    {

        std::weak_ptr<LocalizationClientImpl<SupportedLanguagesJob>> const weakThis = this->shared_from_this();

        auto gotResults = [weakThis](LocalizationImpl::Execution::TransactionId id, S31::Localization::LocalizedTextReferences&& refs, DFL::Mdib::LocalizedTexts&& texts)
        {
            if (auto lockedThis = weakThis.lock())
            {
                lockedThis->gotResults(id, std::move(refs), std::move(texts));
            }
        };

        auto completed = [weakThis](LocalizationImpl::Execution::TransactionId id, const boost::optional<S31::Utils::Error>& error)
        {
            if (auto lockedThis = weakThis.lock())
            {
                lockedThis->completed(id, error);
            }
        };

        m_localizedTextExecutor = std::make_shared<
                LocalizationImpl::LocalizedTextExecutor<S31::Sdc::Impl::GetLocalizedTextJob>>(
                        m_mdibVersion, m_executor, gotResults, completed);
    }
    return DFL::asNotNull(m_localizedTextExecutor);
}

template<class SupportedLanguagesJob>
inline void LocalizationClientImpl<SupportedLanguagesJob>::gotResults(LocalizationImpl::Execution::TransactionId id, S31::Localization::LocalizedTextReferences&& refs, DFL::Mdib::LocalizedTexts&& texts)
{
    std::lock_guard<std::mutex> const guard(m_mutex);

    {
        auto it = m_notifiers.find(id);
        if (it == m_notifiers.end())
        {
            S31_STREAM_TRACE_LOGGER("Localization", "Got 'gotResults' callback for unknown transaction");
            return;
        }
    }

    std::move(refs.begin(), refs.end(),
              std::inserter(m_alreadyRequestedReferences, m_alreadyRequestedReferences.begin()));

    std::for_each(texts.begin(), texts.end(),
                    [&](DFL::Mdib::LocalizedText& text)
                    {
                        if (!text.reference().get().empty() && text.languageTag() == m_activeLanguage && text.version())
                        {
                            m_textStore.add(std::move(text));
                        }
                    });
}

template<class SupportedLanguagesJob>
inline void LocalizationClientImpl<SupportedLanguagesJob>::completed(LocalizationImpl::Execution::TransactionId id, const boost::optional<S31::Utils::Error>& error)
{
    if (error)
    {
        raiseError(*error);
    }

    NotifierPtr notifier;
    {
        std::lock_guard<std::mutex> const guard(m_mutex);
        auto it = m_notifiers.find(id);
        if (it == m_notifiers.end())
        {
            S31_STREAM_TRACE_LOGGER("Localization", "Got 'completed' callback for unknown transaction");
            return;
        }

        notifier = it->second;
        m_notifiers.erase(it);
    }

    if (notifier)
    {
        notifier->complete();
    }
}

template<class SupportedLanguagesJob>
inline void LocalizationClientImpl<SupportedLanguagesJob>::raiseError(const Utils::Error& error) const
{
    if (auto errorHandler = m_errorHandler.lock())
    {
        errorHandler->handleError(error);
    }
}

}
