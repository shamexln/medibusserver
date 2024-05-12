#pragma once

#include <S31/Safety/Public/Information.h>
#include <S31/SetService/Private/Client/CheckerResult.h>
#include <S31/SetService/Private/Common/VisitMembers.h>
#include <S31/SetService/Public/Common/Argument.h>
#include <S31/SetService/Public/Common/ProposedAlertState.h>
#include <S31/SetService/Public/Common/ProposedAlertStates.h>
#include <S31/SetService/Public/Common/ProposedComponentStates.h>
#include <S31/SetService/Public/Common/ProposedContextStates.h>
#include <S31/SetService/Public/Common/ProposedMetricStates.h>

#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifierSemantic.h>
#include <Framework/Mdib/Public/Utils/VisitMembers.h>

#include <type_traits>

namespace S31::SetService::Impl
{
/**
 * @brief Checks for valid InstanceIdentifier Root.
 *
 * @details
 * S31TSR_3574:
 * > An SDC PARTICIPANT SHALL limit values of pm:InstanceIdentifier/\@Root
 * > to those matching the form scheme ":" hier-part as defined in section 3 of RFC 3986.
 * > The only exception from this is the "biceps.uri.unk" and "sdc.ctxt.loc.detail" value.
 *
 * @ingroup S31SetService
 */
class InstanceIdentifierChecker
{
    public:
        template<class T_Data>
        CheckerResult operator()(const T_Data& data)
        {
            std::vector<std::string> invalidUris;
            auto handler = [&](const DFL::Mdib::InstanceIdentifier& ii)
            {
                if (!DFL::Mdib::validInstanceIdentifierRoot(ii))
                {
                    invalidUris.push_back(ii.root().get().get());
                }
            };
            DFL::Mdib::visitTypeInMembers<DFL::Mdib::InstanceIdentifier>(handler, data);
            if (!invalidUris.empty())
            {
                DFL::Format::Stream msg;
                msg << "The following URIs are invalid InstanceIdentifier roots: " << invalidUris;
                return CheckerResult::failed(ClientError::InvalidInstanceIdentifierRoot, msg.cStr());
            }
            return CheckerResult::success();
        }
};

}
