// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the SDCPROVIDER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// SDCPROVIDER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef SDCPROVIDER_EXPORTS
#define SDCPROVIDER_API __declspec(dllexport)
#else
#define SDCPROVIDER_API __declspec(dllimport)
#endif
#include <memory>
#include <string>
#include <S31/Sdc/Public/Common/IDispatcher.h>
#include <S31/Sdc/Public/Device/LocalDevice.h>

// This class is exported from the dll
class SDCPROVIDER_API CSdcProvider {
public:
    explicit CSdcProvider(void);
	// TODO: add your methods here.
public:
    ~CSdcProvider();

    void start(const std::string& strDeviceName, const std::string& strMdsCFCode, const std::string& strMdsHandle
       /* const std::string& strVmdCFCode, const std::string& strVmdHandle, const std::string& strChannelCFCode, const std::string& strChannelHandle*/);
    void shutdownMdsAndWaitReportSent();
    void initLocation(const std::string& strFacility, const std::string& strPointOfCare,
        const std::string& strBed, const std::string& strRoom = "", const std::string& strBuilding = "",
        const std::string& strFloor = "");
    void initNumericMetric(DFL::Mdib::MdibChangeSet& changeSets,
        const std::string& strMdsHandle,
        const std::string& strVmdHandle,
        const std::string& strVmdCode,
        const std::string& strChannelHandle,
        const std::string& strChannelCode,
        const std::string& strHandleNumericMetric,
        const std::string& strMedicalClass,
        const std::string& strTypeCode,
        const std::string& strUnitCode,
        const std::string& strMetricCategory,
        const std::string& strLowerRange,
        const std::string& strUpperRange,
        const std::string& strDeterminationPeriod,
        const std::string& strLifeTimePeriod,
        const std::string& strMaxDelayTime,
        const std::string& strResolution,
        const std::string& strDerivation,
        const std::string& strAvailability);

    void initEnumStringMetric(DFL::Mdib::MdibChangeSet& changeSets,
        const std::string& strMdsHandle,
        const std::string& strVmdHandle,
        const std::string& strVmdCode,
        const std::string& strChannelHandle,
        const std::string& strChannelCode,
        const std::string& strHandleEnumStringMetric,
        const std::string& strMedicalClass,
        const std::string& strTypeCode,
        const std::string& strUnitCode,
        const std::vector<std::string>& vecAllowedValueCodes,
        const std::vector<std::string>& vecAllowedValues,
        const std::string& strMetricCategory,
        const std::string& strDerivation,
        const std::string& strAvailability);
    void initRealTimeMetric(DFL::Mdib::MdibChangeSet& changeSets, const std::string& strMdsHandle,
                            const std::string& strVmdHandle, const std::string& strVmdCode,
                            const std::string& strChannelHandle, const std::string& strChannelCode,
                            const std::string& strHandleRealTimeMetric, const std::string& strMedicalClass,
                            const std::string& strTypeCode, const std::string& strUnitCode,
                            const std::string& strMetricCategory, const std::string& strLowerRange,
                            const std::string& strUpperRange, const std::string& strDeterminationPeriod,
                            const std::string& strLifeTimePeriod, const std::string& strMaxDelayTime,
                            const std::string& strResolution, const std::string& strDerivation,
                            const std::string& strAvailability, const std::string& strSamplePeriod);
    void initAlarmStatus(DFL::Mdib::MdibChangeSet& changeSets,
        const std::string& strMdsHandle,
        const std::string& strVmdHandle,
        const std::string& strVmdCode,
        const std::string& strHandleAlarmStatus,
        const std::string& strMedicalClass,
        const std::string& strTypeCode,
        const std::string& strSysHandle,
        const std::string& strSysSelfCheckPeriod,
        const std::string& strSysMaxPhysiologicalParallelAlarms,
        const std::string& strSysMaxTechnicalParallelAlarms,
        const std::string& strHandle,
        const std::string& strSource,
        const std::string& strDefaultConditionGenerationDelay,
        const std::string& strKind,
        const std::string& strPriority,
        const std::string& strAlertType,
        const std::string& strInitialActivationState);
    void updateNumericMetricValue(const std::string& handle, int value);
    void updateEnumStringMetricValue(const std::string& handle, const std::string& value);
    void updateRealTimeMetricValue(const std::string& handle, const std::vector<double>& values);
    void updateAlarmStatus(const std::string& mdshandle, const std::string& vmdhandle, const std::string& syshandle, const std::string& handle, const std::string& strKind, const std::string& value);

private:
    void initMetadata(std::string strDeviceName, std::string strDeviceId);
    void initPatient();
    void initMdib(const std::string& strDeviceName, const std::string& strMdsCFCode, const std::string& strMdsHandle
        /*const std::string& strVmdCFCode, const std::string& strVmdHandle, const std::string& strChannelCFCode, const std::string& strChannelHandle*/);
    DFL::Mdib::MetricCategory getMetricCategory(const std::string& strMetricCategory);
    DFL::Mdib::Duration getDuration(const std::string& strPeriod);
    DFL::Mdib::DerivationMethod getDerivationMethod(const std::string& strDerivation);
    DFL::Mdib::MetricAvailability getAvailability(const std::string& strAvailability);
    DFL::Mdib::SafetyClassification getMedicalClass(const std::string& strMedicalClass);
    DFL::Mdib::Duration getMaxDelayTime(const std::string& strMaxDelayTime);
    DFL::Mdib::AlertConditionPriority getAlarmPriority(const std::string& strAlarmPriority);
    DFL::Mdib::AlertConditionKind getAlarmKind(const std::string& strAlarmKind);
    boost::optional<DFL::Chrono::SystemClock::TimePoint> getTimePoint(const std::string& strDuration);

    DFL::Mdib::MdsHandle m_mdsHandle;

    std::shared_ptr<S31::Sdc::LocalDevice>            m_dpwsDevice;
    DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr> m_localMdibAccess;
    std::shared_ptr<S31::Sdc::IDispatcher>            m_dispatcher;
};

extern SDCPROVIDER_API int nSdcProvider;

SDCPROVIDER_API int fnSdcProvider(void);
