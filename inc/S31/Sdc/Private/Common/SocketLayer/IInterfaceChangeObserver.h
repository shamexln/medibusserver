#pragma once

#include <S31/Sdc/Private/Common/SocketLayer/NetworkInterfaceUpdateList.h>

namespace S31::Sdc::Impl
{

/**
 * \brief Observer to notify on any network interface changes.
 *
 * \ingroup S31SdcCommonSocket
 */
class IInterfaceChangeObserver
{
    public:
        virtual ~IInterfaceChangeObserver() noexcept = default;
        virtual void onInterfaceChange(NetworkInterfaceUpdateList updateList) = 0;
};

}
