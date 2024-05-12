#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>
#include <S31/S31CoreExImp.h>

#include <cstddef>

namespace S31::Sdc::Impl::OutboundSizeCheck
{

/**
 * @brief Check that the response is not larger than 4MB.
 * @details See 11073-20701-2018:R0067. To be used as callback given to Gsoap.
 */
int S31_CORE_EXPIMP check(struct soap* soapHandle, const char* buf, std::size_t len);

}
