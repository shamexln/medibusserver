#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace S31::Sdc::Impl::Expat
{

/**
 * @brief Status of the parser.
 * @ingroup S31SdcCommon
 */
enum class ParserStatus
{
    RequireMoreData,
    ParsingDone
};
DFL_ENUM_CLASS_STREAM_OPERATOR(ParserStatus, (RequireMoreData)(ParsingDone))

/**
 * @ingroup S31SdcCommon
 */
class XmlParser
{
    public:
        virtual ~XmlParser() noexcept = default;

        /**
         * @brief Push XML byte stream into parser.
         * @returns Status of parsing
         */
        [[nodiscard]] virtual ParserStatus parseBuffer(const char* buffer, size_t bufferLength) = 0;

        /**
         * @brief Reset parser to parse next XML document.
         */
        virtual void resetParser() = 0;

};

}
