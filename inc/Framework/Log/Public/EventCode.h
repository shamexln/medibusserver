#pragma once

#include <Framework/Log/Private/ExpImp.h>

#include <cstdint>

namespace DFL
{
namespace Log
{
/**
 * @brief A code which refers to an event that can be retrieved from a database.
 *
 * In that database much more information is stored which otherwise would not
 * fit into a log message.
 *
 * @ingroup Log
 */
class DFL_LOG_EXPIMP EventCode
{
public:
    /**
     * @brief Type in which event code value is stored.
     */
    using NativeType = std::uint32_t;
    /**
     * @brief Constructs an event code with the value 0.
     */
    EventCode() = default;
    /**
     * @brief Constructs an event code from a native value.
     */
    explicit EventCode(NativeType codeValue);
    /**
     * @brief Accessor for the stored event code.
     */
    NativeType value() const;

private:
    NativeType m_value{};
};
/**
 * @brief Returns true if this and other hold the same values otherwise
 * false.
 *
 * @ingroup Log
 */
DFL_LOG_EXPIMP bool operator==(const EventCode& a, const EventCode& b) noexcept;
/**
 * @brief Returns true if this and other hold differents values otherwise
 * false.
 *
 * @ingroup Log
 */
DFL_LOG_EXPIMP bool operator!=(const EventCode& a, const EventCode& b) noexcept;
}
}
