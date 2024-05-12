#pragma once

#include <S31/Localization/Private/Common/LocalizedTextStore.h>

namespace S31::Localization::Client
{

/**
 * @brief Localized text store as used in the client.
 * @ingroup S31LocalizationClient
 */
class LocalizedTextStore: private S31::Localization::Impl::LocalizedTextStore
{
    public:
        using S31::Localization::Impl::LocalizedTextStore::add;
        using S31::Localization::Impl::LocalizedTextStore::text;
        using S31::Localization::Impl::LocalizedTextStore::clear;

        /// not using 'using' because the other overloaded texts() is unwanted here
        LocalizedTexts texts(
                const DFL::Mdib::LocalizedTextRef& reference,
                const boost::optional<DFL::Mdib::VersionCounter>& version) const
        {
            return S31::Localization::Impl::LocalizedTextStore::texts(reference, version);
        }
};

}
