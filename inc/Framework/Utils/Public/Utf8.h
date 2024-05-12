#pragma once

#include <Framework/Utils/Private/ExpImp.h>

#include <string>
#include <string_view>

namespace DFL::Locale
{

/**
 * @brief Container for UTF-8 encoded string.
 * @details Container with a valid UTF-8 encoded string.
 * All instances contain valid UTF-8 data only.
 *
 * @ingroup Utils
 */
class DFL_UTILS_EXPIMP Utf8
{
    public:

        /**
         * @brief Empty UTF-8 string.
         */
        Utf8() = default;

        /**
         * @brief Conversion uses REPLACEMENT CHARACTER (U+FFFD) for invalid byte sequences.
         * @details This implicit conversion from \c std::string to Utf8 converts invalid byte sequences
         * to the REPLACEMENT CHARACTER (U+FFFD). Thus no error occur and valid UTF-8 encoding is assured.
         *
         * @param utf8String UTF-8 encoded string
         */
        explicit Utf8(const std::string& utf8String);


        /**
         * @brief Conversion uses REPLACEMENT CHARACTER (U+FFFD) for invalid byte sequences.
         * @details This implicit conversion from \c std::string to Utf8 converts invalid byte sequences
         * to the REPLACEMENT CHARACTER (U+FFFD). Thus no error occur and valid UTF-8 encoding is assured.
         *
         * @param utf8String UTF-8 encoded string
         */
        explicit Utf8(const char* utf8String);

        /**
         * @brief Returns UTF-8 encoded string as const reference \c std::string.
         */
        const std::string& value() const noexcept;

        /**
         * @brief Returns UTF-8 encoded string as \c std::string.
         */
        operator std::string() const;

        /**
         * @brief Checks for empty string.
         * @return \c true for empty string.
         */
        bool empty() const noexcept;

        /**
         * @brief Number of Unicode code points.
         * @details
         * For ASCII string it is the same as the number of bytes, but for other
         * strings the number of bytes is greater.
         */
        [[nodiscard]] std::size_t codePointSize() const noexcept;

        /**
         * @brief Erases the contents of the UTF-8 string, which becomes an empty string (with a length of 0 characters).
         */
        void clear() noexcept;

        /**
         * @brief Appends additional \ref Utf8.
         * @param rhs the string that will be appended.
         * @return this.
         */
        Utf8& operator+=(const Utf8& rhs);

        /**
         * @brief Compares two Utf8 instances.
         * @param rhs Instance to compare with.
         * @return \c true in case both instances have the same code point sequence.
         */
        bool equals(const Utf8& rhs) const noexcept;

        /**
         * @brief Compares \ref Utf8 with std::string_view.
         * @param rhs string to compare with.
         * @return \c true in case both strings are equal.
         */
        bool equals(std::string_view rhs) const noexcept;

    private:
        std::string m_utf8{};
        std::size_t m_codePointSize{};
};

/**
 * @brief Compares two \ref Utf8 instances.
 * @param lhs first string to compare with.
 * @param rhs second string to compare with.
 * @return \c true in case both strings are equal.
 *
 * @ingroup Utils
 */
bool DFL_UTILS_EXPIMP operator==(const Utf8& lhs, const Utf8& rhs) noexcept;

/**
 * @brief Compares std::string_view with \ref Utf8.
 * @param lhs first string to compare with.
 * @param rhs second string to compare with.
 * @return \c true in case both strings are equal.
 *
 * @ingroup Utils
 */
bool DFL_UTILS_EXPIMP operator==(std::string_view lhs,
                                 const Utf8& rhs) noexcept;

/**
 * @brief Compares \ref Utf8 with std::string_view.
 * @param lhs first string to compare with.
 * @param rhs second string to compare with.
 * @return \c true in case both strings are equal.
 *
 * @ingroup Utils
 */
bool DFL_UTILS_EXPIMP operator==(const Utf8& lhs,
                                 std::string_view rhs) noexcept;

/**
 * @brief Compares two \ref Utf8 instances.
 * @param lhs first string to compare with.
 * @param rhs second string to compare with.
 * @return \c true in case both strings differ.
 *
 * @ingroup Utils
 */
bool DFL_UTILS_EXPIMP operator!=(const Utf8& lhs, const Utf8& rhs) noexcept;

/**
 * @brief Compares std::string_view with \ref Utf8.
 * @param lhs first string to compare with.
 * @param rhs second string to compare with.
 * @return \c true in case both strings differ.
 *
 * @ingroup Utils
 */
bool DFL_UTILS_EXPIMP operator!=(std::string_view lhs,
                                 const Utf8& rhs) noexcept;

/**
 * @brief Compares \ref Utf8 with std::string_view.
 * @param lhs first string to compare with.
 * @param rhs second string to compare with.
 * @return \c true in case both strings differ.
 *
 * @ingroup Utils
 */
bool DFL_UTILS_EXPIMP operator!=(const Utf8& lhs,
                                 std::string_view rhs) noexcept;

/**
 * @brief Compares two \ref Utf8 instances.
 * @param lhs first string to compare with.
 * @param rhs second string to compare with.
 * @return \c true in first string is lesser then second string
 *
 * @ingroup Utils
 */
bool operator<(const Utf8& lhs, const Utf8& rhs) noexcept;

/**
 * @brief Compares two \ref Utf8 instances.
 * @param lhs first string to compare with.
 * @param rhs second string to compare with.
 * @return \c true in first string is lesser or equal then second string
 *
 * @ingroup Utils
 */
bool operator<=(const Utf8& lhs, const Utf8& rhs) noexcept;

/**
 * @brief Compares two \ref Utf8 instances.
 * @param lhs first string to compare with.
 * @param rhs second string to compare with.
 * @return \c true in first string is greater then second string
 *
 * @ingroup Utils
 */
bool operator>(const Utf8& lhs, const Utf8& rhs) noexcept;

/**
 * @brief Compares two \ref Utf8 instances.
 * @param lhs first string to compare with.
 * @param rhs second string to compare with.
 * @return \c true in first string is greater then second string
 *
 * @ingroup Utils
 */
bool operator>=(const Utf8& lhs, const Utf8& rhs) noexcept;


/**
 * @brief Concatenate two \ref Utf8 string.
 * @param lhs first string to concatenate.
 * @param rhs second string to concatenate.
 * @return Concatenated string.
 *
 * @ingroup Utils
 */
Utf8 DFL_UTILS_EXPIMP operator+(const Utf8& lhs, const Utf8& rhs);


// Due to performance reasons all const/read/compare/... methods (except
// constructors) are inline.

inline Utf8& Utf8::operator +=(const Utf8& rhs)
{
    m_utf8.append(rhs.value());
    m_codePointSize += rhs.m_codePointSize;
    return *this;
}

inline Utf8 operator +(const Utf8& lhs, const Utf8& rhs)
{
    Utf8 txt = lhs;
    txt += rhs;
    return txt;
}

inline const std::string& Utf8::value() const noexcept
{
    return m_utf8;
}

inline Utf8::operator std::string() const
{
    return m_utf8;
}

inline bool Utf8::empty() const noexcept
{
    return m_utf8.empty();
}

inline std::size_t Utf8::codePointSize() const noexcept
{
    return m_codePointSize;
}

inline bool Utf8::equals(const Utf8& rhs) const noexcept
{
    return m_utf8 == rhs.m_utf8;
}

inline void Utf8::clear() noexcept
{
    m_utf8.clear();
    m_codePointSize = 0U;
}

inline bool Utf8::equals(std::string_view rhs) const noexcept
{
    return m_utf8 == rhs;
}

inline bool operator ==(const Utf8& lhs, const Utf8& rhs) noexcept
{
    return lhs.equals(rhs);
}

inline bool operator==(std::string_view lhs, const Utf8& rhs) noexcept
{
    return rhs.equals(lhs);
}

inline bool operator==(const Utf8& lhs, std::string_view rhs) noexcept
{
    return lhs.equals(rhs);
}

inline bool operator !=(const Utf8& lhs, const Utf8& rhs) noexcept
{
    return !(lhs == rhs);
}

inline bool operator!=(const Utf8& lhs, std::string_view rhs) noexcept
{
    return !(lhs == rhs);
}

inline bool operator!=(std::string_view lhs, const Utf8& rhs) noexcept
{
    return !(lhs == rhs);
}

inline bool operator <(const Utf8& lhs, const Utf8& rhs) noexcept
{
    return lhs.value() < rhs.value();
}

inline bool operator <=(const Utf8& lhs, const Utf8& rhs) noexcept
{
    return lhs.value() <= rhs.value();
}

inline bool operator >(const Utf8& lhs, const Utf8& rhs) noexcept
{
    return lhs.value() > rhs.value();
}

inline bool operator >=(const Utf8& lhs, const Utf8& rhs) noexcept
{
    return lhs.value() >= rhs.value();
}

}
