#pragma once

#include <Framework/Log/Private/Logger.h>

#include <deque>

namespace DFL
{
    namespace Log
    {
        class Message;

        namespace Impl
        {
            using Loggers = std::deque<Logger>;

            Message callLogger(Message const& msg, Logger const& logger);
            Message process(Message const& msg, Loggers const& loggers);
        }
    }
}
