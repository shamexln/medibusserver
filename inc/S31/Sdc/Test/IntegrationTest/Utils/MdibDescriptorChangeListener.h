#pragma once

#include <Framework/Mdib/Public/MdibObserver.h>
#include <Framework/Mdib/Public/Model/Handle.h>

#include <condition_variable>
#include <vector>

namespace S31::Sdc::Test
{

/**
 * Mdib change listener for descriptor modifications.
 *
 * This class is a helper implementation for Mdib descriptor modification
 * reports. It receives the descriptor updates to allow verification
 * of change reception by the unit test.
 */
class MdibDescriptorChangeListener: public DFL::Mdib::MdibObserver
{
    public:
        /**
         * This method is called for each set of changes to the %MDIB.
         *
         * @param changes Container with all changes.
         */
        void onChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib,
                      const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes,
                      DFL::Mdib::MdibChangeType changeType) override;

        void waitForDeletedDescriptors();
        void waitForNewDescriptors();
        void waitForNewStates();
        void waitForUpdatedStates();

        void eraseLists();

        DFL::Mdib::Handles getDeletedDescriptors();
        DFL::Mdib::Handles getNewDescriptors();
        DFL::Mdib::Handles getNewStates();
        DFL::Mdib::Handles getUpdatedStates();

    private:
        template<class T> void processStateList(const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes);
        template<class... T1> void processDescriptorList(const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes,
                                                         typename std::enable_if<sizeof...(T1) == 0>::type* = 0);
        template<class T1, class... T2> void processDescriptorList(const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes);

        DFL::Mdib::Handles m_deletedDescriptors;
        DFL::Mdib::Handles m_newDescriptors;
        DFL::Mdib::Handles m_newStates;
        DFL::Mdib::Handles m_updatedStates;
        std::mutex m_mutex;
        std::condition_variable m_delDescCond;
        std::condition_variable m_newDescCond;
        std::condition_variable m_newStateCond;
        std::condition_variable m_updatedStateCond;
};

}
