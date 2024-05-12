#pragma once

#include <S31/S31CoreExImp.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapStub.h>

#include <memory>
#include <string>
#include <string_view>

namespace S31::Sdc::Impl
{

/**
 * \brief Container for a WS-Addressing EndpointReference in \ref gSOAP.
 * \details
 * It will be used for WS-Eventing on client and device side to handle the reference parameters.
 *
 * \ingroup S31SdcCommonWebServices
 */
class S31_CORE_EXPIMP GsoapEpr
{
    public:
        explicit GsoapEpr(std::string_view address);
        explicit GsoapEpr(std::shared_ptr<wsa5__EndpointReferenceType> eprType);

        std::string getAddress() const;
        const char* address() const noexcept;

        const wsa5__ReferenceParametersType* getReferenceParameters() const noexcept;
        const std::string& addressAuthority() const noexcept;
        const std::string& referenceParametersXmlSnippet() const noexcept;

    private:
        std::shared_ptr<wsa5__EndpointReferenceType> m_epr;
        std::string m_addressAuthority;
        std::string m_referenceParametersXmlSnippet;
};

}
