#pragma once

#include <S31/Base/S31Only/Exception.h>
#include <S31/Utils/Public/SpecificError.h>
#include <S31/Utils/Public/Utf8AppenderStream.h>

#include <Framework/Utils/Public/Utf8.h>

#include <boost/optional/optional.hpp>

#include <string>
#include <sstream>
#include <type_traits>
#include <utility>
#include <any>

namespace S31::Utils
{

/**
 * @brief Class that wraps an error and an error description
 *
 * ### Error handling conventions
 * - if a class handles errors, then it has do it in a function called 'void handleError(const Utils::Error& error)'
 * - if a class handles errors raised by dependent classes it should derive from ErrorHandler.
 * - if a class raise errors, it should
 *   - do raise in handleError()
 *   - have only 1 handle function
 *   - have only 1 point to raise to
 *
 * ### Specific errors
 * A specific error (the error that is contained in Error) should
 * - only contain information to dispatch/handle the error.
 * - must not contain and refs/ptr to internal data
 *
 * @ingroup S31Utils
 */
class Error
{
    public:
        /// returns the specific error object iff it is of the given type (T_Error)
        template<class T_Error>
        boost::optional<T_Error> is() const;

        /// @returns @c true iff the specific error is one of the given types
        template<typename T_Error, typename... T_Errors>
        [[nodiscard]] bool isOneOf() const;

        /// Returns the text that describes the error.
        [[nodiscard]] const DFL::Locale::Utf8& message() const noexcept;

        /// returns the source code line number where the error occurs
        [[nodiscard]] int sourceFileLineNumber() const;
        void sourceFileLineNumber(int line);

        [[nodiscard]] const std::string& sourceFilename() const;
        void sourceFilename(const std::string& sourceFilename);

        /// Returns a stream to modify the error message.
        Utf8AppenderStream& messageStream();

        /**
         * @brief sets a new error message but keeps the specific error
         * @param newMessage The new message to set in the error
         */
        void resetMessage(const std::string& newMessage);

        /// Returns the specific error.
        [[nodiscard]] const AnySubclassOfSpecificError& value() const;

        /// Returns the typename of the specific error.
        const char* errorTypeName() const;

        /**
         * factory functions have to be friends to access the private ctor
         */
        ///@{
        friend Error makeError(const AnySubclassOfSpecificError& errorContainer);

        friend Error makeError(const AnySubclassOfSpecificError& errorContainer, const DFL::Locale::Utf8& message);

        friend Error makeError(const AnySubclassOfSpecificError& errorContainer, const std::string& message);
        ///@}

    protected:
    private:

        /**
         * @brief Constructor
         */
        Error(AnySubclassOfSpecificError err, DFL::Locale::Utf8 msg);

        template<typename... T_Errors>
        bool isOneOf(typename std::enable_if<sizeof...(T_Errors) == 0>::type* = nullptr) const;

        AnySubclassOfSpecificError m_error;
        DFL::Locale::Utf8 m_errorMessage;
        int m_sourceFileLineNumber = -1;
        std::string m_sourcefilename;
        boost::optional<Utf8AppenderStream> m_errorMsgStream;

};

/**
 * @brief  Exception that holds an error
 * @note There is a suiting test macro for this kind of exception: `EXPECT_THROW_EXCEPTION_WITH_ERROR`.
 * @ingroup S31Utils
 */
class ExceptionWithError: public S31::Exception
{
    public:
        explicit ExceptionWithError(const Error& error);
        explicit ExceptionWithError(Error&& error);

        const Error& error() const noexcept;
    private:
        Error m_error;
};

/**
 * @brief Throw an exception with error with file/line information.
 * @details
 * Example: `S31_THROW_EXCEPTION_WITH_ERROR(Errors::IncomingDataNotUnderstood{}, "Wrong version " << *m_currentMdibVersion);`
 * @ingroup S31CoreBase
 */
#define S31_THROW_EXCEPTION_WITH_ERROR(specificError, msg) do { \
    std::ostringstream stream; \
    stream << msg; \
    S31::Utils::Error error = makeError(specificError, stream.str()); \
    error.sourceFilename(__FILE__); \
    error.sourceFileLineNumber(__LINE__); \
    throw S31::Utils::ExceptionWithError(std::move(error)); } while(0)

//! @cond Ignore_for_Doxygen
// (as of 2021-09) Doxygen cannot align the following implementations with the S31::Utils::Error class
// instead it looks at the enum DFL::Crypto::Impl::Ral::Error
inline Error::Error(AnySubclassOfSpecificError err, DFL::Locale::Utf8 msg):
        m_error(std::move(err)),
        m_errorMessage(std::move(msg)),
        m_errorMsgStream(boost::none)
    {
    }

    template<class T_Error>
    inline boost::optional<T_Error> Error::is() const
    {
        if (!m_error.get().has_value())
        {
            return boost::none;
        }
        auto anyError = m_error.get();
        if (const auto* result = std::any_cast<T_Error>(&anyError))
        {
            return boost::optional<T_Error>(*result);
        }
        return boost::none;
    }

    template<typename T_Error, typename... T_Errors>
inline bool Error::isOneOf() const
{
    if (is<T_Error>())
    {
        return true;
    }
    return isOneOf<T_Errors...>();
}

template<typename... T_Errors>
inline bool Error::isOneOf(typename std::enable_if<sizeof...(T_Errors) == 0>::type*) const
{
    return false;
}

inline const DFL::Locale::Utf8& Error::message() const noexcept
{
    return m_errorMessage;
}

inline Utf8AppenderStream& Error::messageStream()
{
    if (!m_errorMsgStream)
    {
        m_errorMsgStream = Utf8AppenderStream(m_errorMessage);
    }
    return *m_errorMsgStream;
}

inline const AnySubclassOfSpecificError& Error::value() const
{
    return m_error;
}

inline const std::string& Error::sourceFilename() const
{
    return m_sourcefilename;
}

inline void Error::sourceFilename(const std::string& sourceFilename)
{
    m_sourcefilename = sourceFilename;
}

inline int Error::sourceFileLineNumber() const
{
    return m_sourceFileLineNumber;
}

inline void Error::sourceFileLineNumber(int line)
{
    m_sourceFileLineNumber = line;
}

inline void Error::resetMessage(const std::string& newMessage)
{
    m_errorMessage = DFL::Locale::Utf8(newMessage);
}

inline const char* Error::errorTypeName() const
{
    return m_error.get().type().name();
}
//! @endcond

inline Error makeError(const AnySubclassOfSpecificError& error)
{
    return {error, DFL::Locale::Utf8()};
}

inline Error makeError(const AnySubclassOfSpecificError& error, const DFL::Locale::Utf8& message)
{
    return {error, message};
}

inline Error makeError(const AnySubclassOfSpecificError& error, const std::string& message)
{
    return {error, DFL::Locale::Utf8(message)};
}

/**
 * @brief Interface for class that can handle errors (see @ref Error)
 *
 * @ingroup S31Utils
 */
class ErrorHandler
{
    public:
        virtual ~ErrorHandler() = default;
        virtual void handleError(const Error& error) = 0;
};

using SharedErrorHandler = std::shared_ptr<ErrorHandler>;
using WeakErrorHandler = std::weak_ptr<ErrorHandler>;

inline ExceptionWithError::ExceptionWithError(const Error& error):
    S31::Exception(error.message().value(), error.sourceFilename().c_str(), error.sourceFileLineNumber()),
    m_error(error)
{
}

inline ExceptionWithError::ExceptionWithError(Error&& error):
    S31::Exception(error.message().value(), error.sourceFilename().c_str(), error.sourceFileLineNumber()),
    m_error(std::move(error))
{
}

inline const Error& ExceptionWithError::error() const noexcept
{
    return m_error;
}

}
