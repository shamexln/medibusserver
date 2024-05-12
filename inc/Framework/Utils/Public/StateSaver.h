#pragma once

#include <functional>
#include <utility>

namespace DFL
{
/**
 * @brief
 * Saves state of given object when constructed and restores this state when
 * destructed.
 *
 * @tparam T Has to fulfill the concepts CopyConstructible and CopyAssignable.
 *
 * @ingroup Utils
 */
template <class T>
class StateSaver
{
public:
    /**
     * @brief Type of setter function.
     */
    using SetterFunc = std::function<void(const T&)>;

    /**
     * @brief Saves state of given object.
     *
     * @snippet Utils/Test/UnitTest/TestStateSaver.cpp saveRestoreByRef
     */
    explicit StateSaver(T& t)
        : m_saved{t}
        , m_setter{[&t](const T& t2) { t = t2; }}
    {
    }
    /**
     * @brief Saves state of given object.
     *
     * The given setter will be used for restoring.
     *
     * @snippet Utils/Test/UnitTest/TestStateSaver.cpp saveRestoreBySetter
     */
    explicit StateSaver(T t, SetterFunc setter)
        : m_saved{std::move(t)}
        , m_setter{std::move(setter)}
    {
    }
    StateSaver(const StateSaver&) = delete;
    StateSaver& operator=(const StateSaver&) = delete;
    /**
     * @brief Restores state of given object.
     */
    ~StateSaver()
    {
        try
        {
            m_setter(m_saved);
        }
        catch (...)
        {
        }
    }
    /**
     * @brief Returns saved object.
     */
    const T& saved() const
    {
        return m_saved;
    }

private:
    T m_saved;
    SetterFunc m_setter;
};
}
