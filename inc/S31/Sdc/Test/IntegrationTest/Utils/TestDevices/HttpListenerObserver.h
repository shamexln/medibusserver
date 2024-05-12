#pragma once

namespace S31::Sdc::Impl::Test
{
class HttpListenerObserver
{
public:
    virtual ~HttpListenerObserver() = default;

    /**
     * The end of the stream was reached.
     * While waiting to read, the connection was closed by the client.
     */
    virtual void endOfStream() = 0;
};

}  // namespace S31::Sdc::Impl::Test
