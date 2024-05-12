#pragma once

#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Public/Model/CodedValueFactory.h>

namespace DFL
{
namespace Mdib
{
namespace CodedValueConstants
{
        /**
         * @brief \ref CodedValue for 11073 code MDC_EVT_BATT_LO.
         */
        const DFL::Mdib::CodedValue MDC_EVT_BATT_LO = DFL::Mdib::CodedValueFactory::create11073cfCode("196802"); ///< 196608 + 194 = 3::194

        /**
         * @brief \ref CodedValue for 11073 code MDC_EVT_FLOW_LO.
         */
        const DFL::Mdib::CodedValue MDC_EVT_FLOW_LO = DFL::Mdib::CodedValueFactory::create11073cfCode("196950"); ///< 196608 + 342 = 3::342

        /**
         * @brief \ref CodedValue for 11073 code MDC_ATTR_ID_INSTNO.
         */
        const DFL::Mdib::CodedValue MDC_ATTR_ID_INSTNO = DFL::Mdib::CodedValueFactory::create11073cfCode("67874"); ///< For VMDs, 65536 + 2338 = 1::2338

        /**
         * @brief \ref CodedValue for 11073 code MDC_ATTR_CHAN_ID.
         */
        const DFL::Mdib::CodedValue MDC_ATTR_CHAN_ID = DFL::Mdib::CodedValueFactory::create11073cfCode("67854"); ///< 65536 + 2318 = 1::2318

        /**
         * @brief \ref CodedValue for 11073 code MDC_DEV_METER_PHYSIO_MULTI_PARAM_MDS.
         */
        const DFL::Mdib::CodedValue MDC_DEV_METER_PHYSIO_MULTI_PARAM_MDS = DFL::Mdib::CodedValueFactory::create11073cfCode("69837");

        /**
         * @brief \ref CodedValue for 11073 code MDC_ATTR_CHAN_NUM_PHYS.
         */
        const DFL::Mdib::CodedValue MDC_ATTR_CHAN_NUM_PHYS = DFL::Mdib::CodedValueFactory::create11073cfCode("67855"); ///< 65536 + 2319 = 1::2319

        /**
         * @brief \ref CodedValue for 11073 code MDC_ATTR_CHAN_NUM_LOGICAL.
         */
        const DFL::Mdib::CodedValue MDC_ATTR_CHAN_NUM_LOGICAL = DFL::Mdib::CodedValueFactory::create11073cfCode("68142"); ///< 65536 + 2606 = 1::2606

        /**
         * @brief \ref CodedValue for 11073 code MDC_ACT_SET_TIME_ZONE.
         */
        const DFL::Mdib::CodedValue MDC_ACT_SET_TIME_ZONE = DFL::Mdib::CodedValueFactory::create11073cfCode("68632");

        /**
         * @brief \ref CodedValue for 11073 code MDC_OP_SET_TIME_SYNC_REF_SRC.
         */
        const DFL::Mdib::CodedValue MDC_OP_SET_TIME_SYNC_REF_SRC = DFL::Mdib::CodedValueFactory::create11073cfCode("128505");

        /**
         * @brief \ref CodedValue for 11073 code MDC_EVT_HI_GT_LIM.
         */
        const DFL::Mdib::CodedValue MDC_EVT_HI_GT_LIM = DFL::Mdib::CodedValueFactory::create11073cfCode("196650");

        /**
         * @brief \ref CodedValue for 11073 code MDC_EVT_LO_LT_LIM.
         */
        const DFL::Mdib::CodedValue MDC_EVT_LO_LT_LIM = DFL::Mdib::CodedValueFactory::create11073cfCode("196672");

        /**
         * @brief \ref CodedValue for 11073 code MDC_EVT_DESAT.
         */
        const DFL::Mdib::CodedValue MDC_EVT_DESAT = DFL::Mdib::CodedValueFactory::create11073cfCode("199854");

        /**
         * @brief \ref CodedValue for 11073 code MDC_ACT_ADMIT_PT.
         */
        const DFL::Mdib::CodedValue MDC_ACT_ADMIT_PT = DFL::Mdib::CodedValueFactory::create11073cfCode("68610");

        /**
         * @brief \ref CodedValue for 11073 code MDC_ACT_PRE_ADMIT_PT.
         */
        const DFL::Mdib::CodedValue MDC_ACT_PRE_ADMIT_PT = DFL::Mdib::CodedValueFactory::create11073cfCode("68614");

        /**
         * @brief \ref CodedValue for 11073 code MDC_TIME_SYNC_NONE.
         */
        const DFL::Mdib::CodedValue MDC_TIME_SYNC_NONE = DFL::Mdib::CodedValueFactory::create11073cfCode("532224");

        /**
         * @brief \ref CodedValue for 11073 code MDC_TIME_SYNC_NTPV3.
         */
        const DFL::Mdib::CodedValue MDC_TIME_SYNC_NTPV3 = DFL::Mdib::CodedValueFactory::create11073cfCode("532225");

        /**
         * @brief \ref CodedValue for 11073 code MDC_TIME_SYNC_NTPV4.
         */
        const DFL::Mdib::CodedValue MDC_TIME_SYNC_NTPV4 = DFL::Mdib::CodedValueFactory::create11073cfCode("532226");

        /**
         * @brief \ref CodedValue for 11073 code MDC_TIME_SYNC_EBWW.
         */
        const DFL::Mdib::CodedValue MDC_TIME_SYNC_EBWW = DFL::Mdib::CodedValueFactory::create11073cfCode("532234");

        /**
         * @brief \ref CodedValue for 11073 code MDC_TIME_SYNC_SNTPV4.
         */
        const DFL::Mdib::CodedValue MDC_TIME_SYNC_SNTPV4 = DFL::Mdib::CodedValueFactory::create11073cfCode("532227");

        /**
         * @brief \ref CodedValue for 11073 code MDC_ATTR_PRIV_CODING_SEMANTICS.
         */
        const DFL::Mdib::CodedValue MDC_ATTR_PRIV_CODING_SEMANTICS = DFL::Mdib::CodedValueFactory::create11073cfCode("68543");

        /**
         * @brief \ref CodedValue for 11073 code MDC_IDT_PATIENT_AUTO_GENERATED.
         */
        const DFL::Mdib::CodedValue MDC_IDT_PATIENT_AUTO_GENERATED = DFL::Mdib::CodedValueFactory::create11073cfCode("194125");

        /**
         * @brief \ref CodedValue for 11073 code MDC_EVT_NOS.
         */
        const DFL::Mdib::CodedValue MDC_EVT_NOS = DFL::Mdib::CodedValueFactory::create11073cfCode("258047");

        /**
         * @brief \ref CodedValue for private 11073 code MDC_DEV_VMD
         */
        const DFL::Mdib::CodedValue MDC_DEV_VMD = DFL::Mdib::CodedValueFactory::create11073cfCode("69634");

        /**
         * @brief \ref CodedValue for private 11073 code MDC_ALERT_SIGNAL_AIS
         */
        const DFL::Mdib::CodedValue MDC_ALERT_SIGNAL_AIS = DFL::Mdib::CodedValueFactory::create11073cfCode("194101");

        /**
         * @brief \ref CodedValue for 11073 code MDC_EVT_DEVICE_AIS_SOME_AUDIO_PAUSED
         */
        const DFL::Mdib::CodedValue MDC_EVT_DEVICE_AIS_SOME_AUDIO_PAUSED = DFL::Mdib::CodedValueFactory::create11073cfCode("204903");

        /**
         * @brief \ref CodedValue for 11073 code MDC_EVT_DEVICE_AIS_AUDIO_OFF
         */
        const DFL::Mdib::CodedValue MDC_EVT_DEVICE_AIS_AUDIO_OFF = DFL::Mdib::CodedValueFactory::create11073cfCode("204805");

        /**
         * @brief \ref CodedValue for 11073 code MDC_EVT_DEVICE_AIS_SOME_ALARM_OFF
         */
        const DFL::Mdib::CodedValue MDC_EVT_DEVICE_AIS_SOME_ALARM_OFF = DFL::Mdib::CodedValueFactory::create11073cfCode("204897");

        /**
         * @brief \ref CodedValue for 11073 code MDC_EVT_DEVICE_AIS_SOME_ALARM_PAUSED
         */
        const DFL::Mdib::CodedValue MDC_EVT_DEVICE_AIS_SOME_ALARM_PAUSED = DFL::Mdib::CodedValueFactory::create11073cfCode("204899");

        /**
         * @brief \ref CodedValue for 11073 code MDC_EVT_STAT_CBP_AIS_ALARM_OFF
         */
        const DFL::Mdib::CodedValue MDC_EVT_STAT_CBP_AIS_ALARM_OFF = DFL::Mdib::CodedValueFactory::create11073cfCode("205984");

        /**
         * @brief \ref CodedValue for 11073 code MDC_EVT_STAT_PRESS_BLD_INV_AIS_ALARM_OFF
         */
        const DFL::Mdib::CodedValue MDC_EVT_STAT_PRESS_BLD_INV_AIS_ALARM_OFF = DFL::Mdib::CodedValueFactory::create11073cfCode("206304");

        /**
         * @brief \ref CodedValue for 11073 code MDC_EVT_STAT_PRESS_BLD_INV_AIS_ALARM_PAUSED
         */
        const DFL::Mdib::CodedValue MDC_EVT_STAT_PRESS_BLD_INV_AIS_ALARM_PAUSED = DFL::Mdib::CodedValueFactory::create11073cfCode("206306");

        /**
         * @brief \ref CodedValue for 11073 code MDC_EVT_STAT_HR_ASYS_VFIB_AIS_ALARM_OFF
         */
        const DFL::Mdib::CodedValue MDC_EVT_STAT_HR_ASYS_VFIB_AIS_ALARM_OFF = DFL::Mdib::CodedValueFactory::create11073cfCode("206176");

        /**
         * @brief \ref CodedValue for 11073 code MDC_EVT_STAT_ASYS_VFIB_AIS_ALARM_OFF
         */
        const DFL::Mdib::CodedValue MDC_EVT_STAT_ASYS_VFIB_AIS_ALARM_OFF = DFL::Mdib::CodedValueFactory::create11073cfCode("205920");

        /**
         * @brief \ref CodedValue for 11073 code MDC_EVT_STAT_HR_AIS_ALARM_OFF
         */
        const DFL::Mdib::CodedValue MDC_EVT_STAT_HR_AIS_ALARM_OFF = DFL::Mdib::CodedValueFactory::create11073cfCode("206144");

        /**
         * @brief \ref CodedValue for 11073 code MDC_EVT_STAT_PRESS_BLD_SYS_DIA_ECMO_AIS_ALARM_OFF
         */
        const DFL::Mdib::CodedValue MDC_EVT_STAT_PRESS_BLD_SYS_DIA_ECMO_AIS_ALARM_OFF = DFL::Mdib::CodedValueFactory::create11073cfCode("206336");

        /**
         * @brief \ref CodedValue for 11073 code MDC_EVT_STAT_PRIVACY_AIS_ALARM_OFF
         */
        const DFL::Mdib::CodedValue MDC_EVT_STAT_PRIVACY_AIS_ALARM_OFF = DFL::Mdib::CodedValueFactory::create11073cfCode("206368");

        /**
         * @brief \ref CodedValue for public 11073 code MDC_IDT_ENSEMBLE_LOCATION_INFERRED.
         */
        const DFL::Mdib::CodedValue MDC_IDT_ENSEMBLE_LOCATION_INFERRED = DFL::Mdib::CodedValueFactory::create11073cfCode("532608");

        /**
         * @brief \ref CodedValue for public 11073 code MDC_IDT_ENSEMBLE_PATIENT_INFERRED
         */
        const DFL::Mdib::CodedValue MDC_IDT_ENSEMBLE_PATIENT_INFERRED = DFL::Mdib::CodedValueFactory::create11073cfCode("532609");

        /**
         * @brief \ref CodedValue for public 11073 code MDC_ID_MODEL_NUMBER
         */
        const DFL::Mdib::CodedValue MDC_ID_MODEL_NUMBER = DFL::Mdib::CodedValueFactory::create11073cfCode("531969");

        /**
         * @brief \ref CodedValue for public 11073 code MDC_ID_MODEL_MANUFACTURER
         */
        const DFL::Mdib::CodedValue MDC_ID_MODEL_MANUFACTURER = DFL::Mdib::CodedValueFactory::create11073cfCode("531970");

        /**
         * @brief \ref CodedValue for public 11073 code MDC_ATTR_ID_SOFT
         */
        const DFL::Mdib::CodedValue MDC_ATTR_ID_SOFT = DFL::Mdib::CodedValueFactory::create11073cfCode("67886");

        /**
         * @brief \ref CodedValue for private 11073 code MDC_ACT_MONITORED_BY_DISTRIBUTED_ALARM_SYSTEM
         * @details From Common Draeger Operation List
         */
        const DFL::Mdib::CodedValue MDC_ACT_MONITORED_BY_DISTRIBUTED_ALARM_SYSTEM = DFL::Mdib::CodedValueFactory::create11073cfCode("128918");


} /* namespace CodedValueConstants */
} /* namespace Mdib */
} /* namespace DFL */
