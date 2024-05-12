#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibChangeType.h>
#include <Framework/Utils/Public/EnumClass.h>
#include <Framework/Utils/Public/NotNull.h>

namespace DFL
{
namespace Mdib
{

class Mdib;
class MdibChangeSet;

/**
 * @brief Interface to register for \ref MdibChangeSet "MDIB changes" of \ref MdibAccess subject.
 * @details Use this interface to get notified on every change to an MDIB along with the type of change that was made.
 * @ingroup Mdib
 */
class MdibObserver
{
    public:
        virtual ~MdibObserver() noexcept = default;

        /**
         * @brief Callback for every change.
         *
         * May throw due to memory allocation errors.
         *
         * @param mdib Whole MDIB on where the changes have been applied.
         * @param changes Change set that comprises changed entities only.
         * @param changeType Whether the provided changes comprise descriptor changes (potentially both descriptor and state changes) or state changes only.
         */
        virtual void onChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes, DFL::Mdib::MdibChangeType changeType) = 0;
};

}
}
