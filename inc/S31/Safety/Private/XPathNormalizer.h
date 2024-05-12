#pragma once

#include <S31/Safety/Private/XpathParser.h>

#include <Framework/Utils/Public/Utf8.h>

#include <boost/optional/optional.hpp>

#include <string>

namespace S31::Safety::Impl
{

/**
 * @brief Provides namespace prefix normalization for XPath expressions.
 * @ingroup S31Safety
 */
class XPathNormalizer
{
    public:
        static boost::optional<DFL::Locale::Utf8> normalizeNamespace(const DFL::Locale::Utf8& xpath, std::string_view ns);
};

inline boost::optional<DFL::Locale::Utf8> XPathNormalizer::normalizeNamespace(const DFL::Locale::Utf8& xpath, std::string_view ns)
{
    XpathParser const xpathParser(xpath.value());
    if (xpathParser.getNamespace() != ns)
    {
        std::string::size_type pos = 0;
        std::string msgXPathStr = xpath.value();
        while ((pos = msgXPathStr.find(xpathParser.getNamespace()+":")) != std::string::npos)
        {
            msgXPathStr.replace(pos, xpathParser.getNamespace().length(), ns);
        }
        return DFL::Locale::Utf8(msgXPathStr);
    }
    return boost::none;
}

}
