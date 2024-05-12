#pragma once

#include <S31/Log/Private/S31LogExImp.h>

#include <Framework/Log/Public/Logger.h>
#include <Framework/Log/Public/Severity.h>

namespace S31::Log::Impl
{

/*!
 * \brief Handle service log entries
 *
 * \details If S32 support the target then this class can be just used. Otherwise a target specific logger
 * is needed in addition.
 *
 * This class uses the \ref ComponentLogger. Every log message is written into the service log and the
 * component log.
 *
 * \ingroup S31Log
 */
class S31_LOG_EXPIMP ServiceLogger
{
    public:
        /**
         * @brief Writes the log message to the service log.
         *
         * Similar to writeBufferMessage(). This function signature is needed by the
         * stream logging macros
         *
         * \see StreamLogger.h
         */
        static void writeBufferMessage(const DFL::Log::Severity& level,
                                       const char* file,
                                       int line,
                                       unsigned int remosCode,
                                       const char* buffer);
    private:
        /**
         * @brief Writes the log message to the service log.
         */
        static void writeBufferMessage(unsigned int remosCode,
                                    const DFL::Log::Severity& level,
                                    const char* file,
                                    int line,
                                    const char* buffer);
};

}
