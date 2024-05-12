#pragma once

#include <S31/Sdc/Test/Utils/s31core_it_utils_exp_imp.h>

#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>
#include <string>

namespace S31::Sdc::Test
{
/**
 * @brief Test handler for descriptor update operations.
 *
 * @details
 * This class allows to trigger descriptor modification from
 * remote devices to test the descriptor modification report
 * sending to remote devices.
 */
class S31_CORE_IT_UTIL_EXPIMP MdibDescriptorOpsHandler
{
    public:
        explicit MdibDescriptorOpsHandler(DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr> mdibAccess);

        void runTestCase(const std::string& testCase);
    private:
        void runCreateMdsSco();
        void runDeleteMdsSco();
        void runCreateMdsSetString();
        void runDeleteMdsSetString();
        void runCreateVmd();
        void runDeleteVmd();
        void runCreateVmdSco();
        void runDeleteVmdSco();
        void runCreateVmdSetString();
        void runDeleteVmdSetString();
        void runCreateChannel();
        void runDeleteChannel();
        void runCreateNumMetric();
        void runDeleteNumMetric();
        void runCreateStrMetric();
        void runDeleteStrMetric();
        void runCreateWaveformMetric();
        void runDeleteWaveformMetric();
        void runCreateChannelTree();
        void runDeleteChannelTree();
        void runCreateVmdTree();
        void runDeleteVmdTree();
        void runCreateActivateOperation();
        void runChangeActivateOperationState();
        void runDeleteActivateOperation();

        DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr> m_mdibAccess;
};
}
