#pragma once

#include <S31/Sdc/Test/Utils/s31core_it_utils_exp_imp.h>
#include <S31/UseCases/S31Only/ILocationHandler.h>

#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>

namespace S31::Test
{
/**
 * @brief Location Handler implementation for the test device.
 *
 * @details
 * This class simulates the behavior of a simple device to allow
 * testing of the location handling for remote devices.
 */
class S31_CORE_IT_UTIL_EXPIMP MockLocationHandler : public S31::ILocationHandler
{
    public:
        explicit MockLocationHandler(DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr> mdibAccess);

        /**
         * start the location handler.
         */
        void start() override;

        /**
         * stops the location handler.
         */
        void stop() override;

        /**
         * @copydoc S31::ILocationHandler::setLocation
         */
        void setLocation(const DFL::Mdib::LocationContextState& locationContextState) override;

    private:
        DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr> m_mdibAccess;
};
} /* namespace S31 */
