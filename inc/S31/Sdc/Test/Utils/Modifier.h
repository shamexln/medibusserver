#pragma once

#include <S31/Sdc/Test/Utils/Matcher.h>

#include <Framework/Mdib/Public/Model/CodedValueTranslation.h>
#include <Framework/Mdib/Test/Public/MdibWriter.h>
#include <Framework/Mdib/Test/Public/ValueFactory.h>

#include <boost/optional/optional.hpp>

namespace S31::Sdc::Test
{

inline DFL::Mdib::ComponentActivation modifyComponentActivation(DFL::Mdib::ComponentActivation in)
{
    return in == DFL::Mdib::ComponentActivation::On
           ? DFL::Mdib::ComponentActivation::NotReady
           : DFL::Mdib::ComponentActivation::On;
}

inline DFL::Mdib::Ranges modifyRanges(const DFL::Mdib::Ranges& oldRanges)
{
    DFL::Mdib::Ranges newRanges{oldRanges};
    newRanges.push_back(DFL::Mdib::Range{DFL::Mdib::Decimal{1}, DFL::Mdib::Decimal{2}});
    return newRanges;
}

inline DFL::Mdib::Decimal incrementDecimal(const DFL::Mdib::Decimal& in)
{
    return DFL::Mdib::Decimal(in.intValue() + 1, in.intExponent());
}

inline DFL::Mdib::Decimal modifyDecimal(const boost::optional<DFL::Mdib::Decimal>& in)
{
    return incrementDecimal(in.get_value_or(DFL::Mdib::Decimal(0)));
}

inline DFL::Mdib::Duration incrementDuration(const DFL::Mdib::Duration& in)
{
    return DFL::Mdib::Duration(in.count() + 1);
}

inline DFL::Mdib::Duration modifyDuration(const boost::optional<DFL::Mdib::Duration>& in)
{
    return incrementDuration(in.get_value_or(DFL::Mdib::Duration(42)));
}

inline DFL::Mdib::CodedValue modifyTranslation(const boost::optional<DFL::Mdib::CodedValue>& optIn)
{
     DFL::Mdib::CodedValueBuilder cvb(DFL::Mdib::Test::ValueFactory::aCodedValue("12345"));
     cvb.addTranslation(DFL::Mdib::Test::ValueFactory::aCodedValueTranslation());
    auto in = optIn.get_value_or(cvb.build());
    return in;
}

}
