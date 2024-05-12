#pragma once

#include <memory>

namespace S31::Base::Impl::PtrHelper
{

template <typename T>
[[nodiscard]] inline std::shared_ptr<T> lock(const std::weak_ptr<T>& ptr)
{
    return ptr.lock();
}

inline void returnsVoid()
{
}

constexpr const char* notLockableMessage = "Weak pointer could not be locked:";

}

/**
 * @brief Macro for the lock-a-weak-pointer-or-return-from-function pattern.
 * @details With return value and custom log message
 * @ingroup S31CoreBase
 */
#define S31_BASE_LOCK_OR_RETURN_VALUE_MSG(weakPtr, value, msg, msgFunc) S31::Base::Impl::PtrHelper::lock(weakPtr);\
do\
{\
    if (weakPtr.expired())\
    {\
        msgFunc(msg + std::string(" " #weakPtr));\
        return value;\
    }\
} while(0)

/**
 * @brief Macro for the lock-a-weak-pointer-or-return-from-function pattern.
 * @ingroup S31CoreBase
 */
#define S31_BASE_LOCK_OR_RETURN(weakPtr, msgFunc) \
    S31_BASE_LOCK_OR_RETURN_VALUE_MSG(weakPtr, S31::Base::Impl::PtrHelper::returnsVoid(), std::string(S31::Base::Impl::PtrHelper::notLockableMessage), msgFunc)

/**
 * @brief Macro for the lock-a-weak-pointer-or-return-from-function pattern.
 * @details With return value.
 * @ingroup S31CoreBase
 */
#define S31_BASE_LOCK_OR_RETURN_VALUE(weakPtr, value, msgFunc) \
    S31_BASE_LOCK_OR_RETURN_VALUE_MSG(weakPtr, value, std::string(S31::Base::Impl::PtrHelper::notLockableMessage), msgFunc)

/**
 * @brief Macro for the lock-a-weak-pointer-or-return-from-function pattern.
 * @details With custom log message.
 * @ingroup S31CoreBase
 */
#define S31_BASE_LOCK_OR_RETURN_MSG(weakPtr, msg, msgFunc) \
    S31_BASE_LOCK_OR_RETURN_VALUE_MSG(weakPtr, S31::Base::Impl::PtrHelper::returnsVoid(), msg, msgFunc)
