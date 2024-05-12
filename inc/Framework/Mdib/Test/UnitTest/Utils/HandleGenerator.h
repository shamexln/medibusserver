#pragma once

#include <Framework/Mdib/Public/Model/Handle.h>

namespace DFLTest
{
namespace Mdib
{
namespace UnitTest
{

class HandleGenerator
{
    public:

        static DFL::Mdib::Handle uniqueHandle(const std::string& prefix);

        template<class T_Entity>
        static
        DFL::Mdib::BasicHandle<T_Entity> createUniqueHandle(const DFL::Mdib::BasicHandle<typename T_Entity::ParentType>& parentHandle);

};

template<class T_Entity>
inline
DFL::Mdib::BasicHandle<T_Entity> HandleGenerator::createUniqueHandle(const DFL::Mdib::BasicHandle<typename T_Entity::ParentType>& parentHandle)
{
    return DFL::Mdib::BasicHandle<T_Entity>(uniqueHandle(parentHandle.string()));
}

}
}
}
