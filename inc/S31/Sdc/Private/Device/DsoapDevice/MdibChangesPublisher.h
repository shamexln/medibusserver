#pragma once

#include <S31/BicepsXml/Public/XmlReportObserver.h>
#include <S31/S31CoreExImp.h>

#include <memory>
#include <string_view>

namespace S31::Sdc::Impl
{
class ILocalEventing;

/**
 * @brief Publishes S31::Mdib::MdibChanges in the SDC network.
 *
 * \ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP MdibChangesPublisher: public BicepsXml::XmlReportObserver
{
    public:
        explicit MdibChangesPublisher(std::weak_ptr<ILocalEventing> localEventing);
        ~MdibChangesPublisher() noexcept override;

        // Observer callbacks
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
        std::weak_ptr<ILocalEventing> m_localEventing;

        void
        sendReport(const DFL::Mdib::Mdib& mdib, std::string_view reportSoapAction, std::string_view bicepsXmlReport);
};

}
