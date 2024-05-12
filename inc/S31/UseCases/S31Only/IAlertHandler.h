#pragma once

#include <S31/S31CoreExImp.h>

namespace S31
{

/*!
 * \brief Interface to access alert specific methods in S31.X.
 *
 * \ingroup S31UseCases
 */
class S31_CORE_EXPIMP IAlertHandler
{
    public:
        virtual ~IAlertHandler() noexcept = default;

        /**
         * Starts the alert handler.
         */
        virtual void start() = 0;

        /**
         * Stops the alert handler.
         */
        virtual void stop() = 0;

};

} /* namespace S31 */
