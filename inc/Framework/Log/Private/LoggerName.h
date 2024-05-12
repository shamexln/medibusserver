#pragma once

#include <Framework/Log/Private/ExpImp.h>

#include <boost/algorithm/string/find_iterator.hpp>

#include <string>

namespace DFL
{
namespace Log
{
namespace Impl
{
/**
 * @brief Identity type of a logger.
 *
 * This type is used to identify a specific instance of an @ref
 * DFL::Log::Logger. LoggerName models a hierarchy similar to a folder path.
 *
 * @snippet Log/Test/UnitTest/TestLoggerName.cpp SlashOp
 *
 * @ingroup Log
 */
class DFL_LOG_EXPIMP LoggerName
{
public:
    /**
     * @brief The token used to separate the parent name from the child name.
     *
     * @snippet Log/Test/UnitTest/TestLoggerName.cpp CtorSep
     */
    static const std::string Sep;
    /**
     * @brief Constructs an empty name.
     *
     * @snippet Log/Test/UnitTest/TestLoggerName.cpp CtorDefault
     */
    LoggerName() = default;
    /**
     * @brief Constructs name from given string where '/' is used as a separator
     * between parent and child.
     *
     * @snippet Log/Test/UnitTest/TestLoggerName.cpp SlashOp
     * @snippet Log/Test/UnitTest/TestLoggerName.cpp CtorSlash
     * @snippet Log/Test/UnitTest/TestLoggerName.cpp CtorSep
     *
     * Punctuations are also allowed in a name:
     * @snippet Log/Test/UnitTest/TestLoggerName.cpp Valid
     *
     * Not all characters are valid in a name. Here are some examples of invalid
     * ones:
     * @snippet Log/Test/UnitTest/TestLoggerName.cpp Invalid
     */
    explicit LoggerName(const std::string& name);
    /**
     * @brief True if no name is currently held otherwise false.
     *
     * @snippet Log/Test/UnitTest/TestLoggerName.cpp ParentLast
     */
    bool empty() const noexcept;
    /**
     * @brief Returns the depth of the hierarchy.
     *
     * @snippet Log/Test/UnitTest/TestLoggerName.cpp CtorDefault
     * @snippet Log/Test/UnitTest/TestLoggerName.cpp CtorSlash
     */
    std::size_t depth() const;
    /**
     * @brief Returns a string representation of this name.
     *
     * @snippet Log/Test/UnitTest/TestLoggerName.cpp Str
     */
    const std::string& str() const noexcept;
    /**
     * @brief Returns a LoggerName containing every part before the last
     * separator.
     *
     * If this is empty an empty name is returned.
     *
     * @snippet Log/Test/UnitTest/TestLoggerName.cpp ParentLast
     */
    LoggerName parent() const;
    /**
     * @brief Returns a LoggerName containing the part behind the last separator
     * or the name itself.
     *
     * If this is empty an empty name is returned.
     *
     * @snippet Log/Test/UnitTest/TestLoggerName.cpp ParentLast
     */
    LoggerName last() const;

private:
    std::string m_name{};
    using string_split_iterator =
        boost::algorithm::split_iterator<std::string::const_iterator>;
    string_split_iterator m_partsIter{};

    LoggerName(const string_split_iterator& b, const string_split_iterator& e);
};
/**
 * @brief True if both contain same name hierachy otherwise false.
 *
 * @snippet Log/Test/UnitTest/TestLoggerName.cpp Compare
 *
 * @ingroup Log
 * @{
 */
DFL_LOG_EXPIMP bool operator==(
    const LoggerName& a, const LoggerName& b) noexcept;
DFL_LOG_EXPIMP bool operator!=(
    const LoggerName& a, const LoggerName& b) noexcept;
/** @} */
/**
 * @brief Lexicographically compares each part of the two names.
 *
 * @snippet Log/Test/UnitTest/TestLoggerName.cpp Compare
 * Since operator< is used e.g. for sorting one can expect the following
 * behaviour:
 * @snippet Log/Test/UnitTest/TestLoggerName.cpp Sorting
 *
 * @ingroup Log
 * @{
 */
DFL_LOG_EXPIMP bool operator<(
    const LoggerName& a, const LoggerName& b) noexcept;
DFL_LOG_EXPIMP bool operator>(
    const LoggerName& a, const LoggerName& b) noexcept;
DFL_LOG_EXPIMP bool operator<=(
    const LoggerName& a, const LoggerName& b) noexcept;
DFL_LOG_EXPIMP bool operator>=(
    const LoggerName& a, const LoggerName& b) noexcept;
/** @{ */
/**
 * @brief Create a new @ref DFL::Log::Impl::LoggerName.
 *
 * @snippet Log/Test/UnitTest/TestLoggerName.cpp SlashOp
 *
 * @ingroup Log
 */
DFL_LOG_EXPIMP LoggerName
operator/(const LoggerName& parentName, const std::string& childName);
}
}
}
