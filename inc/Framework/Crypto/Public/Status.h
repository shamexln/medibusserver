#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <Framework/Utils/Public/TypesafeEnum.h>

namespace DFL
{
namespace Crypto
{
/**
 * @brief Defines the different status states of a certificate
 *
 * @snippet Crypto/Test/UnitTest/TestStatus.cpp status
 * @ingroup Crypto
 */
// NOLINTNEXTLINE(bugprone-branch-clone)
DFL_TYPESAFE_ENUM(Status, (Initial)(Valid)(Expired))

class Certificate;
class TableItem;
/**
 * @brief Checks whether a certificate is valid.
 *
 * Returns
 * - Status::Initial if no signed certificate is available
 * - Status::Valid if @ref DFL::Chrono::SystemClock::now() is within the range
 *   @c Certificate::validFrom() - @c Certificate::validUntil()
 * - Status::Expired is returned otherwise
 *
 * @snippet Crypto/Test/UnitTest/TestStatus.cpp status
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP Status::Type statusFrom(const Certificate& cert);
/**
 * @brief Same as statusFromCert(item.chain().leafCert()).
 *
 * @snippet Crypto/Test/UnitTest/TestStatus.cpp status
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP Status::Type statusFrom(const TableItem& item);
}
}
