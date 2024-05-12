#pragma once

#include <S31/SetService/Public/Device/SynchronousDeviceTransaction.h>
#include <S31/SetService/Test/Public/Device/DeviceTransactionFactoryMock.h>

#include <Framework/Crypto/Public/RandomUuidGenerator.h>
#include <Framework/Utils/Public/NotNull.h>

#include <cstdint>

namespace S31::SetService::Test
{

/**
 * @brief Factory function to get a SynchronousDeviceTransaction with a mock DeviceTransaction
 */
inline SynchronousDeviceTransaction synchronousTransaction(std::uint32_t transactionId)
{
    auto deviceTransaction = DFL::asNotNull(std::make_shared<S31::SetService::Test::DeviceTransactionMock>(S31::SetService::TransactionId(transactionId)));
    DFL::Mdib::MdibVersion mdibVersion{DFL::Mdib::Uri{"urn:uuid:" + DFL::Crypto::generateRandomUuidString()}};
    return {std::move(deviceTransaction), mdibVersion};
}

struct SynchronousDeviceTransactionAndMock
{
        SynchronousDeviceTransaction synchronousDeviceTransaction;
        DFL::NotNull<std::shared_ptr<S31::SetService::Test::DeviceTransactionMock>> deviceTransaction;
};

/**
 * @brief Factory function to get a SynchronousDeviceTransaction and its mock DeviceTransaction
 */
inline SynchronousDeviceTransactionAndMock synchronousTransactionAndMock(std::uint32_t transactionId)
{
    auto deviceTransaction = DFL::asNotNull(std::make_shared<S31::SetService::Test::DeviceTransactionMock>(S31::SetService::TransactionId(transactionId)));
    DFL::Mdib::MdibVersion mdibVersion{DFL::Mdib::Uri{"urn:uuid:" + DFL::Crypto::generateRandomUuidString()}};
    return {{deviceTransaction, mdibVersion}, deviceTransaction};
}

}
