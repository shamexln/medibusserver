#pragma once

#include <algorithm>
#include <string>
#include <string_view>

namespace S31
{

/**
 * @brief Null terminated string view.
 * @details
 * This class is similar to \c std::string_view, except that is guarantees to be a null terminated string view.
 * Very often there are some constants in %S31 that are null terminated strings. In some places \c std::string is used
 * with heap allocation and in other places <tt>const char*</tt> is used.
 * This string view class allows to use \c constexpr and has string_view like equality operator for example for easy
 * usage of the constant.
 */
class NtStringView
{
public:
    using size_type = std::size_t;
    using const_iterator = std::string_view::const_iterator;

    /**
     * @brief Call only with valid null terminated strings only (contract).
     */
    constexpr explicit NtStringView(const char* string);

    constexpr const char* c_str() const noexcept;
    constexpr const char* data() const noexcept;

    constexpr size_type size() const noexcept;

    constexpr bool empty() const noexcept;

    /**
     * @brief Skipping some characters preserve the null termination.
     */
    constexpr NtStringView substr(size_type pos) const;

    /**
     * @brief Extracting a substring cannot preserve the null termination.
     */
    constexpr std::string_view substr(size_type pos, size_type count) const;

    constexpr std::string_view string_view() const noexcept;

    // NOLINTNEXTLINE(google-explicit-constructor)
    constexpr /* implicit */ operator std::string_view() const noexcept;

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    // no null pointer are allowed
    explicit NtStringView(std::nullptr_t)   = delete;
    NtStringView& operator=(std::nullptr_t) = delete;
    explicit NtStringView(int)              = delete;
    NtStringView& operator=(int)            = delete;

private:
    std::string_view m_stringView;
};

bool operator==(NtStringView lhs, NtStringView rhs) noexcept;
bool operator!=(NtStringView lhs, NtStringView rhs) noexcept;
bool operator<(NtStringView lhs, NtStringView rhs) noexcept;


bool operator==(NtStringView lhs, std::string_view rhs) noexcept;
bool operator!=(NtStringView lhs, std::string_view rhs) noexcept;
bool operator<(NtStringView lhs, std::string_view rhs) noexcept;

bool operator==(std::string_view lhs, NtStringView rhs) noexcept;
bool operator!=(std::string_view lhs, NtStringView rhs) noexcept;
bool operator<(std::string_view lhs, NtStringView rhs) noexcept;

std::string operator+(const std::string& lhs, NtStringView rhs);
std::string operator+(NtStringView lhs, const std::string& rhs);

bool operator==(const char* lhs, NtStringView rhs) noexcept;
bool operator!=(const char* lhs, NtStringView rhs) noexcept;
bool operator<(const char* lhs, NtStringView rhs) noexcept;

bool operator==(NtStringView lhs, const char* rhs) noexcept;
bool operator!=(NtStringView lhs, const char* rhs) noexcept;
bool operator<(NtStringView lhs, const char* rhs) noexcept;

// ----- implementation -----

inline constexpr NtStringView::NtStringView(const char* string)
    : m_stringView{string}
{
}

inline constexpr const char* NtStringView::c_str() const noexcept
{
    return m_stringView.data();
}

inline constexpr const char* NtStringView::data() const noexcept
{
    return m_stringView.data();
}

inline constexpr NtStringView::size_type NtStringView::size() const noexcept
{
    return m_stringView.size();
}

inline constexpr bool NtStringView::empty() const noexcept
{
    return m_stringView.empty();
}

inline constexpr NtStringView NtStringView::substr(size_type pos) const
{
    return NtStringView{m_stringView.substr((std::min)(pos, m_stringView.size())).data()};
}

inline constexpr std::string_view NtStringView::substr(size_type pos, size_type count) const
{
    return m_stringView.substr((std::min)(pos, m_stringView.size()), count);
}

inline constexpr std::string_view NtStringView::string_view() const noexcept
{
    return m_stringView;
}

inline constexpr NtStringView::operator std::string_view() const noexcept
{
    return m_stringView;
}

inline bool operator==(NtStringView lhs, NtStringView rhs) noexcept
{
    return lhs.string_view() == rhs.string_view();
}

inline bool operator!=(NtStringView lhs, NtStringView rhs) noexcept
{
    return !(lhs == rhs);
}

inline bool operator<(NtStringView lhs, NtStringView rhs) noexcept
{
    return lhs.string_view() < rhs.string_view();
}

inline bool operator==(NtStringView lhs, std::string_view rhs) noexcept
{
    return lhs.string_view() == rhs;
}

inline bool operator!=(NtStringView lhs, std::string_view rhs) noexcept
{
    return !(lhs == rhs);
}

inline bool operator<(NtStringView lhs, std::string_view rhs) noexcept
{
    return lhs.string_view() < rhs;
}

inline bool operator==(std::string_view lhs, NtStringView rhs) noexcept
{
    return lhs == rhs.string_view();
}

inline bool operator!=(std::string_view lhs, NtStringView rhs) noexcept
{
    return !(lhs == rhs);
}

inline bool operator<(std::string_view lhs, NtStringView rhs) noexcept
{
    return lhs < rhs.string_view();
}

inline bool operator==(const char* lhs, NtStringView rhs) noexcept
{
    return lhs && std::string_view{lhs} == rhs.string_view();
}

inline bool operator!=(const char* lhs, NtStringView rhs) noexcept
{
    return !(lhs == rhs);
}

inline bool operator<(const char* lhs, NtStringView rhs) noexcept
{
    return !lhs || lhs < rhs.string_view();
}

inline bool operator==(NtStringView lhs, const char* rhs) noexcept
{
    return rhs && lhs.string_view() == std::string_view{rhs};
}

inline bool operator!=(NtStringView lhs, const char* rhs) noexcept
{
    return !(lhs == rhs);
}

inline bool operator<(NtStringView lhs, const char* rhs) noexcept
{
    return rhs && lhs.string_view() < std::string_view{rhs};
}

inline std::string operator+(const std::string& lhs, NtStringView rhs)
{
    std::string result;
    result.reserve(lhs.size() + rhs.size());
    result.append(lhs);
    result.append(rhs.string_view());
    return result;
}

inline std::string operator+(NtStringView lhs, const std::string& rhs)
{
    std::string result;
    result.reserve(lhs.size() + rhs.size());
    result.append(lhs.string_view());
    result.append(rhs);
    return result;
}

inline NtStringView::const_iterator NtStringView::begin() const noexcept
{
    return m_stringView.begin();
}

inline NtStringView::const_iterator NtStringView::end() const noexcept
{
    return m_stringView.end();
}
}  // namespace S31
