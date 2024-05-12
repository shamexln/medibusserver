#pragma once

#include <S31/Sdc/Private/Client/Report/ReportVersionTracker.h>
#include <Framework/Utils/Public/Utf8Io.h>
#include <ostream>

namespace S31::Sdc::Impl::Report
{

template <typename Validity>
std::ostream& operator<<(std::ostream& out, const ValidityAndReason<Validity>& data)
{
    out << data.validity() ;

    const auto& r = data.reason();
    if (!r.empty())
    {
        out << ": " << data.reason();
    }

    return out;
}

}
