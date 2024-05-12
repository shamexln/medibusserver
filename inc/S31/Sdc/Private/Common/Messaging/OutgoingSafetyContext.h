#pragma once

#include <Framework/Utils/Public/CompilerGenerated.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapStub.h>

#include <memory>
#include <string>

namespace S31::Sdc::Impl
{

/**
 * @brief Helper class to add safety context information to a soap header.
 *
 * @ingroup S31SdcCommon
 */
class OutgoingSafetyContext
{
        DFL_NOT_COPYABLE(OutgoingSafetyContext)
    public:
        /**
         * @brief Construct helper for specific soap handle.
         * @param soapHandle Soap context to add safety context to.
         */
        explicit OutgoingSafetyContext(struct soap* soapHandle);

        /**
         * @brief Adds a safety context to the soap header.
         * @param selectorId ID
         * @param value safety value
         */
        void addSafetyContext(const std::string& selectorId, const std::string& value);

    private:
        struct soap* m_soapHandle;
        std::shared_ptr<si__T_USCORESafetyContext> m_safetyContext;
};

}
