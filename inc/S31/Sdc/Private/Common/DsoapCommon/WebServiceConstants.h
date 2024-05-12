#pragma once

#include <S31/Base/S31Only/NtStringView.h>

#include <Framework/Utils/Public/QName.h>

#include <string_view>
#include <vector>

#define S31_CORE_IMPL_SDC_GLUE_URI "http://standards.ieee.org/downloads/11073/11073-20701-2018"
#define S31_CORE_IMPL_CONTEXT_SERVICE_ACTION_PREFIX "http://standards.ieee.org/downloads/11073/11073-20701-2018/ContextService/"
#define S31_CORE_IMPL_LOCALIZATION_SERVICE_ACTION_PREFIX "http://standards.ieee.org/downloads/11073/11073-20701-2018/LocalizationService/"
#define S31_CORE_IMPL_GET_SERVICE_ACTION_PREFIX "http://standards.ieee.org/downloads/11073/11073-20701-2018/GetService/"
#define S31_CORE_IMPL_SET_SERVICE_ACTION_PREFIX "http://standards.ieee.org/downloads/11073/11073-20701-2018/SetService/"
#define S31_CORE_IMPL_DESCRIPTOR_EVENT_SERVICE_ACTION_PREFIX "http://standards.ieee.org/downloads/11073/11073-20701-2018/DescriptionEventService/"
#define S31_CORE_IMPL_STATE_EVENT_SERVICE_ACTION_PREFIX "http://standards.ieee.org/downloads/11073/11073-20701-2018/StateEventService/"
#define S31_CORE_IMPL_WAVEFORM_SERVICE_ACTION_PREFIX "http://standards.ieee.org/downloads/11073/11073-20701-2018/WaveformService/"

namespace S31::Sdc::Impl
{

/**
 * \brief Web service constants from SDC protocol.
 *
 * This class contains constants for XML names and namespaces as well as SOAP actions for Web Services communication.
 *
 * \ingroup S31SdcCommon
 */
class WebServiceConstants
{
    public:
        /**
         * @name Action prefixes of all BICEPS services
         */
        static constexpr NtStringView GET_SERVICE_ACTION_PREFIX{S31_CORE_IMPL_GET_SERVICE_ACTION_PREFIX};
        static constexpr NtStringView SET_SERVICE_ACTION_PREFIX{S31_CORE_IMPL_SET_SERVICE_ACTION_PREFIX};
        static constexpr NtStringView CONTEXT_SERVICE_ACTION_PREFIX{S31_CORE_IMPL_CONTEXT_SERVICE_ACTION_PREFIX};
        static constexpr NtStringView STATE_EVENT_SERVICE_ACTION_PREFIX{
                S31_CORE_IMPL_STATE_EVENT_SERVICE_ACTION_PREFIX};
        static constexpr NtStringView DESCRIPTOR_EVENT_SERVICE_ACTION_PREFIX{
                S31_CORE_IMPL_DESCRIPTOR_EVENT_SERVICE_ACTION_PREFIX};
        static constexpr NtStringView WAVEFORM_SERVICE_ACTION_PREFIX{S31_CORE_IMPL_WAVEFORM_SERVICE_ACTION_PREFIX};
        static constexpr NtStringView LOCALIZATION_SERVICE_ACTION_PREFIX{
                S31_CORE_IMPL_LOCALIZATION_SERVICE_ACTION_PREFIX};

        /**
         * @name DPWS hosted service WSDL port types for BICEPS services as defined in SDC protocol
         */
        ///@{
        static constexpr NtStringView CONTEXT_SERVICE_NAMESPACE{S31_CORE_IMPL_SDC_GLUE_URI};
        static constexpr NtStringView CONTEXT_SERVICE_NAME{"ContextService"};

        static DFL::QName contextServiceQName()
        {
            return {DFL::NamespaceUri{CONTEXT_SERVICE_NAMESPACE.c_str()},
                    DFL::NamePrefix{},
                    CONTEXT_SERVICE_NAME.c_str()};
        }

        static constexpr NtStringView DESCRIPTOR_EVENT_SERVICE_NAMESPACE{S31_CORE_IMPL_SDC_GLUE_URI};
        static constexpr NtStringView DESCRIPTOR_EVENT_SERVICE_NAME{"DescriptionEventService"};

        static DFL::QName descriptorServiceQName()
        {
            return {DFL::NamespaceUri{DESCRIPTOR_EVENT_SERVICE_NAMESPACE.c_str()},
                    DFL::NamePrefix{},
                    DESCRIPTOR_EVENT_SERVICE_NAME.c_str()};
        }

        static constexpr NtStringView GET_SERVICE_NAMESPACE{S31_CORE_IMPL_SDC_GLUE_URI};
        static constexpr NtStringView GET_SERVICE_NAME{"GetService"};

        static DFL::QName getServiceQName()
        {
            return {DFL::NamespaceUri{GET_SERVICE_NAMESPACE.c_str()},
                    DFL::NamePrefix{},
                    GET_SERVICE_NAME.c_str()};
        }

        static constexpr NtStringView LOCALIZATION_SERVICE_NAMESPACE{S31_CORE_IMPL_SDC_GLUE_URI};
        static constexpr NtStringView LOCALIZATION_SERVICE_NAME{"LocalizationService"};

        static DFL::QName localizationServiceQName()
        {
            return {DFL::NamespaceUri{LOCALIZATION_SERVICE_NAMESPACE.c_str()},
                    DFL::NamePrefix{},
                    LOCALIZATION_SERVICE_NAME.c_str()};
        }

        static constexpr NtStringView SET_SERVICE_NAMESPACE{S31_CORE_IMPL_SDC_GLUE_URI};
        static constexpr NtStringView SET_SERVICE_NAME{"SetService"};

        static DFL::QName setServiceQName()
        {
            return {DFL::NamespaceUri{SET_SERVICE_NAMESPACE.c_str()}, DFL::NamePrefix{}, SET_SERVICE_NAME.c_str()};
        }

        static constexpr NtStringView STATE_EVENT_SERVICE_NAMESPACE{S31_CORE_IMPL_SDC_GLUE_URI};
        static constexpr NtStringView STATE_EVENT_SERVICE_NAME{"StateEventService"};

        static DFL::QName stateEventServiceQName()
        {
            return {DFL::NamespaceUri{STATE_EVENT_SERVICE_NAMESPACE.c_str()},
                    DFL::NamePrefix{},
                    STATE_EVENT_SERVICE_NAME.c_str()};
        }

        static constexpr NtStringView WAVEFORM_SERVICE_NAMESPACE{S31_CORE_IMPL_SDC_GLUE_URI};
        static constexpr NtStringView WAVEFORM_SERVICE_NAME{"WaveformService"};

        static DFL::QName waveformServiceQName()
        {
            return {DFL::NamespaceUri{WAVEFORM_SERVICE_NAMESPACE.c_str()},
                    DFL::NamePrefix{},
                    WAVEFORM_SERVICE_NAME.c_str()};
        }

        ///@}

        static constexpr NtStringView HISTORY_SERVICE_NAMESPACE{"urn:oid:1.3.6.1.4.1.3592.2.6934.1.1"};
        static constexpr NtStringView HISTORY_SERVICE_NAME{"HistoryService"};

        static DFL::QName historyServiceQName()
        {
            return {DFL::NamespaceUri{HISTORY_SERVICE_NAMESPACE.c_str()},
                    DFL::NamePrefix{},
                    HISTORY_SERVICE_NAME.c_str()};
        }

        /**
         * @name WS-Discovery types as defined in SDC protocol
         * @details
         * This is also the MDPWS discovery type.
         */
        ///@{
        static constexpr NtStringView DISCOVERY_TYPE_NS{"http://standards.ieee.org/downloads/11073/11073-20702-2016"};
        static constexpr NtStringView DISCOVERY_TYPE_NAME{"MedicalDevice"};

        static DFL::QName medicalDeviceQName()
        {
            return {DFL::NamespaceUri{DISCOVERY_TYPE_NS.c_str()}, DFL::NamePrefix{}, DISCOVERY_TYPE_NAME.c_str()};
        }
        ///@}

        /**
         * @name GET/SET message SOAP actions
         */
        ///@{
        static constexpr NtStringView SET_CONTEXT_STATE_ACTION{S31_CORE_IMPL_CONTEXT_SERVICE_ACTION_PREFIX
                                                               "SetContextState"};
        static constexpr NtStringView SET_CONTEXT_STATE_RESPONSE_ACTION{S31_CORE_IMPL_CONTEXT_SERVICE_ACTION_PREFIX
                                                                        "SetContextStateResponse"};

        static constexpr NtStringView GET_CONTEXT_STATE_ACTION{S31_CORE_IMPL_CONTEXT_SERVICE_ACTION_PREFIX
                                                               "GetContextStates"};
        static constexpr NtStringView GET_CONTEXT_STATE_RESPONSE_ACTION{S31_CORE_IMPL_CONTEXT_SERVICE_ACTION_PREFIX
                                                                        "GetContextStatesResponse"};

        static constexpr NtStringView GET_CONTEXT_STATE_BY_IDENTIFICATION_ACTION{
                S31_CORE_IMPL_CONTEXT_SERVICE_ACTION_PREFIX "GetContextStatesByIdentification"};
        static constexpr NtStringView GET_CONTEXT_STATE_BY_IDENTIFICATION_RESPONSE_ACTION{
                S31_CORE_IMPL_CONTEXT_SERVICE_ACTION_PREFIX "GetContextStatesByIdentificationResponse"};

        static constexpr NtStringView GET_CONTEXT_STATE_BY_FILTER_ACTION{S31_CORE_IMPL_CONTEXT_SERVICE_ACTION_PREFIX
                                                                         "GetContextStatesByFilter"};
        static constexpr NtStringView GET_CONTEXT_STATE_BY_FILTER_RESPONSE_ACTION{
                S31_CORE_IMPL_CONTEXT_SERVICE_ACTION_PREFIX "GetContextStatesByFilterResponse"};

        static constexpr NtStringView GET_LOCALIZED_TEXT_ACTION{S31_CORE_IMPL_LOCALIZATION_SERVICE_ACTION_PREFIX
                                                                "GetLocalizedText"};
        static constexpr NtStringView GET_LOCALIZED_TEXT_RESPONSE_ACTION{
                S31_CORE_IMPL_LOCALIZATION_SERVICE_ACTION_PREFIX "GetLocalizedTextResponse"};

        static constexpr NtStringView GET_MDIB_ACTION{S31_CORE_IMPL_GET_SERVICE_ACTION_PREFIX "GetMdib"};
        static constexpr NtStringView GET_MDIB_RESPONSE_ACTION{S31_CORE_IMPL_GET_SERVICE_ACTION_PREFIX
                                                               "GetMdibResponse"};

        static constexpr NtStringView GET_MDDESCRIPTION_ACTION{S31_CORE_IMPL_GET_SERVICE_ACTION_PREFIX
                                                               "GetMdDescription"};
        static constexpr NtStringView GET_MDDESCRIPTION_RESPONSE_ACTION{S31_CORE_IMPL_GET_SERVICE_ACTION_PREFIX
                                                                        "GetMdDescriptionResponse"};

        static constexpr NtStringView GET_MDSTATE_ACTION{S31_CORE_IMPL_GET_SERVICE_ACTION_PREFIX "GetMdState"};
        static constexpr NtStringView GET_MDSTATE_RESPONSE_ACTION{S31_CORE_IMPL_GET_SERVICE_ACTION_PREFIX
                                                                  "GetMdStateResponse"};

        static constexpr NtStringView GET_SUPPORTED_LANGUAGES_ACTION{S31_CORE_IMPL_LOCALIZATION_SERVICE_ACTION_PREFIX
                                                                     "GetSupportedLanguages"};
        static constexpr NtStringView GET_SUPPORTED_LANGUAGES_RESPONSE_ACTION{
                S31_CORE_IMPL_LOCALIZATION_SERVICE_ACTION_PREFIX "GetSupportedLanguagesResponse"};

        static constexpr NtStringView ACTIVATE_ACTION{S31_CORE_IMPL_SET_SERVICE_ACTION_PREFIX "Activate"};
        static constexpr NtStringView ACTIVATE_RESPONSE_ACTION{S31_CORE_IMPL_SET_SERVICE_ACTION_PREFIX
                                                               "ActivateResponse"};

        static constexpr NtStringView SET_STRING_ACTION{S31_CORE_IMPL_SET_SERVICE_ACTION_PREFIX "SetString"};
        static constexpr NtStringView SET_STRING_RESPONSE_ACTION{S31_CORE_IMPL_SET_SERVICE_ACTION_PREFIX
                                                                 "SetStringResponse"};

        static constexpr NtStringView SET_VALUE_ACTION{S31_CORE_IMPL_SET_SERVICE_ACTION_PREFIX "SetValue"};
        static constexpr NtStringView SET_VALUE_RESPONSE_ACTION{S31_CORE_IMPL_SET_SERVICE_ACTION_PREFIX
                                                                "SetValueResponse"};

        static constexpr NtStringView SET_ALERT_STATE_ACTION{S31_CORE_IMPL_SET_SERVICE_ACTION_PREFIX "SetAlertState"};
        static constexpr NtStringView SET_ALERT_STATE_RESPONSE_ACTION{S31_CORE_IMPL_SET_SERVICE_ACTION_PREFIX
                                                                      "SetAlertStateResponse"};

        static constexpr NtStringView SET_COMPONENT_STATE_ACTION{S31_CORE_IMPL_SET_SERVICE_ACTION_PREFIX
                                                                 "SetComponentState"};
        static constexpr NtStringView SET_COMPONENT_STATE_RESPONSE_ACTION{S31_CORE_IMPL_SET_SERVICE_ACTION_PREFIX
                                                                          "SetComponentStateResponse"};

        static constexpr NtStringView SET_METRIC_STATE_ACTION{S31_CORE_IMPL_SET_SERVICE_ACTION_PREFIX "SetMetricState"};
        static constexpr NtStringView SET_METRIC_STATE_RESPONSE_ACTION{S31_CORE_IMPL_SET_SERVICE_ACTION_PREFIX
                                                                       "SetMetricStateResponse"};
        ///@}

        /**
         * @name Report message SOAP actions
         */
        ///@{
        static constexpr NtStringView PERIODIC_CONTEXT_REPORT_ACTION{S31_CORE_IMPL_CONTEXT_SERVICE_ACTION_PREFIX
                                                                     "PeriodicContextReport"};
        static constexpr NtStringView EPISODIC_CONTEXT_REPORT_ACTION{S31_CORE_IMPL_CONTEXT_SERVICE_ACTION_PREFIX
                                                                     "EpisodicContextReport"};

        static constexpr NtStringView DESCRIPTION_MODIFICATION_REPORT_ACTION{
                S31_CORE_IMPL_DESCRIPTOR_EVENT_SERVICE_ACTION_PREFIX "DescriptionModificationReport"};

        static constexpr NtStringView OPERATION_INVOKED_REPORT_ACTION{S31_CORE_IMPL_SET_SERVICE_ACTION_PREFIX
                                                                      "OperationInvokedReport"};

        static constexpr NtStringView EPISODIC_ALERT_REPORT_ACTION{S31_CORE_IMPL_STATE_EVENT_SERVICE_ACTION_PREFIX
                                                                   "EpisodicAlertReport"};
        static constexpr NtStringView SYSTEM_ERROR_REPORT_ACTION{S31_CORE_IMPL_STATE_EVENT_SERVICE_ACTION_PREFIX
                                                                 "SystemErrorReport"};
        static constexpr NtStringView PERIODIC_ALERT_REPORT_ACTION{S31_CORE_IMPL_STATE_EVENT_SERVICE_ACTION_PREFIX
                                                                   "PeriodicAlertReport"};
        static constexpr NtStringView EPISODIC_COMPONENT_REPORT_ACTION{S31_CORE_IMPL_STATE_EVENT_SERVICE_ACTION_PREFIX
                                                                       "EpisodicComponentReport"};
        static constexpr NtStringView PERIODIC_OPERATIONAL_STATE_REPORT_ACTION{
                S31_CORE_IMPL_STATE_EVENT_SERVICE_ACTION_PREFIX "PeriodicOperationalStateReport"};
        static constexpr NtStringView PERIODIC_COMPONENT_REPORT_ACTION{S31_CORE_IMPL_STATE_EVENT_SERVICE_ACTION_PREFIX
                                                                       "PeriodicComponentReport"};
        static constexpr NtStringView EPISODIC_OPERATIONAL_STATE_REPORT_ACTION{
                S31_CORE_IMPL_STATE_EVENT_SERVICE_ACTION_PREFIX "EpisodicOperationalStateReport"};
        static constexpr NtStringView PERIODIC_METRIC_REPORT_ACTION{S31_CORE_IMPL_STATE_EVENT_SERVICE_ACTION_PREFIX
                                                                    "PeriodicMetricReport"};
        static constexpr NtStringView EPISODIC_METRIC_REPORT_ACTION{S31_CORE_IMPL_STATE_EVENT_SERVICE_ACTION_PREFIX
                                                                    "EpisodicMetricReport"};
        ///@}

        /**
         * @name Waveform message SOAP actions
         */
        ///@{
        static constexpr NtStringView WAVEFORM_STREAM_REPORT_ACTION{S31_CORE_IMPL_WAVEFORM_SERVICE_ACTION_PREFIX
                                                                    "WaveformStream"};
        ///@}

        /// All BICEPS actions.
        static const std::vector<std::string>& bicepsActions();

        /// Check whether the given string is a BICEPS action.
        static bool isBicepsAction(std::string_view s);

        /**
         * @name SDC defined @ref DFL::Mdib::InstanceIdentifier "instance identifier" roots and extensions.
         */
        ///@{
        static constexpr NtStringView ROOT_INVOCATION_SOURCE{S31_CORE_IMPL_SDC_GLUE_URI "/X509Certificate/PEM"};
        static constexpr NtStringView EXTENSION_ANONYMOUS_SDC_PARTICIPANT{"AnonymousSdcParticipant"};
        ///@}
};

}

#undef S31_CORE_IMPL_SDC_GLUE_URI
#undef S31_CORE_IMPL_CONTEXT_SERVICE_ACTION_PREFIX
#undef S31_CORE_IMPL_LOCALIZATION_SERVICE_ACTION_PREFIX
#undef S31_CORE_IMPL_GET_SERVICE_ACTION_PREFIX
#undef S31_CORE_IMPL_SET_SERVICE_ACTION_PREFIX
#undef S31_CORE_IMPL_DESCRIPTOR_EVENT_SERVICE_ACTION_PREFIX
#undef S31_CORE_IMPL_STATE_EVENT_SERVICE_ACTION_PREFIX
#undef S31_CORE_IMPL_WAVEFORM_SERVICE_ACTION_PREFIX
