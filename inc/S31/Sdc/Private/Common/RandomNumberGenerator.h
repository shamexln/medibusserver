#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Chrono/Public/Duration.h>

#include <string>

namespace S31::Sdc::Impl
{
/**
 * Random data generator for integers and UUIDs.
 *
 * \ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP RandomNumberGenerator
{
    public:
        /**
         * @brief Creates a URN based on random UUID.
         * @details
         * E.g., urn:uuid:cf513302-71bb-4181-83e3-d508c2ef7482
         *
         * @return newly created random URN
         */
        static std::string getRandomUuidUrn();

        /**
         * @brief Generates a random duration up to maximum (given upper limit).
         */
        static DFL::Chrono::Milliseconds getRandomDuration(DFL::Chrono::Milliseconds max);

};

}
