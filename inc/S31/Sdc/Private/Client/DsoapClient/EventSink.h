#pragma once

#include <S31/BicepsXml/S31Only/Report.h>
#include <S31/Sdc/Private/Client/Report/ReportParsing.h>
#include <S31/Sdc/Private/Client/Report/ReportProcessor.h>
#include <S31/Sdc/Private/Client/SetService/InvocationReportSubject.h>
#include <S31/Utils/Public/Errors.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Utils/Public/CompilerGenerated.h>
#include <Framework/Utils/Public/NotNull.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapGetServiceBindingService.h>

#include <memory>

namespace S31
{
namespace SetService
{
class InvocationReportObserver;
}

namespace Sdc::Impl
{

/**
 * \brief This class handles incoming BICEPS client network events.
 *
 * Incoming client network messages (one-way) are Episodic Alert Reports, Episodic Context Reports etc.
 *
 * \ingroup S31SdcClient
 */
class S31_CORE_EXPIMP EventSink : private GetServiceBindingService
{
        // gSOAP assign and copy do not work as expected (Coverity findings)
        DFL_NOT_COPYABLE(EventSink)
    public:
        EventSink(struct soap* soapHandle,
                  std::weak_ptr<Sdc::Impl::InvocationReportSubject> invocationReportSubject,
                  std::weak_ptr<Sdc::Impl::Report::ReportProcessor> reportProcessor,
                  Utils::ErrorHandler& errorHandler);

        int dispatch() override;

    private:
        // these functions shall not be called, it is implementation detail
        int EpisodicAlertReport(_msg__EpisodicAlertReport* report) override;
        int EpisodicContextReport(_msg__EpisodicContextReport* report) override;
        int EpisodicComponentReport(_msg__EpisodicComponentReport *report) override;
        int OperationInvokedReport(_msg__OperationInvokedReport* report) override;
        int EpisodicOperationalStateReport(_msg__EpisodicOperationalStateReport* report) override;
        int DescriptionModificationReport(_msg__DescriptionModificationReport* report) override;

        /**
         * \warning Do NOT use! We can not copy the internal soap struct without side effects!
         * \return returns this
         */
        EventSink* copy() override;

        template<class Report>
        int handleStateReport(const Report* report);
        int handleStateModifications(Report::StateModifications&& stateReport);
        int handleDescriptorModifications(Report::DescriptorModifications&& descriptorReport);

        int handleError(const Utils::Error& error);

        template<class Modifications>
        int pushToProcessorAndSendResponse(Modifications&& m);

        int convertExceptionInSoapFault(const std::function<int()>& func);
        int dispatchConvertSoapError(struct soap* soapHandle);
        std::weak_ptr<Sdc::Impl::InvocationReportSubject> m_invocationReportSubject;
        std::weak_ptr<Sdc::Impl::Report::ReportProcessor> m_reportProcessor;
        Utils::ErrorHandler& m_errorHandler;
        S31::Sdc::Impl::ReportParsing m_parser;
};

}
}
