#pragma once

#include <PCS/Test/TsrTestReport.h>

namespace DFL::Mdib::UnitTest
{

inline void comprehensiveCheckerDocumentation(const std::string& checkerName, const std::string& checkerRoles)
{
    DRAEGER_TESTOBJECTIVE(checkerName + " Mdib Consistency Checker");
    DRAEGER_TESTMETHOD("For each test case, a Test Mdib with a well defined initial state and with the " + checkerName + "Checker active is created. "
                       "Subsequently, it is attempted to write different changesets into the Mdib which the checker either accepts or rejects. "
                       "The write result is cross checked against expected behavior.");
    DRAEGER_PASS_CRITERIA("The test passes if the checker correctly accepts and rejects the mdib changesets as specified and if the checker "
                          "provides the correct reasons for rejecting a changeset.");
    DRAEGER_SCOPE("To ensure consistency of the mdib and compliance with the SDC Standard Family, "
                  "only certain combinations of values are allowed for the attributes of descriptors and states. "
                  "This is enforced via a Mdib Consistency Checker which ensures that the mdib adheres to these restrictions. "
                  "The restrictions tested here are relevant for " + checkerRoles + ".");
}

inline void comprehensiveAlertProviderCheckerDocumentation(const std::string& checkerName)
{
    comprehensiveCheckerDocumentation("AlertProvider::" + checkerName, "Alert Providers");
}

inline void comprehensiveMetricProviderCheckerDocumentation(const std::string& checkerName)
{
    comprehensiveCheckerDocumentation("MetricProvider::" + checkerName, "Metric Providers");
}

inline void comprehensiveLocalizingProviderCheckerDocumentation(const std::string& checkerName)
{
    comprehensiveCheckerDocumentation("LocalizingProvider::" + checkerName, "Localizing Providers");
}

inline void comprehensiveCommonCheckerDocumentation(const std::string& checkerName)
{
    comprehensiveCheckerDocumentation(checkerName, "SDC Service Providers");
}

}
