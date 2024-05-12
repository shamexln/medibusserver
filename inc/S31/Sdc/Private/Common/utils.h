#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>
#include <S31/Sdc/Private/Common/SoapPtr.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/Uri.h>

#include <string>

namespace S31::Sdc::Impl
{

S31_CORE_EXPIMP bool isUdpSocket(const SoapPtrWithoutPooling& soapHandle);
S31_CORE_EXPIMP bool isUdpSocket(const struct soap* soapHandle);
S31_CORE_EXPIMP bool isUdpSocket(const DFL::NotNull<struct soap*>& soapHandle);

S31_CORE_EXPIMP std::string createHttpUri(const std::string& ipAddr, unsigned short port);

S31_CORE_EXPIMP std::string createHttpsUri(const std::string& ipAddr, unsigned short port);

S31_CORE_EXPIMP boost::optional<DFL::Net::Uri> createSoapOverUdpUri(const std::string& ipAddr, unsigned short port);

}
