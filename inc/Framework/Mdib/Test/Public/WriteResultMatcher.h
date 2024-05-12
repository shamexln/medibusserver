#pragma once

#include <Framework/Mdib/Public/WriteResultIo.h>
#include <Framework/Utils/Public/StdContainerIo.h>

#include <gmock/gmock.h>

namespace DFL::Mdib::Test
{

/**
 * @brief GMock Matcher to match against @ref DFL::Mdib::WriteResult.
 * @details In case the expected WriteStatus is @ref DFL::Mdib::WriteStatus::CheckPluginError,
 *          the error message is matched against the second parameter which is a container of strings.
 *          All strings in that container are expected to appear within the error message, otherwise
 *          the matcher fails.
 *
 * @tparam expectedWriteResultStatus_type @ref DFL::Mdib::WriteStatus that is expected
 * @tparam expectedErrorSubstrings_type Container of expected sub-strings
 */

MATCHER_P2(MatchesWriteResult,
           expectedWriteResultStatus,
           expectedErrorSubstrings,
           [&]()
           {
               std::stringstream ss;
               ss << expectedWriteResultStatus << ": ErrorSubstrings '" << expectedErrorSubstrings << "'";
               return ss.str();
           }())
{
    *result_listener << "";

    if (arg.status() != expectedWriteResultStatus)
    {
        return false;
    }
    if (expectedWriteResultStatus == WriteStatus::CheckPluginError)
    {
        return std::find_if(expectedErrorSubstrings.begin(),
                            expectedErrorSubstrings.end(),
                            [&](const std::string& expectedErrorSubstring)
                            {
                                return arg.error().value().find(expectedErrorSubstring) == std::string::npos;
                            }) == expectedErrorSubstrings.end();
    }
    return true;
}

}