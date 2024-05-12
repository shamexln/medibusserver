#pragma once

#include <Framework/Log/Public/Message.h>
#include <Framework/Utils/Public/NotNull.h>

namespace S31::Log::Impl
{
class FileLoggerData;

/*!
 * \brief Functor that puts logging output to a file.
 * \details
 * The "configuration" data is stored as shared member to allow copying of the logger
 * into a logger queue. It automatically keeps track of the opened file.
 *
 * \ingroup S31Log
 */
class FileLogger
{
    public:
        explicit FileLogger(DFL::NotNull<std::shared_ptr<FileLoggerData>> fileLoggerData);

        /**
         * @brief Functor for DFL logging
         *
         * @param message the message to be printed
         */
        const DFL::Log::Message& operator()(const DFL::Log::Message& message) const;

    private:
        DFL::NotNull<std::shared_ptr<FileLoggerData>> m_fileLoggerData;
};

}
