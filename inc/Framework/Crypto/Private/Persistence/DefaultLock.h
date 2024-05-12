#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Filesystem/Private/Protected/Path.h>
#include <Framework/Persistence/Private/Protected/InterprocessLock.h>

#include <memory>

namespace DFL::Crypto::Impl::Persistence
{
class DFL_CRYPTO_EXPIMP DefaultLock
{
public:
    explicit DefaultLock(Filesystem::Path filePath,
                         Chrono::Milliseconds tryLockDuration);

    void remove();
    void lock();
    void unlock();

private:
    void create();

    Filesystem::Path m_filePath;
    Chrono::Milliseconds m_tryLockDuration;
    std::unique_ptr<::DFL::Persistence::InterprocessLock> m_lock{};
};
}
