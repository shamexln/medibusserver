#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Utils/Public/Utf8.h>
#include <Framework/Utils/Public/LanguageTag.h>
#include <Framework/Utils/Public/StrongTypedef.h>
#include <boost/optional.hpp>
#include <Framework/Mdib/Public/Model/VersionCounter.h>
#include <Framework/Mdib/Public/Model/LocalizedTextWidth.h>

namespace DFL
{
namespace Mdib
{

/// @brief References a text in a localized text file.
/// @ingroup Mdib
using LocalizedTextRef = DFL::StrongTypedef<DFL::Locale::Utf8, struct LocalizedTextRefTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

/**
 * @brief Models BICEPS's LocalizedText.
 * @details
 * > LocalizedText is a bundled ELEMENT to reference texts in different languages
 * > or to provide a text in a specific language. (BICEPS)
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP LocalizedText
{
    public:

        /**
         * @brief Constructs a text only with reference and version.
         * @param reference Reference of the text.
         * @param version Referenced version.
         */
        explicit LocalizedText(LocalizedTextRef reference, boost::optional<VersionCounter> version);

        /**
         * @brief Constructs a text without language information.
         * @param text The text in unknown language.
         */
        explicit LocalizedText(Locale::Utf8 text);

        /**
         * @brief Constructs a text language pair.
         * @param localizedText The text in a specific language
         * @param langTag optional language tag according to RFC 5646.
         */
        explicit LocalizedText(Locale::Utf8 localizedText, boost::optional<Locale::LanguageTag> langTag);
        /**
         * @brief Constructs a text with a reference.
         * @param text The text in unknown language.
         * @param ref References a text in a localized text file
         * @param version referenced version
         * @param textWidth LocalizedTextWidth indicating the width of the text
         */
        explicit LocalizedText(Locale::Utf8 text, LocalizedTextRef ref, boost::optional<VersionCounter> version, boost::optional<LocalizedTextWidth> textWidth);

        /**
         * @brief Constructs a text language pair.
         * @param localizedText The text in a specific language
         * @param langTag optional language tag according to RFC 5646.
         * @param textWidth LocalizedTextWidth indicating the width of the text.
         */
        explicit LocalizedText(Locale::Utf8 localizedText, boost::optional<Locale::LanguageTag> langTag, boost::optional<LocalizedTextWidth> textWidth);

        /**
         * @brief Full constructor
         * @param localizedText The text in a specific language
         * @param langTag optional language tag according to RFC 5646.
         * @param ref References a text in a localized text file
         * @param version referenced version
         * @param textWidth LocalizedTextWidth indicating the width of the text
         */
        LocalizedText(Locale::Utf8 localizedText,
                      boost::optional<Locale::LanguageTag> langTag,
                      LocalizedTextRef ref,
                      boost::optional<VersionCounter> version,
                      boost::optional<LocalizedTextWidth> textWidth);

        /**
         * @brief Returns the text.
         * @returns Constant reference to the text.
         */
        const Locale::Utf8& text() const;

        /**
         * @brief Returns the reference.
         * @details Note that the empty reference represents that there is no reference.
         * @returns Constant reference to the reference.
         */
        const LocalizedTextRef& reference() const;

        /**
         * @brief Returns the version.
         * @returns Constant reference to the version.
         */
        const boost::optional<VersionCounter>& version() const;

        /**
         * @brief Returns the text width.
         * @returns Constant reference to the text width.
         */
        const boost::optional<LocalizedTextWidth>& textWidth() const;

        /**
         * @brief Returns the language (if available).
         * @returns Constant reference to the language.
         */
        const boost::optional<Locale::LanguageTag>& languageTag() const;

        /**
         * @brief Check whether the object is empty or not.
         * @details This only depends on @ref text(). The other attributes are not considered (language, version,...)
         * @return \c true if the object is empty
         */
        bool empty() const;
    private:
        boost::optional<Locale::LanguageTag> m_languageTag;
        Locale::Utf8 m_text;
        LocalizedTextRef m_ref;
        boost::optional<VersionCounter> m_version;
        boost::optional<LocalizedTextWidth> m_textWidth;

};

/**
 * @brief Compares two LocalizedText instances.
 * @param lhs first value to compare with.
 * @param rhs second value to compare with.
 * @return \c true in case text and language are the same
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator==(const LocalizedText& lhs, const LocalizedText& rhs) noexcept;

/**
 * @brief Compares two LocalizedText instances.
 * @param lhs first value to compare with.
 * @param rhs second value to compare with
 * @return \c true in case text or language differ
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator!=(const LocalizedText& lhs, const LocalizedText& rhs) noexcept;

inline LocalizedText::LocalizedText(LocalizedTextRef reference, boost::optional<VersionCounter> version) :
        m_languageTag(boost::none),
        m_text(),
        m_ref(std::move(reference)),
        m_version(std::move(version)),
        m_textWidth(boost::none)
{
}

inline LocalizedText::LocalizedText(Locale::Utf8 text) :
        m_languageTag(boost::none),
        m_text(std::move(text)),
        m_ref(Locale::Utf8()),
        m_version(boost::none),
        m_textWidth(boost::none)
{
}

inline LocalizedText::LocalizedText(Locale::Utf8 localizedText, boost::optional<Locale::LanguageTag> langTag) :
        m_languageTag(std::move(langTag)),
        m_text(std::move(localizedText)),
        m_ref(Locale::Utf8()),
        m_version(boost::none),
        m_textWidth(boost::none)
{
}

inline LocalizedText::LocalizedText(Locale::Utf8 text, LocalizedTextRef ref, boost::optional<VersionCounter> version, boost::optional<LocalizedTextWidth> textWidth) :
        m_languageTag(boost::none),
        m_text(std::move(text)),
        m_ref(std::move(ref)),
        m_version(std::move(version)),
        m_textWidth(textWidth)
{
}

inline LocalizedText::LocalizedText(Locale::Utf8 localizedText, boost::optional<Locale::LanguageTag> langTag, boost::optional<LocalizedTextWidth> textWidth) :
        m_languageTag(std::move(langTag)),
        m_text(std::move(localizedText)),
        m_ref(Locale::Utf8()),
        m_version(boost::none),
        m_textWidth(textWidth)
{
}

inline LocalizedText::LocalizedText(Locale::Utf8 localizedText,
                                    boost::optional<Locale::LanguageTag> langTag,
                                    LocalizedTextRef ref,
                                    boost::optional<VersionCounter> version,
                                    boost::optional<LocalizedTextWidth> textWidth) :
        m_languageTag(std::move(langTag)),
        m_text(std::move(localizedText)),
        m_ref(std::move(ref)),
        m_version(std::move(version)),
        m_textWidth(textWidth)
{
}

inline const Locale::Utf8& LocalizedText::text() const
{
    return m_text;
}

inline const LocalizedTextRef& LocalizedText::reference() const
{
    return m_ref;
}

inline const boost::optional<VersionCounter>& LocalizedText::version() const
{
    return m_version;
}

inline const boost::optional<Locale::LanguageTag>& LocalizedText::languageTag() const
{
    return m_languageTag;
}

inline bool LocalizedText::empty() const
{
    return text().empty();
}

inline const boost::optional<LocalizedTextWidth>& LocalizedText::textWidth() const
{
    return m_textWidth;
}

inline bool operator==(const LocalizedText& lhs, const LocalizedText& rhs) noexcept
{
    if (&lhs == &rhs)
    {
        return true;
    }
    return (lhs.languageTag() == rhs.languageTag()
            && lhs.text() == rhs.text()
            && lhs.reference() == rhs.reference()
            && lhs.version() == rhs.version()
            && lhs.textWidth() == rhs.textWidth());
}

inline bool operator!=(const LocalizedText& lhs, const LocalizedText& rhs) noexcept
{
    return !(lhs == rhs);
}

} /* namespace Mdib */
} /* namespace DFL */
