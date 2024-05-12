#pragma once

#include <string>

namespace S31
{

/**
 * @brief Define abstract interface for %S31 services to start by the application.
 *
 * \ingroup S31Utils
 */
class S31Service
{
    public:
        virtual ~S31Service() = default;

        /**
         * @brief Starts the service.
         *
         * @details After that the service should work normally.
         */
        virtual void start() = 0;

        /**
         * @brief Stops the service.
         *
         * @details After that the service should no longer process data. It should be safe to destroy the
         * object.
         */
        virtual void stop() = 0;

        /**
         * @brief Returns a self describing string (used for logging only).
         */
        virtual std::string getName()
        {
            return "(service name n/a)";
        }
};

}
