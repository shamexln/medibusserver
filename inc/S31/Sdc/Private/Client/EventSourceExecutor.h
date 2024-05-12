#pragma once

#include <S31/Sdc/Private/Client/Endpoint/HostedServiceExecutor.h>
#include <S31/Sdc/Private/Client/Metadata/DeviceMetadata.h>
#include <S31/Sdc/Private/Client/Metadata/ServiceId.h>

#include <boost/optional/optional.hpp>
#include <map>

namespace S31::Sdc::Impl
{

/**
 * @brief Tests if given device metadata fulfills SDC Glue requirement R0034.
 * @details R0034: An SDC SERVICE PROVIDER SHALL implement at least the following BICEPS SERVICEs
 *          as one MDPWS HOSTED SERVICE if the SDC SERVICE PROVIDER exhibits the capabilities
 *          that require the BICEPS SERVICE:
 *
 *          - Description Event Service
 *          - State Event Service
 *          - Context Service
 *          - Waveform Service
 * @ingroup S31SdcClient
 */
class EventSourceExecutor
{
    public:
        /**
         * @brief Default constructor with no mapped executor.
         */
        EventSourceExecutor();

        /**
         * @brief Constructor that accepts metadata and executors.
         * @details Immediately resolves the event source executor in compliance with R0034 from SDC Glue.
         */
        EventSourceExecutor(const DeviceMetadata& metadata, const std::map<ServiceId, Endpoint::HostedServiceExecutor>& executors);

        /**
         * @brief Returns event source executor of hosted service or \c boost::none.
         * @details \c boost::none is returned in case that
         *
         *          - there are either no event sources provided or
         *          - event sources are scattered across different hosted services.
         */
        const boost::optional<Endpoint::HostedServiceExecutor>& get() const;

    private:
        boost::optional<Endpoint::HostedServiceExecutor> m_executor;
};

}
