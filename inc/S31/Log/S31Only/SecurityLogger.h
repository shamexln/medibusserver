#pragma once

#include <S31/Log/Private/S31LogExImp.h>

#include <S31/Log/Public/KeyValue.h>
#include <S31/Log/Public/KeyValueIo.h>
#include <S31/Log/Public/SecurityEventCodes.h>

#include <Framework/Format/Public/StreamEach.h>
#include <Framework/Log/Public/SecurityState.h>

namespace S31::Log::Impl
{
void S31_LOG_EXPIMP writeSecurityBufferLogMessage(const char* file,
                                   int line,
                                   S31::Log::SecurityEventCodes eventCode,
                                   const char* buffer,
                                   DFL::Log::SecurityState securityState) noexcept;

void writeSecurityStreamLogMessage(const char* file, int line, DFL::Log::SecurityState securityState,
                                   S31::Log::SecurityEventCodes eventCode) noexcept;

void writeSecurityStreamLogMessage(const char* file, int line, DFL::Log::SecurityState securityState,
                                   S31::Log::SecurityEventCodes eventCode, KeyValue&& keyValue) noexcept;

void writeSecurityStreamLogMessage(const char* file, int line, DFL::Log::SecurityState securityState,
                                   S31::Log::SecurityEventCodes eventCode, std::initializer_list<KeyValue> keyValues) noexcept;

template<class ... Args>
void writeSecurityStreamLogMessage(const char* file, int line, DFL::Log::SecurityState securityState,
                                   S31::Log::SecurityEventCodes eventCode, KeyValue&& keyValue, Args&& ... args) noexcept;

template<class ... Args>
void writeSecurityStreamLogMessage(const char* file, int line, DFL::Log::SecurityState securityState,
                                   S31::Log::SecurityEventCodes eventCode, std::initializer_list<KeyValue> keyValues, Args&& ... args) noexcept;

template<class ... Args>
void writeSecurityStreamLogMessage(const char* file, int line, DFL::Log::SecurityState securityState,
                                   S31::Log::SecurityEventCodes eventCode, Args&& ... args) noexcept;


inline void writeSecurityStreamLogMessage(const char* file, int line, DFL::Log::SecurityState securityState,
                                          S31::Log::SecurityEventCodes eventCode) noexcept
{
    writeSecurityBufferLogMessage(file, line, eventCode, "", securityState);
}

inline void writeSecurityStreamLogMessage(const char* file, int line, DFL::Log::SecurityState securityState,
                                          S31::Log::SecurityEventCodes eventCode, KeyValue&& keyValue) noexcept
{
    writeSecurityStreamLogMessage(file, line, securityState, eventCode, {keyValue});
}

inline void writeSecurityStreamLogMessage(const char* file, int line, DFL::Log::SecurityState securityState,
                                          S31::Log::SecurityEventCodes eventCode, std::initializer_list<KeyValue> keyValues) noexcept
{
    try
    {
        DFL::Format::Stream stream;
        if (keyValues.size())
        {
            DFL::Format::streamEach(stream, keyValues.begin(), keyValues.end(), "[", "]", " ");
        }
        writeSecurityBufferLogMessage(file, line, eventCode, stream.cStr(), securityState);
    }
    catch (...)
    {
    }
}

inline void writeSecurityStreamLogMessage(const char* file, int line, DFL::Log::SecurityState securityState,
                                          S31::Log::SecurityEventCodes eventCode, const KeyValues& keyValues) noexcept
{
    try
    {
        DFL::Format::Stream stream;
        if (!keyValues.empty())
        {
            DFL::Format::streamEach(stream, keyValues.begin(), keyValues.end(), "[", "]", " ");
        }
        writeSecurityBufferLogMessage(file, line, eventCode, stream.cStr(), securityState);
    }
    catch (...)
    {
    }
}

template<class ... Args>
inline void writeSecurityStreamLogMessage(const char* file, int line, DFL::Log::SecurityState securityState,
                                          S31::Log::SecurityEventCodes eventCode, KeyValue&& keyValue, Args&& ... args) noexcept
{
    writeSecurityStreamLogMessage(file, line, securityState, eventCode, {keyValue}, std::forward<Args>(args)...);
}

template<class ... Args>
inline void writeSecurityStreamLogMessage(const char* file, int line, DFL::Log::SecurityState securityState,
                                          S31::Log::SecurityEventCodes eventCode, std::initializer_list<KeyValue> keyValues, Args&& ... args) noexcept
{
    try
    {
        DFL::Format::Stream stream;
        if (keyValues.size())
        {
            DFL::Format::streamEach(stream, keyValues.begin(), keyValues.end(), "[", "]", " ");
            stream << ' '; // space between key values and following free text
        }
        (stream << ... << args);
        writeSecurityBufferLogMessage(file, line, eventCode, stream.cStr(), securityState);
    }
    catch (...)
    {
    }
}

template<class ... Args>
inline void writeSecurityStreamLogMessage(const char* file, int line, DFL::Log::SecurityState securityState,
                                          S31::Log::SecurityEventCodes eventCode, const KeyValues& keyValues, Args&& ... args) noexcept
{
    try
    {
        DFL::Format::Stream stream;
        if (!keyValues.empty())
        {
            DFL::Format::streamEach(stream, keyValues.begin(), keyValues.end(), "[", "]", " ");
            stream << ' '; // space between key values and following free text
        }
        (stream << ... << args);
        writeSecurityBufferLogMessage(file, line, eventCode, stream.cStr(), securityState);
    }
    catch (...)
    {
    }
}

template<class ... Args>
inline void writeSecurityStreamLogMessage(const char* file, int line, DFL::Log::SecurityState securityState,
                                          S31::Log::SecurityEventCodes eventCode, Args&& ... args) noexcept
{
    try
    {
        // NOLINTNEXTLINE(misc-const-correctness)
        DFL::Format::Stream stream;
        (stream << ... << args);
        writeSecurityBufferLogMessage(file, line, eventCode, stream.cStr(), securityState);
    }
    catch (...)
    {
    }
}

}
