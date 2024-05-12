#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/EnumClass.h>
#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Utils/Public/Utf8.h>

#include <boost/optional/optional.hpp>

namespace S31::Safety
{
namespace Impl
{
class XpathParser;
}

/**
 * @brief Argument index for activate operation parameters.
 * @details If a dual channel definition refers to a specific parameter of an activate operation,
 * the index of that argument is specified by this data type.
 * @ingroup S31Safety
 */
using ArgumentIndex = DFL::StrongTypedef<unsigned int, struct ArgumentIndexTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

/**
 * @brief A \ref S31::Safety::MessageXPath represented as enumeration.
 * @details \ref S31::Safety::MessageXPath supports a variety of predefined expressions that can be used to <i>understand</i> a message XPath
 * expression without understanding the specific XPath syntax (example: <tt>/msg:SetValue/msg:RequestedNumericValue/text()</tt>).
 * @ingroup S31Safety
 */
enum class MessageXPathExpression
{
    SetValueRequestedNumericValue,    ///< XPath expression that points to the \c RequestedNumericValue element in a <tt>msg:SetValue</tt> SOAP message.
    SetStringRequestedStringValue     ///< XPath expression pointing to the \c RequestedStringValue element in the <tt>msg:SetString</tt> SOAP message.
};
DFL_ENUM_CLASS_STREAM_OPERATOR(MessageXPathExpression, (SetValueRequestedNumericValue)(SetStringRequestedStringValue))

/**
 * @brief XPath expression with the message SOAP12:Body element as the root.
 * @details %MessageXPath can be created from a \ref MessageXPathExpression "enumeration" or plain \ref DFL::Locale::Utf8.
 * @ingroup S31Safety
 */
class S31_CORE_EXPIMP MessageXPath
{
    public:

        /**
         * @brief Constructs a %MessageXPath object based on a predefined XPath expression.
         */
        explicit MessageXPath(const MessageXPathExpression& xpathExpression);

        /**
         * @brief Constructs a %MessageXPath object based on plain \ref DFL::Locale::Utf8.
         * @details \attention Customers require knowledge about the XML BICEPS schema!
         */
        explicit MessageXPath(const DFL::Locale::Utf8& xpath);
        /**
         * @brief Constructs a %MessageXPath object based on the index of an activate operation parameter index.
         * @details \attention XPath indices begin with 1 instead of 0!
         */
        explicit MessageXPath(const ArgumentIndex& argurmentIndex);

        /**
         * @brief Provides the raw XPath in string format (as required for network and advanced usage).
         */
        DFL::Locale::Utf8 stringExpression() const;

        /**
         * @brief Returns the predefined (enum) expression if available.
         * @details Since multiple XPath expressions can lead to the same element, internally a normalization might be required.
         *
         * Example: <tt>/msg:Activate/msg:Argument[1]/msg:ArgValue/text()</tt> points to the same value as
         * <tt>/msg:Activate[1]/msg:Argument[1]/msg:ArgValue/text()</tt>.
         * @return The predefined %MessageXPathExpression if resolvable, otherwise \c boost::none.
         */
        boost::optional<MessageXPathExpression> predefinedExpression() const;

        /**
         * @brief Provides the index of the activate argument.
         * @return The index of the activate argument starting at 1 or \c boost::none if the XPath expression does not point to an activate argument.
         */
        boost::optional<ArgumentIndex> argumentIndex() const;

    private:
        void convertToXpathExpression(const DFL::Locale::Utf8& xpath);
        void convertToXpathExpression(Impl::XpathParser& xpathParser,
                                      const std::string& nodeName,
                                      const MessageXPathExpression& xpathExpression);
        void convertActivateToXpathExpression(Impl::XpathParser& xpathParser);
        static DFL::Locale::Utf8 convertToMsgXPath(const MessageXPathExpression& xpathExpression);
        static DFL::Locale::Utf8 convertToMsgXPath(const ArgumentIndex& argumentIndex);
        DFL::Locale::Utf8 m_messageXPath;
        boost::optional<MessageXPathExpression> m_xpathExpression;
        boost::optional<ArgumentIndex> m_argumentIndex;
};

}
