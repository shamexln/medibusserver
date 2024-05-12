#pragma once

#include <Framework/Log/Public/Message.h>

#include <boost/function/function1.hpp>

namespace DFL
{
    namespace Log
    {
        namespace Impl
        {
            using Logger = boost::function<Message(Message const&)>;
        }
    }
}
