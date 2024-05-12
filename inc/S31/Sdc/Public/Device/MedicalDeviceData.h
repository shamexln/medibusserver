#pragma once

#include <S31/History/Public/Service.h>
#include <S31/Localization/Public/Device/LocalizedTextStore.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>
#include <Framework/Mdib/Public/MdibConstraints.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::BicepsXml
{
class MdibChangesSerializer;
class XmlReportObserver;
}

namespace S31::History
{
class BicepsToStoreMapper;
}

namespace S31::Sdc
{
class DualChannelFactoryManager;

/**
 * @brief Container for MDIB related information for a local medical device.
 * @details
 * Combines a local MDIB with optional localized text store and optional history service.
 * @ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP MedicalDeviceData
{
public:
    explicit MedicalDeviceData(
            DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr>         mdib,
            std::shared_ptr<Localization::Device::LocalizedTextStore> lts            = nullptr,
            std::shared_ptr<History::Service>                         historyService = nullptr);

    const DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr>& localMdibAccess() const noexcept;

    const DFL::Mdib::MdibConstraints& mdibConstraints() const;

    const std::shared_ptr<Localization::Device::LocalizedTextStore>& lts() const noexcept;

    const std::shared_ptr<History::Service>& historyService() const noexcept;

    const DFL::NotNull<std::shared_ptr<S31::Sdc::DualChannelFactoryManager>>& dualChannelFactoryManager() const noexcept;

    void registerObserver(const std::weak_ptr<BicepsXml::XmlReportObserver>& observer);
    void unregisterObserver(const std::weak_ptr<BicepsXml::XmlReportObserver>& observer);

private:
    DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr>                  m_mdib;
    std::shared_ptr<Localization::Device::LocalizedTextStore>          m_lts;
    std::shared_ptr<History::Service>                                  m_historyService;
    DFL::NotNull<std::shared_ptr<BicepsXml::MdibChangesSerializer>>    m_mdibChangesSerializer;
    std::shared_ptr<History::BicepsToStoreMapper>                      m_bicepsToStoreMapper;
    DFL::NotNull<std::shared_ptr<S31::Sdc::DualChannelFactoryManager>> m_dualChannelFactoryManager;
};
}  // namespace S31::Sdc
