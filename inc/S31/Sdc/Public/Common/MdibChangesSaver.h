#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibChangeType.h>

#include <iosfwd>
#include <utility>
#include <vector>

/// Things from here shall not end up in production code.
namespace S31::Sdc::Experimental
{
/**
 * @brief Keep a record of an @ref DFL::Mdib::MdibChangeSet and the @ref DFL::Mdib::MdibChangeType it was applied with.
 * @ingroup S31SdcCommon
 */
class MdibChangesSaver
{
    public:
        /// @brief Default constructor
        MdibChangesSaver() = default;

        /// @brief Construct with changes and type to serialize data to an archive
        explicit MdibChangesSaver(DFL::Mdib::ConstMdibChangeSetSharedPtr changes,
                                  DFL::Mdib::MdibChangeType changeType);

        /// @brief The change set holding mdib changes.
        /// @{
        void changes(DFL::Mdib::ConstMdibChangeSetSharedPtr newChanges);
        DFL::Mdib::ConstMdibChangeSetSharedPtr changes() const;
        /// @}

        /// @brief The change type that the change set was applied with.
        /// @{
        void changeType(DFL::Mdib::MdibChangeType newChangeType);
        DFL::Mdib::MdibChangeType changeType() const;
        /// @}

    private:
        DFL::Mdib::ConstMdibChangeSetSharedPtr m_changes;
        DFL::Mdib::MdibChangeType m_changeType{DFL::Mdib::MdibChangeType::Description};
};

/**
 * @brief Sequence of @ref MdibChangesSaver.
 * @ingroup S31SdcCommon
 */
using MdibChangesSavers = std::vector<MdibChangesSaver>;

inline MdibChangesSaver::MdibChangesSaver(DFL::Mdib::ConstMdibChangeSetSharedPtr changes,
                                          DFL::Mdib::MdibChangeType changeType) :
    m_changes{std::move(changes)},
    m_changeType{changeType}
{
}

inline void MdibChangesSaver::changes(DFL::Mdib::ConstMdibChangeSetSharedPtr newChanges)
{
    m_changes = std::move(newChanges);
}

inline DFL::Mdib::ConstMdibChangeSetSharedPtr MdibChangesSaver::changes() const
{
    return m_changes;
}

inline void MdibChangesSaver::changeType(DFL::Mdib::MdibChangeType newChangeType)
{
    m_changeType = newChangeType;
}

inline DFL::Mdib::MdibChangeType MdibChangesSaver::changeType() const
{
    return m_changeType;
}

/**
 * @brief Stream operator needed for serialization round trip tests
 * @ingroup S31SdcCommon
 */
inline std::ostream& operator<<(std::ostream& os, const MdibChangesSaver& changes)
{
    os << changes.changeType() << " changeset";
    return os;
}

/**
 * @brief Make a (boost serialized) archive from a sequence of @ref MdibChangesSaver.
 * @ingroup S31SdcCommon
 */
/// @{
S31_CORE_EXPIMP void serializeMdibChanges(std::ostream& os, const MdibChangesSavers& changes);
S31_CORE_EXPIMP std::string serializeMdibChanges(const MdibChangesSavers& changes);
/// @}

/**
 * @brief Make a sequence of @ref MdibChangesSaver from (boost serialized) archive data.
 * @ingroup S31SdcCommon
 */
/// @{
S31_CORE_EXPIMP MdibChangesSavers deserializeMdibChanges(std::istream& is);
S31_CORE_EXPIMP MdibChangesSavers deserializeMdibChanges(const std::string& data);
/// @}

}
