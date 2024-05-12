#pragma once

#include <S31/Safety/Public/SerializableInformation.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapStub.h>

#include <Framework/Crypto/Public/Certificate.h>
#include <Framework/Crypto/Public/OpenSsl.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <string>

namespace S31::Sdc::Impl
{

/**
 * @brief Helper functions to extract certain information and return them in certain format.
 * @ingroup S31SdcCommon
 */
///@{
std::string peer(const struct soap* soap);
std::string distinguishedName(const struct soap* soap);
std::string operationHandle(const DFL::Mdib::Handle& handle);
std::string safetyInformation(const Safety::SerializableInformation& safetyInfo);
std::string payload(_msg__Activate* request);
std::string payload(_msg__SetString* request);
std::string payload(_msg__SetValue* request);
std::string payload(_msg__SetAlertState* request);
std::string payload(_msg__SetContextState* request);
std::string payload(_msg__SetComponentState* request);
std::string payload(_msg__SetMetricState* request);
std::string retrieveOperationType(_msg__Activate* /*request*/);
std::string retrieveOperationType(_msg__SetString* /*request*/);
std::string retrieveOperationType(_msg__SetValue* /*request*/);
std::string retrieveOperationType(_msg__SetAlertState* /*request*/);
std::string retrieveOperationType(_msg__SetContextState* /*request*/);
std::string retrieveOperationType(_msg__SetComponentState* /*request*/);
std::string retrieveOperationType(_msg__SetMetricState* /*request*/);
std::string action(const struct soap* soap);
std::string cipherSuite(const struct soap* soap);
std::string basicConstraints(const ::X509& cert);
std::string roles(const DFL::Oids& roles);
std::string printableCommonName(const ::X509& cert);
///@}

/**
 * @brief Clean unsecure text to ascii only, with a size limit.
 * @details This function is to remove possible junk from an string for logging,
 * where it is enough only to remove unwanted chars.
 * Characters outside the range 0x20 - 0x7E are replaced with '?'.
 * @ingroup S31SdcCommon
 */
std::string sizeLimitedAscii(const char* unsecureText, std::size_t sizeLimit);


}
