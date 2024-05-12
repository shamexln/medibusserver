#pragma once

#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/MdibVersion.h>
#include <Framework/Mdib/Public/Model/Uri.h>

#include <Framework/Utils/Public/NotNull.h>

#include <boost/optional/optional.hpp>

#include <map>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/**
 * @brief General MDIB entity descriptive part.
 * @details An MDIB entity descriptive part has a
 *
 * - handle for unique identification
 * - pointer to a descriptor data container that changes in a low frequency (mostly static)
 * - descriptor version that identifies the enclosed descriptor's version
 *
 * @ingroup Mdib
 */
template<class T_Entity, class T_DescrBuilder, class T_Parent>
class MdibEntityDescriptor
{
    public:
        using EntityType = T_Entity;
        using DescriptorBuilderType = T_DescrBuilder;
        using DescriptorType = typename T_DescrBuilder::BuiltType;
        using ParentType = T_Parent;

        /**
         * @brief Unique identification of the entity.
         */
        const BasicHandle<EntityType>& handle() const;

        /**
         * @brief Version of the encapsulated descriptor.
         */
        VersionCounter descriptorVersion() const;

        /**
         * @brief Encapsulated descriptor.
         */
        DFL::NotNull<SharedPtr<DescriptorType>> descriptor() const;

        /**
         * @brief Parent entity.
         * @details
         * - \ref Mds shall always return \c boost::none, other entities should always possess a parent entity.
         * - There might be no parent entity in remote MDIBs. In this case the parent is allowed to be \c boost::none for entities other than \ref Mds.
         * @return The handle of the parent entity or \c boost::none if no parent exists.
         */
        const BasicHandle<T_Parent>& parent() const;

    protected:
        /**
         * Constructor to populate all fields.
         */
        MdibEntityDescriptor(BasicHandle<T_Entity> handle,
                             DFL::NotNull<SharedPtr<DescriptorType>> descriptor,
                             VersionCounter versionCounter,
                             BasicHandle<T_Parent> parent);

    private:
        BasicHandle<EntityType> m_handle;
        VersionCounter m_descriptorVersion;
        DFL::NotNull<SharedPtr<DescriptorType>> m_descriptor;
        BasicHandle<T_Parent> m_parent;
};

template<class T_Entity, class T_DescrBuilder, class T_Parent>
MdibEntityDescriptor<T_Entity, T_DescrBuilder, T_Parent>::MdibEntityDescriptor(BasicHandle<T_Entity> handle,
                                                                               DFL::NotNull<SharedPtr<DescriptorType>> descriptor,
                                                                               VersionCounter versionCounter,
                                                                               BasicHandle<T_Parent> parent) :
        m_handle(std::move(handle)),
        m_descriptorVersion(versionCounter),
        m_descriptor(std::move(descriptor)),
        m_parent(std::move(parent))
{
}

template<class T_Entity, class T_DescrBuilder, class T_Parent>
const BasicHandle<T_Entity>& MdibEntityDescriptor<T_Entity, T_DescrBuilder, T_Parent>::handle() const
{
    return m_handle;
}

template<class T_Entity, class T_DescrBuilder, class T_Parent>
VersionCounter MdibEntityDescriptor<T_Entity, T_DescrBuilder, T_Parent>::descriptorVersion() const
{
    return m_descriptorVersion;
}

template<class T_Entity, class T_DescrBuilder, class T_Parent>
DFL::NotNull<SharedPtr<typename T_DescrBuilder::BuiltType>> MdibEntityDescriptor<T_Entity, T_DescrBuilder, T_Parent>::descriptor() const
{
    return m_descriptor;
}

template<class T_Entity, class T_DescrBuilder, class T_Parent>
const BasicHandle<T_Parent>& MdibEntityDescriptor<T_Entity, T_DescrBuilder, T_Parent>::parent() const
{
    return m_parent;
}

}
}
}
