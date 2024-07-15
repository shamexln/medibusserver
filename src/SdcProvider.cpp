#include "SdcProvider.h"

#include <string>
#include <windows.h>



void SdcProvider::initMetadata(std::string strDeviceName, std::string strDeviceId)
{
    
}



 void SdcProvider::initPatient()
{
    
} 



void SdcProvider::initLocation(const std::string& strFacility, const std::string& strPointOfCare,
    const std::string& strBed, const std::string& strRoom, const std::string& strBuilding, const std::string& strFloor)
{
    m_provider.initLocation(strFacility, strPointOfCare, strBed, strRoom, strBuilding, strFloor);
}


SdcProvider::SdcProvider()
{
    
    HINSTANCE dllHandle = LoadLibrary(TEXT("SdcProvider.dll"));
    
}

SdcProvider::~SdcProvider()
{

}

void SdcProvider::start(const std::string& strDeviceName, const std::string& strMdsCFCode, const std::string& strMdsHandle)
{
    m_provider.start(strDeviceName, strMdsCFCode, strMdsHandle);
}

void SdcProvider::initNumericMetric(DFL::Mdib::MdibChangeSet& changeSet,
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
	const std::string& strAvailability)
{
	m_provider.initNumericMetric(changeSet, strMdsHandle, strVmdHandle, strVmdCode, strChannelHandle, strChannelCode,
	                             strHandleNumericMetric, strMedicalClass, strTypeCode, strUnitCode, strMetricCategory, strLowerRange,
	                             strUpperRange, strDeterminationPeriod, strLifeTimePeriod, strMaxDelayTime, strResolution, strDerivation, strAvailability);
}

void SdcProvider::initEnumStringMetric(DFL::Mdib::MdibChangeSet& changeSets,
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
    const std::string& strAvailability)
{
	m_provider.initEnumStringMetric(
		changeSets, strMdsHandle, strVmdHandle, strVmdCode, strChannelHandle, strChannelCode, strHandleEnumStringMetric,
		strMedicalClass, strTypeCode, strUnitCode, vecAllowedValueCodes, vecAllowedValues, strMetricCategory, strDerivation, strAvailability);

}

void SdcProvider::updateNumericMetricValue(const std::string& handle, int value)
{
	m_provider.updateNumericMetricValue(handle, value);
}

void SdcProvider::updateEnumStringMetricValue(const std::string& handle, const std::string& value)
{
	m_provider.updateEnumStringMetricValue(handle, value);
}

void SdcProvider::initMdib(std::string strDeviceName, std::string strCode)
{
   
}

void SdcProvider::shutdownMdsAndWaitReportSent()
{
    
}
