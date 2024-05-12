#pragma once

#include <S31/UseCases/S31Only/utils/S31Service.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31
{
class ILocationHandler;

/**
 * @brief Is responsible to connect all location relevant classes with each other.
 *
 * These connected classes transfer location information between the network, %MDIB, and S31.X.
 *
 * \ingroup S31UseCases
 */
class S31_CORE_EXPIMP LocationService: public S31Service
{
    public:
        explicit LocationService(DFL::NotNull<std::shared_ptr<S31::ILocationHandler>> handler);

        void start() override;
        void stop() override;

        std::string getName() override;
    private:
        bool m_running{false};
        DFL::NotNull<std::shared_ptr<ILocationHandler>> m_locationHandler;
};

}
