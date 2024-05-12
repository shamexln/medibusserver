#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/CodingSystem.h>
#include <Framework/Utils/Public/Utf8.h>

namespace DFL::Mdib
{

/**
 * @brief Factory to create CodingSystem instances for common nomenclatures.
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP CodingSystemFactory
{
    public:
        /**
         * @brief ISO/IEEE 11073-10101 nomenclature.
         * @details It uses the implied coding system string for SDC.
         * @return CodingSystem for ISO/IEEE 11073-10101 nomenclature.
         */
        static const CodingSystem& ieee11073CodingSystem();
};

}
