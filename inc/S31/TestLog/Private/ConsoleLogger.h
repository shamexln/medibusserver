#pragma once

#include <Framework/Log/Public/Message.h>

#include <mutex>

namespace S31::Log::Impl
{

/*!
 * \brief Provides functor that puts output to the console
 *
 * \ingroup S31Log
 */
class ConsoleLogger
{
    public:

        /**
         * Constructor of the console logger.
         */
        ConsoleLogger() = default;

        /**
         * Destructor of the console logger.
         */
        virtual ~ConsoleLogger() = default;

        /**
         * Functor for DFL logging
         *
         * @param message the message to be printed
         */
        DFL::Log::Message operator()(const DFL::Log::Message& message) const;

    private:

        static std::mutex s_consoleMutex;
};

}
