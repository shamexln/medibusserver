#pragma once

#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Test/IntegrationTest/Utils/DiscoveryProxy/DeviceInformation.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapDiscoveryBindingService.h>

namespace S31::Sdc::Impl::Test
{

class DiscoveryParser: private DiscoveryBindingService
{
    DFL_NOT_COPYABLE(DiscoveryParser)
    public:
        struct Result
        {
            enum class Type
            {
                    None,
                    Hello,
                    Bye,
                    Probe,
                    ProbeMatch,
                    Resolve,
                    ResolveMatch
            };
            using MatchBy = std::string;

            Result() = default;
            Result(Type rt, DiscoveryInformationMap dim, MatchBy mb) :
                resultType(std::move(rt)),
                discoveryInformationMap(std::move(dim)),
                matchBy(std::move(mb))
            {};

            Type resultType{Type::None};
            DiscoveryInformationMap discoveryInformationMap{};
            MatchBy matchBy{""};
        };

        DiscoveryParser();

        int dispatch() override;
        int dispatch(struct soap* soapDispatch) override;

        const Result& lastResult() const;
        void resetLastResult();

    private:
        DiscoveryBindingService* copy() override;

        int HelloOp(wsd11__HelloType* msg) override;
        int ByeOp(wsd11__ByeType* msg) override;
        int ProbeOp(wsd11__ProbeType* msg) override;
        int ProbeMatchOp(wsd11__ProbeMatchesType* msg) override;
        int ResolveOp(wsd11__ResolveType* msg) override;
        int ResolveMatchOp(wsd11__ResolveMatchesType* msg) override;

        Result m_lastResult;
};

}
