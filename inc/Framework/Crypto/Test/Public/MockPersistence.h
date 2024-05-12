#pragma once

#include <Framework/Crypto/Test/Private/MockPersistence.h>

#include <Framework/Thread/Public/NoLock.h>
#include <Framework/Thread/Public/RecursiveMutex.h>

namespace DFL::Crypto::Test
{
/**
 * @brief
 * Exchanges the service used for persisting and locking in Crypto::Store with
 * a volatile persistence without locking.
 *
 * @details
 * After destroying the instance, the previous persistence and locking service
 * will be restored.
 *
 * @note
 * Do not call DFL::Crypto::Environment::init after creating an instance.
 * Otherwise the default services will be used again!
 *
 * @snippet Crypto/Test/UnitTest/TestUtils/TestMockPersistence.cpp nolock
 *
 * @ingroup Crypto
 */
class MockPersistence
{
public:
    /**
     * @brief Injects a non-existing table into persistence.
     */
    MockPersistence() = default;
    /**
     * @brief Injects given init table into persistence.
     */
    explicit MockPersistence(Table init)
        : m_pers{Impl::MockVolatilePersistence<Thread::NoLock>{std::move(init)}}
    {
    }

private:
    Impl::MockVolatilePersistence<Thread::NoLock> m_pers{};
};
/**
 * @brief
 * Exchanges the service used for persisting and locking in Crypto::Store with
 * a volatile persistence with threadsafe locking.
 *
 * @details
 * After destroying the instance, the previous persistence and locking service
 * will be restored.
 *
 * @note
 * Do not call DFL::Crypto::Environment::init after creating an instance.
 * Otherwise the default services will be used again!
 *
 * @snippet Crypto/Test/UnitTest/TestUtils/TestMockPersistence.cpp threadsafe
 *
 * @ingroup Crypto
 */
class ThreadsafeMockPersistence
{
public:
    /**
     * @brief Injects a non-existing table into persistence.
     */
    ThreadsafeMockPersistence() = default;
    /**
     * @brief Injects given init table into persistence.
     */
    explicit ThreadsafeMockPersistence(Table init)
        : m_pers{Impl::MockVolatilePersistence<Thread::RecursiveMutex>{
              std::move(init)}}
    {
    }

private:
    Impl::MockVolatilePersistence<Thread::RecursiveMutex> m_pers{};
};
}
