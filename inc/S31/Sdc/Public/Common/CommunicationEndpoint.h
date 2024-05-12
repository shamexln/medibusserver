#pragma once

#include <S31/Sdc/Public/Common/SdcMessageObserver.h>
#include <S31/Utils/Public/ObservableSubject.h>

namespace S31::Sdc
{
/**
 * @brief Allows to access information regarding the communication endpoint for all devices and clients.
 * @ingroup S31SdcCommon
 */
class CommunicationEndpoint: public S31::Utils::ObservableSubject<SdcMessageObserver>
{
    public:
        ~CommunicationEndpoint() override = default;

        /**
         * @brief Register to observe SOAP XML messages.
         * @param observer The weak reference is stored internally (as weak, not strong ref)
         */
        void registerObserver(const std::weak_ptr<SdcMessageObserver>& observer) override = 0;

        /**
         * @brief Unregister to observe SOAP XML messages.
         */
        void unregisterObserver(const std::weak_ptr<SdcMessageObserver>& observer) override = 0;

};

}
