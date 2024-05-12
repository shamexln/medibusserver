#pragma once

#include <S31/Log/Public/Logger.h>

#include <deque>
#include <functional>
#include <string>

namespace S31::Sdc::Test
{

static std::size_t fakeFrecv(struct soap* soapHandle, char* destinationBuffer, std::size_t destinationBufferLen);


class GsoapDataSource
{
    public:
        explicit GsoapDataSource(struct soap* handle);
        ~GsoapDataSource();

        void data(const std::string& httpMessage);

        void maxReadSize(std::size_t maxRead);
        std::size_t maxReadSize() const;

        std::size_t frecv(struct soap* soapHandle, char* destinationBuffer, std::size_t destinationBufferLen);

    private:
        size_t (*m_originalFrecv)(struct soap* soapHandle, char* destinationBuffer, size_t destinationBufferLen);
        struct soap* m_soapHandle;
        std::size_t m_maxReadSize = 0; // no default max read size
        std::deque<std::string> m_data;
};

inline GsoapDataSource::GsoapDataSource(struct soap* handle):
        m_originalFrecv(handle->frecv),
        m_soapHandle(handle)
{
    if (m_soapHandle->data[3])
    {
        throw std::runtime_error("soap->data[3] already used by someone else");
    }
    m_soapHandle->data[3] = this;
    m_soapHandle->frecv = fakeFrecv;
}

inline GsoapDataSource::~GsoapDataSource()
{
    m_soapHandle->frecv = m_originalFrecv;
    m_soapHandle->data[3] = nullptr;
}

inline void GsoapDataSource::maxReadSize(std::size_t maxRead)
{
    m_maxReadSize = maxRead;
}

inline std::size_t GsoapDataSource::maxReadSize() const
{
    return m_maxReadSize;
}

inline void GsoapDataSource::data(const std::string& httpMessage)
{
    m_data.push_back(httpMessage);
}

inline std::size_t GsoapDataSource::frecv(struct soap* soapHandle, char* destinationBuffer, std::size_t destinationBufferLen)
{
    S31_STREAM_INFO_LOGGER("Test", "frecv: soap->buf: ", S31::Log::ptrToString(soapHandle->buf),
                           ", buffer: ", S31::Log::ptrToString(destinationBuffer),
                           ", len: ", destinationBufferLen);

    if (soapHandle != m_soapHandle)
    {
        S31_STREAM_ERROR_LOGGER("Test", "frecv: different soap handle injected, abort");
        return 0;
    }
    if (m_data.empty())
    {
        S31_STREAM_INFO_LOGGER("Test", "frecv: EOF, no more data");
        return 0;
    }
    size_t srcLength = m_data.front().size();

    if (m_maxReadSize > 0 && destinationBufferLen > m_maxReadSize)
    {
        // limit amount of data to read
        destinationBufferLen = m_maxReadSize;
    }

    if (srcLength > destinationBufferLen)
    {
        // split src buffer
        auto first = m_data.front().substr(0, destinationBufferLen);
        auto second = m_data.front().substr(destinationBufferLen);
        m_data.pop_front();
        m_data.push_front(std::move(second));
        m_data.push_front(std::move(first));
    }

    const auto len = m_data.front().size();
    soap_memcpy(static_cast<void*>(destinationBuffer), destinationBufferLen, m_data.front().c_str(), len);
    m_data.pop_front();
    S31_STREAM_INFO_LOGGER("Test", "frecv: provided ", len, " byte data");
    return len;
}

static inline std::size_t fakeFrecv(struct soap* soapHandle, char* destinationBuffer, std::size_t destinationBufferLen)
{
    if (!soapHandle->data[3])
    {
        S31_STREAM_ERROR_LOGGER("Test", "frecv: failed to get data from soap context");
        return 0;
    }
    auto* dataSource = reinterpret_cast<GsoapDataSource*>(soapHandle->data[3]);
    return dataSource->frecv(soapHandle, destinationBuffer, destinationBufferLen);
}

}
