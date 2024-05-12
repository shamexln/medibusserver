#pragma once

#include <Framework/Crypto/Private/Ral/Type.h>

#include <Framework/Chrono/Public/Convert.h>
#include <Framework/Chrono/Public/ZonedTime.h>
#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Utils/Public/Oid.h>
#include <Framework/Utils/Public/Oids.h>

#include <string>

namespace DFL::Crypto
{
class PemString;
class DerFormat;
class DistinguishedName;
}
namespace DFLTest::Crypto::UnitTest
{
extern const ::DFL::Crypto::PemString HardCodedRootCa;
extern const ::DFL::Crypto::PemString HardCodedCsr;
extern const ::DFL::Crypto::PemString HardCodedSignedCert;
extern const ::DFL::Crypto::DerFormat HardCodedSignedCertInDerFormat;
extern const ::DFL::Crypto::PemString HardCodedPrivateKey;
extern const ::DFL::Crypto::PemString HardCodedPublicKey;
extern const ::DFL::Crypto::DistinguishedName HardCodedSubjectDn;
extern const std::string HardCodedSubjectDnStr;
extern const ::DFL::Crypto::DistinguishedName HardCodedIssuerDn;
extern const ::DFL::Oids HardCodedCsrRoles;
extern const ::DFL::Oids HardCodedSignedCertRoles;
extern const std::string HardCodedSignedCertValidFromStr;
extern const std::string HardCodedSignedCertValidUntilStr;
extern const ::DFL::Chrono::ZonedTime HardCodedSignedCertValidFrom;
extern const ::DFL::Chrono::ZonedTime HardCodedSignedCertValidUntil;
extern const ::DFL::Crypto::Impl::Ral::Fingerprint HardCodedRootCaFingerprint;
extern const ::DFL::Crypto::Impl::Ral::Fingerprint
    HardCodedSignedCertFingerprint;
namespace StagingPki
{
extern const ::DFL::Crypto::PemString RootCa;
extern const ::DFL::Crypto::PemString IntermediateCa;
extern const ::DFL::Crypto::PemString LeafCert;
extern const ::DFL::Crypto::PemString Chain;
}
extern const ::DFL::Crypto::DerFormat HardCodedEcdsaSigDer;
extern const ::DFL::Encoding::Bytes HardCodedEcdsaSigR;
extern const ::DFL::Encoding::Bytes HardCodedEcdsaSigS;
}
