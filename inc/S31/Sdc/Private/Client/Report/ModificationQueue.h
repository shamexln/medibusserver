#pragma once

#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibChangeType.h>
#include <Framework/Mdib/Public/Model/MdibVersion.h>
#include <Framework/Utils/Public/NotNull.h>

#include <boost/optional/optional.hpp>

#include <memory>

namespace S31::Sdc::Impl::Report
{

/**
 * @brief Queuing of state reports and description reports.
 *
 * @details
 * It just checks that the version number increases and that the sequence id stays the same. Otherwise an exception is raised.
 *
 * @note This class is not threadsafe.
 *
 * @ingroup S31SdcCommon
 */
class ModificationQueue
{
    public:
        explicit ModificationQueue();
        ~ModificationQueue();

        /// Add a modification report (state or descriptors) to the queue
        template <class Mod>
        void push(Mod&& modification);

        /// Returns a pointer to oldest element in the queue if there is one and if it is of the given type
        template <class Mod>
        Mod* oldest();

        /// Deletes the oldest element or does nothing if the queue is empty
        void deleteOldest();

        size_t size() const;
        bool empty() const;

    private:
        class Impl;
        DFL::NotNull<std::unique_ptr<Impl>> m_impl;

};


}
