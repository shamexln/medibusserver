#pragma once

#include <Framework/Mdib/Public/Model/CodedValue.h>

namespace S31::Nomenclature
{

/**
 * \brief \ref DFL::Mdib::CodeId representing audio-pause activate operation.
 *
 * \details Refid is MDC_OP_SET_ALL_ALARMS_AUDIO_PAUSE.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodeId AudioPauseActivate = DFL::Mdib::CodeId(DFL::Locale::Utf8("128284"));

/**
 * \brief \ref DFL::Mdib::CodeId representing audio-pause de-activate operation.
 *
 * \details Refid is MDC_OP_CANCEL_ALARMS_AUDIO_PAUSE.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodeId AudioPauseDeactivate = DFL::Mdib::CodeId(DFL::Locale::Utf8("128285"));

/**
 * \brief \ref DFL::Mdib::CodeId representing Leakage Of Breathing System.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodeId LeakageOfBreathingSystem = DFL::Mdib::CodeId(DFL::Locale::Utf8("194054"));

/**
 * \brief \ref DFL::Mdib::CodeId representing Device Check.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodeId DeviceCheck = DFL::Mdib::CodeId(DFL::Locale::Utf8("192686"));

/**
 * \brief \ref DFL::Mdib::CodeId for source relations.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodeId MdcEvtAddSourceRel = DFL::Mdib::CodeId(DFL::Locale::Utf8("194468"));

/**
 * \brief \ref DFL::Mdib::CodeId representing MDC Mode - On.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodeId MdcModeOn = DFL::Mdib::CodeId(DFL::Locale::Utf8("192834"));

/**
 * \brief \ref DFL::Mdib::CodeId representing MDC Mode - Off.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodeId MdcModeOff = DFL::Mdib::CodeId(DFL::Locale::Utf8("192835"));

/**
 * \brief \ref DFL::Mdib::CodeId representing MDC Mode - PSD.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodeId MdcModePsd = DFL::Mdib::CodeId(DFL::Locale::Utf8("193933"));

/**
 * \brief \ref DFL::Mdib::CodeId representing MDC Mode Of Operation - On.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodeId MdcModeOfOperationOn = DFL::Mdib::CodeId(DFL::Locale::Utf8("532736"));

/**
 * \brief \ref DFL::Mdib::CodeId representing MDC Mode Of Operation - Off.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodeId MdcModeOfOperationOff = DFL::Mdib::CodeId(DFL::Locale::Utf8("532737"));

/**
 * \brief \ref DFL::Mdib::CodeId representing MDC Mode Of Operation - PSD.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodeId MdcModeOfOperationPsd = DFL::Mdib::CodeId(DFL::Locale::Utf8("532738"));

/**
 * \brief \ref DFL::Mdib::CodeId representing MDC alert signal types.
 *
 * \ingroup S31Nomenclature
 *
 * @{
 */
static const DFL::Mdib::CodeId MdcAlertSignalNormal = DFL::Mdib::CodeId(DFL::Locale::Utf8("194088"));
static const DFL::Mdib::CodeId MdcAlertSignalNormalPrioColorLatched = DFL::Mdib::CodeId(DFL::Locale::Utf8("194086"));
static const DFL::Mdib::CodeId MdcAlertSignalNoPrioColorLatched = DFL::Mdib::CodeId(DFL::Locale::Utf8("194087"));
static const DFL::Mdib::CodeId MdcAlertSignalRepeatedBurst = DFL::Mdib::CodeId(DFL::Locale::Utf8("194090"));
/** @} */

/**
 * \brief \ref DFL::Mdib::CodeId representing Waveform Flow.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodeId WaveformFlow = DFL::Mdib::CodeId(DFL::Locale::Utf8("151764"));

/**
 * \brief \ref DFL::Mdib::CodeId representing Waveform Volume.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodeId WaveformVolume = DFL::Mdib::CodeId(DFL::Locale::Utf8("151876"));

/**
 * \brief \ref DFL::Mdib::CodeId representing the color scheme set operation.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodeId TypeColorScheme = DFL::Mdib::CodeId(DFL::Locale::Utf8("128283"));

/**
 * \brief \ref DFL::Mdib::CodeId representing the color scheme set operation of target.
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodeId TargetTypeColorScheme = DFL::Mdib::CodeId(DFL::Locale::Utf8("16971357"));

/**
 * \brief \ref DFL::Mdib::CodeId for Common Draeger Enum AGENT::NONE
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodeId AgentNone = DFL::Mdib::CodeId(DFL::Locale::Utf8("192871"));

/**
 * \brief \ref DFL::Mdib::CodeId for Common Draeger Enum VENT_RUNNING
 *
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodeId VentRunning = DFL::Mdib::CodeId(DFL::Locale::Utf8("193795"));
}
