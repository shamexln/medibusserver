#pragma once

#include <Framework/Crypto/Private/Cipher/Decrypter.h>
#include <Framework/Crypto/Private/Cipher/Encrypter.h>
#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/RandSourceFuncType.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Filesystem/Private/Protected/Path.h>
#include <Framework/Persistence/Private/Protected/Persistence.h>

#include <atomic>
#include <memory>

namespace DFL::Log
{
class Logger;
}
namespace DFL::Crypto
{
class PublicKey;
class Table;
}
namespace DFL::Crypto::Impl
{
class DFL_CRYPTO_EXPIMP Registry
{
public:
    static void init();
    static void shutdown();

    static Log::Logger& debugLogger();

    static void encrypter(Encrypter enc);
    static Encrypter& encrypter();
    static void resetEncrypter();

    static void decrypter(Decrypter dec);
    static Decrypter& decrypter();
    static void resetDecrypter();

    static RandSourceFunc randSource();
    static void randSource(RandSourceFunc func);
    static void resetRandSource();
    static RandSourceFunc defaultRandSource();

    static const Filesystem::Path& storageFolder();
    static void storageFolder(const Filesystem::Path& folder);
    static void resetStorageFolder();

    static ::DFL::Persistence::Persistence<Crypto::Table> persistence();
    static void persistence(
        ::DFL::Persistence::Persistence<Crypto::Table> pers);
    static void resetPersistence();

    static bool removePersistence();

    static const PublicKey& ralPublicKey();
    static void ralPublicKey(const PublicKey& publicKey);
    static void resetRalPublicKey();
    static const PublicKey& defaultRalPublicKey();

    static Chrono::Milliseconds ipcTryLockDuration();
    static void ipcTryLockDuration(Chrono::Milliseconds d);
    static void resetIpcTryLockDuration();

    // using atomic to support multi-threaded generateKeys calls
    static std::atomic_bool& forceKeyGeneration();
};
}
