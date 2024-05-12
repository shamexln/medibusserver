#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn
{

/**
 * @brief Checks that all sdpi:MdcAttribute/Code falls within the allowable range
 * @details This checker applies to all roles.
 *
 * It covers the following requirements:
 *
 * S32_SRS_1300:
 * S32 shall provide a CHECKER for SDC SERVICE PROVIDERs to verify that the following condition holds true:
 * sdpi:MdcAttribute/Code must be in the range of 67841 to 68609.
 *
 *
 * Note: From requirements for CodedAttribute extension types in the SDPi Supplement Rev 1.0:
 *
 * R0001: An SDC SERVICE PROVIDER shall set sdpi:MdcAttribute/Code to any code from the first
 * partition of the IEEE 11073-10101 nomenclature in the range of 67841 (1::2305) to 68609 (1::3073).
 *
 * This will check all flavors of CodedAttribute, including \ref DFL::Mdib::Ext::CodedStringAttribute,
 * CodedIntegerAttribute and CodedDecimalAttribute
 *
 * @ingroup Mdib
 */
class CodedAttributeChecker : public Checker
{
    public:
        CheckerResult check(
            MdibChangeType changeType,
            const NotNull<MdibSharedPtr>& mdib,
            const MdibTreeStore& mdibTreeStore,
            const MdibChangeSet& changes) override;
};

}
