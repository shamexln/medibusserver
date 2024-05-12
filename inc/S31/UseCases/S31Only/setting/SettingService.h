#pragma once

#include <S31/UseCases/S31Only/utils/S31Service.h>

#include <memory>

namespace S31
{
class ISettingHandler;

/**
 * Main class for setting functionality.
 *
 * Takes care of transmitting setting data between network and local repository.
 *
 * \ingroup S31UseCases
 */
class SettingService: public S31Service
{
    public:
        explicit SettingService(std::shared_ptr<ISettingHandler> handler);
        ~SettingService() override;

        void start() override;
        void stop() override;

        std::string getName() override;
    private:
        std::shared_ptr<ISettingHandler> m_handler;
};

} /* namespace S31 */
