#pragma once

#include <S31/S31CoreExImp.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapStub.h>

namespace S31::Sdc::Impl
{

class Probe;

/**
 * Maps a probe request to a network message (\ref gSOAP structure).
 *
 * \ingroup S31SdcWsDiscovery
 */
class S31_CORE_EXPIMP ProbeMapper
{
    public:
        static std::shared_ptr<wsd11__ProbeType> mapProbeRequestToGsoapMessage(const Probe& request);
};

}
