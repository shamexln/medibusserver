#pragma once

#include <S31/Log/Public/Logger.h>
#include <S31/SetService/Public/Device/InvocationCallbacks.h>

namespace S31::Sdc::Test
{

/**
 * @brief A mock set operation invocation callback that simulates transitions through various invocation state sequences.
 */
class MockMdsSetStringCallback : public S31::SetService::V3::MdsSetStringCallback
{
    public:
        void callback(const DFL::Mdib::MdsSetStringOperationHandle& operationHandle,
                      const DFL::Locale::Utf8& value,
                      S31::SetService::SynchronousDeviceTransaction& transaction) override
        {
            S31_STREAM_INFO_LOGGER("Test", "set operation callback value=", value);
            std::istringstream stream(value.value());
            std::vector<std::string> operationsVec;
            while (stream.good())
            {
                std::string op;
                std::getline(stream, op, ',');
                operationsVec.push_back(op);
            }
            auto asyncTransaction = transaction.waiting();
            const DFL::Mdib::MdibVersion dummyMdibVersion{DFL::Mdib::Uri{"urn:uuid:c49dbf7b-a971-4d54-be16-3d6cf853061c"}};
            for (const auto& operation : operationsVec)
            {
                if (operation == "started")
                {
                    asyncTransaction->started();
                }
                else if (operation == "finished")
                {
                    asyncTransaction->finished(dummyMdibVersion);
                }
                else if (operation == "finishedWithVersion")
                {
                    // this test case should send a specific MDIB version
                    asyncTransaction->finished(DFL::Mdib::MdibVersion(DFL::Mdib::Uri("urn:uuid:7777")));
                }
                else if (operation == "finishedWithModification")
                {
                    asyncTransaction->finishedWithModification(dummyMdibVersion);
                }
                else if (operation == "finishedWithModificationWithVersion")
                {
                    // this test case should send a specific MDIB version
                    asyncTransaction->finishedWithModification(DFL::Mdib::MdibVersion(DFL::Mdib::MdibVersion(DFL::Mdib::Uri("urn:uuid:7778"))));
                }
                else if (operation == "cancelled")
                {
                    asyncTransaction->cancelled({S31::SetService::ErrorMessage{DFL::Locale::Utf8("cancelledMessage"), DFL::Locale::LanguageTag{"en"}}});
                }
                else if (operation == "failed")
                {
                    asyncTransaction->failed(DFL::Locale::Utf8("failedMessage"));
                }
                else if (operation == "cancelledManually")
                {
                    asyncTransaction->cancelledManually({S31::SetService::ErrorMessage{DFL::Locale::Utf8("cancelledManuallyMessage"), DFL::Locale::LanguageTag{"en"}}});
                }
                else
                {
                    S31_STREAM_ERROR_LOGGER("Test", "unknown test case handle=", operationHandle, " with value=", operation);
                    return;
                }
            }
        }
};

/**
 * @brief A mock set operation invocation callback that sets the operation target.
 */
class MockMdsSetStringCallbackOperationTarget : public S31::SetService::V3::MdsSetStringCallback
{
    public:
        void callback(const DFL::Mdib::MdsSetStringOperationHandle&,
                      const DFL::Locale::Utf8& value,
                      S31::SetService::SynchronousDeviceTransaction& transaction) override
        {
            const auto version = DFL::Mdib::MdibVersion(DFL::Mdib::Uri("urn:uuid:7777"));
            const auto target = SetService::OperationTarget(DFL::Mdib::Handle("operation_target"));


            if (value.value() == "synchronous")
            {
                transaction.finished(version, target);
            }

            if (value.value() == "synchronousWithModifications")
            {
                transaction.finishedWithModification(version, target);
            }

            if (value.value() == "asynchronous")
            {
                auto atransaction = transaction.waiting();
                atransaction->started();
                atransaction->finished(version, target);
            }

            if (value.value() == "asynchronousWithModifications")
            {
                auto atransaction = transaction.waiting();
                atransaction->started();
                atransaction->finishedWithModification(version, target);
            }
        }

};

}
