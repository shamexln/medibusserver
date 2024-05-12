#pragma once

#include <S31/Sdc/Private/Common/Expat/XmlEvents.h>

#include <string>
#include <utility>
#include <vector>

namespace S31Test::Sdc::Impl::Expat::UnitTest
{

class XmlEventsMock: public S31::Sdc::Impl::Expat::XmlEvents
{
    public:
        struct CommentTag
        {
        };
        struct Payload
        {
            public:
                explicit Payload(const char* e) :
                        element(e)
                {
                }
                Payload(const char* e, const char** a) :
                        element(e)
                {
                    for (int i = 0; a[i]; i += 2)
                    {
                        xmlAttributes.push_back(std::pair<std::string, std::string>(a[i], a[i + 1]));
                    }
                }
                friend bool operator==(const Payload& lhs, const Payload& rhs)
                {
                    return lhs.element == rhs.element;
                }
                explicit Payload(std::string&& t) :
                        text(std::move(t))
                {
                }
                Payload(const std::string& comment, struct CommentTag) :
                        comment(comment)
                {
                }
                std::string element;
                std::vector<std::pair<std::string, std::string>> xmlAttributes;
                std::string text;
                std::string comment;
        };

        void startElement(const char* element, const char **attributes) override
        {
            m_payloadChunks.push_back(Payload(element, attributes));
        }
        void endElement(const char* element) override
        {
            m_payloadChunks.push_back(Payload(element));
        }
        void text(const char *text, int length) override
        {
            m_payloadChunks.push_back(Payload(std::string(text, static_cast<size_t>(length))));
        }
        void comment(const char* commentText) override
        {
            m_payloadChunks.push_back(Payload(std::string(commentText), CommentTag()));
        }

        bool findElement(const char* element)
        {
            if (std::find(m_payloadChunks.begin(), m_payloadChunks.end(), Payload(element)) != m_payloadChunks.end())
            {
                return true;
            }
            return false;
        }

        const std::vector<Payload>& calls() const
        {
            return m_payloadChunks;
        }

        std::string getTextForElement(const char* element)
        {
            std::string result;

            auto it = std::find(m_payloadChunks.begin(), m_payloadChunks.end(), Payload(element));
            if (it != m_payloadChunks.end())
            {
                // Skip the first Payload, as it is the XML element opening tag
                ++it;
            }

            // Read until the next XML element tag is found
            while (it != m_payloadChunks.end() && it->element.empty())
            {
                result += it->text;
                ++it;
            }

            return result;
        }

        /*
         * This function is useful whenever payload has a vector representation of text.
         * For example: ArgValues in the Argument payload of an activate message.
         */
        std::vector<std::string> getTextsForAllOccurencesOfElement(const char* element)
        {
            std::vector<std::string> textsOfElement;
            auto it = std::find(m_payloadChunks.begin(), m_payloadChunks.end(), Payload(element));
            while (it != m_payloadChunks.end())
            {
                std::string resultText;
                // Skip the first Payload, as it is the XML element opening tag
                ++it;

                // Read until the next XML element tag is found and ignore \n since the text we are looking for does not contain \n as the text.
                while (it != m_payloadChunks.end() && it->element.empty() && (it->text != "\n"))
                {
                    resultText += it->text;
                    textsOfElement.push_back(resultText);
                    ++it;
                }

                /*
                 * Since the text of the current occurrence of the element has been already read and inserted into the resultText vector,
                 * go to the next occurrence of the element and repeat.
                 */
                it = std::find(it, m_payloadChunks.end(), Payload(element));
            }

            return textsOfElement;
        }

        const std::vector<Payload> getAllChildElementsContaining(const std::string elementName)
        {
            std::vector<Payload> elementCollection;
            for (auto& payload : m_payloadChunks)
            {
                if (!payload.element.empty() && !payload.xmlAttributes.empty() && payload.element.find(elementName) != std::string::npos)
                {
                    elementCollection.push_back(payload);
                }
            }
            return elementCollection;
        }
    private:
        std::vector<Payload> m_payloadChunks;
};

}
