#pragma once

#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/Model/Metric/NumericMetric.h>
#include <Framework/Utils/Public/NotNull.h>

#include <atomic>
#include <thread>

#define THROW_ON_MDIB_WRITE_FAILED(writeOperation)                                                                \
    do                                                                                                          \
    {                                                                                                           \
        const DFL::Mdib::WriteResult& resultFromWriteOperation = writeOperation;                                \
        if (resultFromWriteOperation.status() != DFL::Mdib::WriteStatus::Success)                               \
        {                                                                                                       \
            DFL::Format::Stream exceptionMsg;                                                                   \
            exceptionMsg << "Updating MDIB failed with: " << resultFromWriteOperation << "~" << __FILE__ << ":" \
                         << __LINE__;                                                                           \
            throw std::runtime_error(exceptionMsg.cStr());                                                      \
        }                                                                                                       \
    } while (0)


namespace S31::Samples
{
class ContinuousBase
{
public:
    ContinuousBase(DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr>& localMdibAccess)
        : m_localMdibAccess{localMdibAccess} {};

    virtual ~ContinuousBase()
    {
        if (m_running)
        {
            stop();
        }
    }

    virtual void
    initMdib(DFL::Mdib::MdibChangeSet& changeSet, DFL::NotNull<std::shared_ptr<DFL::Mdib::Vmd>> vmd, DFL::NotNull<std::shared_ptr<DFL::Mdib::Channel>> channel) const = 0;

    virtual void start()
    {
        m_running            = true;
        m_metricUpdateThread = std::thread([this] { metricUpdateThread(); });
    }

    virtual void stop()
    {
        m_running = false;
        if (m_metricUpdateThread.joinable())
        {
            m_metricUpdateThread.join();
        }
    }

protected:
    virtual void metricUpdateThread() = 0;

    DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr>& m_localMdibAccess;

    std::atomic_bool m_running{false};
    std::thread      m_metricUpdateThread;
};
class CursorHelper
{
public:
    CursorHelper(int lineOffset)
    {
        std::stringstream cursor_ansi_sequence;
        // ansi sequence for 'move cursor n lines up' and carriage return
        cursor_ansi_sequence << "\x1b[" << lineOffset << "A\r";
        curUpStr = cursor_ansi_sequence.str();

        // carriage return and n lines down
        curDownStr.reserve(static_cast<size_t>(lineOffset + 2));
        curDownStr = "\r";
        for (int i = 0; i < lineOffset; i++)
        {
            curDownStr += "\n";
        }
    }
    const char* down()
    {
        return curDownStr.c_str();
    }
    const char* up()
    {
        return curUpStr.c_str();
    }

private:
    std::string curDownStr;
    std::string curUpStr;
};
}  // namespace S31::Samples
