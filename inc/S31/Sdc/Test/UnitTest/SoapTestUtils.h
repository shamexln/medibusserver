#pragma once

#include <memory>

#include <S31/Sdc/Private/Common/SoapContextPool.h>
#include <S31/Sdc/Private/Common/SoapPtr.h>

#include <Framework/Utils/Public/NotNull.h>

namespace S31Test::Sdc::UnitTest
{

inline DFL::NotNull<S31::Sdc::Impl::SoapPtr> createSoapPtr()
{
    auto pool = std::make_shared<S31::Sdc::Impl::SoapContextPool>();
    return pool->getSoapPtr();
}

}
