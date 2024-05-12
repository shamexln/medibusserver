#pragma once

#include <Framework/Utils/Public/Utf8.h>
#include <Framework/Utils/Public/Utf8Io.h>
#include <Framework/Mdib/Public/Model/CodingSystemFactory.h>
#include <Framework/Mdib/Public/MdibEntityRange.h>
#include <Framework/Mdib/Private/MdibEntityFiltersHelper.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief The MdibEntityFilters template class gives predefined filter functions for Mdib iterators and ranges.
 * @details Needs a parent MDIB (to use the parent.entity() member function).
 *
 * @ingroup Mdib
 */
template<class T_Mdib>
class MdibEntityFilters
{
    public:
        /**
         * @brief Mdib Constructor
         * @param parentMdib The connected parent object.
         */
        explicit MdibEntityFilters(const T_Mdib &parentMdib):
            m_parentMdib(parentMdib) {}

        /**
         * @name Children
         * @brief Get a filter function for all child entities of the given parent
         * ### Example
         * Get the child channels of a certain VMD
         * over a @ref DFL::Mdib::Mdib.
         * @snippet Mdib/Test/UnitTest/TestMdib.cpp children
         */
        template<class T_Entity>
        typename Impl::MdibIterator<T_Entity>::FilterFunction children(const BasicHandle<typename T_Entity::ParentType> &parent) const;


        /**
         * @name Filter function chaining over parents
         *
         * An entity can have 1..3 parents. This template uses the defined parent type on MdibEntity.
         *
         * ### Example
         * A chain with 2 parents: Find numeric metrics where the parents (Channel and Vmd) have certain handles
         * over a @ref DFL::Mdib::Mdib.
         * @snippet Mdib/Test/UnitTest/TestMdib.cpp chain2parents
         */
        ///@{
        /// Chaining with one parent
        template<class T_Entity>
        typename Impl::MdibIterator<T_Entity>::FilterFunction chain(
            const typename Impl::MdibIterator<T_Entity>::FilterFunction &entityFilterfunc,
            const typename Impl::MdibIterator<typename T_Entity::ParentType>::FilterFunction &parent1Filterfunc
           ) const;

        /// Chaining with two parents
        template<class T_Entity>
        typename Impl::MdibIterator<T_Entity>::FilterFunction chain(
            const typename Impl::MdibIterator<T_Entity>::FilterFunction &entityFilterfunc,
            const typename Impl::MdibIterator<typename T_Entity::ParentType>::FilterFunction &parent1Filterfunc,
            const typename Impl::MdibIterator<typename T_Entity::ParentType::ParentType>::FilterFunction &parent2Filterfunc
           ) const;


        /// Chaining with three parents
        template<class T_Entity>
        typename Impl::MdibIterator<T_Entity>::FilterFunction chain(
            const typename Impl::MdibIterator<T_Entity>::FilterFunction &entityFilterfunc,
            const typename Impl::MdibIterator<typename T_Entity::ParentType>::FilterFunction &parent1Filterfunc,
            const typename Impl::MdibIterator<typename T_Entity::ParentType::ParentType>::FilterFunction &parent2Filterfunc,
            const typename Impl::MdibIterator<typename T_Entity::ParentType::ParentType::ParentType>::FilterFunction &parent3Filterfunc
           ) const;

        ///@}

        /// @name Type Path
        /// @brief Get a filter function for all entities of a certain type path.
        ///
        /// Having the given type path is that the entity itself and it's parent have the given types.
        ///
        /// ### Example
        /// Using type path filter with a @ref DFL::Mdib::Mdib.
        /// @snippet Mdib/Test/UnitTest/TestMdib.cpp filterCtp
        /// @{
        template<class T_Entity>
        typename Impl::MdibIterator<T_Entity>::FilterFunction typePath(
                const CodeId &parent1Code,
                const CodeId &entityCode) const;
        template<class T_Entity>
        typename Impl::MdibIterator<T_Entity>::FilterFunction typePath(
                const CodeId &parent2Code,
                const CodeId &parent1Code,
                const CodeId &entityCode) const;
        template<class T_Entity>
        typename Impl::MdibIterator<T_Entity>::FilterFunction typePath(
                const CodeId &parent3Code,
                const CodeId &parent2Code,
                const CodeId &parent1Code,
                const CodeId &entityCode) const;
        /// @}
    private:
        const T_Mdib &m_parentMdib;
};

/// @brief Implementation of children()
template<class T_Mdib>
template<class T_Entity>
inline typename Impl::MdibIterator<T_Entity>::FilterFunction MdibEntityFilters<T_Mdib>::children(const BasicHandle<typename T_Entity::ParentType> &parent) const
{
    return typename Impl::MdibIterator<T_Entity>::FilterFunction(
                [parent]
                (const NotNull<SharedPtr<T_Entity>>& e) -> bool
                {
                    return (parent == e->parent());
                });
}

/// @brief Implementation of chain() with 1 parents
template<class T_Mdib>
template<class T_Entity>
inline typename Impl::MdibIterator<T_Entity>::FilterFunction MdibEntityFilters<T_Mdib>::chain(
    const typename Impl::MdibIterator<T_Entity>::FilterFunction &entityFilterfunc,
    const typename Impl::MdibIterator<typename T_Entity::ParentType>::FilterFunction &parent1Filterfunc
   ) const
{
    return typename Impl::MdibIterator<T_Entity>::FilterFunction(
                [entityFilterfunc, parent1Filterfunc, this]
                (const NotNull<SharedPtr<T_Entity>>& e) -> bool
                {
                    if (!entityFilterfunc(e))
                    {
                        return false;
                    }

                    const auto& parent1Handle = e->parent();
                    const auto parent1 = m_parentMdib.entity(parent1Handle);
                    if (!parent1)
                    {
                        return false;
                    }
                    return parent1Filterfunc(asNotNull(parent1));
                });
}



/// @brief Implementation of chain() with 2 parents
template<class T_Mdib>
template<class T_Entity>
inline typename Impl::MdibIterator<T_Entity>::FilterFunction MdibEntityFilters<T_Mdib>::chain(
    const typename Impl::MdibIterator<T_Entity>::FilterFunction &entityFilterfunc,
    const typename Impl::MdibIterator<typename T_Entity::ParentType>::FilterFunction &parent1Filterfunc,
    const typename Impl::MdibIterator<typename T_Entity::ParentType::ParentType>::FilterFunction &parent2Filterfunc
) const
{
    using T_Parent = typename T_Entity::ParentType;

    return typename Impl::MdibIterator<T_Entity>::FilterFunction(
                [entityFilterfunc, parent1Filterfunc, parent2Filterfunc, this]
                (const NotNull<SharedPtr<T_Entity>>& e) -> bool
                {
                    if (!entityFilterfunc(e))
                    {
                        return false;
                    }

                    const auto parent = m_parentMdib.entity(e->parent());
                    if (!parent)
                    {
                        return false;
                    }
                    const auto chainf = this->template chain<T_Parent>(
                                parent1Filterfunc, parent2Filterfunc);
                    return chainf(asNotNull(parent));
                });
}

/// @brief Implementation of chain() with 3 parents
template<class T_Mdib>
template<class T_Entity>
inline typename Impl::MdibIterator<T_Entity>::FilterFunction MdibEntityFilters<T_Mdib>::chain(
    const typename Impl::MdibIterator<T_Entity>::FilterFunction &entityFilterfunc,
    const typename Impl::MdibIterator<typename T_Entity::ParentType>::FilterFunction &parent1Filterfunc,
    const typename Impl::MdibIterator<typename T_Entity::ParentType::ParentType>::FilterFunction &parent2Filterfunc,
    const typename Impl::MdibIterator<typename T_Entity::ParentType::ParentType::ParentType>::FilterFunction &parent3Filterfunc
   ) const
{
    using T_Parent = typename T_Entity::ParentType;

    return typename Impl::MdibIterator<T_Entity>::FilterFunction(
                [entityFilterfunc, parent1Filterfunc, parent2Filterfunc, parent3Filterfunc, this]
                (const NotNull<SharedPtr<T_Entity>>& e) -> bool
                {
                    if (!entityFilterfunc(e))
                    {
                        return false;
                    }

                    const auto parent = m_parentMdib.entity(e->parent());
                    if (!parent)
                    {
                        return false;
                    }
                    const auto chainf = this->template chain<T_Parent>(
                                parent1Filterfunc, parent2Filterfunc, parent3Filterfunc);
                    return chainf(asNotNull(parent));
                });

}

/// @brief Implementation of typePath() with 1 parent
template<class T_Mdib>
template<class T_Entity>
inline typename Impl::MdibIterator<T_Entity>::FilterFunction MdibEntityFilters<T_Mdib>::typePath(
        const CodeId &parent1Code,
        const CodeId &entityCode) const
{
    using T_Parent1 = typename T_Entity::ParentType;
    return chain<T_Entity>(
                [=](const NotNull<SharedPtr<T_Entity>> &e) -> bool
                {
                    return Impl::MdibEntityFiltersHelper::filterTypeCode(e, entityCode);
                },
                [=](const NotNull<SharedPtr<T_Parent1>> &p) -> bool
                {
                    return Impl::MdibEntityFiltersHelper::filterTypeCode(p, parent1Code);
                }
            );
}

/// @brief Implementation of typePath() with 2 parents
template<class T_Mdib>
template<class T_Entity>
inline typename Impl::MdibIterator<T_Entity>::FilterFunction MdibEntityFilters<T_Mdib>::typePath(
        const CodeId &parent2Code,
        const CodeId &parent1Code,
        const CodeId &entityCode) const
{
    using T_Parent1 = typename T_Entity::ParentType;
    using T_Parent2 = typename T_Entity::ParentType::ParentType;
    return chain<T_Entity>(
                [=](const NotNull<SharedPtr<T_Entity>> &e) -> bool
                {
                    return Impl::MdibEntityFiltersHelper::filterTypeCode(e, entityCode);
                },
                [=](const NotNull<SharedPtr<T_Parent1>> &p) -> bool
                {
                    return Impl::MdibEntityFiltersHelper::filterTypeCode(p, parent1Code);
                },
                [=](const NotNull<SharedPtr<T_Parent2>> &p) -> bool
                {
                    return Impl::MdibEntityFiltersHelper::filterTypeCode(p, parent2Code);
                }
            );
}

/// @brief Implementation of typePath() with 3 parents
template<class T_Mdib>
template<class T_Entity>
inline typename Impl::MdibIterator<T_Entity>::FilterFunction MdibEntityFilters<T_Mdib>::typePath(
        const CodeId &parent3Code,
        const CodeId &parent2Code,
        const CodeId &parent1Code,
        const CodeId &entityCode) const
{
    using T_Parent1 = typename T_Entity::ParentType;
    using T_Parent2 = typename T_Entity::ParentType::ParentType;
    using T_Parent3 = typename T_Entity::ParentType::ParentType::ParentType;
    return chain<T_Entity>(
                [=](const NotNull<SharedPtr<T_Entity>> &e) -> bool
                {
                    return Impl::MdibEntityFiltersHelper::filterTypeCode(e, entityCode);
                },
                [=](const NotNull<SharedPtr<T_Parent1>> &p) -> bool
                {
                    return Impl::MdibEntityFiltersHelper::filterTypeCode(p, parent1Code);
                },
                [=](const NotNull<SharedPtr<T_Parent2>> &p) -> bool
                {
                    return Impl::MdibEntityFiltersHelper::filterTypeCode(p, parent2Code);
                },
                [=](const NotNull<SharedPtr<T_Parent3>> &p) -> bool
                {
                    return Impl::MdibEntityFiltersHelper::filterTypeCode(p, parent3Code);
                }
            );
}

} /* namespace Mdib */
} /* namespace DFL */
