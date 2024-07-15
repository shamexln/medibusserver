#pragma once
#pragma comment(lib, "../SdcProvider/bin/SdcProvider.lib")  
#include <string>
#include "../SdcProvider/SdcProvider.h"
//class __declspec(dllimport) CSdcProvider;

/**
 * @brief Sample SDC provider for metric values, waveforms and alarms.
 */
class SdcProvider
{
public:
    explicit SdcProvider();
    ~SdcProvider();

    void start(const std::string& strDeviceName, const std::string& strMdsCFCode, const std::string& strMdsHandle);
    void initLocation(const std::string& strFacility, const std::string& strPointOfCare,
        const std::string& strBed, const std::string& strRoom = "", const std::string& strBuilding = "", const std::string& strFloor = "");
	void initNumericMetric(DFL::Mdib::MdibChangeSet& changeSet,
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
    void initEnumStringMetric(DFL::Mdib::MdibChangeSet& changeSets, const std::string& strMdsHandle,
                              const std::string& strVmdHandle, const std::string& strVmdCode,
                              const std::string& strChannelHandle, const std::string& strChannelCode,
                              const std::string& strHandleEnumStringMetric, const std::string& strMedicalClass,
                              const std::string& strTypeCode, const std::string& strUnitCode,
                              const std::vector<std::string>& vecAllowedValueCodes,
                              const std::vector<std::string>& vecAllowedValues, const std::string& strMetricCategory,
                              const std::string& strDerivation, const std::string& strAvailability);
    void updateNumericMetricValue(const std::string& handle, int value);
    void updateEnumStringMetricValue(const std::string& handle, const std::string& value);
    void shutdownMdsAndWaitReportSent();

private:
    void initMetadata(std::string strDeviceName, std::string strDeviceId);
    void initPatient();
    
    void initMdib(std::string strDeviceName, std::string strCode);
    CSdcProvider m_provider;
};
