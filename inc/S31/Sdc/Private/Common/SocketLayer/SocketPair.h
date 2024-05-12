#pragma once

#include <S31/Gsoap/S31Only/stdsoap2.h>
#include <S31/S31CoreExImp.h>

#include <utility>

namespace S31::Sdc::Impl
{

class S31_CORE_EXPIMP SocketPair
{
public:
    static std::pair<SOAP_SOCKET, SOAP_SOCKET> createSocketPair();
};

}
