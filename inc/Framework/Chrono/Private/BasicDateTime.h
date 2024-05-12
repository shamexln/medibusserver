#pragma once

#include <Framework/Chrono/Private/LibImpl.h>

#include <string>

namespace DFL
{
namespace Chrono
{
namespace Impl
{
template <typename T>
class BasicDateTime
{
public:
    BasicDateTime() = default;
    BasicDateTime(int year,
                  int month,
                  int day,
                  int hour,
                  int minute,
                  Seconds::rep second);
    int year() const;
    int month() const;
    int day() const;
    int hour() const;
    int minute() const;
    Seconds::rep second() const;
    std::string toIso8601() const;
    bool equals(const BasicDateTime<T>& other) const noexcept;

private:
    int m_year{};
    int m_month{};
    int m_day{};
    int m_hour{};
    int m_minute{};
    Seconds::rep m_second{0};
};

template <typename T>
inline bool operator==(const BasicDateTime<T>& lhs,
                       const BasicDateTime<T>& rhs) noexcept
{
    return lhs.equals(rhs);
}

template <typename T>
inline bool operator!=(const BasicDateTime<T>& lhs,
                       const BasicDateTime<T>& rhs) noexcept
{
    return !(lhs == rhs);
}

struct UtcDateTimeTag
{
};
struct LocalDateTimeTag
{
};

using UtcDateTime = BasicDateTime<UtcDateTimeTag>;
using LocalDateTime = BasicDateTime<LocalDateTimeTag>;
}
}
}
