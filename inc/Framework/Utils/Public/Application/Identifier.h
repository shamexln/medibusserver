#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <Framework/Utils/Public/Application/SoftwareVersionNumber.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <string>

namespace DFL
{
namespace Application
{
/**
 * @brief Tag type for MaterialNumber.
 *
 * @ingroup Utils
 */
struct MaterialNumberTag;
/**
 * @brief Tag type for SerialNumber.
 *
 * @ingroup Utils
 */
struct SerialNumberTag;
/**
 * @brief Represents a material number.
 *
 * @ingroup Utils
 */
using MaterialNumber = DFL::StrongTypedef<std::string,
                                          MaterialNumberTag,
                                          DFL::Skill::EqualityComparable,
                                          DFL::Skill::Streamable>;
/**
 * @brief Represents a serial number.
 *
 * @ingroup Utils
 */
using SerialNumber = DFL::StrongTypedef<std::string,
                                        SerialNumberTag,
                                        DFL::Skill::EqualityComparable,
                                        DFL::Skill::Streamable>;
/**
 * @brief Represents an application identifier.
 *
 * @ingroup Utils
 */
class DFL_UTILS_EXPIMP Identifier
{
public:
    /**
     * @brief Creates an empty application identifier.
     *
     * @snippet Utils/Test/UnitTest/TestIdentifier.cpp defaultCtor
     */
    Identifier() = default;
    /**
     * @brief Creates an application identifier from the given parameters.
     *
     * @snippet Utils/Test/UnitTest/TestIdentifier.cpp fullCtor
     */
    Identifier(MaterialNumber material,
               SerialNumber serial,
               SoftwareVersionNumber softwareVersion);
    /**
     * @brief Returns the material number.
     *
     * @snippet Utils/Test/UnitTest/TestIdentifier.cpp fullCtor
     */
    const MaterialNumber& materialNumber() const noexcept;
    /**
     * @brief Returns the serial number.
     *
     * @snippet Utils/Test/UnitTest/TestIdentifier.cpp fullCtor
     */
    const SerialNumber& serialNumber() const noexcept;
    /**
     * @brief Returns the software version number.
     *
     * @snippet Utils/Test/UnitTest/TestIdentifier.cpp fullCtor
     */
    const SoftwareVersionNumber& softwareVersionNumber() const noexcept;
    /**
     * @brief Exchanges the contents of application identifier with those of
     * other.
     *
     * @snippet Utils/Test/UnitTest/TestIdentifier.cpp swap
     */
    void swap(Identifier& other) noexcept;

private:
    MaterialNumber m_materialNumber{""};
    SerialNumber m_serialNumber{""};
    SoftwareVersionNumber m_softwareVersionNumber{};
};
/**
 * @brief Compares two application identifier.
 *
 * @snippet Utils/Test/UnitTest/TestIdentifier.cpp equalityComparable
 *
 * @ingroup Utils
 * @{
 */
DFL_UTILS_EXPIMP bool operator==(const Identifier& lhs,
                                 const Identifier& rhs) noexcept;
DFL_UTILS_EXPIMP bool operator!=(const Identifier& lhs,
                                 const Identifier& rhs) noexcept;
/** @} */
/**
 * @brief Exchanges the given application identifier.
 *
 * @snippet Utils/Test/UnitTest/TestIdentifier.cpp swap
 *
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP void swap(Identifier& a, Identifier& b) noexcept;
}
}
