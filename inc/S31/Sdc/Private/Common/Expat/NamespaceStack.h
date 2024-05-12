#pragma once

#include <boost/optional/optional.hpp>

#include <string>
#include <string_view>
#include <tuple>
#include <vector>

namespace S31::Sdc::Impl::Expat
{

/**
 * @brief Stack container for xml namespace to prefix mapping
 * @details This is intended for use by the expat parser to add namespaces
 * as they are discovered, and remove them as they go out of scope.
 * @ingroup S31SdcCommon
 */
class NamespaceStack
{
    public:
        /**
         * @brief Add a new namespace mapping
         * @details Mappings must be added in order of increasing depth.
         */
        void addNamespace(int xmlDepth, const char* prefix, const char* namespaceUri);

        /**
         * @brief Remove all namespace mappings down to and including a given depth
         */
        void removeNamespaces(int xmlDepth);

        /**
         * @brief Finds the most recent namespace for a given prefix.
         * @details
         * If the prefix is unknown empty string view is returned.
         */
        std::string_view namespaceForPrefix(std::string_view prefix) const;

        /**
         * @brief Finds the most recent prefix for a given namespace.
         * @details the returned prefix is either the prefix string, an empty string indicaing
         * the default namespace, or boost::none indicating there is not a known or active prefix
         * for the namespace.
         */
        boost::optional<std::string> prefixForNamespace(const char* namespaceUri) const;

        /**
         * @brief Returns the local part of a qualified name for given namespace
         * @details The method compares the prefix portion of the qualified name with
         * the given namespace.  If these are found to match in the namespace stack,
         * then the local part of the name is returned.  Otherwise nullptr is returned.
         */
        const char* extractLocalNameFor(const char* namespaceUri, const char* qName) const;

    private:
        using XmlDepth = int;
        using NamespacePrefix = std::string;
        using NamespaceUri = std::string;
        using NamespaceEntry = std::tuple<XmlDepth, NamespacePrefix, NamespaceUri>;
        std::vector<NamespaceEntry> m_namespaces;
};

}
