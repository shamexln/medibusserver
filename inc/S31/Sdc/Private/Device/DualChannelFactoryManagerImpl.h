#pragma once

#include <S31/Sdc/Public/Device/DualChannelFactoryManager.h>

#include <Framework/Mdib/Public/Model/Handle.h>

#include <mutex>

namespace S31::Sdc::Impl
{

/**
 * @brief Default implementation of \ref S31::Sdc::DualChannelFactoryManager.
 * @ingroup S31SdcDevice
 */
class DualChannelFactoryManagerImpl: public S31::Sdc::DualChannelFactoryManager
{
    public:
        void remove(const S31::Safety::DualChannelId& selectorId) override;
        void set(const S31::Safety::DualChannelId& selectorId, const DFL::NotNull<std::shared_ptr<S31::Safety::DualChannelFactory>>& dualChannelFactory) override;
        std::shared_ptr<S31::Safety::DualChannelFactory> get(const S31::Safety::DualChannelId& selectorId) const override;

    private:
        using DualChannelFactories = std::map<S31::Safety::DualChannelId, DFL::NotNull<std::shared_ptr<S31::Safety::DualChannelFactory>>>;

        mutable std::mutex m_dualChannelFactoriesMutex;
        DualChannelFactories m_dualChannelFactories;
};

inline void DualChannelFactoryManagerImpl::remove(const S31::Safety::DualChannelId& selectorId)
{
    std::lock_guard<std::mutex> const lock(m_dualChannelFactoriesMutex);
    m_dualChannelFactories.erase(selectorId);
}

inline void DualChannelFactoryManagerImpl::set(const S31::Safety::DualChannelId& selectorId, const DFL::NotNull<std::shared_ptr<S31::Safety::DualChannelFactory>>& dualChannelFactory)
{
    std::lock_guard<std::mutex> const lock(m_dualChannelFactoriesMutex);
    m_dualChannelFactories.erase(selectorId);
    m_dualChannelFactories.insert(std::make_pair(selectorId, dualChannelFactory));
}

inline std::shared_ptr<S31::Safety::DualChannelFactory> DualChannelFactoryManagerImpl::get(const S31::Safety::DualChannelId& selectorId) const
{
    std::lock_guard<std::mutex> const lock(m_dualChannelFactoriesMutex);
    auto dualChannelFactoryIt = m_dualChannelFactories.find(selectorId);
    if (dualChannelFactoryIt != m_dualChannelFactories.end())
    {
        return dualChannelFactoryIt->second.get();
    }

    return nullptr;
}

}
