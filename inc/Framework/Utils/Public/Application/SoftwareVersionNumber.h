#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <Framework/Config/Public/UnixUndefMajorMinor.h>

namespace DFL
{
namespace Application
{
namespace Impl
{
struct MajorVersionTag;
struct MinorVersionTag;
struct PatchVersionTag;
}
/**
 * @brief Represents a major version number.
 */
using MajorVersion = DFL::StrongTypedef<unsigned int, Impl::MajorVersionTag,
    DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;
/**
 * @brief Represents a minor version number.
 */
using MinorVersion = DFL::StrongTypedef<unsigned int, Impl::MinorVersionTag,
    DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;
/**
 * @brief Represents a patch version number.
 */
using PatchVersion = DFL::StrongTypedef<unsigned int, Impl::PatchVersionTag,
    DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

/**
 * @brief Represents a software version number.
 * @details Format is MAJOR.MINOR.PATCH (as defined by DCS IN4206).
 * @ingroup Utils
 */
class DFL_UTILS_EXPIMP SoftwareVersionNumber
{
public:
    /**
     * @brief Creates a software version number '0.0.0'.
     *
     * @snippet Utils/Test/UnitTest/TestSoftwareVersionNumber.cpp defaultCtor
     */
    SoftwareVersionNumber() = default;
    /**
     * @brief Creates a software version number from the given parameters.
     *
     * @snippet Utils/Test/UnitTest/TestSoftwareVersionNumber.cpp fullCtor
     */
    SoftwareVersionNumber(MajorVersion majorVersion,
                          MinorVersion minorVersion,
                          PatchVersion patchVersion);
    /**
     * @name Getter for major, minor, patch of version.
     *
     * @snippet Utils/Test/UnitTest/TestSoftwareVersionNumber.cpp fullCtor
     * @{
     */
    const MajorVersion& major() const noexcept;
    const MinorVersion& minor() const noexcept;
    const PatchVersion& patch() const noexcept;
    /** @} */
    /**
     * @brief Exchanges the contents of version number with those of other.
     *
     * @snippet Utils/Test/UnitTest/TestSoftwareVersionNumber.cpp swap
     */
    void swap(SoftwareVersionNumber& other) noexcept;

private:
    MajorVersion m_major{0};
    MinorVersion m_minor{0};
    PatchVersion m_patch{0};
};
/**
 * @brief Compares two version numbers.
 *
 * @snippet Utils/Test/UnitTest/TestSoftwareVersionNumber.cpp equalityComparable
 * @snippet Utils/Test/UnitTest/TestSoftwareVersionNumber.cpp ordering
 *
 * @ingroup Utils
 * @{
 */
DFL_UTILS_EXPIMP bool operator==(
    const SoftwareVersionNumber& lhs,
    const SoftwareVersionNumber& rhs) noexcept;
DFL_UTILS_EXPIMP bool operator!=(
    const SoftwareVersionNumber& lhs,
    const SoftwareVersionNumber& rhs) noexcept;
DFL_UTILS_EXPIMP bool operator<(
    const SoftwareVersionNumber& lhs,
    const SoftwareVersionNumber& rhs) noexcept;
DFL_UTILS_EXPIMP bool operator>(
    const SoftwareVersionNumber& lhs,
    const SoftwareVersionNumber& rhs) noexcept;
DFL_UTILS_EXPIMP bool operator<=(
    const SoftwareVersionNumber& lhs,
    const SoftwareVersionNumber& rhs) noexcept;
DFL_UTILS_EXPIMP bool operator>=(
    const SoftwareVersionNumber& lhs,
    const SoftwareVersionNumber& rhs) noexcept;
/** @} */
/**
 * @brief Exchanges the given version numbers.
 *
 * @snippet Utils/Test/UnitTest/TestSoftwareVersionNumber.cpp swap
 *
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP void swap(SoftwareVersionNumber& a, SoftwareVersionNumber& b) noexcept;
}
}
