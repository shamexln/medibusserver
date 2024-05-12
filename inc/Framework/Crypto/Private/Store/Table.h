#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/TableItem.h>

#include <Framework/Utils/Public/Application/Identifier.h>

#include <vector>

namespace DFL::Crypto
{
class Table;
}
namespace DFL::Crypto::Impl
{
class DFL_CRYPTO_EXPIMP Table
{
public:
    Application::Identifier m_applicationIdentifier{};
    std::vector<Crypto::TableItem> m_items{};
};

class DFL_CRYPTO_EXPIMP TableAccess
{
public:
    explicit TableAccess(Crypto::Table* table);

    TableAccess applicationIdentifier(const Application::Identifier& id) &&;
    TableAccess insert(const Crypto::TableItem& item) &&;

private:
    Crypto::Table* m_table;
};

DFL_CRYPTO_EXPIMP bool operator==(const Table& lhs, const Table& rhs) noexcept;
DFL_CRYPTO_EXPIMP bool operator!=(const Table& lhs, const Table& rhs) noexcept;
DFL_CRYPTO_EXPIMP void swap(Table& a, Table& b) noexcept;
}
