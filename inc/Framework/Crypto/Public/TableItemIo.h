#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <iosfwd>

namespace DFL
{
namespace Crypto
{
class TableItem;
/**
 * @snippet Crypto/Test/UnitTest/TestTableItem.cpp ostream
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::ostream& operator<<(std::ostream& str, const TableItem& item);
}
}
namespace DFL
{
namespace Format
{
class Stream;
/**
 * @snippet Crypto/Test/UnitTest/TestTableItem.cpp formatStream
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP Stream& operator<<(Stream& str, const Crypto::TableItem& item);
}
}
