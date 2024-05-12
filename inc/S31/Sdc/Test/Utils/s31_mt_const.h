#pragma once

#include <Framework/Chrono/Public/Duration.h>

namespace S31::Test
{

const char SPO2[] = "SpO2";
const char HR[] = "HR";
const char PLS[] = "PLS";
const char FIO2[] = "FiO2";
const char FIO2_32[] = "FiO2_32";
const char HLM[] = "HLM";
const char HLM_32[] = "HLM_32";
const char P_HLM[] = "P_HLM";
const char CALC1[] = "Calc1";

/// Unit in S14 id and according CF10
/// @{
const char GRAMS_PER_LITER[] = "GRAMS_PER_LITER";
const char GRAMS_PER_LITER_CF10[] = "264192";
const char HERTZ[] = "HERTZ";
const char HERTZ_CF10[] = "264640";
const char YEAR[] = "YEAR";
const char YEAR_CF10[] = "264512";
const char PERCENT_CF10[] = "262688";
const char CENTIMETER[] = "CENTIMETER";
const char CENTIMETER_CF10[] = "263441";
const char METER[] = "METER";
const char METER_CF10[] = "263424";
const char MMHG[] = "MMHG";
const char MMHG_CF10[] = "266016";
const char INCH[] = "INCH";
const char INCH_CF10[] = "263520";
const char LITER_PER_SEC[] = "LITER_PER_SEC";
const char LITER_PER_MIN[] = "LITER_PER_MIN";
const char GRAM[] = "GRAM";
const char GRAM_CF10[] = "263872";
/// @}

/// Coded values types of MDIB elements
/// @{
const char SPO2_TYPE_CODE_CF10[] = "150456";
const char PLS_TYPE_CODE_CF10[] = "149530";
/// @}

// PDR
const char S31_TESTS_WPF_SENDMEASUREMENTS_[] = "S31_Tests.WPF.SendMeasurements.";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_[] = "S31_Tests.WPF.ReceivedSettings.";
const char _INTERNALUNIT[] = ".InternalUnit";
const char _DISPLAYUNIT[] = ".DisplayUnit";
const char _VALUE[] = ".Value";
const char _PARAMETERSTATE[] = ".ParameterState";
const char _RANGE[] = ".Range";
const char _ACTIVATIONSTATE[] = ".ActivationState";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_FIO2_VALUE[] = "S31_Tests.WPF.ReceivedSettings.FiO2.Value";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_FIO2_32_VALUE[] = "S31_Tests.WPF.ReceivedSettings.FiO2_32.Value";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_FIO2_RANGE[] = "S31_Tests.WPF.ReceivedSettings.FiO2.NormalRange";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_FIO2_32_RANGE[] = "S31_Tests.WPF.ReceivedSettings.FiO2_32.NormalRange";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_FIO2_PARAMETERSTATE[] = "S31_Tests.WPF.ReceivedSettings.FiO2.ParameterState";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_FIO2_32_PARAMETERSTATE[] = "S31_Tests.WPF.ReceivedSettings.FiO2_32.ParameterState";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_FIO2_ACTIVATED[] = "S31_Tests.WPF.ReceivedSettings.FiO2.ActivationState";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_FIO2_32_ACTIVATED[] = "S31_Tests.WPF.ReceivedSettings.FiO2_32.ActivationState";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_FIO2_DISPLAYUNIT[] = "S31_Tests.WPF.ReceivedSettings.FiO2.DisplayUnit";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_FIO2_32_DISPLAYUNIT[] = "S31_Tests.WPF.ReceivedSettings.FiO2_32.DisplayUnit";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_FIO2_INTERNALUNIT[] = "S31_Tests.WPF.ReceivedSettings.FiO2.InternalUnit";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_FIO2_32_INTERNALUNIT[] = "S31_Tests.WPF.ReceivedSettings.FiO2_32.InternalUnit";

const char S31_TESTS_WPF_RECEIVEDSETTINGS_HLM_VALUE[] = "S31_Tests.WPF.ReceivedSettings.HLM.Value";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_HLM_32_VALUE[] = "S31_Tests.WPF.ReceivedSettings.HLM_32.Value";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_HLM_PARAMETERSTATE[] = "S31_Tests.WPF.ReceivedSettings.HLM.ParameterState";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_HLM_32_PARAMETERSTATE[] = "S31_Tests.WPF.ReceivedSettings.HLM_32.ParameterState";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_HLM_ACTIVATED[] = "S31_Tests.WPF.ReceivedSettings.HLM.ActivationState";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_HLM_32_ACTIVATED[] = "S31_Tests.WPF.ReceivedSettings.HLM_32.ActivationState";

const char S31_TESTS_WPF_RECEIVEDSETTINGS_P_HLM_VALUE[] = "S31_Tests.WPF.ReceivedSettings.P_HLM.Value";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_P_HLM_DISPLAYUNIT[] = "S31_Tests.WPF.ReceivedSettings.P_HLM.DisplayUnit";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_P_HLM_INTERNALUNIT[] = "S31_Tests.WPF.ReceivedSettings.P_HLM.InternalUnit";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_P_HLM_PARAMETERSTATE[] = "S31_Tests.WPF.ReceivedSettings.P_HLM.ParameterState";
const char S31_TESTS_WPF_RECEIVEDSETTINGS_P_HLM_ACTIVATED[] = "S31_Tests.WPF.ReceivedSettings.P_HLM.ActivationState";

const char S31_TESTS_WPF_SENDSETTINGS_HR_UPPERLIMIT_VALUE[] = "S31_Tests.WPF.SendSettings.HR_UpperLimit.Value";
const char S31_TESTS_WPF_SENDSETTINGS_HR_UPPERLIMIT_ENABLE[] = "S31_Tests.WPF.SendSettings.HR_UpperLimit.Enable";

const char S31_TESTS_WPF_SENDSETTINGS_HR_LOWERLIMIT_VALUE[] = "S31_Tests.WPF.SendSettings.HR_LowerLimit.Value";
const char S31_TESTS_WPF_SENDSETTINGS_HR_LOWERLIMIT_ENABLE[] = "S31_Tests.WPF.SendSettings.HR_LowerLimit.Enable";

const char S31_TESTS_WPF_RECEIVEDMEASUREMENTS_SPO2[] = "S31_Tests.WPF.ReceivedMeasurements.SpO2";
const char S31_TESTS_WPF_RECEIVEDMEASUREMENTS_SPO2_VALUE[] = "S31_Tests.WPF.ReceivedMeasurements.SpO2.Value";
const char S31_TESTS_WPF_RECEIVEDMEASUREMENTS_SPO2_DISPLAYUNIT[] = "S31_Tests.WPF.ReceivedMeasurements.SpO2.DisplayUnit";
const char S31_TESTS_WPF_RECEIVEDMEASUREMENTS_SPO2_INTERNALUNIT[] = "S31_Tests.WPF.ReceivedMeasurements.SpO2.InternalUnit";
const char S31_TESTS_WPF_RECEIVEDMEASUREMENTS_SPO2_RANGE[] = "S31_Tests.WPF.ReceivedMeasurements.SpO2.Range";
const char S31_TESTS_WPF_RECEIVEDMEASUREMENTS_SPO2_NORMALRANGE[] = "S31_Tests.WPF.ReceivedMeasurements.SpO2.NormalRange";
const char S31_TESTS_WPF_RECEIVEDMEASUREMENTS_SPO2_PARAMETERSTATE[] = "S31_Tests.WPF.ReceivedMeasurements.SpO2.ParameterState";

const char S31_TESTS_WPF_RECEIVEDMEASUREMENTS_PLS[] = "S31_Tests.WPF.ReceivedMeasurements.PLS";
const char S31_TESTS_WPF_RECEIVEDMEASUREMENTS_PLS_VALUE[] = "S31_Tests.WPF.ReceivedMeasurements.PLS.Value";
const char S31_TESTS_WPF_RECEIVEDMEASUREMENTS_PLS_DISPLAYUNIT[] = "S31_Tests.WPF.ReceivedMeasurements.PLS.DisplayUnit";
const char S31_TESTS_WPF_RECEIVEDMEASUREMENTS_PLS_INTERNALUNIT[] = "S31_Tests.WPF.ReceivedMeasurements.PLS.InternalUnit";

const char S31_TESTS_WPF_RECEIVEDWAVEFORMS_DISPLAYUNIT[] = "S31_Tests.WPF.ReceivedWaveforms.Flow.DisplayUnit";
const char S31_TESTS_WPF_RECEIVEDWAVEFORMS_INTERNALUNIT[] = "S31_Tests.WPF.ReceivedWaveforms.Flow.InternalUnit";
const char S31_TESTS_WPF_RECEIVEDWAVEFORMS_CONNECTSTATUS[] = "S31_Tests.WPF.ReceivedWaveforms.Flow.Status";
const char S31_TESTS_WPF_SENDWAVEFORMS_DISPLAYUNIT[] = "S31_Tests.WPF.SendWaveforms.Flow.DisplayUnit";
const char S31_TESTS_WPF_SENDWAVEFORMS_INTERNALUNIT[] = "S31_Tests.WPF.SendWaveforms.Flow.InternalUnit";
const char S31_TESTS_WPF_SENDWAVEFORMS_CONNECTSTATUS[] = "S31_Tests.WPF.SendWaveforms.Flow.Status";

const char S31_TESTS_WPF_SENDMEASUREMENTS_SPO2[] = "S31_Tests.WPF.SendMeasurements.SpO2";
const char S31_TESTS_WPF_SENDMEASUREMENTS_PLS[] = "S31_Tests.WPF.SendMeasurements.PLS";
const char S31_TESTS_WPF_SENDMEASUREMENTS_CALC1[] = "S31_Tests.WPF.SendMeasurements.Calc1";
const char S31_TESTS_WPF_SENDMEASUREMENTS_HR_INTERNALUNIT[] = "S31_Tests.WPF.SendMeasurements.HR.InternalUnit";

const char S31_TESTS_WPF_ALERTLIMITS_HR[] = "WPF_AlertLimits.HR";
const char S31_TESTS_WPF_ALERTLIMITS_HR2[] = "WPF_AlertLimits.HR2";

const char S31_TESTS_WPF_CONNECTION_DEVICEIDNODE[] = "S31_Tests.WPF.Connection.DeviceIdNode";
const char S31_TESTS_WPF_CONNECTION_CONNECTIONSTATE1[] = "S31_Tests.WPF.Connection.ConnectionState1";
const char S31_TESTS_WPF_CONNECTION_CONNECTIONSTATE2[] = "S31_Tests.WPF.Connection.ConnectionState2";
const char S31_TESTS_WPF_CONNECTION_CONNECTIONSTATE3[] = "S31_Tests.WPF.Connection.ConnectionState3";

const char S31_TESTS_WPF_ALARMS_HIGHEST_GRADE_ALARM[] = "S20.SYSTEM.InternalValues.ExtDevHighestGradeAlarm";
const char S31_TESTS_WPF_ALARMS_INFO_LIST[] = "S20.SYSTEM.InternalValues.ExtDevAlarmInfoList";

const char S31_TESTS_WPF_ALARMS_HANDLECONDITION[] = "TestAlertCondition";
const char S31_TESTS_WPF_ALARMS_HANDLELIMITCONDITION[] = "TestLimitAlertCondition";

const char S31_TESTS_WAVEFORM_HANDLE_THAT_NEVER_CHANGES[] = "rtsaNeverChanges";

const char A0X80009999[] = "0x80009999";
const char A0X80009001[] = "0x80009001";

const char A0X80009999_AUD[] = "AlertSignal_0x80009999_Aud";
const char A0X80009999_VIS[] = "AlertSignal_0x80009999_Vis";
const char A0X80009001_AUD[] = "AlertSignal_0x80009001_Aud";
const char A0X80009001_VIS[] = "AlertSignal_0x80009001_Vis";

const char A0X80009010[] = "0x80009010";
const char A0X80009011[] = "0x80009011";
const char A0X80009000[] = "0x80009000";
const char A0X80009020[] = "0x80009020";
const char A0X80009021[] = "0x80009021";
const char A0X80009022[] = "0x80009022";

const char A0X80009010_AUD[] = "AlertSignal_0x80009010_Aud";
const char A0X80009010_VIS[] = "AlertSignal_0x80009010_Vis";
const char A0X80009011_AUD[] = "AlertSignal_0x80009011_Aud";
const char A0X80009011_VIS[] = "AlertSignal_0x80009011_Vis";

const char A0X80009999_STARTTIME[] = "S20.Alarms.1.0x9999.StartTime";
const char A0X80009000_STARTTIME[] = "S20.Alarms.1.0x9000.StartTime";
const char A0X80009010_STARTTIME[] = "S20.Alarms.1.0x9010.StartTime";
const char A0X80009011_STARTTIME[] = "S20.Alarms.1.0x9011.StartTime";

const char A0X80009000_ASSOALARMPARAMETER[] = "S20.Alarms.1.0x9000.AssociatedAlarmParameter";
const char A0X80009020_ASSOALARMPARAMETER[] = "S20.Alarms.1.0x9020.AssociatedAlarmParameter";
const char A0X80009021_ASSOALARMPARAMETER[] = "S20.Alarms.1.0x9021.AssociatedAlarmParameter";

const char A0X80009999_TEXTID[] = "S20.Alarms.1.0x9999.MasterAlarmTextId";
const char A0X80009000_TEXTID[] = "S20.Alarms.1.0x9000.MasterAlarmTextId";
const char A0X80009010_TEXTID[] = "S20.Alarms.1.0x9010.MasterAlarmTextId";
const char A0X80009011_TEXTID[] = "S20.Alarms.1.0x9011.MasterAlarmTextId";

const char SOURCEMETRIC1[] = "sourcemetric1";

const char URN_DEVICE_WORK_PLACE_1[] = "urn:uuid:00000000-5544-2222-4433-444444444401";
const char URN_DEVICE_WORK_PLACE_2[] = "urn:uuid:00000000-5544-2222-4433-444444444402";
const char URN_DEVICE_NOT_AT_WORK_PLACE[] = "urn:uuid:00000000-5544-2222-4433-444444444403";
const unsigned int ALARM_ID = 111999;
const unsigned int ALARM_ID_2 = 1234;
const char ALARM_ID_2_STR[] = "1234";

const char WPF_RECEIVEDSETTINGS_FIO2[] = "WPF_ReceivedSettings.FiO2";
const char WPF_RECEIVEDSETTINGS_FIO2_32[] = "WPF_ReceivedSettings.FiO2_32";
const char WPF_RECEIVEDSETTINGS_HLM[] = "WPF_ReceivedSettings.HLM";
const char WPF_RECEIVEDSETTINGS_HLM_32[] = "WPF_ReceivedSettings.HLM_32";
const char WPF_RECEIVEDSETTINGS_P_HLM[] = "WPF_ReceivedSettings.P_HLM";

/// handles used as S14 IDs and MDIB handles
/// @{
const char WPF_SENDMEASURES[] = "WPF_SendMeasures.";
const char WPF_SENDMEASURES_SPO2[] = "WPF_SendMeasures.SpO2";
const char WPF_SENDSETTING_PEF[] = "S17SettingTable.PEF";
const char WPF_SENDSETTING_ENUM[] = "SendEnumSetting";
const char WPF_RECEIVEDMEASURES_SPO2[] = "WPF_ReceivedMeasures.SpO2";
const char WPF_RECEIVEDMEASURES_PLS[] = "WPF_ReceivedMeasures.PLS";
const char WPF_RECEIVEDMEASURES_PLS_1[] = "WPF_ReceivedMeasures.PLS1";
const char WPF_RECEIVEDMEASURES_PLS_2[] = "WPF_ReceivedMeasures.PLS2";
const char WPF_RECEIVEDMEASURES_PLS_3[] = "WPF_ReceivedMeasures.PLS3";
const char HEMO_ST_ST_LEAD_DERIVED_V6[] = "Hemo_ST.ST_LEAD_DERIVED_V6";
const char HEMO_ST_ST_LEAD_DERIVED_V6_REMOTE[] = "Hemo_ST.ST_LEAD_DERIVED_V6_REMOTE";
const char WPF_RECEIVEDSETTINGS_FIO2_MDIB[] = "WPF_ReceivedSettings.FiO2.MDIB";
const char WPF_RECEIVEDSETTINGS_FIO2_32_MDIB[] = "WPF_ReceivedSettings.FiO2_32.MDIB";
const char WPF_RECEIVEDSETTINGS_HLM_MDIB[] = "WPF_ReceivedSettings.HLM.MDIB";
const char WPF_RECEIVEDSETTINGS_HLM_MDIB2[] = "WPF_ReceivedSettings.HLM.MDIB2";
const char WPF_RECEIVEDSETTINGS_HLM_32_MDIB[] = "WPF_ReceivedSettings.HLM_32.MDIB";
const char WPF_RECEEIVEDWAVEFORMS_FLOWIN[] = "WPF_ReceivedWaveforms.FlowIn";
const char WPF_RECEEIVEDWAVEFORMS_FLOWIN1[] = "WPF_ReceivedWaveforms.FlowIn1";
const char WPF_RECEEIVEDWAVEFORMS_FLOWIN2[] = "WPF_ReceivedWaveforms.FlowIn2";
const char WPF_RECEEIVEDWAVEFORMS_FLOWIN3[] = "WPF_ReceivedWaveforms.FlowIn3";

const char WPF_RECOMMENDATION_REC1[] = "WPF.Recommendation1";
const char WPF_CALCULATION_CALC1[] = "S31_Tests.WPF.SendMeasurements.Calc1";
/// @}

const unsigned int MAPPING_ID_SPO2 = 200;
const unsigned int MAPPING_ID_PLS = 201;
const unsigned int MAPPING_ID_HLM = 205;

// constants used in integration tests

const DFL::Chrono::Milliseconds IT_TESTONCHANGE_WAITTIME(2500);
const unsigned int IT_TESTONCHANGE_EXTRAWAITTIME = 2000; // ms
const unsigned int IT_TESTONCHANGE_EXTRAWAITTIME_DIV100 = IT_TESTONCHANGE_EXTRAWAITTIME / 100; // 1/10th of s

// Arbitrary public 11073 codes used in integration tests
const char APublic11073Code1[] = "66000";
const char APublic11073Code2[] = "66001";

}
