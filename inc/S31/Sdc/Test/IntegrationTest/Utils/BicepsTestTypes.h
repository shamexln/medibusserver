#pragma once

#include <Framework/Utils/Public/EnumClass.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <string>

namespace S31Test::Sdc
{

using ExpectedResponseFilename = DFL::StrongTypedef<std::string, struct ExpectedResponseFilenameTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;
using RequestFilename = DFL::StrongTypedef<std::string, struct RequestFilenameTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;
using ReportFilename = DFL::StrongTypedef<std::string, struct ReportFilenameTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;
using ExpectedReportFilename = DFL::StrongTypedef<std::string, struct ExpectedReportFilenameTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;
using InputMdibFilename = DFL::StrongTypedef<std::string, struct InputMdibFilenameTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;
using InjectedResponseFilename = DFL::StrongTypedef<std::string, struct InjectedResponseFilenameTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;
using InjectedResponse = DFL::StrongTypedef<std::string, struct InjectedResponseTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;
using InjectedGetMdStateResponseFilename = DFL::StrongTypedef<std::string, struct InjectedGetMdStateResponseFilenameTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;
using GetMdStateRequestFilename = DFL::StrongTypedef<std::string, struct GetMdStateRequestFilenameTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;
using ExpectedGetMdStateResponseFilename = DFL::StrongTypedef<std::string, struct ExpectedGetMdStateResponseFilenameTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;
using ExpectedFaultSubString = DFL::StrongTypedef<std::string, struct ExpectedFaultSubStringTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

/**
 * @brief Enum Represents the serialization format of the XML
 */
enum class SoapXmlFormat
{
        NoFormatting,
        Indent
};
DFL_ENUM_CLASS_STREAM_OPERATOR(SoapXmlFormat, (NoFormatting)(Indent))

}

