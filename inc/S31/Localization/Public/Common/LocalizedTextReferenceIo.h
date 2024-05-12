#pragma once

#include <S31/Localization/Public/Common/LocalizedTextReference.h>
#include <S31/Localization/Public/Common/S31LtsExImp.h>

#include <Framework/Format/Public/Stream.h>

#include <iosfwd>

namespace S31::Localization
{

/**
 * @brief stream data to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup S31LocalizationCommon
 */
S31_LTS_EXPIMP std::ostream& operator<<(std::ostream& out, const LocalizedTextReference& data);

/**
 * @brief stream data to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup S31LocalizationCommon
 */
S31_LTS_EXPIMP DFL::Format::Stream& operator<<(DFL::Format::Stream& out, const LocalizedTextReference& data);


}