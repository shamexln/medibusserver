#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>
#include <S31/Sdc/Private/Common/Messaging/QNameList.h>
#include <S31/S31CoreExImp.h>

namespace S31::Sdc::Impl::QNameConversion
{
/**
 * @brief Creates a @ref S31::Sdc::Impl::QNameList "QNameList" from a whitespace separated gSOAP QName list string.
 * @details The format of the gSOAP QName is described in the following example:
 *          With a QName prefixed by the dpws namespace, e.g. <code>dpws:Device</code>.
 *          The expanded gSOAP format without namespace prefix is as follows:
 *          <code>"http://docs.oasis-open.org/ws-dd/ns/dpws/2009/01":Device</code>.
 *          The namespace is quoted with double quotes followed by a colon and the local name.
 * @param soap handle containing namespace prefixes.
 * @param qNameListString whitespace separated string where each string is in the gSOAP QName format.
 * @return Strongly typed QNameList.
 * @ingroup S31SdcCommon
 */
S31_CORE_EXPIMP QNameList fromGSoapQNameList(
        const soap* soap,
        const std::string& qNameListString);

/**
 * @brief Creates a space separated string containing all @ref DFL::QName "QNames" from the input @ref QNameList.
 * @return string in the format of @ref DFL::QName "QNames" specified in QNameConversion::fromGSoapQName().
 * @ingroup S31SdcCommon
 */
S31_CORE_EXPIMP std::string toGSoapFormatString(const QNameList& qNameList);
}
