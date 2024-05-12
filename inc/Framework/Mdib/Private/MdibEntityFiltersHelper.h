#pragma once

#include <Framework/Utils/Public/Utf8.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/CodedValueFactory.h>
#include <Framework/Mdib/Public/Model/CodedValueSemantic.h>
#include <Framework/Utils/Public/NotNull.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/**
 * @brief Helpers for \ref MdibEntityFilters.
 * @ingroup Mdib
 */
class MdibEntityFiltersHelper
{
    public:

        template <class T_Entity>
        static bool filterTypeCode(const NotNull<SharedPtr<T_Entity>>& entity, const CodeId& code);

};

template <class T_Entity>
inline bool MdibEntityFiltersHelper::filterTypeCode(const NotNull<SharedPtr<T_Entity>>& entity, const CodeId& code)
{
    const auto& descriptor = entity->descriptor();
    const auto& type = descriptor->type();
    if (!type)
    {
        return false;
    }
    return isSemanticallyEqual(*type, CodedValueFactory::create11073cfCode(code));
}

}
}
}
