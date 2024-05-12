#pragma once

#include <S31/Utils/Private/S31UtilsExImp.h>

#include <Framework/Encoding/Public/BytesView.h>

#include <string_view>
#include <istream>

namespace S31::Utils
{
/**
 * @brief Input only stream implementation which reads from memory.
 *
 * @details Character data may be provided by \c std::string_view
 * or @ref DFL::Encoding::BytesView.  The stream does not own memory
 * it reads from, so user code must take care that the provided view
 * is valid for the lifetime of the stream.
 *
 * @ingroup S31Utils
 */
class S31_UTILS_EXPIMP StringViewInputStream : public std::istream
{
public:
    explicit StringViewInputStream(std::string_view view);

    explicit StringViewInputStream(DFL::Encoding::BytesView view);

private:
    class Impl : public std::streambuf
    {
    public:
        Impl(const char* begin, std::size_t length);
    };

    Impl m_impl;
};

}
