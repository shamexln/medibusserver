#pragma once

#include <Framework/Mdib/Public/LatestMdib.h>
#include <Framework/Mdib/Public/MdibAccessSmartPtrTypes.h>

namespace DFL::Mdib
{
class SubdividedMdibObserver;
class MdibObserver;

/**
 * @brief Provides read access to the latest version of an MDIB.
 * @ingroup Mdib
 */
class MdibAccess : public LatestMdib
{
    public:
        /**
         * @brief Add observer for MDIB changes with change type info (descriptor or state).
         */
        virtual void registerObserver(const std::weak_ptr<MdibObserver>& observer) = 0;

        /**
         * @brief Remove observer.
         */
        virtual void unregisterObserver(const std::weak_ptr<MdibObserver>& observer) = 0;

        /**
         * @brief Add observer for subdivided notifications.
         * @details \attention Only use this observer if you know the details of \ref DFL::Mdib::SubdividedMdibObserver.
         */
        virtual void registerSubdividedObserver(const std::weak_ptr<SubdividedMdibObserver>& observer) = 0;

        /**
         * @brief Remove observer for subdivided notifications.
         */
        virtual void unregisterSubdividedObserver(const std::weak_ptr<SubdividedMdibObserver>& observer) = 0;
};

}
