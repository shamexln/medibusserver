#pragma once

#include <S31/Sdc/Test/Utils/s31core_it_utils_exp_imp.h>

#include <Framework/Mdib/Public/MdibChangeSet.h>

#include <string>

namespace DFL::Mdib
{
class LocalMdibAccess;
}

namespace S31::Test
{

enum class MdsWithDeviceNameAndModelNameAndManufacturer
{
    Yes,
    No
};

/**
 * Generates data for tests based on a given device instance, including mdibs and local mdib handles.
 */
class S31_CORE_IT_UTIL_EXPIMP TestDataGenerator
{
    public:
        /**
         * Dynamically generates a MDIB for a given TestDevice. This eliminates the need
         * for XML MDIB-files to be written for tests.
         *
         * @param deviceInstance instance of the test device for which the mdib is to be generated, Mdibs that have different values
         *                       here have different Mds types.
         * @param access MDIB access of the test device
         * @param mdsWithDeviceNameAndModelNameAndManufacturer Controls whether the Mds of generated Mdib has device name, mode name, and manufacturer.
         */
        static void generateMdib(int deviceInstance, DFL::Mdib::LocalMdibAccess& access, MdsWithDeviceNameAndModelNameAndManufacturer mdsWithDeviceNameAndModelNameAndManufacturer = MdsWithDeviceNameAndModelNameAndManufacturer::No);

        /**
         * @brief The change set used in generateMdib().
         */
        static DFL::Mdib::MdibChangeSet generateMdibChangeSet(int deviceInstance, MdsWithDeviceNameAndModelNameAndManufacturer mdsWithDeviceNameAndModelNameAndManufacturer = MdsWithDeviceNameAndModelNameAndManufacturer::No);

        /**
         * Generates a handle string, which is unique to a local client and remote device, in tests.
         *
         * @param remoteHandle handle of the remote MDIB entry
         * @param deviceInstance instance of the local client
         * @param remoteInstance instance of the remote device
         */
        static std::string generateLocalMdibHandle(const std::string& remoteHandle, int deviceInstance = 0, int remoteInstance = 0);
};

}
