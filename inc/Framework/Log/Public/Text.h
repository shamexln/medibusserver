#pragma once

#include <Framework/Log/Private/ExpImp.h>

#include <string>

namespace DFL
{
namespace Log
{
/**
 * @brief Holds text to be logged.
 *
 * @ingroup Log
 */
class DFL_LOG_EXPIMP Text
{
public:
    /**
     * @brief Constructs a empty text.
     */
    Text() = default;
    /**
     * @brief Constructs a text object from given string.
     */
    explicit Text(std::string txt);
    /**
     * @brief Returns null terminated pointer to internal text.
     */
    const char* cStr() const;
    /**
     * @brief Returns text as string.
     */
    const std::string& str() const;
    /**
     * @brief Returns true if this and other hold the same text, otherwise
     * false.
     */
    bool equals(const Text& other) const noexcept;
    /**
     * @brief Swaps content of given text with this.
     */
    void swap(Text& other) noexcept;

private:
    std::string m_buffer{};
};
/**
 * @brief Returns true if both hold the same text, otherwise
 *
 * @ingroup Log
 */
DFL_LOG_EXPIMP bool operator==(const Text& a, const Text& b) noexcept;
/**
 * @brief Returns true if both hold different text, otherwise
 *
 * @ingroup Log
 */
DFL_LOG_EXPIMP bool operator!=(const Text& a, const Text& b) noexcept;
/**
 * @brief Swaps content of given texts.
 *
 * @ingroup Log
 */
DFL_LOG_EXPIMP void swap(Text& a, Text& b) noexcept;
}
}
