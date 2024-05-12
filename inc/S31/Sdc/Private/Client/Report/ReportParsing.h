#pragma once

#include <S31/Sdc/Private/Common/Expat/XmlParser.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace DFL::Mdib
{
class MdibChangeSet;
}

namespace S31::Sdc::Impl
{
namespace Report
{
class StateModifications;
}

/**
 * \ingroup S31SdcCommon
 */
class ReportParsing: public S31::Sdc::Impl::Expat::XmlParser
{
    public:
        // instantiate parsing object
        ReportParsing();
        ~ReportParsing() override;

        /**
         * @brief XML input for BICEPS parser.
         */
        Expat::ParserStatus parseBuffer(const char* buffer, size_t bufferLength) override;

        void resetParser() override;

        /**
         * @brief Access to parsed changes.
         *
         * Either as const& or moved out.
         */
        ///@{
        const Report::StateModifications& changes() const;
        Report::StateModifications extractChanges();
        ///@}

    private:
        class Impl;
        DFL::NotNull<std::unique_ptr<Impl>> m_impl;
};

}
