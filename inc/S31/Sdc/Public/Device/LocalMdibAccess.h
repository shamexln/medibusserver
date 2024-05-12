#pragma once

#include <S31/Sdc/Public/Common/MdibAccess.h>
#include <S31/Sdc/Public/Device/DualChannelFactoryManager.h>
#include <S31/Sdc/Public/Device/LocalMdibAccessSmartPtrTypes.h>

#include <Framework/Mdib/Public/LocalMdibAccess.h>

namespace S31::Sdc
{

/**
 * @brief Reflects a decorated \ref DFL::Mdib::LocalMdibAccess that supports transport specific SDC functionality.
 * @ingroup S31SdcDevice
 */
class LocalMdibAccess: public DFL::Mdib::LocalMdibAccess, public MdibAccess
{
    public:
        /**
         * @brief Returns an instance to manage dual channel factories that are used by the \c S31::Sdc component to
         * create \ref S31::Safety::DualChannelComparator "dual channel comparators".
         */
        virtual DFL::NotNull<std::shared_ptr<S31::Sdc::DualChannelFactoryManager>> dualChannelFactoryManager() const = 0;
};

}