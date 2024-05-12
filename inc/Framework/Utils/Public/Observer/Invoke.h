#pragma once

#include <stdexcept>
#include <utility>

namespace DFL
{
namespace Observer
{
/**
 * @brief Catching invoke policy for @ref BasicSubject
 *
 * @details
 * Exception raised by the called code are catched and given to the
 * handler.
 *
 * @tparam ExceptionHandler
 * Has to implement two static functions. One is called with a known exception
 * the other one is called in case of an unknown exception.
 * An example handler, can be found here:
 * @snippet Utils/Sample/Sample.cpp LogExceptionMessage
 *
 * @ingroup Utils
 */
template <class ExceptionHandler>
class InvokeAndCatch
{
public:
    /**
     * @brief Wraps given function in a try-catch block and delegates
     * exceptions to the handler.
     */
    template <class ObserverType, class Func>
    static void invoke(ObserverType&& observer, Func&& func)
    {
        try
        {
            std::forward<Func>(func)(std::forward<ObserverType>(observer));
        }
        catch (const std::exception& e)
        {
            ExceptionHandler::handleException(e);
        }
        catch (...)
        {
            ExceptionHandler::handleUnknownException();
        }
    }
};
/**
 * @brief Simple invoke policy for @ref BasicSubject
 *
 * @details
 * The given invocable is just executed with the observer.
 *
 * @ingroup Utils
 */
class Invoke
{
public:
    /**
     * @brief Calls given function with given observer.
     */
    template <class ObserverType, class Func>
    static void invoke(ObserverType&& observer, Func&& func)
    {
        std::forward<Func>(func)(std::forward<ObserverType>(observer));
    }
};
}
}
