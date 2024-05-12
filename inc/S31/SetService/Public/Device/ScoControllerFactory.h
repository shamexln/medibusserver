#pragma once

#include <S31/SetService/Public/Device/ScoController.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/NotNull.h>

namespace S31::SetService
{

/**
 * @brief Factory to create \ref ScoController instances.
 * @ingroup S31SetServiceDevice
 */
class S31_CORE_EXPIMP ScoControllerFactory
{
    public:
        /**
         * @brief Creates an \ref ScoController instance based on the given dependencies.
         * @param timerFactory Factory top create timer for timeout handling.
         * @param mdibAccess Is used to find typed operations and check the operating modes.
         * @param deviceTransactionFactory Factory to create device transaction contexts.
         */
        static DFL::NotNull<std::unique_ptr<ScoController>>
        create(const DFL::NotNull<std::shared_ptr<Utils::TimerFactory>>&      timerFactory,
               const DFL::NotNull<DFL::Mdib::MdibAccessSharedPtr>&            mdibAccess,
               const DFL::NotNull<std::shared_ptr<DeviceTransactionFactory>>& deviceTransactionFactory);
};
}
