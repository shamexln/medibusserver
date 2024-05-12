#pragma once

#include <Framework/Utils/Public/Utf8.h>

namespace S31::Safety::Impl
{

/**
 * @brief Contains an XPath helper function.
 * @ingroup S31Safety
 */
class Xpath
{
    public:
        /**
         * @brief Encodes a raw text string to an XPath expression string.
         * @details
         * - Text strings in XPath expressions must be encoded as literals.
         * - They may be quoted with single or double quotes.
         * - Since XPath strings do not support escaping for quotes, strings that contain both (single and double) quotes cannot be a simple literal.
         * Instead, the XPath \c concat() function is used to concatenate multiple literals to one string.
         *
         * @param rawString A string that is intended to be used in an XPath expression.
         * @return An XPath literal (if possible) or an XPath expression that represents the string by using a concatenation of literals.
         */
        static std::string encodeStringToExpression(const std::string& rawString);
};

}
