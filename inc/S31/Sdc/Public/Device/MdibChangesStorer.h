#pragma once

#include <S31/Sdc/Public/Device/MedicalDeviceData.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>
#include <string>

namespace S31::BicepsXml
{
class XmlReportObserver;
}

namespace S31::Sdc::Experimental
{

/**
 * @brief Stores all Mdib changes as (BICEPS-)XML reports in the given directory.
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP MdibChangesStorer
{
    public:
        MdibChangesStorer(const std::string& path, S31::Sdc::MedicalDeviceData deviceData);

    private:
        DFL::NotNull<std::shared_ptr<S31::BicepsXml::XmlReportObserver>> m_observer;
        S31::Sdc::MedicalDeviceData                                      m_medicalDeviceData;
};

}
