#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>
#include <Framework/Mdib/Private/ExpImp.h>

namespace DFL::Mdib::Impl::PlugIn::MetricProvider
{

/**
 * @brief Checks consistency of Setting/PreSetting metrics in relation to MetricQuality/Validity
 * @details This checker applies to the Metric Provider role.
 *
 * It covers the following requirements:
 *
 * S32_SRS_1283 [PTSR.24464 .. OSF.1274]:
 * S32 shall provide a CHECKER for METRIC PROVIDERs to verify that the following
 * condition holds true: if a metric's \@MetricCategory in { Set, Preset }, then
 * \@MetricAvailability = Intr.
 *
 * S32_SRS_1286 [PTSR.21913 .. OSF.673]:
 * For each Metric with \@ActivationState in { On, StndBy } and \@MetricCategory in { Set, Preset },
 * a Metric Provider shall set pm:MetricQuality/\@Validity in { Vld, Vldated, NA }.
 *
 * Note:
 * This only applies to metrics which contain the ComponentActivation::On or ComponentActivation::Standby due to
 * OSF 717: "A Metric Provider shall not provide a MetricValue if the ActivationState = Shtdn|Off|Fail."
 * Metrics with ComponentActivation::NotReady are also not checked. There is no explicit definition of what
 * NotReady implies for metric value validity, so checking for Valid/Validated does not make sense.
 * The checker will fail if there is no Metric Value or the Validity is incorrect.
 *
 * @ingroup Mdib
 */

class DFL_MDIB_EXPIMP SettingsValidityChecker: public Checker
{
    public:
        CheckerResult check(
            MdibChangeType changeType,
            const NotNull<MdibSharedPtr>& mdib,
            const MdibTreeStore& mdibTreeStore,
            const MdibChangeSet& changes) override;
};

}
