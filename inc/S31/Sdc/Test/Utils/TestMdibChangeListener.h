#pragma once

#include <S31/Sdc/Test/Utils/s31core_it_utils_exp_imp.h>

#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibObserver.h>
#include <Framework/Mdib/Public/MdibSmartPtrTypes.h>
#include <Framework/Utils/Public/NotNull.h>

#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>

namespace S31::Test
{

/// Type of change to be watched by the listener.
enum MdibChangeType {
    MdibChangeType_RealTimeSampleArray,
    MdibChangeType_MdsDescriptor,
    MdibChangeType_VmdAlertSystem,
    MdibChangeType_NumericMetric,
    MdibChangeType_Any
};

///
/// \brief A Mdib change listener used by class S31::Test::TestBase.
///
/// Used to provide a simple interface to watch for Mdib changes in integration tests.
class S31_CORE_IT_UTIL_EXPIMP TestMdibChangeListener: public DFL::Mdib::MdibObserver
{
    public:
        /// \param t The type of change the listener ist interested in.
        explicit TestMdibChangeListener(MdibChangeType t);
        virtual ~TestMdibChangeListener();

        void onChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib,
                      const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes,
                      DFL::Mdib::MdibChangeType changeType) override;

        /// Wait the given time for the expected change to appear.
        /// \returns true if the the expected change happened otherwise false
        bool waitForChange(unsigned int timeout_ms);

        /// Get the latest expected change.
        const DFL::Mdib::ConstMdibChangeSetSharedPtr latestChange();

        /// Forget about any received changes.
        void reset();
    private:

        MdibChangeType m_expectedMdibChangeType;
        std::atomic_bool m_expectedChangeHasHappened;
        std::condition_variable m_waitForChangeConditionVariable;
        std::mutex m_mutex;

        DFL::Mdib::ConstMdibChangeSetSharedPtr m_latestChange;
};

}
