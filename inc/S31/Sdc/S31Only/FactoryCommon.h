#pragma once

#include <S31/Sdc/Public/Common/CoreConfiguration.h>
#include <S31/Sdc/Private/Common/CommunicationEndpoint.h>
#include <S31/S31CoreExImp.h>

/**
 *  @file
 *  @brief Common functionality for initializing and configuration checking of (high-level) S31 factories.
 */

namespace S31::Sdc
{

/**
 * @brief Common checks that S31 factories should do in ctors.
 * @details
 * Found problems are logged and/or signaled through the error registry with
 * suiting RemoS codes. Some parameters may also be fixed (e.g. set valid compression level).
 */
S31_CORE_EXPIMP void factoryCheck(CoreConfiguration& configuration);

/**
 * @brief Common initialization for S31 factories.
 * @details
 * E.g. configure periodic jobs for check of own certificate.
 */
S31_CORE_EXPIMP void factoryInit(DFL::NotNull<std::shared_ptr<CoreConfiguration>> configuration, S31::Sdc::Impl::CommunicationEndpoint& communicationEndpoint);


}
