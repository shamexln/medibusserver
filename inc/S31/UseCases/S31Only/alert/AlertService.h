#pragma once

#include <S31/UseCases/S31Only/utils/S31Service.h>

#include <atomic>
#include <memory>

namespace S31
{

class IAlertHandler;

namespace Sdc
{
class RemoteDevice;
class RemoteDevicesSubject;
}

/*!
 * \brief Service for alert functionality.
 *
 * \ingroup S31UseCases
 */
class AlertService: public S31Service
{
    public:
        explicit AlertService(std::shared_ptr<IAlertHandler> handler);
        ~AlertService() override;

        /// \copydoc S31Service::start()
        void start() override;

        /// \copydoc S31Service::stop()
        void stop() override;

        /// \copydoc S31Service::getName()
        std::string getName() override;

    private:
        std::shared_ptr<IAlertHandler> m_alertHandler;
        std::atomic_bool m_isRunning;
};

} /* namespace S31 */
