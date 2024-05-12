#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Private/PublisherCache.h>
#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibObserver.h>
#include <Framework/Mdib/Public/SubdividedMdibObserver.h>

#include <Framework/Utils/Public/Observer/BasicSubject.h>
#include <Framework/Utils/Public/Observer/Invoke.h>

#include <mutex>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/**
 * \brief %PublisherHelper is responsible for publishing MDIB changes in the correct order based on the \ref MdibVersion.
 *
 * \ingroup Mdib
 *
 * \details %PublisherHelper manages \ref DFL::Mdib::MdibObserver and \ref SubdividedMdibObserver instances and publishes changes
 * in the correct \ref MdibVersion order.

 * The queueStateChanges or queueDescriptorChanges function is invoked during an Mdib write operation to queue all Mdib changes to a
 * \ref PublisherCache. Note it must be called under the transaction lock to avoid potentially skipping an MdibVersion changed on
 * a low priority thread.  The queueing function will block if no space is available in the %PublisherCache.
 *
 * The executePendingChanges function is responsible for generating function callback(s) and publishing them based on the
 * \ref MdibVersion.
 */
class DFL_MDIB_EXPIMP PublisherHelper
{
    public:
        explicit PublisherHelper(unsigned int cacheSize = 10);
        void registerSubdividedObserver(const std::weak_ptr<SubdividedMdibObserver>& observer);
        void unregisterSubdividedObserver(const std::weak_ptr<SubdividedMdibObserver>& observer);
        void registerObserver(const std::weak_ptr<MdibObserver>& observer);
        void unregisterObserver(const std::weak_ptr<MdibObserver>& observer);
        void queueStateChanges(const NotificationCall& subdividedNotify, const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes, DFL::Mdib::MdibChangeType changeType);
        void queueDescriptorChanges(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes);
        void executePendingChanges();

    private:
        DFL::Observer::BasicSubject<MdibObserver, std::mutex, DFL::Observer::Invoke> m_mdibSubject;
        DFL::Observer::BasicSubject<SubdividedMdibObserver, std::mutex, DFL::Observer::Invoke> m_subdividedMdibSubject;
        static std::vector<NotificationCall> buildNotificationCalls(const NotNull<ConstMdibChangeSetSharedPtr>& changes);
        void publishChanges(const std::vector<NotificationCall>& notificationCalls, const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes, DFL::Mdib::MdibChangeType changeType);
        void publishChanges(const NotificationCall& notificationCall, const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes, DFL::Mdib::MdibChangeType changeType) ;

        void notifyMdibObserver(const NotNull<MdibSharedPtr>& mdib,
                                const NotNull<ConstMdibChangeSetSharedPtr>& changes,
                                DFL::Mdib::MdibChangeType changeType);
        void notifyAndSendReport(boost::optional<NotificationCall> notificationCall,
                                 const NotNull<MdibSharedPtr>& mdib,
                                 const NotNull<ConstMdibChangeSetSharedPtr>& changes,
                                 DFL::Mdib::MdibChangeType changeType);

        PublisherCache m_publisherCache;
        mutable std::mutex m_lock;
        bool m_publishInProgress = false;
};

} /* namespace Impl */
} /* namespace Mdib */
} /* namespace DFL */
