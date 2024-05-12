#pragma once

#include <Framework/Format/Public/Stream.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/Utf8.h>
#include <Framework/Utils/Public/Utf8Io.h>

namespace S31::Utils
{

/**
 * @brief Class that wraps a @ref DFL::Locale::Utf8 in a way that stream operators
 * can be used to append data.
 *
 * This allows to use the << operators that exist for various classes.
 *
 * @ingroup S31Utils
 */
class Utf8AppenderStream
{
    public:
        /**
         * @brief Constructor
         * @param utf8 Reference of a @ref DFL::Locale::Utf8, that is modifiable with << operations.
         */
        explicit Utf8AppenderStream(DFL::Locale::Utf8& utf8): m_utf8(DFL::asNotNull(&utf8)) {}

        /**
         * This template is the purpose of this class. Now we can wrap here a Utf8 object
         * and can append data to it using the << operator.
         */
        template<class T>
        friend Utf8AppenderStream& operator<<(Utf8AppenderStream& out, const T& data);

    private:
        DFL::NotNull<DFL::Locale::Utf8*> m_utf8;
};

template<class T>
inline Utf8AppenderStream& operator<<(Utf8AppenderStream& out, const T& data)
{
    DFL::Format::Stream stream;
    stream << data;
    out.m_utf8->operator+=(DFL::Locale::Utf8(stream.cStr()));
    return out;
}

}
