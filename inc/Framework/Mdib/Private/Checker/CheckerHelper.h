#pragma once

/**
 * @file
 * @brief Supporting macros for implementing Mdib checkers.
 */

#ifdef DFL_MDIB_TEST_CHECKER_IGNORE_ERROR
#define RETURN_ON_FAIL(func) do {\
    const auto& callResult = func; \
    if (callResult.status() == CheckerStatus::CheckFailed) \
    { \
        std::cout<<"ERROR: "<<callResult.message()<<"\n"; \
    } \
} while(0)
#else
#define RETURN_ON_FAIL(func) do {\
    const auto& callResult = func; \
    if (callResult.status() == CheckerStatus::CheckFailed) \
    { \
        return callResult; \
    } \
} while(0)
#endif
