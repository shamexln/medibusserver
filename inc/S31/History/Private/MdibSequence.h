#pragma once

#include <Framework/Mdib/Public/Model/MdibVersion.h>
#include <Framework/Mdib/Public/Model/Uri.h>

#include <optional>

namespace S31::History::Impl
{

/// To identify a local MDIB access instance (without version)
class MdibSequence
{
public:
    MdibSequence() = default;

    inline explicit MdibSequence(DFL::Mdib::Uri seq)
        : sequenceId{std::move(seq)}
    {
    }

    inline MdibSequence(
            DFL::Mdib::Uri                       seq,
            std::optional<DFL::Mdib::InstanceId> instance  // NOLINT(modernize-pass-by-value)
            )
        : sequenceId{std::move(seq)}
        , instanceId{instance}
    {
    }

    DFL::Mdib::Uri                       sequenceId{std::string{}};
    std::optional<DFL::Mdib::InstanceId> instanceId;
};

MdibSequence buildSequence(const DFL::Mdib::MdibVersion& version);

inline bool operator==(const MdibSequence& lhs, const MdibSequence& rhs)
{
    return lhs.sequenceId == rhs.sequenceId && lhs.instanceId == rhs.instanceId;
}

inline bool operator!=(const MdibSequence& lhs, const MdibSequence& rhs)
{
    return !(lhs == rhs);
}
}
