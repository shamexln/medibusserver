#pragma once

#include <S31/Sdc/Public/Common/MetadataVersion.h>

#include <Framework/Format/Public/Stream.h>

#include <atomic>
#include <cstdint>

namespace S31::Sdc::Impl
{

/**
 * @brief MetadataVersion class for atomic use.
 * @details This class provides a wrapper for an atomic (32 bit) unsigned int while exposing the Strong Typedef @ref
 * S31::Sdc::MetadataVersion to the outside. Additionally, it restricts operations on the underlying data to those that
 * are sensible for metadata versions, e.g. it does not allow decrementing.
 * @ingroup S31SdcCommon
 */
class AtomicMetadataVersion
{
public:
    AtomicMetadataVersion() = default;

    explicit AtomicMetadataVersion(MetadataVersion val);

    ~AtomicMetadataVersion() = default;

    AtomicMetadataVersion(const AtomicMetadataVersion&)            = delete;
    AtomicMetadataVersion& operator=(const AtomicMetadataVersion&) = delete;
    AtomicMetadataVersion(AtomicMetadataVersion&&)                 = delete;
    AtomicMetadataVersion& operator=(AtomicMetadataVersion&&)      = delete;

    AtomicMetadataVersion& operator++();
    MetadataVersion operator++(int);

    MetadataVersion get() const noexcept;

private:
    std::atomic_uint32_t m_metadataVersion;
};

inline AtomicMetadataVersion::AtomicMetadataVersion(MetadataVersion val)
    : m_metadataVersion{val.get()}
{
}

inline MetadataVersion AtomicMetadataVersion::get() const noexcept
{
    return MetadataVersion{m_metadataVersion.load()};
}

inline AtomicMetadataVersion& AtomicMetadataVersion::operator++()
{
    ++m_metadataVersion;
    return *this;
}

inline MetadataVersion AtomicMetadataVersion::operator++(int)
{
    return MetadataVersion{m_metadataVersion++};
}

/**
 * @brief Allows to compare \ref AtomicMetadataVersion with another \ref AtomicMetadataVersion.
 * @param lhs AtomicMetadataVersion to compare with
 * @param rhs AtomicMetadataVersion to compare with
 */
inline bool operator<(const AtomicMetadataVersion& lhs, const AtomicMetadataVersion& rhs) noexcept
{
    return lhs.get() < rhs.get();
}

/**
 * @brief Allows to compare \ref AtomicMetadataVersion with another \ref AtomicMetadataVersion.
* @param lhs AtomicMetadataVersion to compare with
* @param rhs AtomicMetadataVersion to compare with
 */
inline bool operator>(const AtomicMetadataVersion& lhs, const AtomicMetadataVersion& rhs) noexcept
{
    return lhs.get() > rhs.get();
}

/**
 * @brief Allows to compare \ref AtomicMetadataVersion with another \ref AtomicMetadataVersion.
* @param lhs AtomicMetadataVersion to compare with
* @param rhs AtomicMetadataVersion to compare with
 */
inline bool operator<=(const AtomicMetadataVersion& lhs, const AtomicMetadataVersion& rhs) noexcept
{
    return lhs.get() <= rhs.get();
}

/**
 * @brief Allows to compare \ref AtomicMetadataVersion with another \ref AtomicMetadataVersion.
* @param lhs AtomicMetadataVersion to compare with
* @param rhs AtomicMetadataVersion to compare with
 */
inline bool operator>=(const AtomicMetadataVersion& lhs, const AtomicMetadataVersion& rhs) noexcept
{
    return lhs.get() >= rhs.get();
}

/**
 * @brief Allows to compare \ref AtomicMetadataVersion with another \ref AtomicMetadataVersion (EqualityComparable).
* @param lhs AtomicMetadataVersion to compare with
* @param rhs AtomicMetadataVersion to compare with
 */
inline bool operator==(const AtomicMetadataVersion& lhs, const AtomicMetadataVersion& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

/**
 * @brief Allows to compare \ref AtomicMetadataVersion with another \ref AtomicMetadataVersion (EqualityComparable).
* @param lhs AtomicMetadataVersion to compare with
* @param rhs AtomicMetadataVersion to compare with
 */
inline bool operator!=(const AtomicMetadataVersion& lhs, const AtomicMetadataVersion& rhs) noexcept
{
    return lhs.get() != rhs.get();
}

/**
 * @brief Allows to stream data to given stream.
 * @ingroup S31SdcCommon
 */
inline std::ostream& operator<<(std::ostream& str, const AtomicMetadataVersion& metadataVersion)
{
    str << metadataVersion.get();
    return str;
}

/**
 * @brief Allows to stream data to given stream.
 * @ingroup S31SdcCommon
 */
inline DFL::Format::Stream& operator<<(DFL::Format::Stream& str, const AtomicMetadataVersion& metadataVersion)
{
    str << metadataVersion.get();
    return str;
}

}  // namespace S31::Sdc::Impl
