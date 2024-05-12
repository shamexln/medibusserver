#pragma once

#include <Framework/Global/Private/ExpImp.h>

#include <Framework/Config/Public/Attributes.h>

#include <cstddef>
#include <cstdint>

DFL_HEADER_DEPRECATED("use Utils.Kind instead")

/**
 * @brief Holds the value of a component kind.
 * @deprecated Use DFL::Component::Kind instead.
 * @ingroup Global
 */
class DFL_GLOBAL_EXPIMP DFL_ATTRIBUTE_DEPRECATED("use DFL::Component::Kind instead") ComponentKind
{
public:
    /**
     * @brief Defines limits and size of kind values.
     */
    using BitNumbers = enum
    {
        ComponentBitAmount = 10, /**< Amount of bits for kind value */
        MaxValue = (1U << ComponentBitAmount) - 1 /**< Maximal value of a component kind. */
    };

    ComponentKind() = default;

    /**
     * @brief Constructs a component kind
     * @param componentPart Uniquely represents the value of a component kind.
     */
    ComponentKind(uint16_t componentPart);

    /**
     * @brief Relational operators
     * @{
     */
    inline bool operator==(const ComponentKind& right) const;
    inline bool operator!=(const ComponentKind& right) const;
    inline bool operator<(const ComponentKind& right) const;
    inline bool operator>(const ComponentKind& right) const;
    inline bool operator<=(const ComponentKind& right) const;
    inline bool operator>=(const ComponentKind& right) const;
    /** @} */

    /**
     * @return Kind value.
     */
    inline uint16_t getInternal() const;

    /**
     * @return A textual representation
     * @param aBuffer Pointer to a buffer that will contain the textual representation
     * @param aBufferLen Size of aBuffer
     */
    char* toString(char* aBuffer, size_t aBufferLen) const;

private:
    uint16_t m_value{0U};
};

inline bool ComponentKind::operator==(const ComponentKind& right) const
{
    return (m_value == right.m_value);
}

inline bool ComponentKind::operator!=(const ComponentKind& right) const
{
    return (m_value != right.m_value);
}

inline bool ComponentKind::operator<(const ComponentKind& right) const
{
    return (m_value < right.m_value);
}

inline bool ComponentKind::operator>(const ComponentKind& right) const
{
    return (m_value > right.m_value);
}

inline bool ComponentKind::operator<=(const ComponentKind& right) const
{
    return (m_value <= right.m_value);
}

inline bool ComponentKind::operator>=(const ComponentKind& right) const
{
    return (m_value >= right.m_value);
}

inline uint16_t ComponentKind::getInternal() const
{
    return m_value;
}
