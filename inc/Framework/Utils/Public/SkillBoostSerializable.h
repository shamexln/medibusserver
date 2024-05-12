#pragma once

#include <Framework/Utils/Private/StrongTypedefHelper.h>

#include <boost/serialization/nvp.hpp>

namespace DFL
{
namespace Skill
{
/**
 * @brief Adapter to enable T to be serialized via boost serialization
 * @ingroup Utils
 */
template<class T>
struct BoostSerializable : Impl::CrtpHelper<T, BoostSerializable>
{
    /**
     * @brief Requires T is serializeable
     */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar & ::boost::serialization::make_nvp("StrongTypedef", this->underlying().get());
    }
};

}
}
