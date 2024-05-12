#pragma once

#include <Framework/Format/Public/Stream.h>

#include <cstdint>
#include <limits>


namespace DFL
{
namespace Mdib
{

/**
 * @brief A version number, e.g., used by %MDIB version or as referenced version.
 * @ingroup Mdib
 */
class VersionCounter
{
    public:
        /**
         * @brief Internal version type
         */
        using VersionType = uint64_t;

        /**
         * @brief Default constructor for VersionCounter
         */
        VersionCounter() = default;
        /**
         * @brief constructor for initializing VersionCounter with proper value
         * @param val VersionType value for initializing VersionCounter
         */
        explicit VersionCounter(const VersionCounter::VersionType& val);

        /**
         * @brief Allows to pre-increment \ref VersionCounter.
         * @return pre-incremented VersionCounter
         */
        VersionCounter operator++();

        /**
         * @brief Allows to post-increment \ref VersionCounter.
         * @return post-incremented VersionCounter
         */
        VersionCounter operator++(int);

        /**
         * @brief returns the value it is holding
         * @return VersionType representation of versionCounter
         */
        VersionType get() const noexcept;

        /**
         * @brief Maximal VersionCounter
         */
        static VersionCounter maximum();

    private:
        VersionType m_versionCounter{0};

};

inline VersionCounter::VersionCounter(const VersionCounter::VersionType& val) :
        m_versionCounter(val)
{
}

inline VersionCounter::VersionType VersionCounter::get() const noexcept
{
    return m_versionCounter;
}

inline VersionCounter VersionCounter::maximum()
{
    return VersionCounter((std::numeric_limits<VersionCounter::VersionType>::max)());
}

inline VersionCounter VersionCounter::operator++()
{
    ++m_versionCounter;
    return *this;
}

inline VersionCounter VersionCounter::operator++(int)
{
    const VersionCounter::VersionType temp = m_versionCounter;
    ++m_versionCounter;
    return VersionCounter(temp);
}

/**
 * @brief Allows to compare \ref VersionCounter with another \ref VersionCounter.
 * @param lhs VersionCounter to compare with
 * @param rhs VersionCounter to compare with
 * @return \c true in case the left instance is less than the right one.
 * @ingroup Mdib
 */
inline bool operator<(const VersionCounter lhs, const VersionCounter rhs) noexcept
{
    return lhs.get() < rhs.get();
}

/**
 * @brief Allows to compare \ref VersionCounter with another \ref VersionCounter.
 * @param lhs VersionCounter to compare with
 * @param rhs VersionCounter to compare with
 * @return \c true in case the left instance is greater than the right one.
 * @ingroup Mdib
 */
inline bool operator>(const VersionCounter lhs, const VersionCounter rhs) noexcept
{
    return lhs.get() > rhs.get();
}

/**
 * @brief Allows to compare \ref VersionCounter with another \ref VersionCounter.
 * @param lhs VersionCounter to compare with
 * @param rhs VersionCounter to compare with
 * @return \c true in case the left instance is less or equal to the right one.
 * @ingroup Mdib
 */
inline bool operator<=(const VersionCounter lhs, const VersionCounter rhs) noexcept
{
    return lhs.get() <= rhs.get();
}

/**
 * @brief Allows to compare \ref VersionCounter with another \ref VersionCounter.
 * @param lhs VersionCounter to compare with
 * @param rhs VersionCounter to compare with
 * @return \c true in case the left instance is greater or equal to the right one.
 * @ingroup Mdib
 */
inline bool operator>=(const VersionCounter lhs, const VersionCounter rhs) noexcept
{
    return lhs.get() >= rhs.get();
}

/**
 * @brief Allows to compare \ref VersionCounter with another \ref VersionCounter (EqualityComparable).
 * @param lhs VersionCounter to compare with
 * @param rhs VersionCounter to compare with
 * @return \c true in case the left instance is equal to the right one.
 * @ingroup Mdib
 */
inline bool operator==(const VersionCounter lhs, const VersionCounter rhs) noexcept
{
    return lhs.get() == rhs.get();
}

/**
 * @brief Allows to compare \ref VersionCounter with another \ref VersionCounter (EqualityComparable).
 * @param lhs VersionCounter to compare with
 * @param rhs VersionCounter to compare with
 * @return \c true in case the left instance is not equal to the right one.
 * @ingroup Mdib
 */
inline bool operator!=(const VersionCounter lhs, const VersionCounter rhs) noexcept
{
    return lhs.get() != rhs.get();
}

/**
 * @brief Allows to stream data to given stream.
 * @ingroup Mdib
 */
inline std::ostream& operator<<(std::ostream& str, const VersionCounter& versionCounter)
{
    str << std::to_string(versionCounter.get());
    return str;
}

/**
 * @brief Allows to stream data to given stream.
 * @ingroup Mdib
 */
inline DFL::Format::Stream& operator<<(DFL::Format::Stream& str, const VersionCounter& versionCounter)
{
    str << std::to_string(versionCounter.get());
    return str;
}

/**
 * @brief Allows to compare unsigned long long with \ref VersionCounter
 * @ingroup Mdib
 */
inline bool operator==(unsigned long long lhs, const VersionCounter& versionCounter)
{
    return lhs == versionCounter.get();
}

/**
 * @brief Allows to compare unsigned long long with \ref VersionCounter
 * @ingroup Mdib
 */
inline bool operator!=(unsigned long long lhs, const VersionCounter& versionCounter)
{
    return lhs != versionCounter.get();
}

/**
 * @brief Allows to compare \ref VersionCounter with unsigned long long
 * @ingroup Mdib
 */
inline bool operator==(const VersionCounter& versionCounter, unsigned long long rhs)
{
    return versionCounter.get() == rhs;
}

/**
 * @brief Allows to compare \ref VersionCounter with unsigned long long
 * @ingroup Mdib
 */
inline bool operator!=(const VersionCounter& versionCounter, unsigned long long rhs)
{
    return versionCounter.get() != rhs;
}

/**
 * @brief Allows to increment version with a given value.
 * @ingroup Mdib
 */
inline VersionCounter operator+(const VersionCounter& versionCounter, unsigned int increment)
{
    return VersionCounter(versionCounter.get() + increment);
}

/**
 * @brief Allows to compare unsigned long long with \ref VersionCounter
 * @ingroup Mdib
 */
inline bool operator<(unsigned long long lhs, const VersionCounter& versionCounter)
{
    return lhs < versionCounter.get();
}

/**
 * @brief Allows to compare unsigned long long with \ref VersionCounter
 * @ingroup Mdib
 */
inline bool operator>(unsigned long long lhs, const VersionCounter& versionCounter)
{
    return lhs > versionCounter.get();
}

}
}
