#pragma once

#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibObserver.h>
#include <Framework/Mdib/Public/SubdividedMdibObserver.h>
#include <Framework/Mdib/Private/Log.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>

#include <boost/optional.hpp>

#include <condition_variable>
#include <functional>
#include <queue>
#include <mutex>
#include <utility>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

using NotificationCall = std::function<void(SubdividedMdibObserver&, const NotNull<MdibSharedPtr>&, const NotNull<ConstMdibChangeSetSharedPtr>&)>;

struct PublisherCacheData
{
        DFL::NotNull<DFL::Mdib::MdibSharedPtr> mdib;
        DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr> changes;
        DFL::Mdib::MdibChangeType changeType;
        boost::optional<NotificationCall> notificationCallback;

        PublisherCacheData(DFL::NotNull<DFL::Mdib::MdibSharedPtr> mdibPtr,
                           DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr> mdibChanges,
                           DFL::Mdib::MdibChangeType changeType,
                           boost::optional<NotificationCall> notificationCallbck);
};

inline PublisherCacheData::PublisherCacheData(DFL::NotNull<DFL::Mdib::MdibSharedPtr> mdibPtr,
                                              DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr> mdibChanges,
                                              DFL::Mdib::MdibChangeType changeType,
                                              boost::optional<NotificationCall> notificationCallbck) :
        mdib(std::move(mdibPtr)),
        changes(std::move(mdibChanges)),
        changeType(changeType),
        notificationCallback(std::move(notificationCallbck))
{
}
/*!
 * \brief Implements a blocking cache in order to store and retrieve data of the type \ref PublisherCacheData
 *
 * \ingroup Mdib
 *
 * \details std::map is used to queue the \ref PublisherCacheData
 * When a write description or state operation is invoked, std::map stores \ref VersionCounter as the key and \ref PublisherCacheData as the data.
 * After it is popped out of the std::map, the function callbacks are constructed and observers are notified.
 * If the queue is full, then the PublisherCache waits until a data is removed from the map.
 */
class PublisherCache
{
    public:
        PublisherCache(unsigned int maxQueueSize = UINT_MAX) :
                m_publisherCache(),
                m_maxQueueSize(maxQueueSize)
        {
        }

        /**
         * \brief Add an element to the queue, if the queue is full then wait until an empty slot
         * is created
         *
         * \param data The element to push onto the queue.
         */
        void waitAndPush(PublisherCacheData&& data)
        {
            std::unique_lock<std::mutex> lock(m_queueLock);

            if (m_publisherCache.size() >= m_maxQueueSize)
            {
                DFL_MDIB_STREAM_WARNING("[DFL.Mdib] PublisherCache maxQueueSize reached (", m_maxQueueSize, ").");

                m_queueCondition.wait(lock, [&] {
                    return m_publisherCache.size() < m_maxQueueSize;
                });
            }

            m_publisherCache.push(std::move(data));
        }

        /**
         * \brief Remove an element from the queue and notify that an element has been removed
         *
         * \param mdibVersion The mdibVersion that has to be removed.
         * \return boost::optional<PublisherCacheData> If the requested version exists in the queue then return it and remove it
         * from the queue, else return boost::none.
         */
        boost::optional<PublisherCacheData> popElement()
        {
            boost::optional<PublisherCacheData> result;
            {
                std::lock_guard<std::mutex> const lock(m_queueLock);
                if (m_publisherCache.empty())
                {
                    return boost::none;
                }
                result = std::move(m_publisherCache.front());
                m_publisherCache.pop();
            }
            m_queueCondition.notify_one();
            return result;
        }

    private:
        std::queue<PublisherCacheData> m_publisherCache;
        mutable std::mutex m_queueLock;
        mutable std::condition_variable m_queueCondition;
        unsigned int m_maxQueueSize;
};

}
}
}
