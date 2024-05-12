#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/MdibSmartPtrTypes.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/MdibVersion.h>
#include <Framework/Mdib/Public/Model/Timestamp.h>
#include <Framework/Mdib/Public/MdibEntityFilters.h>
#include <Framework/Mdib/Public/MdibQuery.h>
#include <Framework/Mdib/Public/MdibEntityRange.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <memory>
#include <optional>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
struct MdDescriptionVersionTag;
struct MdStateVersionTag;
class MdibTreeStore;
}
/**
 * @brief Strong type def for MdDescription/\@DescriptionVersion
 * @ingroup Mdib
 */
using MdDescriptionVersion = DFL::StrongTypedef<VersionCounter, Impl::MdDescriptionVersionTag, DFL::Skill::EqualityComparable, DFL::Skill::Streamable>;

/**
 * @brief Strong type def for MdState/\@StateVersion
 * @ingroup Mdib
 */
using MdStateVersion = DFL::StrongTypedef<VersionCounter, Impl::MdStateVersionTag, DFL::Skill::EqualityComparable, DFL::Skill::Streamable>;

/**
 * @brief Root object that comprises the capability description of the represented medical devices systems (MDSs).
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP Mdib
{
    public:
        /**
         * @brief Constructor.
         */
        Mdib(const Impl::MdibTreeStore& treeStore,
             MdibVersion mdibVersion,
             std::optional<Timestamp> timestamp,
             const boost::optional<MdDescriptionVersion>& mdDescriptionVersion,
             const boost::optional<MdStateVersion>& mdStateVersion);

        ~Mdib() noexcept;

        /**
         * @brief Provides the version of the %MDIB.
         */
        const MdibVersion& mdibVersion() const;

        /**
         * @brief Provides the write timestamp of the local MDIB change.
         * @details
         * The write time is only available for local MDIB instances due to the
         * fact that it is not transmitted in  report updates.
         * Only via the history service of a device the timestamp is available.
         * For a local MDIB it is used for the (optional) history service.
         */
        std::optional<Timestamp> timestamp() const noexcept;

        /**
         * @brief Provides the MdDescription/DescriptionVersion, if supported by implementation.
         * @details Only for local MDIBs it is possible to provide these information.
         * For remote MDIB it is not received via network in reports.
         */
        const boost::optional<DFL::Mdib::VersionCounter>& mdDescriptionVersion() const;

        /**
         * @brief Provides the MdState/StateVersion, if supported by implementation.
         * @details Only for local MDIBs it is possible to provide these information.
         * For remote MDIB it is not received via network in reports.
         */
        const boost::optional<DFL::Mdib::VersionCounter>& mdStateVersion() const;

        /**
         * @brief Get an entity by it's handle name.
         * @returns the entity or an empty SharedPtr if the entity was not found
         *
         * #### Example
         * @snippet Mdib/Test/UnitTest/TestMdib.cpp getByEntity
         */
        template<class T_Entity>
        SharedPtr<T_Entity> entity(const BasicHandle<T_Entity>& handle) const;

        /**
         * @name Range
         *
         * @brief Get ranges (i.e., something with begin() and end()).
         *
         * These ranges can be used with range based loops (from C++11).
         *
         * Note, that just as with iterators in general, you have to hold the container (in this case the %Mdib
         * itself) as long as you hold and use the iterator or range.
         *
         * ### Examples
         * #### %Range based for loop
         * @snippet Mdib/Test/UnitTest/TestMdib.cpp rangedfor
         *
         * #### Filtered range and algorithm
         * @snippet Mdib/Test/UnitTest/TestMdib.cpp filteredranged
         */
        ///@{
        /// @brief get a range (of one entity)
        template<class T_Entity>
        MdibEntityRange<T_Entity> range() const;

        /// @brief get a filtered range (of one entity)
        template<class T_Entity>
        MdibEntityRange<T_Entity> range(typename MdibEntityRange<T_Entity>::FilterFunction filterFunc) const;

        /// @brief get the given parent's ordered range of children
        template<class T_ParentEntity>
        MdibEntityChildRange<T_ParentEntity, Mdib> rangeOfChildren(const BasicHandle<T_ParentEntity>& parentHandle) const;
        ///@}

        /**
         * @brief Returns the filters object, to get predefined filter functions to be used with
         * iterators and ranges.
         *
         * @return  The filters object.
         */
        const MdibEntityFilters<Mdib>& filters() const;

        /**
         * @brief Returns the query object, to get special entities or data from MDIB.
         *
         * @return  The query object.
         */
        const MdibQuery& query() const;

    private:
        std::shared_ptr<const Impl::MdibTreeStore> m_treeStore;
        MdibVersion m_mdibVersion;
        std::optional<Timestamp> m_timestamp;
        boost::optional<DFL::Mdib::VersionCounter> m_mdDescriptionVersion;
        boost::optional<DFL::Mdib::VersionCounter> m_mdStateVersion;
        MdibEntityFilters<Mdib> m_entityFilters;
        MdibQuery m_query;

};

inline const MdibEntityFilters<Mdib>& Mdib::filters() const
{
    return m_entityFilters;
}

inline const boost::optional<DFL::Mdib::VersionCounter>& Mdib::mdDescriptionVersion() const
{
    return m_mdDescriptionVersion;
}

inline const boost::optional<DFL::Mdib::VersionCounter>& Mdib::mdStateVersion() const
{
    return m_mdStateVersion;
}

inline const MdibQuery& Mdib::query() const
{
    return m_query;
}

inline const MdibVersion& Mdib::mdibVersion() const
{
    return m_mdibVersion;
}

inline std::optional<Timestamp> Mdib::timestamp() const noexcept
{
    return m_timestamp;
}
}
}
