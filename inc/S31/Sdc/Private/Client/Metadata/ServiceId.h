#pragma once

#include <Framework/Utils/Public/Utf8.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Service ID as defined in DPWS.
 * @details %ServiceId is not of type \ref DFL::Net::Uri as the %Uri data type does not support relative URIs.
 *          As DPWS stipulates case-sensitive string comparison for the %ServiceId, it is ok to stick to %UTF8
 *          character sequence here.
 *
 *          From the DPWS standard:
 *
 *          <blockquote>
 *              Identifier for a HOSTED SERVICE which MUST be persisted across re-initialization and
 *              MUST NOT be shared across multiple Hosted elements. ServiceId MUST be unique within a DEVICE.
 *              This value should be compared directly, as a case-sensitive string, with no attempt to make a
 *              relative URI into an absolute URI, to unescape, or to otherwise canonicalize it.
 *          </blockquote>
 */
using ServiceId = DFL::Locale::Utf8;

}
