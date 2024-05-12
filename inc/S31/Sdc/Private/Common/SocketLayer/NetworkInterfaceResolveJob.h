#pragma once

#include <S31/Sdc/Private/Common/SocketLayer/NetworkInterfaceRegistry.h>
#include <S31/Sdc/Private/Common/SocketLayer/NetworkInterfaceUpdateList.h>
#include <S31/Sdc/Public/Common/Job.h>
#include <S31/Utils/Public/Outcome.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Result of @ref NetworkInterfaceResolveJob.
 * @ingroup S31SdcCommonSocket
 */
struct NetworkInterfaceResolveJobResult
{
    NetworkInterfaceUpdateList updates;
};

/**
 * \brief Job that is scheduled to periodically retrieve network interfaces from system.
 * \details
 * Calls itself as a delayed job to create periodicity.
 * \ingroup S31SdcCommonSocket
 */
class NetworkInterfaceResolveJob: public Job, protected Utils::OutcomeProvider<NetworkInterfaceResolveJobResult>
{
    public:
        /**
         * Constructor with dependencies.
         * @param handler The outcome handler.
         * @param ifRegistry Registry to retrieve changed interfaces.
         */
        NetworkInterfaceResolveJob(const OutcomeHandlerPtr& handler,
                                   const std::shared_ptr<NetworkInterfaceRegistry>& ifRegistry);

        void execute() override;
        std::string jobName() const override;

    private:
        std::weak_ptr<NetworkInterfaceRegistry> m_ifRegistry;
};

}
