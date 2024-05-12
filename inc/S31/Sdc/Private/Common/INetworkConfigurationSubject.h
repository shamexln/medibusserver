#pragma once

#include <S31/Sdc/Private/Common/INetworkConfigurationObserver.h>
#include <S31/Utils/Public/ObservableSubject.h>

#include <memory>

namespace S31::Sdc::Impl
{
class INetworkConfigurationObserver;
class INetworkMediaObserver;

/**
 * \brief Allow to observer network configuration changes.
 *
 * \ingroup S31SdcCommon
 */
class INetworkConfigurationSubject : public Utils::ObservableSubject<INetworkConfigurationObserver>
{
    public:
        ~INetworkConfigurationSubject() override = default;

        /**
         * @brief Provides information about media state.
         */
        virtual void addMediaObserver(const std::weak_ptr<INetworkMediaObserver>& observer) = 0;

        /**
         * @brief Provides information about media state.
         * @details The initial state is reported in registration call.
         */
        virtual void addMediaObserverWithInitialCallback(const std::shared_ptr<INetworkMediaObserver>& observer) = 0;
};

}
