#pragma once

#include <S31/Utils/Private/S31UtilsExImp.h>

#include <Framework/Thread/Public/RecursiveMutex.h>
#include <Framework/Utils/Public/Observer/BasicSubject.h>
#include <Framework/Utils/Public/Observer/Invoke.h>

#include <memory>

namespace S31::Utils
{

/**
 * @brief Observer alias for S31.
 * @ingroup S31Utils
 */
template<typename ObserverType>
using ObservableSubject = DFL::Observer::Subject<ObserverType>;

/**
 * @brief Policy for DFL::Observer to catch and log exceptions on notification.
 * @ingroup S31Utils
 */
 // Named 'except' to not trigger clang-tidy check 'bugprone-throw-keyword-missing'
struct S31_UTILS_EXPIMP LogExceptMessage
{
    static void handleException(const std::exception& e);

    static void handleUnknownException();
};

/**
 * @brief ObservableSubjectDelegate alias for S31.
 * @ingroup S31Utils
 */
template<typename ObserverType>
using ObservableSubjectDelegate =
    DFL::Observer::BasicSubject<ObserverType, DFL::Thread::RecursiveMutex, DFL::Observer::InvokeAndCatch<LogExceptMessage>>;

}
