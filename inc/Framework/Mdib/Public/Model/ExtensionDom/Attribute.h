#pragma once

#include <Framework/Utils/Public/Utf8.h>
#include <Framework/Utils/Public/QName.h>
#include <vector>

namespace DFL
{
namespace Mdib
{
namespace Dom
{

/**
 * @brief Models an attribute of an xml element.
 * @details This class provides the \ref DFL::QName "Qualified name" of the xml attribute, and its value.
 * @ingroup Mdib
 */
class Attribute
{
    public:
        /**
         * @brief Full constructor
         */
        Attribute(const QName& name, Locale::Utf8 value);

        /**
         * @brief Full constructor
         */
        Attribute(QName&& name, Locale::Utf8 value);

        /**
         * @brief The attribute name, which is possibly qualified with a prefix and namespace
         */
        const QName& name() const;

        /**
         * @brief The text of the attribute value
         */
        const Locale::Utf8& value() const;

        /**
         * @brief Equal operator compares all members
         * @return \c true in case all members equals.
         */
        bool operator==(const Attribute& rhs) const;

        /**
         * @brief Not equal operator compares all members
         * @return \c true in case at least one member does not equal.
         */
        bool operator!=(const Attribute& rhs) const;

    private:
        QName m_name;
        Locale::Utf8 m_value;
};

/**
 * @brief Sequence of attributes
 * @ingroup Mdib
 */
using Attributes = std::vector<Attribute>;

inline Attribute::Attribute(const QName& name, // NOLINT(modernize-pass-by-value)
                            Locale::Utf8 value) :
        m_name(name),
        m_value(std::move(value))
{
}

inline Attribute::Attribute(QName&& name,
                            Locale::Utf8 value) :
        m_name(std::move(name)),
        m_value(std::move(value))
{
}

inline const QName& Attribute::name() const
{
    return m_name;
}

inline const Locale::Utf8& Attribute::value() const
{
    return m_value;
}

inline bool Attribute::operator==(const Attribute& rhs) const
{
    if (this == &rhs)
    {
        return true;
    }
    return m_name == rhs.m_name && m_value == rhs.m_value;
}

inline bool Attribute::operator!=(const Attribute& rhs) const
{
    return !(*this == rhs);
}

}
}
}
