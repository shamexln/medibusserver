#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Private/Registry.h>

#include <Framework/Persistence/Private/Protected/LoadSave.h>

#include <utility>

namespace DFL::Crypto
{
class Table;
}
namespace DFL::Crypto::Impl::Persistence
{
class DFL_CRYPTO_EXPIMP StorePersistence
{
public:
    static Crypto::Table load();
    static void save(const Crypto::Table& table);
    template <class ModifyFunc>
    static void modify(ModifyFunc&& modifyFunc)
    {
        return ::DFL::Persistence::modify(Registry::persistence(),
                                          std::forward<ModifyFunc>(modifyFunc));
    }
};
}
