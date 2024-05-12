#pragma once

#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/Model/Alert/AlertCondition.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignal.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystem.h>
#include <Framework/Mdib/Public/Model/Alert/LimitAlertCondition.h>
#include <Framework/Mdib/Public/Model/Component/Battery.h>
#include <Framework/Mdib/Public/Model/Component/Channel.h>
#include <Framework/Mdib/Public/Model/Component/Clock.h>
#include <Framework/Mdib/Public/Model/Component/Mds.h>
#include <Framework/Mdib/Public/Model/Component/Sco.h>
#include <Framework/Mdib/Public/Model/Component/SystemContext.h>
#include <Framework/Mdib/Public/Model/Component/Vmd.h>
#include <Framework/Mdib/Public/Model/Context/EnsembleContext.h>
#include <Framework/Mdib/Public/Model/Context/LocationContext.h>
#include <Framework/Mdib/Public/Model/Context/PatientContext.h>
#include <Framework/Mdib/Public/Model/Metric/DistributionSampleArrayMetric.h>
#include <Framework/Mdib/Public/Model/Metric/EnumStringMetric.h>
#include <Framework/Mdib/Public/Model/Metric/NumericMetric.h>
#include <Framework/Mdib/Public/Model/Metric/RealTimeSampleArrayMetric.h>
#include <Framework/Mdib/Public/Model/Operation/ActivateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetAlertStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetComponentStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetContextStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetMetricStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetStringOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetValueOperation.h>

namespace DFLTest
{
namespace Mdib
{
namespace UnitTest
{

class MdibChangeSetModifier
{
    public:
        static void addMds(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::MdsHandle& mdsHandle);
        static void addMdsAlertSystem(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::MdsAlertSystemHandle& mdsAlertSystemHandle, const DFL::Mdib::MdsHandle& mdsHandle);
        static void addMdsAlerts(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::MdsAlertSystemHandle& mdsAlertSystem);
        static void addSystemContext(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::SystemContextHandle& systemContextHandle, const DFL::Mdib::MdsHandle& mdsHandle);
        static void addPatientContextIndicator(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::PatientContextIndicatorHandle& patientContextIndicatorHandle, const DFL::Mdib::SystemContextHandle& systemContextHandle);
        static void addPatientContext(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::PatientContextIndicatorHandle& patientContextIndicatorHandle);
        static void addLocationContextIndicator(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::LocationContextIndicatorHandle& locationContextIndicatorHandle, const DFL::Mdib::SystemContextHandle& systemContextHandle);
        static void addLocationContext(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::LocationContextIndicatorHandle& locationContextIndicatorHandle);
        static void addEnsembleContextIndicator(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::EnsembleContextIndicatorHandle& ensembleContextIndicatorHandle, const DFL::Mdib::SystemContextHandle& systemContextHandle);
        static void addEnsembleContext(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::EnsembleContextIndicatorHandle& ensembleContextIndicatorHandle);
        static void addBattery(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::MdsHandle& mdsHandle);
        static void addClock(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::MdsHandle& mdsHandle);
        static void addVmd(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::VmdHandle& vmdHandle, const DFL::Mdib::MdsHandle& mdsHandle);
        static void addVmdAlertSystem(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::VmdAlertSystemHandle& vmdAlertSystemHandle, const DFL::Mdib::VmdHandle& vmdHandle);
        static void addVmdAlerts(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::VmdAlertSystemHandle& vmdAlertSystemHandle);
        static void addMdsSco(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::MdsScoHandle& mdsScoHandle, const DFL::Mdib::MdsHandle& mdsHandle);
        static void addVmdSco(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::VmdScoHandle& vmdScoHandle, const DFL::Mdib::VmdHandle& vmdHandle);
        static void addMdsScos(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::MdsScoHandle& mdsScoHandleHandle);
        static void addVmdScos(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::VmdScoHandle& vmdScoHandleHandle);
        static void addChannel(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::ChannelHandle& channelHandle, const DFL::Mdib::VmdHandle& vmdHandle);
        static void addMetrics(DFL::Mdib::MdibChangeSet& mdibChangeSet, const DFL::Mdib::ChannelHandle& channelHandle);
};

}
}
}
