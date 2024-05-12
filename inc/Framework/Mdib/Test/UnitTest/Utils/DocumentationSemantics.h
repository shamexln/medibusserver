#pragma once

#include <PCS/Test/TsrTestReport.h>

namespace DFL::Mdib::UnitTest
{

inline void comprehensiveSemanticsDocumentation(const std::string& entity)
{
    DRAEGER_TESTOBJECTIVE(entity + " semantics");
    DRAEGER_TESTMETHOD("Create instances of the object under test (or related objects like descriptors, states and builders) and use the provided class interface.");
    DRAEGER_PASS_CRITERIA("The test passes if objects have the expected default values and get and set functions behave accordingly.");
    DRAEGER_SCOPE("Tests ensure compliance with the SDC Standard Family.");
}

}
