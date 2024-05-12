#pragma once

#include <S31/Log/Private/S31LogExImp.h>

#include <Framework/Log/Public/EventCode.h>
#include <Framework/Utils/Public/Key.h>

#include <cstdio>
#include <mutex>
#include <string>

namespace S31::Log::Impl
{

/**
 * \brief Class to provide access to global log objects.
 *
 * \ingroup S31Log
 */
class S31_LOG_EXPIMP LogRegistry
{
    public:

        static const std::string& globalLoggerName();
        static const std::string& s31LoggerPrefix();

        static const DFL::Component::Key ComponentKey;
        static const DFL::Log::EventCode EventCode;

    private:

        static std::mutex s_accessLock;
        static bool s_initialized;
};

}
