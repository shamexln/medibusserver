#pragma once

#include <S31/Sdc/Private/Client/DsoapClient/Jobs/GetMdibJob.h>
#include <S31/Sdc/Private/Common/SoapPtr.h>
#include <S31/Sdc/Test/IntegrationTest/Utils/BicepsTestTypes.h>

#include <Framework/Utils/Public/NotNull.h>

#include <boost/filesystem.hpp>

#include <istream>
#include <ostream>
#include <sstream>
#include <string>

namespace S31Test::Sdc
{

const char SoapToAddress[] = "http://www.w3.org/2005/08/addressing/anonymous";
const char SomeUrn[] = "http://SomeUrn";
const char SomeTargetAddress[] = "https://127.0.0.1:6464/somedevice/someservice";

std::stringstream readXmlFile(const boost::filesystem::path& file);

DFL::NotNull<S31::Sdc::Impl::SoapPtr> newSoapPtr(std::istream& inputStream,
                                                 std::ostream& outputStream,
                                                 SoapXmlFormat outputFormat = SoapXmlFormat::Indent);

DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::GetMdibJobResult>> executeGetMdibJob(std::istream& mdibResponseStream,
                                                                                  const SoapXmlFormat outputFormat = SoapXmlFormat::Indent);
DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::GetMdibJobResult>> executeGetMdibJob(const boost::filesystem::path& injectedResponse,
                                                                                  const SoapXmlFormat outputFormat=SoapXmlFormat::Indent);


}
