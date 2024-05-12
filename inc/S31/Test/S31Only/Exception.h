#pragma once

#include <S31/Test/Private/S31TestUtilsExImp.h>

#include <exception>
#include <sstream>
#include <stdexcept>
#include <type_traits>

/**
  * @brief Throws an exception with file+line info.
  * @details To be used in tests where ASSERT_* cannot be used and EXPECT_* is not
  * possible as replacement.
  *
  * For the typed version: it is required that T_Exception has a ctor that takes a std::string.
  */
#define THROW_EXCEPTION_TYPED(T_Exception, msg) do { S31::Test::Impl::throwTheException<T_Exception>(msg, __FILE__, __LINE__); } while(false)
#define THROW_EXCEPTION(msg) THROW_EXCEPTION_TYPED(std::runtime_error, msg)

/**
  * @brief Throws exception if condition is fulfilled.
  */
#define THROW_IF(condition) do { if (condition) { S31::Test::Impl::throwTheException<std::runtime_error>("Condition (" #condition ") is fulfilled.", __FILE__, __LINE__); } } while(false)

/**
  * @brief Throws exception if condition is not fulfilled.
  */
#define THROW_IF_NOT(condition) do { if (!(condition)) { S31::Test::Impl::throwTheException<std::runtime_error>("Condition (" #condition ") is not fulfilled.", __FILE__, __LINE__); } } while(false)

/**
  * @brief Throws exception with text "not implemented".
  */
#define THROW_EXCEPTION_NOT_IMPLEMENTED() do { S31::Test::Impl::throwTheExceptionNotImplemented(__func__, __FILE__, __LINE__); } while(false)

namespace S31::Test::Impl
{

S31_TESTUTILS_EXPIMP void logErrorOnThrownException(const std::string& msg, const char* filename, int lineNumber);

template <typename T_Exception>
[[noreturn]] inline void throwTheException(const std::ostringstream& msg, const char* filename, int lineNumber)
{
    static_assert(std::is_base_of<std::exception, T_Exception>::value, "T_Exception has to be an exception derived from std::exception.");
    Impl::logErrorOnThrownException(msg.str(), filename, lineNumber);
    std::ostringstream extendedMsg;
    extendedMsg << msg.str() << "~" << filename << ":" << lineNumber;
    throw T_Exception(extendedMsg.str());
}

template <typename T_Exception, typename Streamable>
[[noreturn]] inline void throwTheException(const Streamable& sa, const char* filename, int lineNumber)
{
    std::ostringstream ss;
    ss << sa;
    throwTheException<T_Exception>(ss, filename, lineNumber);
}

[[noreturn]] inline void throwTheExceptionNotImplemented(const char* functionName, const char* filename, int lineNumber)
{
    std::ostringstream ss;
    ss << functionName << "() is not implemented.";
    throwTheException<std::runtime_error>(ss, filename, lineNumber);
}

}
