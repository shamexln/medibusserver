#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Utils/Public/ConstContainer.h>

namespace DFL
{
namespace Crypto
{
/**
 * @brief Holds data encoded in DER format.
 * @details
 * DER (Distinguished Encoding Rules) is a binary format for data structures
 * described by ASN.1.
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP DerFormat : public Utils::ConstContainer<Encoding::Bytes>
{
private:
    using Base = Utils::ConstContainer<Encoding::Bytes>;

public:
    using Base::ConstContainer;
    /**
     * @brief Returns a constant pointer to the first byte.
     */
    typename underlying_type::const_pointer data() const noexcept;
};
}
}
