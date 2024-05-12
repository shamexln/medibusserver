#pragma once

#include <Framework/Net/Public/Adapter/Infos.h>

#include <boost/optional/optional.hpp>

#include <utility>
#include <vector>

namespace S31::Sdc::Impl
{

/**
 * @brief Data of one changed network interface.
 * @details Contains the data @c before and @c after a detected network interface change.
 * @ingroup S31SdcCommonSocket
 */
struct NetworkInterfaceUpdate
{
    /**
     * @brief Previous state.
     * @details
     * Is \c boost::none in case fo a new adapter.
     */
    boost::optional<DFL::Net::Adapter::Info> before;

    /**
     * @brief new state.
     * @details
     * Is \c boost::none in case the adapter is removed.
     */
    boost::optional<DFL::Net::Adapter::Info> after;
};

/**
 * @brief
 * A container of @ref NetworkInterfaceUpdate
 *
 * @ingroup S31SdcCommonSocket
 */
using NetworkInterfaceUpdateList = std::vector<NetworkInterfaceUpdate>;

}
