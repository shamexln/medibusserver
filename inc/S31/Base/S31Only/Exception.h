#pragma once

#include <sstream>
#include <stdexcept>

namespace S31
{

/**
 * @brief %S31 base exception for all exceptions thrown in %S31.
 * @ingroup S31CoreBase
 */
class Exception : public std::runtime_error
{
public:
    Exception(const std::string& message, const char* file, int line)
        : std::runtime_error(message)
        , m_file(file)
        , m_line(line)
    {
    }

    [[nodiscard]] const char* file() const noexcept
    {
        return m_file;
    }

    [[nodiscard]] int line() const noexcept
    {
        return m_line;
    }

private:
    const char* m_file;
    int         m_line;
};

/**
 * @brief Shall be thrown when internal resources like scheduling, shared memory, ... are not available.
 * @ingroup S31CoreBase
 */
class InternalResourceMissing : public Exception
{
public:
    using Exception::Exception;
};

/**
 * @brief Shall be thrown when internal data cannot be mapped.
 * @ingroup S31CoreBase
 */
class InternalDataMappingFailed : public Exception
{
public:
    using Exception::Exception;
};

/**
 * @brief Shall be thrown when internal consistency cross-checks fail.
 * @ingroup S31CoreBase
 */
class InternalConsistencyFailure : public Exception
{
public:
    using Exception::Exception;
};

/**
 * @brief Shall be thrown when some internal resource limit is reached.
 * @details E.g. A container has a maximum number of elements and
 * this limit would be crossed.
 * @ingroup S31CoreBase
 */
class ResourceDepleted : public Exception
{
public:
    using Exception::Exception;
};

/**
 * @brief Base type for all kind of failures triggered by remote (invalid data).
 * @ingroup S31CoreBase
 */
class ExternalFailure : public Exception
{
public:
    using Exception::Exception;
};

/**
 * @brief Shall be thrown when external data (from remote) cannot be mapped.
 * @ingroup S31CoreBase
 */
class ExternalDataMappingFailed : public ExternalFailure
{
public:
    using ExternalFailure::ExternalFailure;
};

/**
 * @brief Shall be thrown when external data contains unknown must understand extensions.
 * @ingroup S31CoreBase
 */
class ExternalMustUnderstandExtensionUnknown : public ExternalFailure
{
public:
    using ExternalFailure::ExternalFailure;
};

/**
 * \brief Throw an exception of the given type with file/line information.
 * @ingroup S31CoreBase
 */
#define S31_THROW_EXCEPTION(exception, msg) do { \
    std::ostringstream stream; \
    stream << msg; \
    throw exception{stream.str(), __FILE__, __LINE__}; } while(0)

} /* namespace S31 */
