#pragma once

#include <Framework/Mdib/Public/Model/LocalizedTexts.h>
#include <Framework/Mdib/Private/HasExtensions.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief   Information on how to remedy an \ref AlertCondition.
 * @ingroup Mdib
 */
class RemedyInfo: public Impl::HasExtensions
{
    public:
        /**
         * @brief Constructor.
         */
        RemedyInfo(const LocalizedTexts& description,
                   ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Human-readable description (in multiple languages) of the remedy information.
         */
        const LocalizedTexts& description() const;

    private:
        LocalizedTexts m_description;
};

inline RemedyInfo::RemedyInfo(const LocalizedTexts& description, // NOLINT(modernize-pass-by-value)
                              ExtensionTypes extensions):
        Impl::HasExtensions(std::move(extensions)),
        m_description(description)
{
}

inline const LocalizedTexts& RemedyInfo::description() const
{
    return m_description;
}

/**
 * @brief Equal compare of \ref RemedyInfo.
 * @param lhs left value for comparison.
 * @param rhs right value for comparison.
 * @return \c true in case all value are equal.
 */
inline bool operator==(const RemedyInfo& lhs, const RemedyInfo& rhs)
{
    return lhs.description() == rhs.description() && lhs.extensions() == rhs.extensions();
}

/**
 * @brief Not equal compare of \ref RemedyInfo.
 * @param lhs left value for comparison.
 * @param rhs right value for comparison.
 * @return \c true in case all value are not equal.
 */
inline bool operator!=(const RemedyInfo& lhs, const RemedyInfo& rhs)
{
    return !(operator==(lhs, rhs));
}

} /* namespace Mdib */
} /* namespace DFL */
