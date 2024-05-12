#pragma once

#include <memory>

namespace DFL
{
namespace Observer
{
/**
 * @brief Interface for generic observable container.
 *
 * @tparam ObserverType
 * Type of the interface implemented by the concrete observers.
 *
 * @ingroup Utils
 */
template <class ObserverType>
class Subject
{
public:
    virtual ~Subject() = default;
    Subject& operator=(Subject&&) = delete;
    /**
     * @brief Add observer to list.
     */
    virtual void registerObserver(
        const std::weak_ptr<ObserverType>& observer) = 0;
    /**
     * @brief Remove observer from list.
     */
    virtual void unregisterObserver(
        const std::weak_ptr<ObserverType>& observer) = 0;
};
}
}
