#pragma once

#include <S31/BicepsXml/Public/XmlReportObserver.h>
#include <S31/History/Private/S31HistoryExImp.h>
#include <S31/History/Public/Service.h>
#include <S31/Utils/Public/ObservableSubject.h>

#include <memory>

namespace S31::History
{
class StoreInterface;

/**
 * @brief Mapper between BicepsXml and History interfaces for MDIB changes.
 * @details
 * The observer interface from the BicepsXml component is different (more complex) due to the fact that it uses the
 * subdivided observer interface and has shared_ptr in its callback functions. The History service interface is by
 * design without shared_ptr to enforce implementations to copy the data into an own format and not storing the
 * shared_ptr.
 * @ingroup S31CoreHistory
 */
class S31_HISTORY_EXPIMP BicepsToStoreMapper : public BicepsXml::XmlReportObserver,
                                               public S31::Utils::ObservableSubjectDelegate<StoreInterface>
{
public:
    void onDescriptionChange(
            const DFL::NotNull<DFL::Mdib::MdibSharedPtr>&               mdib,
            const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes,
            std::string_view                                            bicepsXmlReportMessage) override;
    void onAlertChange(
            const DFL::NotNull<DFL::Mdib::MdibSharedPtr>&               mdib,
            const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes,
            std::string_view                                            bicepsXmlReportMessage) override;
    void onComponentChange(
            const DFL::NotNull<DFL::Mdib::MdibSharedPtr>&               mdib,
            const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes,
            std::string_view                                            bicepsXmlReportMessage) override;
    void onContextChange(
            const DFL::NotNull<DFL::Mdib::MdibSharedPtr>&               mdib,
            const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes,
            std::string_view                                            bicepsXmlReportMessage) override;
    void onMetricChange(
            const DFL::NotNull<DFL::Mdib::MdibSharedPtr>&               mdib,
            const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes,
            std::string_view                                            bicepsXmlReportMessage) override;
    void onOperationChange(
            const DFL::NotNull<DFL::Mdib::MdibSharedPtr>&               mdib,
            const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes,
            std::string_view                                            bicepsXmlReportMessage) override;
    void onSampleArrayMetricChange(
            const DFL::NotNull<DFL::Mdib::MdibSharedPtr>&               mdib,
            const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes,
            std::string_view                                            bicepsXmlReportMessage) override;

private:
    void
    store(const DFL::Mdib::Mdib&          mdib,
          const DFL::Mdib::MdibChangeSet& changes,
          DFL::Mdib::MdibChangeType       changeType,
          std::string_view                bicepsXmlReportMessage);
};

}  // namespace S31::History
