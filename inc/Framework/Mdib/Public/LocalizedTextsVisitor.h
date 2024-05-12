#pragma once

#include <functional>
#include <utility>
#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/Model/LocalizedText.h>
#include <Framework/Mdib/Public/Model/LocalizedTexts.h>
#include <Framework/Mdib/Public/Utils/VisitMdib.h>
#include <Framework/Mdib/Private/ExpImp.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Type of the function that the visitor user gives to handle @ref DFL::Mdib::LocalizedTexts.
 * @ingroup Mdib
 */
using LocalizedTextsHandler = std::function<void(const DFL::Mdib::LocalizedTexts&)>;

/**
 * @brief Which parts of the entities should be visited.
 * @details These are the entity parts that are needed currently. There is no descriptor-only part.
 * @ingroup Mdib
 */
enum class EntityPart
{
    DescriptorAndState,
    State
};

/**
 * @brief Visitor class to call a function for each entity's localized texts.
 *
 * @details With the @ref EntityPart it's possible to define which localized texts locations in the @ref DFL::Mdib::Mdib
 * or @ref DFL::Mdib::MdibChangeSet are visited.
 *
 * Note that in the case of a change set the removed entities are not visited.
 *
 * @ingroup Mdib
 */
class LocalizedTextsVisitor
{
    public:
        /// @brief Ctor to visit a @ref DFL::Mdib::Mdib
        LocalizedTextsVisitor(const DFL::Mdib::Mdib& mdib, LocalizedTextsHandler handler, EntityPart entityPart) :
                m_mdib(&mdib),
                m_changeSet(nullptr),
                m_handler(std::move(handler)),
                m_entityPart(entityPart)
        {
        }

        /// @brief Ctor to visit a @ref DFL::Mdib::MdibChangeSet
        LocalizedTextsVisitor(const DFL::Mdib::MdibChangeSet& changeSet, LocalizedTextsHandler handler, EntityPart entityPart) :
                m_mdib(nullptr),
                m_changeSet(&changeSet),
                m_handler(std::move(handler)),
                m_entityPart(entityPart)
        {
        }

        /**
         * @brief visitEntity is called for each entity
         * @details invokes the appropriate wrapper to invoke the function provided
         */
        template<class T_Entity>
        void visitEntity()
        {
            Impl::TypeVisitor<LocalizedTexts> typeVisitor{m_handler};
            if (m_mdib)
            {
                if (m_entityPart == EntityPart::DescriptorAndState)
                {
                    Impl::MdibEntityDescriptorVisitor<Impl::TypeVisitor<LocalizedTexts>> visitor(typeVisitor, *m_mdib);
                    visitor.template visitEntity<T_Entity>();
                }
                Impl::MdibEntityStateVisitor<Impl::TypeVisitor<LocalizedTexts>> visitor(typeVisitor, *m_mdib);
                visitor.template visitEntity<T_Entity>();
            }
            else if (m_changeSet)
            {
                if (m_entityPart == EntityPart::DescriptorAndState)
                {
                    Impl::ChangeSetEntityDescriptorVisitor<Impl::TypeVisitor<LocalizedTexts>> visitor(typeVisitor, *m_changeSet);
                    visitor.template visitEntity<T_Entity>();
                }
                Impl::ChangeSetEntityStateVisitor<Impl::TypeVisitor<LocalizedTexts>> visitor(typeVisitor, *m_changeSet);
                visitor.template visitEntity<T_Entity>();
            }
        }

    private:
        const DFL::Mdib::Mdib* m_mdib;
        const DFL::Mdib::MdibChangeSet* m_changeSet;
        const LocalizedTextsHandler m_handler;
        const EntityPart m_entityPart;
};

}
}
