#pragma once

#include <S31/Sdc/Private/Common/SetService/EnhancedProposedContextStates.h>
#include <S31/Sdc/Test/IntegrationTest/Utils/BicepsTestTypes.h>
#include <S31/SetService/Public/Common/ProposedComponentStates.h>
#include <S31/SetService/Public/Common/ProposedMetricStates.h>

#include <boost/filesystem.hpp>

#include <string>

namespace S31Test::Sdc
{

/**
 * @brief Get the relative path to the test resource SOAP request with the given name
 */
boost::filesystem::path requestPath(const std::string& filename);

/**
 * @brief Get the relative path to the test resource MDIB XML with the given name
 */
boost::filesystem::path mdibPath(const InputMdibFilename& filename);

/**
 * @brief Get the relative path to the test resource SOAP report with the given name
 */
boost::filesystem::path reportPath(const ReportFilename& filename);

/**
 * @brief Get the relative path to the test resource SOAP expected report (after round trip) with the given name
 */
///@{
boost::filesystem::path expectedResponsePath(const ExpectedReportFilename& filename);
boost::filesystem::path expectedResponsePath(const ExpectedResponseFilename& filename);
///@}

/**
 * @brief Get the relative path to the actual SOAP response with the given name
 */
boost::filesystem::path actualResponsePath(const std::string& filename);

/**
 * @brief Perform a generic BICEPS Service test for the S31 device-side.
 *
 * @details Send the given request to an S31 instance and compare the received response
 * with the expected response. Throw an assertion if the responses do not match.
 *
 * @param requestFilename path of the XML file with the request (relative to TestResources/Requests)
 * @param inputMdibFilename path of the XML file with the input Mdib (relative to TestResources/Mdibs)
 * @param expectedResponseFilename path of the XML file with the expected GetMdibResponse (relative to TestResources/ExpectedResponses)
 */
void runBicepsServiceTest_DeviceSide(
        const RequestFilename& requestFilename,
        const InputMdibFilename& inputMdibFilename,
        const ExpectedResponseFilename& expectedResponseFilename);

/**
 * @brief Perform a complete (client side + device side) test targeted at Biceps data type parsing and serialization.
 *
 * @details For the client-side test, parse the given GetMdibResponse, serialize the resulting Mdib and test that the input and output GetMdibResponses match.
 * For the device-side test, parse the given input Mdib XML using the MdibXmlReader and serialize the resulting Mdib into a GetMdibResponse. Then test that
 * the received and expected GetMdibResponses match.
 *
 * @param inputMdibFilename path of the XML file with the input Mdib (relative to TestResources/Mdibs)
 * @param mdibResponseFilename path of the XML file with the expected GetMdibResponse (relative to TestResources/ExpectedResponses)
 * @param outputFormat Specifies the serialization format of the output XML.
 * Defaults to SoapXmlFormat::Indent for human readability and maintainability of tests
 */
void runBicepsDataTypeTest(
        const InputMdibFilename& inputMdibFilename,
        const ExpectedResponseFilename& mdibResponseFilename,
        SoapXmlFormat outputFormat = SoapXmlFormat::Indent);

/**
 * @brief Perform client and device side tests for GetMdState
 *
 * @details For the client side, parse a given GetMdibResponse into an initial Mdib, parse the injected GetMdStateResponse and apply the State Modifications therein,
 *          perform a subsequent GetMdStateRequest, serialize a corresponding GetMdStateResponse and compare with an expected GetMdStateResponse.
 *          For the device side, parse a given GetMdibResponse into an initial Mdib, parse the expectedGetMdStateResponse and apply the State Modifications therein,
 *          perform a subsequent GetMdStateRequest, serialize the corresponding GetMdStateResponse and compare with the same expected GetMdStateResponse.
 *
 * @param initialMdibFilename filename of initial Mdib file (in form of GetMdibResponse message) on which State modifications are performed via GetMdStateResponse messages
 * @param injectedGetMdStateResponseFilename filename of the message containing state modifications that are applied to the initial Mdib
 * @param followUpGetMdStateRequestFilename filename of the message containing a GetMdStateRequest that is performed after applying the injected response
 * @param expectedGetMdStateResponseFilename filename of the expected GetMdStateResponse that the followup request shall result in
 */
void runGetMdStateTest(const InputMdibFilename& initialMdibFilename,
        const InjectedGetMdStateResponseFilename& injectedGetMdStateResponseFilename,
        const GetMdStateRequestFilename& followUpGetMdStateRequestFilename,
        const ExpectedGetMdStateResponseFilename& expectedGetMdStateResponseFilename);

/**
 * @brief Perform device side tests for GetMdState
 *
 * @details Parse a given GetMdibResponse into an initial Mdib, perform a GetMdStateRequest, serialize the corresponding GetMdStateResponse
 *          and compare with the same expected GetMdStateResponse.
 *
 * @param initialMdibFilename filename of initial Mdib file (in form of GetMdibResponse message) on which State modifications are performed via GetMdStateResponse messages
 * @param getMdStateRequestFilename filename of the message containing a GetMdStateRequest that is performed
 * @param expectedGetMdStateResponseFilename filename of the expected GetMdStateResponse that the followup request shall result in
 */
void runGetMdStateTest_DeviceSide(const InputMdibFilename& initialMdibFilename,
                                  const GetMdStateRequestFilename& getMdStateRequestFilename,
                                  const ExpectedGetMdStateResponseFilename& expectedGetMdStateResponseFilename);

/**
 * @brief Performs only the device side tests for GetLocalizedText, used primarily for testing error cases.
 *
 * @details Populate a localizedTextStore with Localized texts, make a request of the store and compare the resulting localizedTexts.
 *
 * @param requestFilename path of the XML file with the request GetLocalizedText request
 * @param expectedResponseFilename path of the XML file with the expected GetLocalizedTextResponse
 */
void runLocalizationServiceTest_DeviceSide(const RequestFilename& requestFilename, const ExpectedResponseFilename& expectedResponseFilename);

/**
 * @brief Perform client and device side tests for GetLocalizedText
 *
 * @details For the device side, populate a localizedTextStore with Localized texts, make a request of the store and compare the resulting localizedTexts.
 *          For the client side, serialize a GetLocalizedTextResponse and compare with the input expected GetLocalizedTextResponse.
 *
 * @param requestFilename path of the XML file with the request GetLocalizedText request
 * @param expectedResponseFilename path of the XML file with the expected GetLocalizedTextResponse
 */
void runGetLocalizedTextTest(
        const RequestFilename& requestFilename,
        const ExpectedResponseFilename& expectedResponseFilename);

/**
 * @brief Perform client side tests for GetLocalizedText with MDIB SequenceId in response.
 *
 * @details Let the job process the given response. Checks outcome from job.
 *
 * @param injectedResponseFilename path of the XML file with the injected GetSupportedLanguagesResponse
 */
void runGetLocalizedTextTestWithMdibSeq(const InjectedResponseFilename& injectedResponseFilename);

/**
 * @brief Perform client and device side tests for GetSupportedLanguages
 *
 * @details For the device side, populate a localizedTextStore with Localized texts, make a request of the store and compare the resulting languages.
 *          For the client side, serialize a GetSupportedLanguagesResponse and compare with the input expected GetSupportedLanguagesResponse.
 *
 * @param requestFilename path of the XML file with the request GetSupportedLanguages request
 * @param expectedResponseFilename path of the XML file with the expected GetSupportedLanguagesResponse
 */
void runGetSupportedLanguagesTest(
        const RequestFilename& requestFilename,
        const ExpectedResponseFilename& expectedResponseFilename);

/**
 * @brief Perform client side tests for GetSupportedLanguages with MDIB SequenceId in response.
 *
 * @details Let the job process the given response. Checks outcome from job.
 *
 * @param injectedResponseFilename path of the XML file with the injected GetSupportedLanguagesResponse
 */
void runGetSupportedLanguagesTestWithMdibSeq(const InjectedResponseFilename& injectedResponseFilename);

/**
 * @brief Perform a generic BICEPS report test.
 *
 * @details The XML report is applied to the given (remote) MDIB (SDC client functionality).
 * The \ref S31::Sdc::Impl::MdibChangesPublisher uses these MDIB modifications
 * to generate an XML report (SDC device functionality).
 *
 * When the resulting report matches the injected XML report,
 * the client side processing creates a MDIB change set with all required information,
 * which are used to create the actual XML report for a readable/observable MDIB on device side.
 *
 * @param reportFilename Hand-written report to test for correct processing
 * @param mdibFilename Initial MDIB the report shall be applied to
 * @param resultReportFilename Result report after MDIB changes round trip.
 * @param outputFormat Specifies the serialization format of the output XML.
 * Defaults to SoapXmlFormat::Indent for human readability and maintainability of tests
 */
void runBicepsReportTest(
        const ReportFilename& reportFilename,
        const InputMdibFilename& mdibFilename,
        const ExpectedReportFilename& resultReportFilename,
        const SoapXmlFormat& outputFormat = SoapXmlFormat::Indent);

/**
 * @brief Performs a generic BICEPS report test that shall result in a SOAP fault (e.g. due to conversion errors)
 * @param reportFilename report to test that is not correctly parseable or cannot be processed correctly with respect to the given MDIB
 * @param mdibFilename Initial MDIB the report shall be applied to
 * @param expectedSoapFaultSubString Appying the given report should result result in error, the given text shall be a substring of this error
 */
void runBicepsReportFaultTest(const ReportFilename& reportFilename, const InputMdibFilename& mdibFilename, const ExpectedFaultSubString& expectedSoapFaultSubString);

/**
 * @brief Perform client and device side tests for OperationInvokedReport
 *
 * @details Triggers an InvocationReport callback via \ref S31::Sdc::Impl::EventSink then serializes the resulting report which is compared to the input XML.
 *
 * @param reportFilename path of hand-written OperationInvokedReport XML
 */
void runOperationInvokedReportTest(const ReportFilename& reportFilename);

/**
 * @brief Performs a client side parsing test and expects a fault
 * @param reportFilename given XML of the report
 * @param expectedFaultText expcted substring of the resulting fault
 */
void runOperationInvokedReportTest(const ReportFilename& reportFilename, const ExpectedFaultSubString& expectedFaultText);

/**
 * @brief Perform client side test for Activate Operation Message
 *
 * @details Triggers an ActivateRequestMessage compares the serialized message with the contents of the input file, parses the response and compares it with
 * the output file.
 *
 * @param requestFilename path of the XML file with the request (relative to TestResources/Requests/SetOperations)
 * @param responseFilename path of the XML file with the response (relative to TestResources/ExpectedReponses/SetOperations)
 */
void runActivateMessageClientSide(const RequestFilename& requestFilename, const ExpectedResponseFilename& responseFilename);

/**
 * @brief Perform client side test for Set Value Message
 *
 * @details Triggers a SetValueRequest message compares the serialized message with the contents of the input file, parses the response and compares it with
 * the output file.
 *
 * @param requestFilename path of the XML file with the request (relative to TestResources/Requests/SetOperations)
 * @param responseFilename path of the XML file with the response (relative to TestResources/ExpectedReponses/SetOperations)
 */
void runSetValueMessageClientSide(const RequestFilename& requestFilename, const ExpectedResponseFilename& responseFilename);

/**
 * @brief Perform client side test for Set String Message
 *
 * @details Triggers a SetStringRequest message compares the serialized message with the contents of the input file, parses the response and compares it with
 * the output file.
 *
 * @param requestFilename path of the XML file with the request (relative to TestResources/Requests/SetOperations)
 * @param responseFilename path of the XML file with the response (relative to TestResources/ExpectedReponses/SetOperations)
 */
void runSetStringMessageClientSide(const RequestFilename& requestFilename, const ExpectedResponseFilename& responseFilename);

/**
 * @brief Perform client side test for Set Context State Message
 *
 * @details Triggers a SetContextStateRequest message compares the serialized message with the contents of the input file, parses the response and compares it with
 * the output file.
 *
 * @param requestFilename path of the XML file with the request (relative to TestResources/Requests/SetOperations)
 * @param responseFilename path of the XML file with the response (relative to TestResources/ExpectedReponses/SetOperations)
 * @param proposedContextStates
 */
void runSetContextStateMessageClientSide(
        const RequestFilename& requestFilename,
        const ExpectedResponseFilename& responseFilename,
        const S31::Sdc::Impl::EnhancedProposedContextStates& proposedContextStates);

/**
 * @brief Perform client side test for Set Component State Message
 *
 * @details Triggers a SetComponentStateRequest message compares the serialized message with the contents of the input file, parses the response and compares it with
 * the output file.
 *
 * @param requestFilename path of the XML file with the request (relative to TestResources/Requests/SetOperations)
 * @param responseFilename path of the XML file with the response (relative to TestResources/ExpectedReponses/SetOperations)
 * @param proposedComponentStates
 */
void runSetComponentStateMessageClientSide(
        const RequestFilename& requestFilename,
        const ExpectedResponseFilename& responseFilename,
        const S31::SetService::ProposedComponentStates& proposedComponentStates);

/**
 * @brief Perform client side test for Set Alert State Message
 *
 * @details Triggers a SetAlertStateRequest message compares the serialized message with the contents of the input file, parses the response and compares it with
 * the output file.
 *
 * @param requestFilename path of the XML file with the request (relative to TestResources/Requests/SetOperations)
 * @param responseFilename path of the XML file with the response (relative to TestResources/ExpectedReponses/SetOperations)
 * @param proposedAlertState
 */
template<typename T_Payload, typename T_GsoapState>
void runSetAlertStateMessageClientSide(
        const RequestFilename& requestFilename,
        const ExpectedResponseFilename& responseFilename,
        const T_Payload& proposedAlertState);

/**
 * @brief Perform client side test for Set Metric State Message
 *
 * @details Triggers a SetMetricStateRequest message compares the serialized message with the contents of the input file, parses the response and compares it with
 * the output file.
 *
 * @param requestFilename path of the XML file with the request (relative to TestResources/Requests/SetOperations)
 * @param responseFilename path of the XML file with the response (relative to TestResources/ExpectedReponses/SetOperations)
 * @param proposedMetricStates
 */
void runSetMetricStateMessageClientSide(
        const RequestFilename& requestFilename,
        const ExpectedResponseFilename& responseFilename,
        const S31::SetService::ProposedMetricStates& proposedComponentStates);

/**
 * @brief Perform device side test for set operation messages
 *
 * @details Send the given request to an S31 instance and compare the received response
 * with the expected response. Throw an assertion if the responses do not match.
 *
 * @param requestFilename path of the XML file with the request (relative to TestResources/Requests/SetOperations)
 * @param inputMdibFilename path of the XML file with the Mdib (relative to TestResources/Mdibs)
 * @param expectedResponseFilename path of the XML file with the response (relative to TestResources/ExpectedReponses/SetOperations)
 */
template<class T_Handle, class T_Data>
void runBicepsSetOperationTest_DeviceSide(
        const RequestFilename& requestFilename,
        const InputMdibFilename& inputMdibFilename,
        const ExpectedResponseFilename& expectedResponseFilename);

}
