#pragma once

#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>
#include <S31/SetService/Public/Device/InvocationCallbackRegistry.h>

namespace S31
{
class MockColorSchemeHandler
{
    public:

        MockColorSchemeHandler(const DFL::NotNull<std::shared_ptr<S31::SetService::InvocationCallbackRegistry>>& invocationCallbackRegistry,
                               const DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr>& mdibAccess);

        virtual ~MockColorSchemeHandler() = default;

        void start();

        void stop();

    private:

        DFL::NotNull<std::shared_ptr<S31::SetService::InvocationCallbackRegistry>> m_invocationCallbackRegistry;
        DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr> m_mdibAccess;
};

} /* namespace S31 */
