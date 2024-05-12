#pragma once

#include <S31/Sdc/Private/Common/Http/StandardRequestBody.h>

#include <Framework/Utils/Public/StrongTypedef.h>

namespace S31::Sdc::Impl
{

using RetryCounter = DFL::StrongTypedef<size_t, struct RetryCounterTag, DFL::Skill::Streamable, DFL::Skill::TotallyOrdered, DFL::Skill::Incrementable>;

struct OutgoingUnicastMessageContext
{
    OutgoingUnicastMessageContext() = default;

    explicit OutgoingUnicastMessageContext(
        RetryCounter retryCounter,
        CreateRequestBody createMessage) :
            m_retryCounter (retryCounter),
            m_createMessage(std::move(createMessage))
    {}

    RetryCounter m_retryCounter = RetryCounter(0);
    CreateRequestBody m_createMessage = StandardBody(std::string{});
};

}
