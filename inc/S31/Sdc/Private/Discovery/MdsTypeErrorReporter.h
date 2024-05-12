#pragma once

#include <S31/Sdc/Public/Discovery/LocationContextDiscovery.h>
#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <mutex>
#include <map>

namespace S31::Sdc::Impl
{

/**
 * @brief Tracks devices of the given (own) Mds type on the location and sets the according RemoS error code.
 * @ingroup S31SdcDiscovery
 */
class MdsTypeErrorReporter: public LocationContextDiscoveryObserver
{
    public:
        explicit MdsTypeErrorReporter(DFL::Mdib::CodedValue mdsType);
        ~MdsTypeErrorReporter() override;

        void joinsLocation(const RemoteDeviceInfo& device) override;
        void leavesLocation(const EndpointReference& epr) override;

    private:
        struct EndpointReferenceCompareLess
        {
                bool operator()(const EndpointReference& lhs, const EndpointReference& rhs) const noexcept
                {
                    return lhs.address().str() < rhs.address().str();
                }
        };

        void updateErrrorState() const;

        mutable std::mutex m_mutex;
        DFL::Mdib::CodedValue m_mdsType;
        std::map<EndpointReference, RemoteDeviceInfo, EndpointReferenceCompareLess> m_remoteDevicesOfType;
};


}
