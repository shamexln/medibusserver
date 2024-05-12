#pragma once

#include <Framework/Crypto/Public/DerFormat.h>
#include <Framework/Crypto/Public/PemString.h>

#include <Framework/Encoding/Public/Bytes.h>

namespace DFLTest::Crypto::UnitTest
{
extern const ::DFL::Crypto::PemString HardCodedRsaPublicKeyPkcs1Pem;
extern const ::DFL::Crypto::PemString HardCodedRsaPublicKeyPkcs8Pem;
extern const ::DFL::Crypto::DerFormat HardCodedRsaPublicKeyPkcs1Der;
extern const ::DFL::Crypto::DerFormat HardCodedRsaPublicKeyPkcs8Der;

extern const ::DFL::Crypto::PemString HardCodedRsaPrivateKeyPkcs1Pem;
extern const ::DFL::Crypto::PemString HardCodedRsaPrivateKeyPkcs8Pem;
extern const ::DFL::Crypto::DerFormat HardCodedRsaPrivateKeyPkcs1Der;
extern const ::DFL::Crypto::DerFormat HardCodedRsaPrivateKeyPkcs8Der;

extern const ::DFL::Crypto::PemString HardCodedEcPublicKeyPkcs8Pem;
extern const ::DFL::Crypto::DerFormat HardCodedEcPublicKeyPkcs8Der;
extern const ::DFL::Encoding::Bytes HardCodedEcPublicKeyX;
extern const ::DFL::Encoding::Bytes HardCodedEcPublicKeyY;

extern const ::DFL::Crypto::PemString HardCodedEcPrivateKeyPkcs1Pem;
extern const ::DFL::Crypto::PemString HardCodedEcPrivateKeyPkcs8Pem;
extern const ::DFL::Crypto::DerFormat HardCodedEcPrivateKeyPkcs1Der;
extern const ::DFL::Crypto::DerFormat HardCodedEcPrivateKeyPkcs8Der;

extern const ::DFL::Crypto::PemString OtherHardCodedEcPrivateKeyPkcs1Pem;
extern const ::DFL::Crypto::PemString OtherHardCodedEcPublicKeyPkcs8Pem;
}
