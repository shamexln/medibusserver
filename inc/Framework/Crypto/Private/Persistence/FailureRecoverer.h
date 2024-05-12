#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Private/Log.h>
#include <Framework/Crypto/Private/Persistence/Cipher.h>
#include <Framework/Crypto/Private/Persistence/Hasher.h>

#include <Framework/Persistence/Private/Protected/ArchiveSerializer.h>
#include <Framework/Persistence/Private/Protected/FilePersistence.h>
#include <Framework/Persistence/Private/Protected/Persistence.h>

#include <string>
#include <utility>

namespace DFL
{
namespace Crypto
{
namespace Impl
{
namespace Persistence
{
template <class T>
class FailureRecoverer
{
public:
    explicit FailureRecoverer(::DFL::Persistence::Persistence<T> pers)
        : m_pers(std::move(pers))
    {
    }

    void remove()
    {
        m_pers.remove();
    }

    T load()
    {
        try
        {
            return m_pers.load();
        }
        catch (const ::DFL::Persistence::FileNotFoundException& e)
        {
            const auto msg{std::string{e.what()} + ". Saving empty data"};
            DFL_CRYPTO_DEBUG_LOG_INFO(msg.c_str());
            return saveEmptyAndReload();
        }
        catch (const HasherException& e)
        {
            const auto msg{std::string{"Hash error: \""} + e.what() +
                           "\" found. Try to recover by saving empty data"};
            DFL_CRYPTO_DEBUG_LOG_WARNING(msg.c_str());
            return saveEmptyAndReload();
        }
        catch (const CipherException&)
        {
            throw;
        }
        catch (const ::DFL::Persistence::SerializerException&)
        {
            throw;
        }
    }

    void save(const T& t)
    {
        m_pers.save(t);
    }

    void setUp()
    {
        m_pers.setUp();
    }

    void tearDown()
    {
        m_pers.tearDown();
    }

private:
    T saveEmptyAndReload()
    {
        m_pers.save(T{});
        return m_pers.load();
    }

    ::DFL::Persistence::Persistence<T> m_pers;
};
}
}
}
}
