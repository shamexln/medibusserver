#pragma once

#include <S31/Log/Public/Logger.h>
#include <S31/Utils/Public/Errors.h>
#include <S31/Utils/Public/Utf8AppenderStream.h>

#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/Utf8.h>
#include <Framework/Utils/Public/Utf8Io.h>

#include <functional>
#include <memory>
#include <type_traits>
#include <utility>
#include <optional>

namespace S31::Utils
{

/**
 * @brief Result object of a job execution or generally the result/outcome of an asynchronous operation.
 *
 * This is basically a 2-tuple of a result data structure and an error object of which exactly one is set.
 *
 * This class represents the concept, that when somebody started/queued a job, then she wants to know
 * the 'outcome' of the job i.e. when the job is finished, either the result or an error.
 *
 * @ingroup S31Utils
 */
template<class T_ResultData>
class Outcome
{
    public:
        using Result = T_ResultData;

        /// Constructor for empty object with error @ref S31::Utils::Errors::NoOutcomeSet.
        Outcome();

        /// Constructor for outcome with result, without error
        template <class R>
        // False positive, enable_if restricts types
        // NOLINTNEXTLINE(misc-forwarding-reference-overload,bugprone-forwarding-reference-overload)
        explicit Outcome(R&& result, typename std::enable_if<std::is_same<typename std::decay<R>::type, Result>::value>::type* = nullptr);

        /// Constructor for outcome with error
        explicit Outcome(const Error& error);

        Outcome(const Error& error, DFL::Locale::Utf8 errorMessage);

        /// Returns the result object if there is one.
        /// @{
        const std::optional<Result>& result() const;
        std::optional<Result>& result();
        /// @}

        /// Returns the error message, may be empty.
        const DFL::Locale::Utf8& errorMessage() const;

        /// Returns @a true if the outcome is an error.
        bool hasError() const;

        /// Returns the error if the outcome was an error (@ref hasError()).
        /// Otherwise the Error is of type \ref Errors::NoErrorInOutcome
        Error error() const;

    private:
        std::optional<Result> m_result;
        std::optional<Error> m_error;
        DFL::Locale::Utf8 m_errorMessage;
};

template<class Derived, class T_ResultData>
class OutcomeConsumer;

/**
 * @brief A generalized handler interface that requires no result data type.
 * @ingroup S31Utils
 */
class UntypedOutcomeHandler
{
    public:
        virtual ~UntypedOutcomeHandler() noexcept = default;
};

namespace Impl
{

/**
 * @brief The handler interface given to the outcome provider
 *
 * This is just @ref OutcomeHandlerWithConsumerType without knowing the type of the outcome consumer.
 * This class is hidden from users.
 *
 * @ingroup S31Utils
 */
template<class T_ResultData>
class OutcomeHandler: public UntypedOutcomeHandler
{
    public:
        using OutcomeType = Outcome<T_ResultData>;
        virtual void endedWithOutcome(OutcomeType& outcome) = 0;
};

/**
 * @brief Wraps a closure and a callback context for outcome notification.
 *
 * This class is hidden from the user (i.e. derived classes of outcome providers/consumers)
 *
 * @ingroup S31Utils
 */
template<class DerivedConsumer, class T_ResultData>
class OutcomeHandlerWithConsumerType: public OutcomeHandler<T_ResultData>
{
    public:
        using CallbackFunction = std::function<void(typename OutcomeHandler<T_ResultData>::OutcomeType&)>;
        using ConsumerPtr = std::shared_ptr<OutcomeConsumer<DerivedConsumer, T_ResultData>>;
        using WeakConsumerPtr = std::weak_ptr<OutcomeConsumer<DerivedConsumer, T_ResultData>>;

        /// Constructor
        OutcomeHandlerWithConsumerType(const ConsumerPtr& callbackContext, CallbackFunction callback);

        /// This will be called from an outcome provider (eg. a job after it is ended/has finished processing)
        /// @param outcome The outcome. Note that this is a reference, it might be moved away
        void endedWithOutcome(typename OutcomeHandler<T_ResultData>::OutcomeType& outcome) override;

    private:
        WeakConsumerPtr m_callbackContext;
        CallbackFunction m_callback;
};

} // namespace Impl

namespace OutcomeTypes
{

/**
 * @brief General shared ownership outcome handler without an attached result type.
 * @ingroup S31Utils
 */
using UntypedHandlerPtr = std::shared_ptr<UntypedOutcomeHandler>;

/**
 * @brief General outcome handler weak ownership definition.
 * @ingroup S31Utils
 */
template<class T_ResultData>
using WeakHandlerPtr = std::weak_ptr<Impl::OutcomeHandler<T_ResultData>>;

/**
 * @brief General outcome handler shared ownership definition.
 * @ingroup S31Utils
 */
template<class T_ResultData>
using HandlerPtr = std::shared_ptr<Impl::OutcomeHandler<T_ResultData>>;

/**
 * @brief General outcome callback function definition.
 * @ingroup S31Utils
 */
template<class T_ResultData>
using CallbackFunction = std::function<void(Outcome<T_ResultData>&)>;

}

/**
 * @brief Things that provide an outcome deriving from this class.
 *
 * Typically that could be a job that is asynchronous executed in another thread. Derived
 * classes set the outcome in their processing code (using protected member functions
 * of this class) and on destroying of objects of this class the outcome consumer is notified.
 *
 * Outcome provider should set either the positive result or the error or avoid processing
 * completely (if there is no outcome consumer)
 *
 * @ingroup S31Utils
 */
template<class T_ResultData>
class OutcomeProvider
{
    public:
        using WeakOutcomeHandlerPtr = OutcomeTypes::WeakHandlerPtr<T_ResultData>;
        using OutcomeHandlerPtr = OutcomeTypes::HandlerPtr<T_ResultData>;
        using OutcomeType = Outcome<T_ResultData>;

    protected:

        /** @name Constructors
         *  @param outcomeHandler Object that will be notified about the outcome.
         */
        ///@{
        explicit OutcomeProvider(const OutcomeHandlerPtr& outcomeHandler):
                m_outcomeHandler(outcomeHandler){}
        explicit OutcomeProvider(WeakOutcomeHandlerPtr outcomeHandler):
                m_outcomeHandler(std::move(outcomeHandler)){}
        ///@}

        /// @brief Destructor.
        /// @details Does the outcome notification.
        ~OutcomeProvider() noexcept;

        /**
         * @brief Use for life time watching: no outcome callback == nobody is interested in this job anymore.
         *
         * @details A derived job should check this and if there is no callback then it has to
         * abort/avoid processing (and no error logging because of this).
         */
        bool hasOutcomeHandler() const
        {
            return m_outcomeHandler.lock() != nullptr;
        }

        /// @brief Set outcome result.
        ///
        /// Set the (positive) outcome result.
        template <class R>
        void setOutcomeResult(R&& result,
                              typename std::enable_if<std::is_same<typename std::decay<R>::type, T_ResultData>::value>::type* = nullptr);

        Utf8AppenderStream& setOutcomeError(const AnySubclassOfSpecificError& error);

        Utf8AppenderStream& setOutcomeError(const AnySubclassOfSpecificError& error, const DFL::Locale::Utf8& errorMsg);

        Utf8AppenderStream& setOutcomeError(const Utils::Error& error);

        /// Get an object that can receive the error message via stream operators.
        Utf8AppenderStream& outcomeErrorStream();

        /// The error currently set.
        std::optional<Error> currentError() const;
    private:

        /// Handling of outcome
        template <class R>
        bool doNotificationWithResult(const OutcomeHandlerPtr& handler);

        const char* getOutcomeNotConstructibleMsg();

        WeakOutcomeHandlerPtr m_outcomeHandler;
        std::optional<Utils::AnySubclassOfSpecificError> m_error;
        std::optional<typename OutcomeType::Result> m_result;
        DFL::Locale::Utf8 m_errorMsg;
        std::optional<Utf8AppenderStream> m_errorMsgStream;
};

/**
 * @brief An consumer/observer of Outcome.
 *
 * Derived classes typically start asynchronous jobs (with outcome) and provide a handler
 * for the outcome (typically a closure).
 *
 * @ingroup S31Utils
 */
template<class Derived, class T_ResultData>
class OutcomeConsumer
{
    public:
        // gcc 4.8 wants to have this using declaration public even it is used only in a derived class (and being 'protected' should be enough)
        using OutcomeType = Outcome<T_ResultData>;

    protected:
        using OutcomeHandlerType = Impl::OutcomeHandlerWithConsumerType<Derived, T_ResultData>;
        using CallbackFunction = OutcomeTypes::CallbackFunction<T_ResultData>;
        using HandlerPtr = OutcomeTypes::HandlerPtr<T_ResultData>;

        /// protected constructor
        OutcomeConsumer() = default;
        /// protected destructor
        ~OutcomeConsumer() = default;

        /**
         * @brief Factory function to get a handler that in the next step is given to the outcome provider.
         * @param callback Handles the outcome. Typically a lambda.
         * @return The handler. Caller has to hold it as long as she is interested in the outcome.
         */
        HandlerPtr makeOutcomeHandler(const CallbackFunction& callback);
};

/** @name Specific errors for Outcome/Error
 */
///@{

namespace Errors
{
/// The error when the job has not set the outcome
/// @ingroup S31Utils
struct NoOutcomeSet: SpecificError
{};

/// Creating of the outcome date structure failed (exception on invoking constructor of the result type)
/// @ingroup S31Utils
struct OutcomeNotConstructible: SpecificError
{};

/// An Error was got from an outcome without error (instead the outcome was success)
/// @ingroup S31Utils
struct NoErrorInOutcome: SpecificError
{};
}

///@}

template<class T_ResultData>
inline Outcome<T_ResultData>::Outcome():
    m_result(),
    m_error(makeError(Errors::NoOutcomeSet())),
    m_errorMessage("Outcome not set")
{}

template<class T_ResultData>
template <class R>
// False positive, enable_if restricts types
// NOLINTNEXTLINE(misc-forwarding-reference-overload,bugprone-forwarding-reference-overload)
inline Outcome<T_ResultData>::Outcome(R&& result,
            typename std::enable_if<std::is_same<typename std::decay<R>::type, Result>::value>::type*):
    m_result(std::forward<R>(result)),
    m_error(),
    m_errorMessage()
{}

template<class T_ResultData>
inline Outcome<T_ResultData>::Outcome(const Error& error):
    m_result(),
    m_error(error),
    m_errorMessage(error.message())
{}

template<class T_ResultData>
inline Outcome<T_ResultData>::Outcome(const Error& error, DFL::Locale::Utf8 errorMessage):
    m_result(),
    m_error(error),
    m_errorMessage(std::move(errorMessage))
{}

template<class T_ResultData>
inline const std::optional<typename Outcome<T_ResultData>::Result>& Outcome<T_ResultData>::result() const
{
    return m_result;
}

template<class T_ResultData>
inline std::optional<typename Outcome<T_ResultData>::Result>& Outcome<T_ResultData>::result()
{
    return m_result;
}

template<class T_ResultData>
inline const DFL::Locale::Utf8& Outcome<T_ResultData>::errorMessage() const
{
    return m_errorMessage;
}

template<class T_ResultData>
inline bool Outcome<T_ResultData>::hasError() const
{
    return m_error.has_value();
}

template<class T_ResultData>
inline Error Outcome<T_ResultData>::error() const
{
    if (m_error)
    {
            auto result = *m_error;
            result.resetMessage(m_errorMessage);
            return result;
    }
    return makeError(Errors::NoErrorInOutcome{}, DFL::Locale::Utf8("The outcome does not contain an error."));
}

namespace Impl {

template<class DerivedConsumer, class T_ResultData>
inline OutcomeHandlerWithConsumerType<DerivedConsumer, T_ResultData>::OutcomeHandlerWithConsumerType(
        const ConsumerPtr& callbackContext,
        CallbackFunction callback):
    m_callbackContext(callbackContext),
    m_callback(std::move(callback))
{}

template<class DerivedConsumer, class T_ResultData>
inline void OutcomeHandlerWithConsumerType<DerivedConsumer, T_ResultData>::endedWithOutcome(typename OutcomeHandler<T_ResultData>::OutcomeType& outcome)
{
    auto callbackContext = m_callbackContext.lock();
    if (callbackContext && m_callback)
    {
        try
        {
            m_callback(outcome);
        }
        catch(std::exception& e)
        {
            S31_STREAM_WARN_LOGGER("Utils", "Invoking outcome callback caused exception: ", e.what());
        }
        catch(...)
        {
            S31_STREAM_WARN_LOGGER("Utils", "Invoking outcome callback caused exception");
        }
    }
}

} // namespace Impl

template<class T_ResultData>
inline OutcomeProvider<T_ResultData>::~OutcomeProvider() noexcept
{
    try
    {
        if (auto handler = m_outcomeHandler.lock())
        {
            if (doNotificationWithResult<T_ResultData>(handler))
            {}
            else if (m_error)
            {
                Outcome<T_ResultData> result(makeError(*m_error), m_errorMsg);
                handler->endedWithOutcome(result);
            }
            else
            {
                Outcome<T_ResultData> result;
                handler->endedWithOutcome(result);
            }
        }
    }
    catch (const std::exception& e)
    {
        S31_STREAM_WARN_LOGGER("Utils", "Invoking outcome callback caused exception: ", e.what());
    }
    catch (...)
    {
        S31_STREAM_WARN_LOGGER("Utils", "Invoking outcome callback caused exception");
    }
}

template<class T_ResultData>
template<class R>
inline void OutcomeProvider<T_ResultData>::setOutcomeResult(R&& result,
                typename std::enable_if<std::is_same<typename std::decay<R>::type, T_ResultData>::value>::type*)
{
    m_result = std::forward<R>(result);
    m_error.reset();
}

template<class T_ResultData>
inline Utf8AppenderStream& OutcomeProvider<T_ResultData>::setOutcomeError(const AnySubclassOfSpecificError& error)
{
    m_error = error;
    m_result.reset();
    return outcomeErrorStream();
}

template<class T_ResultData>
inline Utf8AppenderStream& OutcomeProvider<T_ResultData>::setOutcomeError(const AnySubclassOfSpecificError& error, const DFL::Locale::Utf8& errorMsg)
{
    m_error = error;
    m_errorMsg = errorMsg;
    m_result.reset();
    return outcomeErrorStream();
}

template<class T_ResultData>
inline Utf8AppenderStream& OutcomeProvider<T_ResultData>::setOutcomeError(const Utils::Error& error)
{
    m_error = error.value();
    m_errorMsg = error.message();
    m_result.reset();
    return outcomeErrorStream();
}

template<class T_ResultData>
template <class R>
inline bool OutcomeProvider<T_ResultData>::doNotificationWithResult(const OutcomeHandlerPtr& handler)
{
    if (m_result)
    {
        try
        {
            if constexpr(std::is_move_constructible_v<R>)
            {
                Outcome<T_ResultData> result(std::move(*m_result));
                handler->endedWithOutcome(result);
            }
            else
            {
                Outcome<T_ResultData> result(*m_result);
                handler->endedWithOutcome(result);
            }
            return true;
        }
        catch(std::exception& e)
        {
            setOutcomeError(Errors::OutcomeNotConstructible{}) << getOutcomeNotConstructibleMsg() << e.what();
        }
        catch(...)
        {
            setOutcomeError(Errors::OutcomeNotConstructible{}) << getOutcomeNotConstructibleMsg();
        }
    }
    return false; // note that because of returning 'false' the outcome error that was set in the 'catch' will be notified.
}

template<class T_ResultData>
inline const char* OutcomeProvider<T_ResultData>::getOutcomeNotConstructibleMsg()
{
    return "Outcome not constructible. ";
}

template<class T_ResultData>
inline Utf8AppenderStream& OutcomeProvider<T_ResultData>::outcomeErrorStream()
{
    if (!m_errorMsgStream)
    {
        m_errorMsgStream = Utf8AppenderStream{m_errorMsg};
    }
    return *m_errorMsgStream;
}

template<class T_ResultData>
inline std::optional<Error> OutcomeProvider<T_ResultData>::currentError() const
{
    if (!m_result && m_error)
    {
        return makeError(*m_error, m_errorMsg);
    }
    return {};
}

template<class Derived, class T_ResultData>
inline typename OutcomeConsumer<Derived, T_ResultData>::HandlerPtr OutcomeConsumer<Derived, T_ResultData>::makeOutcomeHandler(
        const CallbackFunction& callback)
{
    static_assert(std::is_base_of<std::enable_shared_from_this<Derived>, Derived>::value,
                  "An OutcomeConsumer class A must be derived from std::enable_shared_from_this<A>" );

    static_assert(std::is_base_of<OutcomeConsumer<Derived, T_ResultData>, Derived>::value,
                  "An OutcomeConsumer class A must be derived from OutcomeConsumer<A, T_ResultData>" );

    auto* thisAsEnabledSharedFromThis = static_cast<Derived*>(this);
    auto sharedThis = thisAsEnabledSharedFromThis->shared_from_this();
    return std::make_shared<OutcomeHandlerType>(sharedThis, callback);
}

}
