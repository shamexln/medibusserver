#pragma once

#include <memory>
#include <string>

namespace S31::Sdc::Impl
{
class HttpClientSession;

class HttpClientIdleKeepAlivePool
{
public:
    virtual ~HttpClientIdleKeepAlivePool() = default;

    virtual void sessionRequestCompleted(const std::string& serverAddress, std::shared_ptr<HttpClientSession>) = 0;
};

}