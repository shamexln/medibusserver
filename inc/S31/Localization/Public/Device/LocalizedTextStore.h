#pragma once

#include <S31/Localization/Public/Common/LocalizedText.h>
#include <S31/Localization/Public/Common/LocalizedTextReference.h>
#include <S31/Localization/Public/Common/S31LtsExImp.h>

#include <Framework/Mdib/Public/Model/LocalizedText.h>
#include <Framework/Mdib/Public/Model/LocalizedTexts.h>
#include <Framework/Utils/Public/LanguageTag.h>

#include <memory>

namespace S31::Localization::Device
{

using Languages = std::vector<DFL::Locale::LanguageTag>;

/**
 * @brief Store for localized texts on device side.
 * @details Used by product to provide the localized texts.
 * @ingroup S31LocalizationDevice
 */
class S31_LTS_EXPIMP LocalizedTextStore
{
    public:
        /**
         * @name Add multiple texts
         * @brief Functions to add multiple texts at once.
         * @details Throws if one of the given texts is invalid for the store, some of the given texts may be added in that case. Checks consistency after adding.
         *
         * It is expected from the device that if a text is given with a certain version and reference in one language that then the localized
         * text store has to contain that version and reference in any other language too.
         *
         * This follows from BICEPS implicitly because if a text referenced in a certain version in the Mdib then it has to be
         * retrievable from the LOCALIZATION SERVICE in any available language.
         *
         * If an exception is thrown then the store is probably not valid and should not be used.
         */
        ///@{
        virtual void add(const DFL::Mdib::LocalizedTexts& localizedTexts) = 0;
        virtual void add(DFL::Mdib::LocalizedTexts&& localizedTexts) = 0;
        ///@}

        /**
         * @brief Add texts.
         * @deprecated Use add() instead.
         */
        [[deprecated("use add() instead")]]
        void addMany(DFL::Mdib::LocalizedTexts localizedTexts)
        {
            add(std::move(localizedTexts));
        }

        /**
         * @brief Provides the languages available in the store.
         * @details E.g. for usage with BICEPS GetSupportedLanguages().
         */
        virtual Languages languages() const = 0;

        /**
         * @copydoc S31::Localization::Impl::LocalizedTextStore::text()
         */
        virtual LocalizedText text(const LocalizedTextReference& reference, const DFL::Locale::LanguageTag& language) const = 0;

        virtual ~LocalizedTextStore() = default;

        /**
         * @brief Factory function to create a LocalizedTextStore instance;
         */
        static std::shared_ptr<Localization::Device::LocalizedTextStore> createLocalizedTextStore();

    protected:
        LocalizedTextStore() = default;
};

}
