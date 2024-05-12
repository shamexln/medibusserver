#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/Model/Context/LocationContextIndicator.h>
#include <Framework/Mdib/Public/Model/Context/PatientContextIndicator.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Utils/Public/EnumClass.h>
#include <Framework/Utils/Public/NotNull.h>
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
 * @brief An \ref S31::Safety::MdibXPath expression represented as enumeration.
 * @details \ref S31::Safety::MdibXPath supports a variety of predefined expressions that can be used to <i>understand</i> an MDIB XPath
 * expression without understanding the specific XPath syntax
 * (example: <tt>/pm:State[\@DescriptorHandle='foo'][\@ContextAssociation='Assoc']/pm:Identification[1]/\@Root</tt>).
 * @ingroup S31Safety
 */
enum class MdibXPathExpression
{
    /**
     * @brief Represents the root part of the first identification entry for a location or patient context.
     */
    RootOfFirstIdentificationOfAssociatedContextState,

    /**
     * @brief Represents the extension part of the first identification entry for a location or patient context.
     */
    ExtensionOfFirstIdentificationOfAssociatedContextState
    // more to come
};
DFL_ENUM_CLASS_STREAM_OPERATOR(MdibXPathExpression, (RootOfFirstIdentificationOfAssociatedContextState)(ExtensionOfFirstIdentificationOfAssociatedContextState))


/**
 * @brief Interface to create %MdibXPath expressions.
 * @details %MdibXPath can be created from an \ref MdibXPathExpression "enumeration" or plain \ref DFL::Locale::Utf8.
 *
 * This class also provides an interface to \ref MdibXPath::instanceIdentifierValue() "retrieve the root or extension" of the identification from a location/patient context.
 *
 * @ingroup S31Safety
 */
class S31_CORE_EXPIMP MdibXPath
{
    public:
        /**
         * @brief Constructs an %MdibXPath object based on a predefined XPath expression for a location or patient context state.
         * @param mdibXPathExpression The predefined XPath expression.
         * @param descHandle The handle of the \ref DFL::Mdib::LocationContextIndicator "location context indicator" or \ref DFL::Mdib::PatientContextIndicator "patient context indicator".
         */
        explicit MdibXPath(const MdibXPathExpression& mdibXPathExpression, const DFL::Mdib::Handle& descHandle);

        ///\todo More constructors for other types of MdibXPath expressions

        /**
         * @brief Constructs an %MdibXPath object based on plain \ref DFL::Locale::Utf8.
         * @details \attention Customers require knowledge about the XML BICEPS schema!
         */
        explicit MdibXPath(const DFL::Locale::Utf8& mdibXPath);

        /**
         * @brief Provides the raw XPath in string format (as required for network and advanced usage).
         */
        DFL::Locale::Utf8 stringExpression() const;

        /**
         * @brief Returns the predefined (enum) expression if available.
         * @details Since multiple XPath expressions can lead to the same element, internally a normalization might be required.
         *
         * Example: <tt>/pm:State[\@DescriptorHandle='foo'][\@ContextAssociation='Assoc']/pm:Identification[1]/\@Root</tt> points to the same value as
         * <tt>/pm:State[\@ContextAssociation='Assoc'][\@DescriptorHandle='foo']/pm:Identification[1]/\@Root</tt>.
         * @return The predefined %MdibXPathExpression if resolvable, otherwise \c boost::none.
         */
        boost::optional<MdibXPathExpression> predefinedExpression() const;

        /**
         * @brief Provides the descriptor handle in case of location/patient context.
         * @details If there is no descriptor handle attached to the expression, then the returned handle is invalid.
         */
        DFL::Mdib::Handle descriptorHandle() const;

        /**
         * @brief Provides the root or extension of the context identification in case of a location/patient context.
         * @param mdib The MDIB where to seek information.
         * @return The root or extension if found, otherwise \c boost::none.
         */
        boost::optional<std::string> instanceIdentifierValue(const DFL::Mdib::Mdib& mdib) const;

    private:
        template <class T_Entity>
        boost::optional<std::string> getInstanceIdentifierText(const DFL::Mdib::MdibEntityRange<T_Entity>& entities) const;
        void convertToMdibXPathExpression(const DFL::Locale::Utf8& mdibXPath);
        void handleParseMdibXpath(Impl::XpathParser& xpathParser);
        bool handledContextStateAttributes(const Impl::XpathParser& xpathParser);
        void handleIdentificationOfAssociatedContextState(const std::string& attributeName);
        boost::optional<MdibXPathExpression> m_mdibXPathExpression;
        DFL::Locale::Utf8 m_mdibXPath;
        DFL::Mdib::Handle m_descrHandle;
};

}
