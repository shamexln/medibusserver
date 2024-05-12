#pragma once

namespace DFL
{
namespace Mdib
{

template <class T, class... Ts>
struct Entities;

/**
 * @brief Specialization for template class recursion end.
 * @ingroup Mdib
 */
template <class T>
struct Entities<T>
{
        /**
         * @name Normal visitor
         * @brief Called during the last or the only recursion.
         */
        ///@{
        template<class V, class... As>
        static void applyVisitor(V& visitor, As&... args)
        {
            visitor.template visitEntity<T>(args...);
            // end of recursion
        }
        template<class V, class... As>
        static void applyVisitor(const V& visitor, As&... args)
        {
            visitor.template visitEntity<T>(args...);
            // end of recursion
        }
        ///@}

        /**
         * @name Visitor with early exit
         * @brief Called during the last or only recursion.
         */
        ///@{
        template<class V, class... As>
        static void applyVisitorWithEarlyExit(V& visitor, As&... args)
        {
            visitor.template visitEntity<T>(args...);
            // end of recursion
        }
        template<class V, class... As>
        static void applyVisitorWithEarlyExit(const V& visitor, As&... args)
        {
            visitor.template visitEntity<T>(args...);
            // end of recursion
        }
        ///@}
};

/**
 * @brief When visitor with early exit is used, this flag defines if visiting is continued or cancelled.
 * @ingroup Mdib
 */
enum class VisitorProcessing
{
    Proceed, //!< Proceed processing.
    Cancel   //!< Cancel processing.
};

/**
 * @brief Templatize this class with all MDIB entities the visitor should be applied to.
 * @ingroup Mdib
 */
template <class T, class T2, class... Ts>
struct Entities<T, T2, Ts...> : private Entities<T2, Ts...>
{
        /**
         * @name Normal visitor.
         * @brief Apply visitor for the first entity in the template and recursively call the function for the rest of the entities.
         */
        ///@{
        template<class V, class... As>
        static void applyVisitor(V& visitor, As&... args)
        {
            // apply visitor for specific entity
            visitor.template visitEntity<T>(args...);

            // recursive call
            Entities<T2, Ts...>::applyVisitor(visitor, args...);
        }
        template<class V, class... As>
        static void applyVisitor(const V& visitor, As&... args)
        {
            // apply visitor for specific entity
            visitor.template visitEntity<T>(args...);

            // recursive call
            Entities<T2, Ts...>::applyVisitor(visitor, args...);
        }
        ///@}

        /**
         * @name Visitor with early exit
         * @brief Apply visitor for the first entity in the template and recursively call the function for the rest of the entities.
         * @details Cancels visiting if visited function returns \c true, continues visiting of entities if visited function returns \c false.
         */
        ///@{
        template<class V, class... As>
        static void applyVisitorWithEarlyExit(V& visitor, As&... args)
        {
            // apply visitor for specific entity
            if (visitor.template visitEntity<T>(args...) == VisitorProcessing::Proceed)
            {
                // recursive call
                Entities<T2, Ts...>::applyVisitorWithEarlyExit(visitor, args...);
            }
        }

        template<class V, class... As>
        static void applyVisitorWithEarlyExit(const V& visitor, As&... args)
        {
            // apply visitor for specific entity
            if (visitor.template visitEntity<T>(args...) == VisitorProcessing::Proceed)
            {
                // recursive call
                Entities<T2, Ts...>::applyVisitorWithEarlyExit(visitor, args...);
            }
        }
        ///@}
};

}
}
