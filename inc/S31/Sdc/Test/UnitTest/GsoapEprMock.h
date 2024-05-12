#pragma once

#include <S31/Sdc/Private/Common/MessageLayer/GsoapEpr.h>
#include <S31/Sdc/Private/Common/SoapPtr.h>
#include <S31/Sdc/Test/UnitTest/SoapTestUtils.h>

#include <Framework/Config/Public/Config.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapH.h>

namespace S31Test::Sdc::UnitTest
{
#ifdef DFL_CONFIG_COMPILER_GCC
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-variable"
// The objects in here are static, hence internally linked into each translation unit.
// Since not all translation units make use of every variable defined herein,
// gcc emits the unused-variable warning.
#endif

static constexpr const char* WsEventingNotifyTo_Default = R"(
<wse:NotifyTo
    xmlns:wsa='http://www.w3.org/2005/08/addressing'
    xmlns:wse='http://schemas.xmlsoap.org/ws/2004/08/eventing'>
  <wsa:Address>https://www.example.com/MyEventSink/OnStormWarning/urn:uuid:28ae9425-1d7a-434d-9d59-f95fcc125720</wsa:Address>
</wse:NotifyTo>
)";

static constexpr const char* WsEventingNotifyTo_WseIdentifier = R"(
<wse:NotifyTo
    xmlns:wsa='http://www.w3.org/2005/08/addressing'
    xmlns:wse='http://schemas.xmlsoap.org/ws/2004/08/eventing'>
  <wsa:Address>https://www.example.com/MyEventSink/OnStormWarning</wsa:Address>
  <wsa:ReferenceParameters>
    <wse:Identifier>urn:uuid:28ae9425-1d7a-434d-9d59-f95fcc125720</wse:Identifier>
  </wsa:ReferenceParameters>
</wse:NotifyTo>
)";

static constexpr const char* WsEventingNotifyTo_MultipleReferenceParameters = R"(
<wse:NotifyTo
    xmlns:wsa='http://www.w3.org/2005/08/addressing'
    xmlns:wse='http://schemas.xmlsoap.org/ws/2004/08/eventing'
    xmlns:myns1='http://www.example.com/namespace1'
    xmlns:myns2='http://www.example.com/namespace2'>
  <wsa:Address>https://www.example.com/MyEventSink/OnStormWarning</wsa:Address>
  <wsa:ReferenceParameters>
    <myns1:Parameter>ReferenceParameter1</myns1:Parameter>
    <myns2:Parameter>ReferenceParameter2</myns2:Parameter>
  </wsa:ReferenceParameters>
</wse:NotifyTo>
)";

static constexpr const char* WsEventingNotifyTo_EmptyReferenceParameters = R"(
<wse:NotifyTo
    xmlns:wsa='http://www.w3.org/2005/08/addressing'
    xmlns:wse='http://schemas.xmlsoap.org/ws/2004/08/eventing'>
  <wsa:Address>https://www.example.com/MyEventSink/OnStormWarning</wsa:Address>
  <wsa:ReferenceParameters>
  </wsa:ReferenceParameters>
</wse:NotifyTo>
)";

/// @todo The example below could use another reference parameter in the form of:
/// <_1:PrefixTest4>Yet another potential conflict for the WaveformStreamSerializer</_1:PrefixTest4>
/// with the _1 namespace defined in the wse:NotifyTo element. This will break the current serialization
/// logic, as gSOAP will add the IsReferenceParameter attribute to PrefixTest4 with the namespace "_1",
/// causing a namespace conflict.
static constexpr const char* WsEventingNotifyTo_ComplexExample = R"(
<wse:NotifyTo
    xmlns:wsa='http://www.w3.org/2005/08/addressing'
    xmlns:wsa5='http://www.examp2.com/'
    xmlns:wse='http://schemas.xmlsoap.org/ws/2004/08/eventing'
    xmlns:ew='http://www.example.com/warnings'
    xmlns:a='http://www.example.com/example_01'>
  <wsa:Address>https://www.example.com/MyEventSink/OnStormWarning</wsa:Address>
  <wsa:ReferenceParameters>
    <ew:MySubscription>
      <ew:MySub2>complex</ew:MySub2>
      <ew:MySub3 test="foo">unknown</ew:MySub3>
    </ew:MySubscription>
    <wse:Identifier>knownTypeId</wse:Identifier>
    <wsa5:PrefixTest>This might conflict with known prefix in typemap file</wsa5:PrefixTest>
    <wsa5:PrefixTest2>wsa5:MyQname</wsa5:PrefixTest2>
    <a:PrefixTest3>Another potential conflict, this time for the WaveformStreamSerializer</a:PrefixTest3>
  </wsa:ReferenceParameters>
</wse:NotifyTo>
)";

#ifdef DFL_CONFIG_COMPILER_GCC
# pragma GCC diagnostic pop
#endif

inline std::shared_ptr<wsa5__EndpointReferenceType> readEpr(const char* xmlString, struct soap* soapHandle)
{
    std::istringstream xml(xmlString);
    soapHandle->is = &xml;
    auto notifyTo  = std::make_shared<_wse4__NotifyTo>();
    notifyTo->soap = soapHandle;
    if (int errorCode = soap_read__wse4__NotifyTo(soapHandle, &*notifyTo))
    {
        DFL::Format::Stream msg;
        msg << "Reading EPR failed with gsoap error " << errorCode;
        throw std::runtime_error(msg.cStr());
    }
    return notifyTo;
}

inline S31::Sdc::Impl::GsoapEpr readGsoapEpr(const char* xmlString)
{
    auto soapPtr = createSoapPtr();
    return S31::Sdc::Impl::GsoapEpr(readEpr(xmlString, soapPtr.get().get()));
}

inline DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::GsoapEpr>> readSharedGsoapEpr(const char* xmlString)
{
    auto soapPtr = createSoapPtr();
    return DFL::asNotNull(std::make_shared<S31::Sdc::Impl::GsoapEpr>(readEpr(xmlString, soapPtr.get().get())));
}

inline DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::GsoapEpr>> dummySharedGsoapEpr()
{
    return readSharedGsoapEpr(WsEventingNotifyTo_EmptyReferenceParameters);
}

}
