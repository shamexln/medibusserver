#pragma once

#include <S31/Sdc/Private/Common/ISoapContextPool.h>
#include <S31/Sdc/Private/Common/SoapPtr.h>

#include <Framework/Utils/Public/CompilerGenerated.h>

namespace S31::Sdc::Test
{

/**
 * @brief Implementation of \ref S31::Sdc::Impl::ISoapContextPool which always returns only one specific \ref S31::Sdc::Impl::SoapPtr.
 * @ingroup S31SdcCommon
 */
class SoapContextPoolMock : public S31::Sdc::Impl::ISoapContextPool
{
    DFL_NOT_COPYABLE(SoapContextPoolMock)
    public:
        explicit SoapContextPoolMock(DFL::NotNull<S31::Sdc::Impl::SoapPtr> soapPtr) :
                m_soapPtr(std::move(soapPtr))
        {
        }

        DFL::NotNull<S31::Sdc::Impl::SoapPtr> getSoapPtr() override
        {
            return std::move(m_soapPtr);
        }

        DFL::NotNull<S31::Sdc::Impl::SoapPtr> getUdpSoapPtr() override
        {
            return std::move(m_soapPtr);
        }

        void setPeerAuthorizationCallback(const PeerAuthorizationCallback& /*callback*/) override
        {
        }

    private:
        DFL::NotNull<S31::Sdc::Impl::SoapPtr> m_soapPtr;
};

}
