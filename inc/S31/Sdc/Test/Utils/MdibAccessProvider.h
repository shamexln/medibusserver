#pragma once

#include <S31/Safety/Public/Requirements.h>
#include <S31/Sdc/Public/Device/LocalMdibAccessSmartPtrTypes.h>
#include <S31/Sdc/Test/Utils/s31core_it_utils_exp_imp.h>

#include <Framework/Utils/Public/NotNull.h>

#include <iostream>

namespace S31::Sdc::Test
{

/**
 * @brief Provider for different pre-initialized MDIB access instances.
 */
class S31_CORE_IT_UTIL_EXPIMP MdibAccessProvider
{
    public:
        /**
         * @brief Creates a populated local MDIB access instance
         * with device instance 0.
         */
        static DFL::NotNull<LocalMdibAccessUniquePtr> createLegacyLocalMdibAccess();

        /**
         * @brief Creates a populated local MDIB access instance
         * with device instance 0 plus given safety requirements.
         */
        static DFL::NotNull<LocalMdibAccessUniquePtr> createLegacyLocalMdibAccess(DFL::NotNull<std::unique_ptr<S31::Safety::Requirements>> safetyRequirements);

        /**
         * @brief Creates a populated local MDIB access instance based on the given MDIB XML stream.
         */
        static DFL::NotNull<LocalMdibAccessUniquePtr> createFromStream(std::istream& mdibXmlStream);

        /**
         * @brief Creates a populated local MDIB access instance based on the given MDIB XML stream plus safety requirements.
         */
        static DFL::NotNull<LocalMdibAccessUniquePtr> createFromStream(std::istream& mdibXmlStream,
                                                                       DFL::NotNull<std::unique_ptr<S31::Safety::Requirements>> safetyRequirements);
};

}
