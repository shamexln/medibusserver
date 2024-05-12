#pragma once

#include <algorithm>
#include <array>
#include <string>
#include <string_view>

namespace S31::Log
{

/**
 * @brief Holds a short text.
 * @details
 * Intended to be used as a return type of functions that need to be @c noexcept and therefore cannot use std::string.
 * The text cannot be modified.
 *
 * Instead of mimicking the interface of a string or a string_view this just provides access to a string_view. So it's
 * called @c ShortText and not @c ShortString.
 *
 * @ingroup S31Log
 */
template<std::size_t Size>
class ShortText
{
public:
    /**
     * @brief Ctor
     * @details
     * For now there is only this ctor taking a string. Naturally others could be
     * defined taking e.g. @c char pointers or @ stringviews if needed.
     *
     * If the given string is too long it will be trucated.
     */
    explicit ShortText(const std::string& s) noexcept:
        m_size((std::min)(s.length(), m_text.size())),
        m_truncated(m_size < s.length())
    {
        std::copy_n(s.begin(), m_size, m_text.begin());
    }

    /**
     * @brief Returns a string view of the text.
     */
    std::string_view view() const noexcept
    {
        return std::string_view(&*m_text.begin(), m_size);
    }

    /**
     * @brief Returns @c true if the initially given string did not fit into the object.
     */
    bool truncated() const noexcept
    {
        return m_truncated;
    }

private:
    std::array<char, Size> m_text{};
    std::string_view::size_type m_size{0};
    bool m_truncated{false};
};




}
