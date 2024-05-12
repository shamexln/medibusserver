#pragma once

#include <S31/Log/Public/Logger.h>
#include <S31/Test/S31Only/Exception.h>

#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/HandleIo.h>
#include <Framework/Utils/Public/NotNull.h>

namespace S31::Sdc::Test
{

template <typename Entity_T>
DFL::NotNull<DFL::Mdib::SharedPtr<Entity_T>> firstEntity(const DFL::Mdib::Mdib& mdib)
{
    auto entityRange = mdib.range<Entity_T>();
    if (entityRange.empty())
    {
        DFL::Format::Stream msg;
        msg << "No " << typeid(Entity_T).name()  << " in MDIB available to change";
        S31_STREAM_ERROR_LOGGER("Test", msg.cStr());
        THROW_EXCEPTION(msg.cStr());
    }
    return *(entityRange.begin());
}



class Matcher
{
    public:
        using MdibMatcher = std::function<bool(const DFL::Mdib::Mdib&)>;
        using ChangesMatcher = std::function<bool(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>&, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>&)>;

        /**
         * @brief Matches for existing entity change.
         * @details The given entityMatcher allows to filter for a certain change in the entity.
         */
        template<typename Entity_T>
        static Matcher createModifiedEntityMatcher(const DFL::Mdib::BasicHandle<Entity_T>& handle,
                                                   std::function<bool(const Entity_T&)> entityMatcher)
        {
            return Matcher(createMdibMatcher(handle, entityMatcher), createChangesMatcher(handle, entityMatcher));
        }

        /**
         * @brief Matches for existing entity change.
         * @details By default any change of the entity matches so that the matcher can be used just to watch for a Mdib/entity change.
         */
        template<typename Entity_T>
        static Matcher createModifiedEntityMatcher(const DFL::Mdib::BasicHandle<Entity_T>& handle)
        {
            std::function<bool(const Entity_T&)> entityMatcher{[](const Entity_T&) {return true;}};
            return Matcher::createModifiedEntityMatcher(handle, entityMatcher);
        }

        /**
         * @brief Matches new entity.
         */
        template<typename Entity_T>
        static Matcher createNewEntityMatcher(const DFL::Mdib::BasicHandle<Entity_T>& handle)
        {
            return Matcher(createNewEntityMdibMatcher(handle), createNewEntityChangesMatcher(handle));
        }

        /**
         * @brief Matches removed entity.
         */
        template<typename Entity_T>
        static Matcher createRemovedEntityMatcher(const DFL::Mdib::BasicHandle<Entity_T>& handle)
        {
            return Matcher(createRemovedEntityMdibMatcher(handle), createRemovedEntityChangesMatcher(handle));
        }


        MdibMatcher mdibMatcher;
        ChangesMatcher changesMatcher;
    private:
        explicit Matcher(MdibMatcher m, ChangesMatcher c):
                mdibMatcher(std::move(m)),
                changesMatcher(std::move(c))
        {
        }

        template<typename Entity_T>
        static MdibMatcher createMdibMatcher(const DFL::Mdib::BasicHandle<Entity_T> handle, std::function<bool(const Entity_T&)> entityMatcher);

        template<typename Entity_T>
        static ChangesMatcher createChangesMatcher(const DFL::Mdib::BasicHandle<Entity_T> handle, std::function<bool(const Entity_T&)> entityMatcher);

        template<typename Entity_T>
        static MdibMatcher createNewEntityMdibMatcher(const DFL::Mdib::BasicHandle<Entity_T> handle);

        template<typename Entity_T>
        static ChangesMatcher createNewEntityChangesMatcher(const DFL::Mdib::BasicHandle<Entity_T> handle);

        template<typename Entity_T>
        static MdibMatcher createRemovedEntityMdibMatcher(const DFL::Mdib::BasicHandle<Entity_T> handle);

        template<typename Entity_T>
        static ChangesMatcher createRemovedEntityChangesMatcher(const DFL::Mdib::BasicHandle<Entity_T> handle);
};

template<typename Entity_T>
inline Matcher::MdibMatcher Matcher::createMdibMatcher(const DFL::Mdib::BasicHandle<Entity_T> handle, std::function<bool(const Entity_T&)> entityMatcher)
{
    return [=](const DFL::Mdib::Mdib& mdib){
        if (auto foundEntity = mdib.entity(handle))
        {
            if (const auto matches = entityMatcher(*foundEntity))
            {
                S31_STREAM_INFO_LOGGER("Test", "changes in MDIB as expected in ", foundEntity->handle());
                return true;
            }
            S31_STREAM_INFO_LOGGER("Test", "no changes in MDIB as expected in", foundEntity->handle());
            return false;
        }
        S31_STREAM_WARN_LOGGER("Test", "entity ", handle," should be in MDIB");
        return false;
    };
}

template<typename Entity_T>
inline Matcher::ChangesMatcher Matcher::createChangesMatcher(const DFL::Mdib::BasicHandle<Entity_T> handle, std::function<bool(const Entity_T&)> entityMatcher)
{
    return [=](const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& /*mdib*/, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes){
        if (auto foundEntity = changes->updatedEntity(handle))
        {
            if (const auto matches = entityMatcher(*foundEntity))
            {
                S31_STREAM_INFO_LOGGER("Test", "MDIB changes as expected in ", foundEntity->handle());
                return true;
            }
            S31_STREAM_INFO_LOGGER("Test", "MDIB changes in a different way as expected in ", foundEntity->handle());
            return false;
        }
        S31_STREAM_INFO_LOGGER("Test", "entity ", handle," not in changes");
        return false;
    };
}

template<typename Entity_T>
inline Matcher::MdibMatcher Matcher::createNewEntityMdibMatcher(const DFL::Mdib::BasicHandle<Entity_T> handle)
{
    return [=](const DFL::Mdib::Mdib& mdib){
        if (auto foundEntity = mdib.entity(handle))
        {
            S31_STREAM_INFO_LOGGER("Test", "MDIB has new entity ", foundEntity->handle());
            return true;
        }
        S31_STREAM_WARN_LOGGER("Test", "entity ", handle," NOT in MDIB");
        return false;
    };
}

template<typename Entity_T>
inline Matcher::ChangesMatcher Matcher::createNewEntityChangesMatcher(const DFL::Mdib::BasicHandle<Entity_T> handle)
{
    return [=](const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& /*mdib*/, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes){
        if (auto foundEntity = changes->insertedEntity(handle))
        {
            S31_STREAM_INFO_LOGGER("Test", "MDIB changes contains new entity ", foundEntity->handle());
            return true;
        }
        S31_STREAM_INFO_LOGGER("Test", "new entity ", handle," not in MDIB changes");
        return false;
    };
}

template<typename Entity_T>
inline Matcher::MdibMatcher Matcher::createRemovedEntityMdibMatcher(const DFL::Mdib::BasicHandle<Entity_T> handle)
{
    return [=](const DFL::Mdib::Mdib& mdib){
        if (auto foundEntity = mdib.entity(handle))
        {
            S31_STREAM_INFO_LOGGER("Test", "MDIB has new entity ", foundEntity->handle());
            return false;
        }
        S31_STREAM_INFO_LOGGER("Test", "entity ", handle," NOT in MDIB");
        return true;
    };
}

template<typename Entity_T>
inline Matcher::ChangesMatcher Matcher::createRemovedEntityChangesMatcher(const DFL::Mdib::BasicHandle<Entity_T> handle)
{
    return [=](const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& /*mdib*/, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes){
        if (auto foundEntity = changes->removedEntity(handle))
        {
            S31_STREAM_INFO_LOGGER("Test", "MDIB change set contains removed entity ", foundEntity->handle());
            return true;
        }
        S31_STREAM_INFO_LOGGER("Test", "Removed entity ", handle," not in MDIB changes");
        return false;
    };
}

}
