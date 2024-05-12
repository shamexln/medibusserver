#pragma once

#ifndef XML_STATIC
#define XML_STATIC
#endif

#include <S31/Sdc/Private/Common/Expat/XmlEvents.h>
#include <S31/Sdc/Private/Common/Expat/XmlParser.h>
#include <S31/Utils/Public/Errors.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/EnumClass.h>
#include <Framework/Utils/Public/NotNull.h>

#include <boost/optional/optional.hpp>
#include <expat.h>

#include <memory>

namespace S31::Sdc::Impl::Expat
{

/**
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP XmlParserImpl: public XmlParser
{
        using XmlParserPtr = std::unique_ptr< ::XML_ParserStruct, decltype(&::XML_ParserFree)>;

    public:
        explicit XmlParserImpl(DFL::NotNull<std::shared_ptr<XmlEvents>> callback);

        [[nodiscard]] ParserStatus parseBuffer(const char* buffer, size_t bufferLength) override;

        void resetParser() override;

        /**
         * @brief Abort and cleanup the parser in case of exception
         */
        void abort(const Utils::Error& error);

        /**
         * @brief Provides the depth of open XML elements.
         * @details Before opening the root element it is \c 0,
         * afterwards it is \c 1.
         */
        [[nodiscard]] int depth() const;

        // internal
        void incrementDepth();
        void decrementDepth();

        [[nodiscard]] XmlEvents& callback();

    private:
        void initParser();

        int m_depth{0};
        XmlParserPtr m_parser;
        DFL::NotNull<std::shared_ptr<XmlEvents>> m_callback;
        boost::optional<Utils::Error> m_abortError;
};

}
