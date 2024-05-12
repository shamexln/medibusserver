#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Public/Model/Alert/RemedyInfo.h>
#include <Framework/Mdib/Private/HasExtensions.h>
#include <Framework/Mdib/Private/ExpImp.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief   Information about possible causes if an \ref AlertCondition is present.
 * @ingroup Mdib
 */
class CauseInfo: public Impl::HasExtensions
{
    public:
        /**
         * @brief Default constructor without any information.
         */
        CauseInfo() = default;

        /**
         * @brief Constructor.
         */
        CauseInfo(boost::optional<RemedyInfo> remedyInfo,
                  const LocalizedTexts& description,
                  ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Information on how to remedy an alert condition.
         * @return If remedy information is available, a \ref RemedyInfo object, otherwise\c boost::none.
         */
        const boost::optional<RemedyInfo>& remedyInfo() const;

        /**
         * @brief Human-readable text (in multiple languages) that describes why an alert condition is present.
         */
        const LocalizedTexts& description() const;

    private:
        boost::optional<RemedyInfo> m_remedyInfo;
        LocalizedTexts m_description;
};

/**
 * @brief Sequence of \ref CauseInfo.
 * @ingroup Mdib
 */
using CauseInfos = std::vector<CauseInfo>;

inline CauseInfo::CauseInfo(boost::optional<RemedyInfo> remedyInfo,
                            const LocalizedTexts& description, // NOLINT(modernize-pass-by-value)
                            ExtensionTypes extensions) :
        Impl::HasExtensions(std::move(extensions)),
        m_remedyInfo(std::move(remedyInfo)),
        m_description(description)
{
}

inline const boost::optional<RemedyInfo>& CauseInfo::remedyInfo() const
{
    return m_remedyInfo;
}

inline const LocalizedTexts& CauseInfo::description() const
{
    return m_description;
}

DFL_MDIB_EXPIMP bool operator==(const CauseInfo& lhs, const CauseInfo& rhs);

DFL_MDIB_EXPIMP bool operator!=(const CauseInfo& lhs, const CauseInfo& rhs);

} /* namespace Mdib */
} /* namespace DFL */
