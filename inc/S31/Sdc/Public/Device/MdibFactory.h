#pragma once

#include <S31/Sdc/Public/Device/LocalMdibAccess.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/MdibConstraints.h>
#include <Framework/Utils/Public/NotNull.h>

namespace DFL::Mdib
{
class MdibChangeSet;
}

namespace S31
{
namespace Safety
{
class Requirements;
}
namespace Sdc
{

/**
 * @brief Factory to create \ref S31::Sdc::LocalMdibAccess instances.
 * @ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP MdibFactory
{
    public:
        /**
         * @brief Creates MDIB access with empty MDIB and safety requirements.
         * @details The sequence ID will be assigned automatically.
         */
        static DFL::NotNull<LocalMdibAccessUniquePtr> createLocalSdcMdibAccess(
                const DFL::Mdib::MdibConstraints& constraints);

        /**
         * @brief Creates MDIB access with empty MDIB and given safety requirements.
         * @details The sequence ID will be assigned automatically.
         */
        static DFL::NotNull<LocalMdibAccessUniquePtr> createLocalSdcMdibAccess(
                const DFL::Mdib::MdibConstraints& constraints,
                DFL::NotNull<std::unique_ptr<S31::Safety::Requirements>> safetyRequirements);

        /**
         * @brief Creates MDIB access with empty MDIB and safety requirements.
         * @details The sequence ID will be assigned automatically.
         *
         * @deprecated Use factory function with \ref DFL::Mdib::MdibConstraints "MdibConstraints".
         */
        [[deprecated("Use MdibFactory::createLocalMdibAccess(const MdibConstraints&) instead")]]
        static DFL::NotNull<LocalMdibAccessUniquePtr> createLocalSdcMdibAccess();

        /**
         * @brief Creates lean MDIB access with empty MDIB and safety requirements.
         * @details The sequence ID will be assigned automatically.
         *
         * @deprecated Use factory function with \ref DFL::Mdib::MdibConstraints "MdibConstraints".
         */
        [[deprecated("Use MdibFactory::createLocalMdibAccess(const MdibConstraints&) instead")]]
        static DFL::NotNull<LocalMdibAccessUniquePtr> createLocalSdcMdibAccessLean();

};

}
}
