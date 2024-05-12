#pragma once

#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::Sdc::Impl
{
class HttpServerSession;

class HttpServerSessionPool
{
public:
    virtual ~HttpServerSessionPool() = default;

    virtual void onSessionClosed(const DFL::NotNull<std::shared_ptr<HttpServerSession>>&) = 0;
};
}
