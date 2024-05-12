#pragma once

#include <S31/Localization/Public/Common/NumberOfLines.h>

#include <Framework/Mdib/Public/Model/LocalizedText.h>
#include <Framework/Mdib/Public/Model/LocalizedTextWidth.h>
#include <Framework/Mdib/Public/Model/VersionCounter.h>

#include <boost/optional/optional.hpp>

namespace S31::Localization::Impl
{

/**
 * @brief Key for ordering @ref S31::Localization::LocalizedTextFilter (without respect to language and reference).
 * @details Used for holding multiple filters on client side in a sorted container.
 * @ingroup S31LocalizationCommon
 */
class LocalizedTextFilterKey
{
    public:
        template<typename T_Version, typename T_TextWidth, typename T_NumberOfLines>
        LocalizedTextFilterKey(T_Version&& version, T_TextWidth&& textWidth, T_NumberOfLines&& numberOfLines):
            m_version(std::forward<T_Version>(version)),
            m_textWidth(std::forward<T_TextWidth>(textWidth)),
            m_numberOfLines(std::forward<T_NumberOfLines>(numberOfLines))
        {}

        const DFL::Mdib::VersionCounter& version() const
        {
            return m_version;
        }

        const boost::optional<DFL::Mdib::LocalizedTextWidth>& textWidth() const
        {
            return m_textWidth;
        }

        const boost::optional<NumberOfLines>& numberOfLines() const
        {
            return m_numberOfLines;
        }

        friend bool operator<(const LocalizedTextFilterKey& lhs, const LocalizedTextFilterKey& rhs)
        {
            if (lhs.version() != rhs.version())
            {
                return lhs.version() < rhs.version();
            }
            if (!lhs.textWidth() && rhs.textWidth())
            {
                return true;
            }
            if (lhs.textWidth() && !rhs.textWidth())
            {
                return false;
            }
            if (lhs.textWidth() != rhs.textWidth())
            {
                return lhs.textWidth() < rhs.textWidth();
            }
            if (!lhs.numberOfLines() && rhs.numberOfLines())
            {
                return true;
            }
            if (lhs.numberOfLines() && !rhs.numberOfLines())
            {
                return false;
            }
            return lhs.numberOfLines() < rhs.numberOfLines();
        }
    private:
        DFL::Mdib::VersionCounter m_version;
        boost::optional<DFL::Mdib::LocalizedTextWidth> m_textWidth;
        boost::optional<NumberOfLines> m_numberOfLines;

};

}
