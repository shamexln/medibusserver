#pragma once

#include <S31/Base/S31Only/NtStringView.h>
#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Private/Client/Metadata/IHostedServiceMetadata.h>
#include <S31/Sdc/Test/Public/Device/RemoteHostedServiceEndpointMock.h>

#include <set>
#include <utility>

namespace S31::Sdc::Impl::Test
{

/**
 * @brief Mock implementation for hosted service metadata.
 */
class HostedServiceMetadataMock: public S31::Sdc::Impl::IHostedServiceMetadata
{
    public:
        HostedServiceMetadataMock() :
                m_serviceId("Get"),
                m_hostedServiceEndpoint(std::make_shared<RemoteHostedServiceEndpointMock>()),
                m_types()
        {
        }

        HostedServiceMetadataMock(std::string_view ns, std::string_view name, std::shared_ptr<RemoteHostedServiceEndpointMock> epr) :
                m_serviceId("Get"),
                m_hostedServiceEndpoint(std::move(epr)),
                m_types()
        {
            addQNameIfNsNonEmpty(DFL::NamespaceUri(std::string{ns}), std::string{name});
        }

        HostedServiceMetadataMock(
                const std::set<std::pair<NtStringView, NtStringView>>& qNames,
                std::shared_ptr<RemoteHostedServiceEndpointMock>       epr)
            : m_serviceId("Get")
            , m_hostedServiceEndpoint(std::move(epr))
            , m_types()
        {
            for (const auto& qName : qNames)
            {
                addQNameIfNsNonEmpty(DFL::NamespaceUri(std::string{qName.first}), std::string{qName.second});
            }
        }

        HostedServiceMetadataMock(
                std::string_view serviceId, const std::set<std::pair<NtStringView, NtStringView>>& qNames)
            : m_serviceId(serviceId)
            , m_hostedServiceEndpoint(std::make_shared<RemoteHostedServiceEndpointMock>())
            , m_types()
        {
            for (const auto& qName : qNames)
            {
                addQNameIfNsNonEmpty(DFL::NamespaceUri(std::string{qName.first}), std::string{qName.second});
            }
        }

        std::string getServiceId() const override
        {
            return m_serviceId;
        }

        bool hasType(const DFL::QName& type) const override
        {
            return containsSemantically(m_types, type);
        }

        std::shared_ptr<S31::Sdc::Impl::IRemoteHostedServiceEndpoint> getRemoteEndpoint() const override
        {
            return m_hostedServiceEndpoint;
        }

        const S31::Sdc::Impl::QNameList& qNameList() const override
        {
            return m_types;
        }

    private:
        void addQNameIfNsNonEmpty(const DFL::NamespaceUri& ns, const std::string& name)
        {
            if (!ns.get().empty())
            {
                m_types.emplace_back(
                        ns,
                        DFL::NamePrefix(""),
                        name);
            }
            else
            {
                S31_STREAM_WARN_LOGGER("Test", __func__, "(ns=", ns, ",name=", name, "): namespace uri invalid. add empty QName.");
                m_types.push_back(DFL::QName());
            }

        }

        std::string m_serviceId;
        std::shared_ptr<RemoteHostedServiceEndpointMock> m_hostedServiceEndpoint;
        S31::Sdc::Impl::QNameList m_types;
};

}
