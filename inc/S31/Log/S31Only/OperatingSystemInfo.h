#pragma once

#include <string>

#include <S31/Log/Private/S31LogExImp.h>

namespace S31::Log::Impl
{

/*!
 * \brief Several OS dependent info functions.
 * \ingroup S31Log
 */
class S31_LOG_EXPIMP OperatingSystemInfo
{
    public:

        /**
          * Returns the current process id.
          *
          * @returns the current process id.
          */
        static unsigned long getProcessId();

        /**
         * Returns the current thread id.
         *
         * @returns the current thread id.
         */
        static unsigned long getThreadId();

        /**
          * Returns the current local time as simplified string (format: hh::mm::ss.mmm).
          *
          * @returns the current local time as simplified string (format: hh::mm::ss.mmm).
          */
        static std::string getSimpleLocalTime();

        /**
         * Returns the filename of a path.
         *
         * @returns the filename of a path.
         */
        static const char* basename(const char* path);

};

}
