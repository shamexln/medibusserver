#pragma once

#include <S31/Utils/Private/S31UtilsExImp.h>

#include <Framework/Utils/Public/StrongTypedef.h>

#include <string>
#include <streambuf>
#include <ostream>

namespace S31::Utils
{
namespace Impl
{
struct StringAppendLimitTag {};
}

/**
 * @brief Size limit type for @ref StringAppendOutputStream
 * @ingroup S31Utils
 */
using StringAppendLimit = DFL::StrongTypedef<std::size_t, Impl::StringAppendLimitTag>;

/**
 * @brief Default size limit for @ref StringAppendOutputStream is 4MB
 * @ingroup S31Utils
 */
constexpr StringAppendLimit DefaultStringAppendLimit{std::size_t{4} * 1024 * 1024};

/**
 * @brief Output only stream implementation which appends to a \c std::string
 *
 * @details The stream does not own the string it writes to, so user code
 * must take care that the output string remains valid for the lifetime of the stream.
 *
 * @ingroup S31Utils
 */
class S31_UTILS_EXPIMP StringAppendOutputStream : public std::ostream
{
public:
    /**
     * @brief Construct the stream with a given string reference for output.
     * @details The output string will be sized limited by default to @ref DefaultStringAppendLimit
     */
    explicit StringAppendOutputStream(std::string& str, StringAppendLimit sizeLimit = DefaultStringAppendLimit);

    /**
     * @brief Indicator that a write exceeded the size limit on the output.
     */
    bool sizeLimitExceeded() const;

    /**
     * @brief Restart the stream
     * @details Clears any failure bits of the stream, and clears all string data.
     */
    void restart();

private:
    class Impl : public std::streambuf
    {
    public:
        Impl(std::string& str, StringAppendLimit sizeLimit);
        bool overLimit() const;
        void clear();
    protected:
        int_type overflow( int_type ch = traits_type::eof() ) override;
        std::streamsize xsputn(const char_type* s, std::streamsize count) override;
    private:
        std::string& m_str;
        const std::size_t m_sizeLimit;
        bool m_overLimit{false};
    };

    Impl m_impl;
};
}
