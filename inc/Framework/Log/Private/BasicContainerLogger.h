#pragma once

#include <utility>

namespace DFL
{
namespace Log
{
namespace Impl
{
/**
 * @brief Logs messages into a container.
 *
 * Stored messages can be accessed via iterators.
 *
 * @ingroup Log
 */
template <class T>
class BasicContainerLogger
{
protected:
    /**
     * @brief Type of the internal container.
     */
    using Type = T;

public:
    /**
     * @brief Types for supporting the const container concept.
     * @{
     */
    using value_type = typename Type::value_type;
    using const_reference = typename Type::const_reference;
    using reference = typename Type::reference;
    using const_iterator = typename Type::const_iterator;
    using iterator = typename Type::iterator;
    using const_reverse_iterator = typename Type::const_reverse_iterator;
    using reverse_iterator = typename Type::reverse_iterator;
    using difference_type = typename Type::difference_type;
    using size_type = typename Type::size_type;
    /** @} */

    /**
     * @brief Constructs an empty container logger.
     */
    BasicContainerLogger() = default;
    /**
     * @brief
     * Constructs the container logger with the contents of the range
     * [first, last).
     */
    template <class InputIt>
    BasicContainerLogger(InputIt first, InputIt last);

    /**
     * @brief Stores given message into container.
     *
     * @param message Message to be stored.
     * @return Given message.
     */
    value_type operator()(const_reference message);
    /**
     * @brief Returns true if empty otherwise false.
     */
    bool empty() const noexcept;
    /**
     * @brief Returns number of messages.
     */
    size_type size() const noexcept;
    /**
     * @brief Returns maximum number of messages.
     */
    size_type max_size() const noexcept;
    /**
     * @brief Returns const iterator pointing to the first message.
     */
    const_iterator cbegin() const noexcept;
    /**
     * @brief Returns const iterator pointing to the first message.
     */
    const_iterator begin() const noexcept;
    /**
     * @brief Returns const reverse iterator pointing to the last message.
     */
    const_reverse_iterator rbegin() const noexcept;
    /**
     * @brief Returns const iterator pointing behind the last message.
     */
    const_iterator cend() const noexcept;
    /**
     * @brief Returns const iterator pointing behind the last message.
     */
    const_iterator end() const noexcept;
    /**
     * @brief Returns const reverse iterator pointing before the first message.
     */
    const_reverse_iterator rend() const noexcept;
    /**
     * @brief Clears all messages.
     */
    void clear();
    /**
     * @brief
     * Exchanges the contents of the container logger with those of other.
     */
    void swap(BasicContainerLogger& other) noexcept;
    /**
     * @brief Compares the container logger with other.
     */
    bool equals(const BasicContainerLogger& other) const noexcept;

protected:
    /**
     * @brief Holds all messages.
     */
    Type m_messages{};
};

/**
 * @brief Compares the contents of two container loggers.
 *
 * @ingroup Log
 * @{
 */
template <class T>
inline bool operator==(const BasicContainerLogger<T>& lhs,
                       const BasicContainerLogger<T>& rhs) noexcept
{
    return lhs.equals(rhs);
}
template <class T>
inline bool operator!=(const BasicContainerLogger<T>& lhs,
                       const BasicContainerLogger<T>& rhs) noexcept
{
    return !(lhs == rhs);
}
/** @} */
/**
 * @brief Exchanges the contents of the given container loggers.
 *
 * @ingroup Log
 */
template <class T>
inline void swap(BasicContainerLogger<T>& a,
                 BasicContainerLogger<T>& b) noexcept
{
    a.swap(b);
}

template <class T>
template <class InputIt>
inline BasicContainerLogger<T>::BasicContainerLogger(InputIt first,
                                                     InputIt last)
    : m_messages(first, last)
{
}

template <class T>
inline typename BasicContainerLogger<T>::value_type BasicContainerLogger<
    T>::operator()(const_reference message)
{
    m_messages.push_back(message);
    return message;
}

template <class T>
inline bool BasicContainerLogger<T>::empty() const noexcept
{
    return m_messages.empty();
}

template <class T>
inline typename BasicContainerLogger<T>::size_type BasicContainerLogger<
    T>::size() const noexcept
{
    return m_messages.size();
}

template <class T>
inline typename BasicContainerLogger<T>::size_type BasicContainerLogger<
    T>::max_size() const noexcept
{
    return m_messages.max_size();
}

template <class T>
inline typename BasicContainerLogger<T>::const_iterator BasicContainerLogger<
    T>::cbegin() const noexcept
{
    return m_messages.begin();
}

template <class T>
inline typename BasicContainerLogger<T>::const_iterator BasicContainerLogger<
    T>::begin() const noexcept
{
    return m_messages.begin();
}

template <class T>
inline typename BasicContainerLogger<T>::const_reverse_iterator
BasicContainerLogger<T>::rbegin() const noexcept
{
    return m_messages.rbegin();
}

template <class T>
inline typename BasicContainerLogger<T>::const_iterator BasicContainerLogger<
    T>::cend() const noexcept
{
    return m_messages.end();
}

template <class T>
inline typename BasicContainerLogger<T>::const_iterator BasicContainerLogger<
    T>::end() const noexcept
{
    return m_messages.end();
}

template <class T>
inline typename BasicContainerLogger<T>::const_reverse_iterator
BasicContainerLogger<T>::rend() const noexcept
{
    return m_messages.rend();
}

template <class T>
inline void BasicContainerLogger<T>::clear()
{
    return m_messages.clear();
}

template <class T>
inline void BasicContainerLogger<T>::swap(BasicContainerLogger& other) noexcept
{
    using std::swap;
    swap(m_messages, other.m_messages);
}

template <class T>
inline bool BasicContainerLogger<T>::equals(
    const BasicContainerLogger& other) const noexcept
{
    return m_messages == other.m_messages;
}
}
}
}
