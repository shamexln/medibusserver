#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>
#include <S31/S31CoreExImp.h>

#include <memory>

namespace S31::Sdc::Impl
{

/**
 * \ingroup S31SdcCommon
 */
S31_CORE_EXPIMP void returnSoapHandleToPool(struct soap* soapHandle);

/**
 * \ingroup S31SdcCommon
 */
S31_CORE_EXPIMP void deleteSoapPtr(struct soap* soapHandle);

/**
 * RAII class for \ref gSOAP's struct soap* handles.
 *
 * Internally it uses a pool of soap structs to avoid reconstruction (plug-in registration etc.).
 * A soap struct shall be used in one thread at a time.
 *
 * \ingroup S31SdcCommon
 */
using SoapPtr = std::unique_ptr<struct soap, decltype(&returnSoapHandleToPool)>;

/**
 * Function for creating a new \ref SoapPtr which upon destruction returns to the \ref SoapContextPool.
 *
 * \ingroup S31SdcCommon
 */
inline SoapPtr emptySoapPtr()
{
    return {nullptr, returnSoapHandleToPool};
}

/**
 * RAII class for \ref gSOAP's struct soap* handles without the use of pooling.
 *
 * \ingroup S31SdcCommon
 */
using SoapPtrWithoutPooling = std::unique_ptr<struct soap, decltype(&deleteSoapPtr)>;

/**
 * Function for creating a new \ref SoapPtrWithoutPooling which upon destruction cleans up the \ref gSOAP context.
 *
 * \ingroup S31SdcCommon
 */
S31_CORE_EXPIMP SoapPtrWithoutPooling newSoapPtr();

/**
 * Function for creating a new \ref SoapPtrWithoutPooling which upon destruction cleans up the \ref gSOAP context.
 *
 * \param mode The input and output mode set in the \ref gSOAP context
 *
 * \ingroup S31SdcCommon
 */
S31_CORE_EXPIMP SoapPtrWithoutPooling newSoapPtr(int mode);

/**
 * Function for creating a new \ref SoapPtrWithoutPooling which upon destruction cleans up the \ref gSOAP context.
 *
 * \param imode The input mode set in the \ref gSOAP context
 * \param omode The output mode set in the \ref gSOAP context
 *
 * \ingroup S31SdcCommon
 */
S31_CORE_EXPIMP SoapPtrWithoutPooling newSoapPtr(int imode, int omode);

}