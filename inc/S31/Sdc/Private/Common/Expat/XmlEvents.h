#pragma once

namespace S31::Sdc::Impl::Expat
{

/**
 * @ingroup S31SdcCommon
 */
class XmlEvents
{
    public:
        virtual ~XmlEvents() noexcept = default;

        virtual void startElement(const char* elementQname, const char** attributes) = 0;
        virtual void endElement(const char* elementQname) = 0;
        virtual void text(const char* text, int textLength) = 0;
        virtual void comment(const char* commentText);

};

inline void XmlEvents::comment(const char* /*commentText*/)
{
    // comments are ignored by default
}

}
