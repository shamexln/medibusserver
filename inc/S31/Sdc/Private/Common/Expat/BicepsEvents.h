#pragma once

#include <string>

namespace S31::Sdc::Impl::Expat
{

/**
 * @ingroup S31SdcCommon
 */
class BicepsEvents
{
    public:
        virtual ~BicepsEvents() noexcept = default;

        virtual void startMsgElement(const char* localName, const char* pmXsiType, const char** attributes) = 0;
        virtual void startParticipantElement(const char* localName, const char* pmXsiType, const char** attributes) = 0;
        virtual void startExtensionElement(const char* localName, const char** attributes) = 0;
        virtual void startAnyElement(const char* elementQname, const char** attributes) = 0;
        virtual void endMsgElement(const char* localName, std::string&& text) = 0;
        virtual void endParticipantElement(const char* localName, std::string&& text) = 0;
        virtual void endExtensionElement(const char* localName) = 0;
        virtual void endAnyElement(const char* elementQname, std::string&& text) = 0;

        virtual void startNamespace(int xmlDepth, const char* prefix, const char* namespaceUri) = 0;
        virtual void endNamespaces(int xmlDepth) = 0;

        virtual void mixedContentText(std::string&& text) = 0;
};

}
