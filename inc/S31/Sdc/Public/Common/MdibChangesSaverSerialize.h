#pragma once

#include <S31/Sdc/Private/Common/MdibChangesSaverSerializeHelper.h>
#include <S31/Sdc/Public/Common/MdibChangesSaver.h>
#include <S31/Base/S31Only/Exception.h>

#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibChangeType.h>
#include <Framework/Mdib/Public/Utils/Entities.h>
#include <Framework/Mdib/Public/Utils/EntityLists.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

#include <memory>
#include <utility>

BOOST_SERIALIZATION_SPLIT_FREE(::S31::Sdc::Experimental::MdibChangesSaver)
// NOLINTNEXTLINE(clang-diagnostic-old-style-cast, clang-diagnostic-zero-as-null-pointer-constant, cert-err58-cpp)
BOOST_CLASS_VERSION(::S31::Sdc::Experimental::MdibChangesSaver, 0)
BOOST_CLASS_TRACKING(::S31::Sdc::Experimental::MdibChangesSaver, boost::serialization::track_never)

namespace boost::serialization
{

template <class Archive>
void save(Archive& ar, const ::S31::Sdc::Experimental::MdibChangesSaver& src, const unsigned int /*version*/)
{
    const auto& changeType = src.changeType();
    ar & make_nvp("ChangeType", changeType);

    const auto& changes = src.changes();
    if (!changes)
    {
        S31_THROW_EXCEPTION(S31::InternalConsistencyFailure, "Missing changes to serialize in " << __func__);
    }

    switch (changeType)
    {
        case DFL::Mdib::MdibChangeType::AlertStates:
        {
            using Entities = DFL::Mdib::Entities<DFL_MDIB_ENTITY_ALERTS>;
            ::S31::Sdc::Experimental::Impl::saveUpdatedStateChanges<Entities>(ar, *changes);
        }
        break;

        case DFL::Mdib::MdibChangeType::ComponentStates:
        {
            using Entities = DFL::Mdib::Entities<DFL_MDIB_ENTITY_COMPONENTS>;
            ::S31::Sdc::Experimental::Impl::saveUpdatedStateChanges<Entities>(ar, *changes);
        }
        break;

        case DFL::Mdib::MdibChangeType::MetricStates:
        {
            using Entities = DFL::Mdib::Entities<DFL_MDIB_ENTITY_METRIC_REPORT>;
            ::S31::Sdc::Experimental::Impl::saveUpdatedStateChanges<Entities>(ar, *changes);
        }
        break;

        case DFL::Mdib::MdibChangeType::OperationStates:
        {
            using Entities = DFL::Mdib::Entities<DFL_MDIB_ENTITY_OPERATIONS>;
            ::S31::Sdc::Experimental::Impl::saveUpdatedStateChanges<Entities>(ar, *changes);
        }
        break;

        case DFL::Mdib::MdibChangeType::WaveformStream:
        {
            using Entities = DFL::Mdib::Entities<DFL_MDIB_ENTITY_WAVEFORM_STREAM>;
            ::S31::Sdc::Experimental::Impl::saveUpdatedStateChanges<Entities>(ar, *changes);
        }
        break;

        case DFL::Mdib::MdibChangeType::ContextStates:
        {
            using Entities = DFL::Mdib::Entities<DFL_MDIB_ENTITY_CONTEXT_STATES>;
            ::S31::Sdc::Experimental::Impl::saveAllChanges<Entities>(ar, *changes);
        }
        break;

        case DFL::Mdib::MdibChangeType::Description:
        {
            using Entities = DFL::Mdib::Entities<DFL_MDIB_ENTITY_ALL>;
            ::S31::Sdc::Experimental::Impl::saveAllChanges<Entities>(ar, *changes);
        }
        break;

        default:
            S31_THROW_EXCEPTION(S31::InternalDataMappingFailed, "Unknown change type in " <<__func__);
    }
}

template <class Archive>
void load(Archive& ar, ::S31::Sdc::Experimental::MdibChangesSaver& dst, const unsigned int /*version*/)
{
    DFL::Mdib::MdibChangeType changeType{};
    ar & make_nvp("ChangeType", changeType);

    DFL::Mdib::MdibChangeSet changes;
    switch (changeType)
    {
        case DFL::Mdib::MdibChangeType::AlertStates:
        {
            using Entities = DFL::Mdib::Entities<DFL_MDIB_ENTITY_ALERTS>;
            ::S31::Sdc::Experimental::Impl::loadUpdatedStateChanges<Entities>(ar, changes);
        }
        break;

        case DFL::Mdib::MdibChangeType::ComponentStates:
        {
            using Entities = DFL::Mdib::Entities<DFL_MDIB_ENTITY_COMPONENTS>;
            ::S31::Sdc::Experimental::Impl::loadUpdatedStateChanges<Entities>(ar, changes);
        }
        break;

        case DFL::Mdib::MdibChangeType::MetricStates:
        {
            using Entities = DFL::Mdib::Entities<DFL_MDIB_ENTITY_METRIC_REPORT>;
            ::S31::Sdc::Experimental::Impl::loadUpdatedStateChanges<Entities>(ar, changes);
        }
        break;

        case DFL::Mdib::MdibChangeType::OperationStates:
        {
            using Entities = DFL::Mdib::Entities<DFL_MDIB_ENTITY_OPERATIONS>;
            ::S31::Sdc::Experimental::Impl::loadUpdatedStateChanges<Entities>(ar, changes);
        }
        break;

        case DFL::Mdib::MdibChangeType::WaveformStream:
        {
            using Entities = DFL::Mdib::Entities<DFL_MDIB_ENTITY_WAVEFORM_STREAM>;
            ::S31::Sdc::Experimental::Impl::loadUpdatedStateChanges<Entities>(ar, changes);
        }
        break;

        case DFL::Mdib::MdibChangeType::ContextStates:
        {
            using Entities = DFL::Mdib::Entities<DFL_MDIB_ENTITY_CONTEXT_STATES>;
            ::S31::Sdc::Experimental::Impl::loadAllChanges<Entities>(ar, changes);
        }
        break;

        case DFL::Mdib::MdibChangeType::Description:
        {
            using Entities = DFL::Mdib::Entities<DFL_MDIB_ENTITY_ALL>;
            ::S31::Sdc::Experimental::Impl::loadAllChanges<Entities>(ar, changes);
        }
        break;

        default:
            S31_THROW_EXCEPTION(S31::InternalDataMappingFailed, "Unknown change type in " << __func__);
    }

    dst.changeType(changeType);
    dst.changes(std::make_shared<const DFL::Mdib::MdibChangeSet>(std::move(changes)));
}

}
