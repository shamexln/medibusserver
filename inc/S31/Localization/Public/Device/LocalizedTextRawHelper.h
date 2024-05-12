#pragma once

#include <S31/Localization/Public/Common/LocalizedTextRawHelper.h>
#include <S31/Localization/Public/Device/LocalizedTextStore.h>

namespace S31::Localization::Device
{

/**
 * @brief Provides a store from the raw localized text data.
 * @details To be used for e.g. raw data generated from Xliff. To be used with a BICEPS device. May throw if there are invalid texts.
 * @ingroup S31LocalizationDevice
 */
template <std::size_t Size>
DFL::NotNull<std::shared_ptr<S31::Localization::Device::LocalizedTextStore>> makeStore(const DFL::Mdib::LocalizedTextRaw(&texts)[Size])
{
    auto localizedTexts = makeTexts(texts);
    auto result = S31::Localization::Device::LocalizedTextStore::createLocalizedTextStore();
    result->add(std::move(localizedTexts));
    return DFL::asNotNull(result);
}

}
