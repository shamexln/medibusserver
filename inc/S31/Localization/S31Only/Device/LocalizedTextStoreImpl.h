#pragma once

#include <S31/Localization/Private/Common/LocalizedTextStore.h>
#include <S31/Localization/Public/Common/S31LtsExImp.h>
#include <S31/Localization/Public/Device/LocalizedTextStore.h>

#include <mutex>
#include <set>

namespace S31::Localization::Device
{

/**
 * @brief Store for localized texts on device side.
 * @ingroup S31LocalizationDevice
 */
class S31_LTS_EXPIMP LocalizedTextStoreImpl: public Localization::Device::LocalizedTextStore, private Localization::Impl::LocalizedTextStore
{
    public:
        LocalizedTextStoreImpl() = default;

        void add(const DFL::Mdib::LocalizedTexts& localizedTexts) override;
        void add(DFL::Mdib::LocalizedTexts&& localizedTexts) override;
        LocalizedText text(const LocalizedTextReference& reference, const DFL::Locale::LanguageTag& language) const override;

        Languages languages() const override;

        /// @brief For usage with BICEPS GetLocalizedText().
        DFL::Mdib::LocalizedTexts localizedTexts(const LocalizedTextFilter& filter) const;
    private:
        void addNoLock(DFL::Mdib::LocalizedText &&localizedText);

        mutable std::mutex m_mutex;
        std::set<DFL::Locale::LanguageTag> m_languages;
};

}
