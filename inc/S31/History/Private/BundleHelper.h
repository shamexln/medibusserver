#pragma once

#include <S31/History/Private/Bundle.h>
#include <S31/History/Private/MdibSequence.h>

namespace S31::History::Impl
{
/**
 * @brief Creates a hm:ChangeSequenceReport string.
 */
std::string createChangeSequenceReport(
        const Bundle&       bundle,
        const MdibSequence& mdibSequence,
        MdibSnippet         mdibSnippet,
        CompressionLevel    compressionLevel);
}  // namespace S31::History::Impl
