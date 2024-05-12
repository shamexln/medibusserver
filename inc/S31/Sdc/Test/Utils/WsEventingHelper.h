#pragma once

#include <S31/Test/S31Only/StringHelper.h>

#include <string>
#include <string_view>

namespace S31::Sdc::Test
{

inline std::string unsubscribeMessage(std::string_view subManAddress)
{
    return R"(<s:Envelope xmlns:s="http://www.w3.org/2003/05/soap-envelope"
            xmlns:wsa5="http://www.w3.org/2005/08/addressing"
            xmlns:wse="http://schemas.xmlsoap.org/ws/2004/08/eventing">
  <s:Header><wsa5:To>)"
           + std::string{subManAddress} + R"(</wsa5:To>
    <wsa5:Action>http://schemas.xmlsoap.org/ws/2004/08/eventing/Unsubscribe</wsa5:Action>
    <wsa5:MessageID>urn:uuid:d7c5726b-de29-4313-b4d4-b3425b200834</wsa5:MessageID>
  </s:Header>
  <s:Body><wse:Unsubscribe /></s:Body>
</s:Envelope>)";
}

inline std::string_view extractSubscriptionManagerAddress(std::string_view message)
{
    const auto subscriptionManager =
            S31::Test::getTextBetweenPatterns(message, "<wse4:SubscriptionManager>", "</wse4:SubscriptionManager>");
    return S31::Test::getTextBetweenPatterns(subscriptionManager, "Address>", "<");
}
}  // namespace S31::Sdc::Test
