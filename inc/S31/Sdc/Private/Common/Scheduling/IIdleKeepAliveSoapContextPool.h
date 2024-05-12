#pragma once

#include <S31/Sdc/Private/Common/SoapPtr.h>

#include <boost/optional/optional.hpp>

#include <string>

namespace S31::Sdc::Impl
{

/**
 * @brief Interface for keep-alive pool.
 * @ingroup S31SdcCommonWebServices
 */
class IIdleKeepAliveSoapContextPool
{
    public:
        virtual ~IIdleKeepAliveSoapContextPool() = default;

        virtual boost::optional<SoapPtr> getIdleSoapContextForTransport(const std::string& transportAddress) = 0;
};

}
