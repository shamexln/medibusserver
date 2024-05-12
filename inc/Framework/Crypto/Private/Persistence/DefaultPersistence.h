#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Private/Persistence/DefaultLock.h>
#include <Framework/Crypto/Public/Table.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>
#include <Framework/Filesystem/Private/Protected/Path.h>
#include <Framework/Persistence/Private/Protected/Persistence.h>

namespace DFL::Crypto::Impl::Persistence
{
class DFL_CRYPTO_EXPIMP DefaultPersistence
{
public:
    explicit DefaultPersistence(Filesystem::Path filePath,
                                Filesystem::Path tmpFilePath,
                                DefaultLock lock);

    void remove();
    Crypto::Table load();
    void save(const Crypto::Table& table);
    void setUp();
    void tearDown();

private:
    Filesystem::Path m_filePath;
    Filesystem::Path m_tmpFilePath;
    ::DFL::Persistence::Persistence<Crypto::Table> m_pers;
    DefaultLock m_lock;
};
}
