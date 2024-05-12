#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibChangeType.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::Sdc
{

class RemoteDevice;

/**
 * @brief Observer to listen to %MDIB changes plus a source where the changes occur.
 * @ingroup S31SdcClient
 */
class S31_CORE_EXPIMP RemoteDeviceMdibObserver
{
    public:
        virtual ~RemoteDeviceMdibObserver() = default;

        /**
         * @brief Change callback.
         * @param source The remote device where the change in the %MDIB occurred.
         * @param mdib MDIB containing the changes.
         * @param changes The changeset.
         * @param changeType Whether the provided changes comprise descriptor changes (potentially both descriptor and state changes) or state changes only.
         */
        virtual void onChange(const std::shared_ptr<Sdc::RemoteDevice>& source,
                              const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib,
                              const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes,
                              DFL::Mdib::MdibChangeType changeType) = 0;
};

}
