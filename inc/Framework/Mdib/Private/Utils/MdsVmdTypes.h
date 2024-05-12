#pragma once

namespace DFL
{
namespace Mdib
{
namespace Impl
{
/**
 * @brief Base class of all MdsVmd type information classes.
 * @ingroup Mdib
 */
class MdsVmdTypesBase {};
}
}
}

/**
 * @brief Type information of \e baseEntity.
 * @details For entity types that have a Mds... and a Vmd... flavour. E.g.: Creates from @ref DFL::Mdib::AlertSystem
 * a class AlertSystemTypes that contains the types of its state and descriptor and the derived @ref DFL::Mdib::MdsAlertSystem
 * and @ref DFL::Mdib::VmdAlertSystem
 * @ingroup Mdib
 */
#define DFL_MDIB_MDSVMD_TYPES(baseEntity) \
    class baseEntity##Types : public Impl::MdsVmdTypesBase{ \
        public: \
            using StateType = baseEntity##State; \
            using DescriptorType = baseEntity##Descriptor; \
            using StateBuilderType = baseEntity##StateBuilder; \
            using DescriptorBuilderType = baseEntity##DescriptorBuilder; \
            using MdsType = Mds##baseEntity; \
            using VmdType = Vmd##baseEntity; \
    };
