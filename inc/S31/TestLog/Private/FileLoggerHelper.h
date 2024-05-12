#pragma once

#include <Framework/Config/Public/Config.h>
#include <Framework/Log/Public/Message.h>

#include <cstdio>
#include <iostream>
#include <mutex>

namespace S31::Log::Impl
{

/**
 * @brief Specify if it shall be appended to log file only (no file clearing at beginning).
 * @ingroup S31Log
 */
enum class LogFileAppending
{
        AppendToFile, ///< Append to (existing) file.
        ClearFile ///< Clear file at start of logging.
};

#if defined(DFL_CONFIG_OS_WIN32)
/**
 * @brief Windows file commit flag (flush to disk).
 *
 * @details
 * Windows allows to set a commit flag to immediately write into the file.
 * "Enable the commit flag for the associated filename
 *  so that the contents of the file buffer are written directly to disk
 *  if either fflush or _flushall is called."
 * See: https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fopen-wfopen
 *
 * @ingroup S31Log
 */
enum class LogFileCommitMode
{
        Disabled, ///< No special functionality.
        Enabled ///< Flush to disk.
};
#endif

/**
 * @brief Common data structure for file logger.
 * @details Is used by different file logger, e.g. buffering file logger and "normal" file logger.
 * @ingroup S31Log
 */
class FileLoggerData
{
    public:
        FileLoggerData(const char* filenamePrefix, LogFileAppending logFileStatus);
#if defined(DFL_CONFIG_OS_WIN32)
        FileLoggerData(const char* filenamePrefix, LogFileAppending logFileStatus, LogFileCommitMode commitMode);
#endif
        ~FileLoggerData();

        FileLoggerData(const FileLoggerData&) = delete;
        FileLoggerData& operator=(const FileLoggerData&) = delete;
        FileLoggerData(FileLoggerData&&) = delete;
        FileLoggerData& operator=(FileLoggerData&&) = delete;

        std::mutex& mutex();
        std::FILE* file() const;
    private:
        std::mutex m_mutex;
        std::FILE* m_file = nullptr;
};


inline FileLoggerData::~FileLoggerData()
{
    if (m_file)
    {
        try
        {
            std::fclose(m_file); // NOLINT(cert-err33-c)
        }
        catch(...) {}
    }
}

inline std::mutex& FileLoggerData::mutex()
{
    return m_mutex;
}


inline std::FILE* FileLoggerData::file() const
{
    return m_file;
}

/**
 * @brief Creates a string from the log message structure that can be used as a line in a logfile.
 * @details
 * This is intended to be used for S31 log messages in tests and samples.
 * Example of a returned string:
 * > [2022-10-24T14:40:24.39048Z][26800][24540][Info][S31.Soap] Device: starting urn:uuid:73768c02-9749-4f90-88cf-4a78593fb15c~DpwsDevice.cpp:436
 */
std::string toLogFileLine(const DFL::Log::Message& message);

}
