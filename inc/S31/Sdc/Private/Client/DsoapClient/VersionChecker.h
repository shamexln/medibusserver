#pragma once

#include <S31/Log/Public/Logger.h>

#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibAccess.h>
#include <Framework/Mdib/Public/MdibSmartPtr.h>
#include <Framework/Mdib/Public/Model/HandleIo.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapStub.h>

namespace S31::Sdc::Impl
{

/**
 * Provides functions for checking MDIB versions.
 *
 * \ingroup S31SdcClient
 */
class VersionChecker
{
    public:
        /**
         * Checker for outdated %MDIB states.
         *
         * @return \c true in case the soap state should be mapped to the corresponding %MDIB state.
         */
        template <typename Entity_Ptr>
        static bool hasNewSoapStateVersion(const pm__AbstractState& soapState, Entity_Ptr entity);

        /**
         * Checker for outdated %MDIB descriptors.
         *
         * @return \c true in case the soap descriptor should be mapped to the corresponding %MDIB descriptor.
         */
        template <typename Entity_Ptr>
        static bool hasNewSoapDescriptorVersion(const pm__AbstractDescriptor& soapDescriptor, Entity_Ptr entity);

};

template <typename T_EntityPtr>
bool VersionChecker::hasNewSoapStateVersion(const pm__AbstractState& soapState, T_EntityPtr entity)
{
    auto soapVersion = soapState.StateVersion ? *soapState.StateVersion : 0ULL;
    auto mdibVersion = entity->stateVersion();
    if (soapVersion < mdibVersion)
    {
        S31_STREAM_TRACE_LOGGER("Sdc.Client", "old state (version ", soapVersion, ") for entity ", entity->handle(), " with current state version ", mdibVersion, " received");
        return false;
    }
    if (soapVersion == mdibVersion)
    {
        S31_STREAM_TRACE_LOGGER("Sdc.Client", "same state version ", soapVersion, " appears again for entity ", entity->handle());
        return false;
    }
    if (soapVersion > (mdibVersion + 1ULL))
    {
        S31_STREAM_TRACE_LOGGER("Sdc.Client", "missed state ", entity->handle(), " updates, updating from ", mdibVersion," to ", soapVersion);
    }
    return true;
}

template <typename T_EntityPtr>
bool VersionChecker::hasNewSoapDescriptorVersion(const pm__AbstractDescriptor& soapDesc, T_EntityPtr entity)
{
    auto soapVersion = soapDesc.DescriptorVersion ? *soapDesc.DescriptorVersion : 0ULL;
    auto mdibVersion = entity->descriptorVersion();
    if (soapVersion < mdibVersion)
    {
        S31_STREAM_TRACE_LOGGER("Sdc.Client", "old descriptor (version ", soapVersion, ") for handle ", entity->handle(),
            " with current descriptor version ", mdibVersion, " received");
        return false;
    }
    if (soapVersion == mdibVersion)
    {
        S31_STREAM_TRACE_LOGGER("Sdc.Client", "same descriptor version ", soapVersion, " appears again for handle ", entity->handle());
        return false;
    }
    if (soapVersion > (mdibVersion + 1ULL))
    {
        S31_STREAM_TRACE_LOGGER("Sdc.Client", "missed descriptor '", soapDesc.Handle, "' updates, updating from ", mdibVersion, " to ", soapVersion);
    }
    else
    {
        S31_STREAM_TRACE_LOGGER("Sdc.Client", "descriptor '", soapDesc.Handle, "' update received ", entity->handle(), " with version ", soapVersion);
    }
    return true;
}

}
