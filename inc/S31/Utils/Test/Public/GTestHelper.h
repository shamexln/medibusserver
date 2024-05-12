#pragma once

#include <S31/Utils/Public/Errors.h>
#include <exception>
#include <typeinfo>

/**
 * @brief Like GTest's EXPECT_THROW but to check for the specific error in @ref S31::Utils::ExceptionWithError exception.
 * @details
 * Example: `EXPECT_THROW_EXCEPTION_WITH_ERROR(queue.push(makeStateModifications(wrongSequenceVersion)), S31::Sdc::Impl::Errors::MdibSequenceChanged);`
 */
#define EXPECT_THROW_EXCEPTION_WITH_ERROR(statement, specificError) EXPECT_THROW_EXCEPTION_WITH_ERROR_IMPL(statement, specificError, FAIL())
#define EXPECT_THROW_EXCEPTION_WITH_ERROR_IMPL(statement, specificError, fail) \
do \
{\
    try \
    { \
        statement; \
    } \
    catch (const S31::Utils::ExceptionWithError& e) \
    { \
        if (auto err = e.error().is<specificError>()) \
        { \
            break; /* the good case - all other paths are fails */ \
        } \
        else \
        { \
            fail << "Execution throwed an ExceptionWithError with different specific error (" <<  e.error().errorTypeName() << "). Msg:" << e.what(); \
            break; \
        } \
    } \
    catch (const std::exception& e) \
    { \
        fail << "Execution throwed a different exception type: " << typeid(e).name() << ": " << e.what(); \
        break; \
    } \
    fail << "Execution did not throw an exception."; \
} while(0)
