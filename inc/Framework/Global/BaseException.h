#pragma once

#include <Framework/Global/Private/ExpImp.h>

#include <Framework/Config/Public/Attributes.h>
#include <Framework/Config/Public/Config.h>

#include <exception>

#ifdef DFL_CONFIG_OS_WIN32
#pragma warning (push)
#pragma warning (disable: 4275)
#endif

#define THROW_BaseException(message) throw BaseException(message, __FILE__, __LINE__)

/**
 * @brief Base class for exceptions.
 * @ingroup Global
 */
class DFL_GLOBAL_EXPIMP BaseException: public std::exception
{
public:
    /**
     * @brief Public constants
     */
    using Constants = enum
    {
        MaxLenMessage = 256
    };

    /**
     * @brief InfoAdapter must be implemented by S16 or S16Bridge only.
     * @note There must not be thrown any S16 Exception inside the implementation!
     */
    class DFL_GLOBAL_EXPIMP InfoAdapter
    {
    public:
        friend class BaseException;

        InfoAdapter(const InfoAdapter& right) = delete;
        InfoAdapter& operator=(const InfoAdapter& right) = delete;
        virtual ~InfoAdapter() = default;

    protected:
        InfoAdapter() = default;

        /**
         * @brief Set specific information for exception in specfic thread
         */
        virtual void* specialSetInfo(const char* msg, const char* file, int line) = 0;
        /**
         * @brief Remove specific information for specific thread
         */
        virtual void specialRemoveInfo(void* handle) = 0;

        /**
         * @brief Initalizes the singleton with the given InfoAdapter
         */
        static void initInstance(InfoAdapter* instance);
        /**
         * @brief Shutdowns the singleton
         */
        static void shutdown();

    private:
        static void* setInfo(const char* msg, const char* file, int line);
        static void removeInfo(void* handle);

        static InfoAdapter* m_instance;
    };

    /**
     * @brief LogAdapter must be implemented by S16 or S16Bridge only.
     * @note There must not be thrown any S16 Exception inside the implementation!
     */
    class DFL_GLOBAL_EXPIMP LogAdapter
    {
    public:
        friend class BaseException;

        LogAdapter(const LogAdapter& right) = delete;
        LogAdapter& operator=(const LogAdapter& right) = delete;
        virtual ~LogAdapter() = default;

    protected:
        LogAdapter() = default;

        /**
         * @brief Make service log entry
         */
        virtual void doSpecialServiceLog(const char* msg, const char* file, int line) = 0;
        /**
         * @brief Initalizes the singleton with the given LogAdapter
         */
        static void initInstance(LogAdapter* instance);
        /**
         * @brief Shutdowns the singleton
         */
        static void shutdown();

    private:
        static void doServiceLog(const char* msg, const char* file, int line);

        static LogAdapter* m_instance;
    };

    /**
     * @brief Constructs an exception object
     * @param message The message of the exception, can be retrieved with what().
     * @param file    The file name of the source, where the exception occurred.
     * @param line    The line number in source file, where the exception occurred.
     */
    explicit BaseException(const char message[], const char* file = "", int line = 0);

    /**
     * @brief Creates a copy of an exception object
     * @param right Exception object to be copied
     */
    BaseException(const BaseException& right);

    BaseException& operator=(const BaseException& right) = delete;

    /**
     * @brief Destructs an exception object
     */
    ~BaseException() override;

    /**
     * @return An explanatory message of the exception
     */
    const char * what() const noexcept override;

    /**
     * @return The file name of the source, where the exception occurred.
     */
    inline const char* getFile() const;

    /**
     * @return The line number in source file, where the exception occurred.
     */
    inline int getLine() const;

    /**
     * @brief Static throw exception method.
     *
     * @param message The message of the exception.
     * @param file    The file name of the source, where the exception occurred.
     * @param line    The line number in source file, where the exception occurred.
     * @return Nothing because an exception is always thrown in the function body
     *
     * This function must not be called directly, it will only be used by THROW_ macro.
     * It will never return; the exception will be built internally and
     * thrown from inside this method.
     *
     * @deprecated Use throw BaseException(message, file, line) instead!
     */
    DFL_ATTRIBUTE_DEPRECATED("use constructor of BaseException instead")
    static int throwBaseException(const char message[], const char* file, int line);

protected:
    /**
     * @brief May be used by derived Exception classes for special logging
     * @param message The message of the exception.
     * @param file    The file name of the source, where the exception occurred.
     * @param line    The line number in source file, where the exception occurred.
     */
    static void doLog(const char* message, const char* file, int line);

    /**
     * @brief An explanatory message of the exception
     */
    char m_message[MaxLenMessage]{};
    /**
     * @brief The file name of the source, where the exception occurred.
     */
    const char* m_file;
    /**
     * @brief The line number in source file, where the exception occurred.
     */
    int m_line;
    /**
     * @brief Task info for the exception.
     */
    void* m_exceptionTaskInfo{};
};

inline int BaseException::getLine() const
{
    return m_line;
}

inline const char* BaseException::getFile() const
{
    return m_file;
}

#ifdef WIN32
#pragma warning (pop)
#endif
