#pragma once

#include <map>
#include <string>

namespace S31::Safety::Impl
{

/**
 * @brief Parser for an absolute XPath path.
 *
 * @details
 * The constructor takes the XPath expression and parses the information for the first
 * path segment. The information is accessible with the \c getXYZ() methods.
 * To move forward to the next path segment call \ref XpathParser::next().
 *
 * @ingroup S31Safety
 */
class XpathParser
{
    public:

        /**
         * @brief Construct the parser with given input path.
         * @details Starts parsing with the first path segment.
         * @param absoluteXpath input XPath to parse.
         */
        explicit XpathParser(std::string absoluteXpath);

        /**
         * @brief Move to next path segment.
         * @details
         * When analyzing the path <tt>/n:elem1/n:elem2/n:elem3</tt>, it
         * starts with the first path segment (data around \c elem1). Calling
         * next(), result in moving forward to the path segment with name
         * \c elem2.
         */
        void next();

        /**
         * @name Path segment access
         */
        ///@{

        /**
         * @brief Returns the XML namespace.
         * @details The path <tt>/dom:MdState/...</tt> has the namespace
         * <tt>dom</tt>.
         *
         * @return namespace of current path segment (or empty string if
         * the name does not have a namespace)
         */
        [[nodiscard]] std::string getNamespace() const;

        /**
         * @brief Returns the local name of the path segment.
         * @details The path <tt>/dom:MdState/...</tt> has the local name
         * <tt>MdState</tt>. In case of a function call (e.g.
         * <tt>.../text()</tt>) the name is empty.
         *
         * @return local name of the current path segment.
         */
        [[nodiscard]] std::string getName() const;

        /**
         * @brief Returns the function name (if any).
         * @details The path <tt>.../text()</tt> has a function name
         * <tt>text</tt> (without parenthesis).
         *
         * @return Function name (or empty string)
         */
        [[nodiscard]] std::string getFunctionName() const;

        /**
         * @brief Returns the attribute name (if any).
         * @details The path <tt>.../\@MustUnderstand</tt> has an attribute
         * name <tt>MustUnderstand</tt>.
         * @return Attribute name (or empty string)
         */
        [[nodiscard]] std::string getAttributeName() const;

        /**
         * @brief Returns the requested index.
         * @details The path <tt>/dom:MdState[4]/...</tt> has the index 4.
         * @return Element index (or 0 as null element)
         */
        [[nodiscard]] unsigned int getIndex() const;

        /**
         * @brief Returns all attribute equality expressions.
         * @details The following path
         * <tt>/n:elem[\@handle='test1'][\@ver=3]/...</tt> would result in a
         * map with the two keys \c test1 and \c ver and the values
         * \c test1 and \c 3.
         * @return Map with attribute name equality value.
         */
        [[nodiscard]] std::map<std::string,std::string> getAttributes() const;

        ///@}
    private:

        void safeIncrementPosition();
        void skipSpaces() noexcept;
        std::string extractName();
        std::string extractDigits();
        std::string extractLiteral();
        std::string extractValue();
        void checkForNodeOrFunction();
        void checkForAttributeName();
        void checkForExpression();
        [[nodiscard]] bool nextCharIs(char c) const noexcept;

        std::string::size_type m_pos{0};
        std::string m_xpath;

        struct Node
        {
                Node() = default;

                std::string ns;
                std::string name;
                std::string functionName;
                std::string attributeName;
                unsigned int index{0};
                std::map<std::string,std::string> attributes;
        };
        Node m_currentNode;
};

}
