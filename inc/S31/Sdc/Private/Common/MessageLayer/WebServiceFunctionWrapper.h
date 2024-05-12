#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>
#include <S31/Sdc/Private/Common/IWebService.h>

#include <functional>

namespace S31::Sdc::Impl
{
class WebServiceFunctionWrapper : public IWebService
{
public:
    using FuncType = std::function<int(struct soap*)>;

    explicit WebServiceFunctionWrapper(FuncType function)
        : m_function{std::move(function)}
    {
    }

    int dispatch(struct soap* soapHandle) override
    {
        return m_function(soapHandle);
    }

private:
    FuncType m_function;
};

}  // namespace S31::Sdc::Impl
