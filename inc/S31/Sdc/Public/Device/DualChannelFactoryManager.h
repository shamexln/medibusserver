#pragma once

#include <S31/Safety/Public/DualChannel.h>
#include <S31/Safety/Public/DualChannelFactory.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::Sdc
{

/**
 * @brief Manages \ref S31::Safety::DualChannelFactory instances to create \ref S31::Safety::DualChannelComparator "comparators".
 * @details The %DualChannelFactoryManager has to be configured to let incoming set request handlers process dual channel information.
 * On the client side the \ref S31::Safety::DualChannelComparator is passed in.
 * @ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP DualChannelFactoryManager
{
    public:
        virtual ~DualChannelFactoryManager() noexcept = default;

        /**
         * @brief Removes a specific dual channel factory from manager.
         */
        virtual void remove(const S31::Safety::DualChannelId& selectorId) = 0;

        /**
         * @brief Sets a specific dual channel factory.
         * @param selectorId Defines the selector identifier that specifies the dual channel the given dual channel factory creates comparators for.
         * Any selector identifier is required to be unique across the MDIB (including \ref S31::Safety::ContextId).
         * @param dualChannelFactory The factory that can produce dual channel comparators.
         * \note See IEEE 11073-20702 clause 9.2.3.5, \c /mdpws:Selector/\@Id: ATTRIBUTE designates a unique identifier over all mdpws:Selector elements.
         */
        virtual void set(const S31::Safety::DualChannelId& selectorId, const DFL::NotNull<std::shared_ptr<S31::Safety::DualChannelFactory>>& dualChannelFactory) = 0;

        /**
         * @brief Seeks a specific dual channel factory.
         * @return The dual channel factory if found, otherwise \c nullptr.
         */
        virtual std::shared_ptr<S31::Safety::DualChannelFactory> get(const S31::Safety::DualChannelId& selectorId) const = 0;
};

}
