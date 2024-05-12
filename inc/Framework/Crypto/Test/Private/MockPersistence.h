#pragma once

#include <Framework/Crypto/Private/Registry.h>
#include <Framework/Crypto/Public/Table.h>

#include <Framework/Persistence/Private/Protected/Persistence.h>
#include <Framework/Persistence/Private/Protected/VolatilePersistence.h>
#include <Framework/Utils/Public/StateSaver.h>

#include <functional>
#include <utility>

namespace DFL::Crypto::Test::Impl
{
class PersistenceStateSaver
{
private:
    using Persistence = ::DFL::Persistence::Persistence<Table>;
    StateSaver<Persistence> m_stateSaverPers{
        Crypto::Impl::Registry::persistence(),
        [](auto p) { Crypto::Impl::Registry::persistence(std::move(p)); }};
};

template <class BasicLockable>
class MockVolatilePersistence
{
public:
    MockVolatilePersistence()
    {
        changeRegistry();
    }
    explicit MockVolatilePersistence(Table init)
        : m_pers{::DFL::Persistence::VolatilePersistence<Table, BasicLockable>{
              std::move(init)}}
    {
        changeRegistry();
    }

private:
    void changeRegistry()
    {
        Crypto::Impl::Registry::persistence(std::ref(m_pers));
    }

    Impl::PersistenceStateSaver m_persSaver{};
    ::DFL::Persistence::VolatilePersistence<Table, BasicLockable> m_pers{};
};
}
