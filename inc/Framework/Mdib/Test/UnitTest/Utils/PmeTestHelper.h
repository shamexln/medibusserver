#pragma once

#include <Framework/Mdib/Public/Model/ExtensionKnown/ParticipantModelExtensions.h>

#include <boost/optional.hpp>

namespace DFLTest::Mdib::UnitTest
{

class PmeTestHelper
{
    public:

        static DFL::QName pmeQname(const char* name);

        template <typename ExtensionType_T>
        static boost::optional<ExtensionType_T> tryParseExt(DFL::Mdib::Dom::Nodes&& extNodes);
};

inline DFL::QName PmeTestHelper::pmeQname(const char* name)
{
    return DFL::QName{ DFL::NamespaceUri{"urn:oid:1.3.6.1.4.1.3592.2.6933.1.1"},  DFL::NamePrefix{"pme"}, name };
}

template <typename ExtensionType_T>
inline boost::optional<ExtensionType_T> PmeTestHelper::tryParseExt(DFL::Mdib::Dom::Nodes&& extNodes)
{
    auto ext = DFL::Mdib::ExtensionType{ extNodes,
                                         DFL::Mdib::MustUnderstand::False };
    return DFL::Mdib::Ext::ParticipantModelExtensions::get<ExtensionType_T>(ext);
}


}
