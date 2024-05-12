#pragma once

#include <S31/Sdc/Private/Common/IWebService.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/LatestMdibSmartPtrTypes.h>

namespace S31::Sdc::Impl
{

/**
 * \brief Realization of the BICEPS GET service
 *
 * \details Note that BicepsGetService has a tight coupling \ref gSOAP. Never use this class directly. Instead, this class uses
 * the MDIB to perform any remote requests.
 *
 * \ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP BicepsGetService : public S31::Sdc::Impl::IWebService
{
    public:
        /**
         * @brief The BICEPS GET service requires an \ref Mdib instance for read access.
         */
        explicit BicepsGetService(DFL::Mdib::LatestMdibWeakPtr latestMdib);

        /**
         * @brief Implementation of S31::Sdc::Impl::IWebService.
         *
         * @details Is used to dispatch incoming SOAP web service requests.
         */
        int dispatch(struct soap* soapHandle) override;

    private:
        DFL::Mdib::LatestMdibWeakPtr m_latestMdib;
};

}
