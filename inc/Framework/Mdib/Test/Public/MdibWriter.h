#pragma once

#include <Framework/Mdib/Public/LocalMdibAccess.h>
#include <Framework/Mdib/Public/Model/Metric/RealTimeSampleArrayMetric.h>
#include <Framework/Mdib/Public/WriteResult.h>
#include <Framework/Mdib/Public/WriteResultIo.h>

#include <Framework/Config/Public/Attributes.h>
#include <Framework/Format/Public/Stream.h>
#include <Framework/Utils/Public/NotNull.h>

/**
 * @brief Ensures that the given Mdib write operation succeeds.
 *
 * Usage example: ASSERT_MDIB_WRITE_SUCCESS(localAccess->writeDescription(changes));
 */
#define ASSERT_MDIB_WRITE_SUCCESS(writeOperation) \
    do {\
        const DFL::Mdib::WriteResult& resultFromWriteOperation = writeOperation;\
        ASSERT_EQ(DFL::Mdib::WriteStatus::Success, resultFromWriteOperation.status()) << resultFromWriteOperation;\
    } while(0)

/**
 * @brief Asserts that the given Mdib write operation succeeds.
 *
 * @details
 * Throws an exception if there was a write error.
 * Usage example: THROW_ON_MDIB_WRITE_FAIL(localAccess->writeDescription(changes));
 *
 * With GoogleTest prefer ASSERT_MDIB_WRITE_SUCCESS if possible.
 */
#define THROW_ON_MDIB_WRITE_FAIL(writeOperation) \
    do {\
        const DFL::Mdib::WriteResult& resultFromWriteOperation = writeOperation;\
        if (resultFromWriteOperation.status() != DFL::Mdib::WriteStatus::Success)\
        {\
            DFL::Format::Stream exceptionMsg;\
            exceptionMsg << "Updating MDIB failed with: " << resultFromWriteOperation << "~" << __FILE__ << ":" << __LINE__;\
            throw std::runtime_error(exceptionMsg.cStr());\
        }\
    } while(0)

namespace DFL::Mdib::Test
{

/**
 * @brief Helper to write in MDIB.
 * @ingroup Mdib
 */
class MdibWriter
{
    public:
        /**
         * @brief Updates a descriptor in given local MDIB.
         */
        template<typename Entity_T>
        static void writeDescriptor(LocalMdibAccess& mdib,
                                    const NotNull<SharedPtr<Entity_T>>& oldEntity,
                                    const typename Entity_T::DescriptorBuilderType& desc);
        /**
         * @brief Updates a descriptor with state in given local MDIB.
         */
        template<typename Entity_T>
        static void writeDescriptor(LocalMdibAccess& mdib,
                                    const NotNull<SharedPtr<Entity_T>>& oldEntity,
                                    const typename Entity_T::DescriptorBuilderType& desc,
                                    const typename Entity_T::StateBuilderType& state);

        /**
         * @brief Updates a component state in given local MDIB.
         */
        template<typename Entity_T>
        static void writeComponentState(
            LocalMdibAccess& mdib,
            const NotNull<SharedPtr<Entity_T>>& oldEntity,
            const typename Entity_T::StateBuilderType& state);

        /**
         * @brief Updates an alert state in given local MDIB.
         */
        template<typename Entity_T>
        static void writeAlertState(LocalMdibAccess& mdib,
                                    const NotNull<SharedPtr<Entity_T>>& oldEntity,
                                    const typename Entity_T::StateBuilderType& state);

        /**
         * @brief Updates a metric state in given local MDIB.
         */
        template<typename Entity_T>
        static void writeMetricState(LocalMdibAccess& mdib,
                                    const NotNull<SharedPtr<Entity_T>>& oldEntity,
                                    const typename Entity_T::StateBuilderType& state);

        /**
         * @brief Updates a waveform state in given local MDIB.
         */
        static void writeSampleArrayMetricState(LocalMdibAccess& mdib,
                                                const NotNull<SharedPtr<RealTimeSampleArrayMetric>>& oldEntity,
                                                const RealTimeSampleArrayMetric::StateBuilderType& state);
};

template<typename Entity_T>
void MdibWriter::writeDescriptor(LocalMdibAccess& mdib,
                                 const NotNull<SharedPtr<Entity_T>>& oldEntity,
                                 const typename Entity_T::DescriptorBuilderType& desc)
{
    MdibChangeSet changes;
    changes.addOneToUpdate(EntityFactory::create(oldEntity, desc));
    THROW_ON_MDIB_WRITE_FAIL(mdib.writeDescription(changes));
}

template<typename Entity_T>
void MdibWriter::writeDescriptor(LocalMdibAccess& mdib,
                                 const NotNull<SharedPtr<Entity_T>>& oldEntity,
                                 const typename Entity_T::DescriptorBuilderType& desc,
                                 const typename Entity_T::StateBuilderType& state)
{
    MdibChangeSet changes;
    changes.addOneToUpdate(EntityFactory::create(oldEntity, desc, state));
    THROW_ON_MDIB_WRITE_FAIL(mdib.writeDescription(changes));
}

template <typename Entity_T>
void MdibWriter::writeComponentState(
    LocalMdibAccess& mdib,
    const NotNull<SharedPtr<Entity_T>>& oldEntity,
    const typename Entity_T::StateBuilderType& state)
{
    MdibChangeSet changes;
    changes.addOneToUpdate(EntityFactory::create(oldEntity, state));
    THROW_ON_MDIB_WRITE_FAIL(mdib.writeComponentStates(changes));
}

template<typename Entity_T>
void MdibWriter::writeAlertState(LocalMdibAccess& mdib,
                                 const NotNull<SharedPtr<Entity_T>>& oldEntity,
                                 const typename Entity_T::StateBuilderType& state)
{
    MdibChangeSet changes;
    changes.addOneToUpdate(EntityFactory::create(oldEntity, state));
    THROW_ON_MDIB_WRITE_FAIL(mdib.writeAlertStates(changes));
}

template<typename Entity_T>
void MdibWriter::writeMetricState(LocalMdibAccess& mdib,
                                 const NotNull<SharedPtr<Entity_T>>& oldEntity,
                                 const typename Entity_T::StateBuilderType& state)
{
    MdibChangeSet changes;
    changes.addOneToUpdate(EntityFactory::create(oldEntity, state));
    THROW_ON_MDIB_WRITE_FAIL(mdib.writeMetricStates(changes));
}

inline void MdibWriter::writeSampleArrayMetricState(LocalMdibAccess& mdib,
                                                    const NotNull<SharedPtr<RealTimeSampleArrayMetric>>& oldEntity,
                                                    const RealTimeSampleArrayMetric::StateBuilderType& state)
{
    MdibChangeSet changes;
    changes.addOneToUpdate(EntityFactory::create(oldEntity, state));
    THROW_ON_MDIB_WRITE_FAIL(mdib.writeSampleArrayMetricStates(changes));
}

}
