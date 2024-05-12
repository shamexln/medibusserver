#pragma once

#include <S31/Sdc/Private/Common/Expat/BicepsEvents.h>
#include <S31/Sdc/Private/Common/Expat/XmlEvents.h>

#include <Framework/Utils/Public/EnumClass.h>
#include <Framework/Utils/Public/NotNull.h>

#include <map>
#include <memory>

#include <boost/optional/optional.hpp>

namespace S31::Sdc::Impl::Expat
{

/**
 * @ingroup S31SdcCommon
 */
enum class KnownNamespace
{
        BicepsMessageModel,
        BicepsParticipantModel,
        BicepsExtension,
        XmlSchemaInstance,
        SoapEnvelope
};

DFL_ENUM_CLASS_STREAM_OPERATOR(KnownNamespace, (BicepsMessageModel)(BicepsParticipantModel)(BicepsExtension)(XmlSchemaInstance)(SoapEnvelope))


/**
 * @ingroup S31SdcCommon
 */
class BicepsParser: public XmlEvents
{
    public:
        explicit BicepsParser(DFL::NotNull<std::shared_ptr<BicepsEvents>> callback);

        // input
        void startElement(const char* element, const char** attributes) override;
        void endElement(const char* element) override;
        void text(const char* text, int length) override;

    private:
        void handleStartElement(const char* element, const char** attributes);
        void handleEndElement(const char* element);
        void addNameSpaces(const char** attributes);
        void removeNameSpaces();
        const char* extractXsiType(const char** attributes);
        const char* extractLocalNameFor(KnownNamespace, const char* qName);
        boost::optional<KnownNamespace> nameSpaceForPrefix(const std::string& prefix) const;

        DFL::NotNull<std::shared_ptr<BicepsEvents>> m_callback;

        // internal state
        std::string m_textBuffer;

        using XmlDepth = int;
        using NamespacePrefix = std::string;
        using NamespaceMap = std::map<NamespacePrefix, KnownNamespace>;
        using NamespaceStack = std::map<XmlDepth, NamespaceMap>;
        NamespaceStack m_namespaces;
        XmlDepth m_xmlDepth{0}; //< root element is depth 0
};

}
