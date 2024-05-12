#pragma once

#include <Framework/Mdib/Public/Model/ExtensionDom/Attribute.h>
#include <Framework/Utils/Public/QName.h>
#include <vector>

namespace DFL
{
namespace Mdib
{
namespace Dom
{

/**
 * @brief Models an xml element for a %BICEPS extension.
 * @details This class provides the \ref DFL::QName "Qualified name" of the xml element,
 * and a sequence of its \ref DFL::Mdib::Dom::Attribute "Attributes".  %Child elements or texts are
 * not modeled directly in the %Element class, but instead as neighboring \ref DFL::Mdib::Dom::Node "Nodes"
 * in tree structure.
 * @ingroup Mdib
 */
class Element
{
    public:
        /**
         * @brief Constructor with name only.
         * @details \ref Element::attributes() "Attributes" is set to an empty sequence
         */
        explicit Element(const QName& name);

        /**
         * @brief Constructor with name only.
         * @details \ref Element::attributes() "Attributes" is set to an empty sequence
         */
        explicit Element(QName&& name);

        /**
         * @brief Full constructor
         */
        Element(const QName& name, Attributes attributes);

        /**
         * @brief Full constructor
         */
        Element(QName&& name, Attributes attributes);

        /**
         * @brief Qualified name of the element
         */
        const QName& name() const noexcept;

        /**
         * @brief Attributes of the element
         */
        const Attributes& attributes() const noexcept;

        /**
         * @brief Equal operator compares all members
         * @return \c true in case all members equals.
         */
        bool operator==(const Element& rhs) const noexcept;

        /**
         * @brief Not equal operator compares all members
         * @return \c true in case at least one member does not equal.
         */
        bool operator!=(const Element& rhs) const noexcept;

    private:
        QName m_name;
        Attributes m_attributes;
};

inline Element::Element(const QName& name) : // NOLINT(modernize-pass-by-value)
        m_name(name)
{
}
inline Element::Element(QName&& name) :
        m_name(std::move(name))
{
}

inline Element::Element(const QName& name, // NOLINT(modernize-pass-by-value)
                        Attributes attributes) :
        m_name(name),
        m_attributes(std::move(attributes))
{
}

inline Element::Element(QName&& name,
                        Attributes attributes) :
        m_name(std::move(name)),
        m_attributes(std::move(attributes))
{
}

inline const QName& Element::name() const noexcept
{
    return m_name;
}

inline const Attributes& Element::attributes() const noexcept
{
    return m_attributes;
}

inline bool Element::operator==(const Element& rhs) const noexcept
{
    if (this == &rhs)
    {
        return true;
    }
    return m_name == rhs.m_name && m_attributes == rhs.m_attributes;
}

inline bool Element::operator!=(const Element& rhs) const noexcept
{
    return !(*this == rhs);
}

}
}
}
