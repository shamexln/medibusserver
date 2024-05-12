#pragma once

#include <Framework/Mdib/Test/Public/WaitingMdibChangesObserver.h>
#include <Framework/Mdib/Test/Public/WaitingMdibObserver.h>
#include <S31/Sdc/Test/Utils/s31core_it_utils_exp_imp.h>

namespace S31::Sdc
{
class Client;
class RemoteDevice;
class EndpointReference;

namespace Test
{

/**
 * @brief Helper class to track remote MDIB changes.
 */
class S31_CORE_IT_UTIL_EXPIMP MdibChangesTracking
{
    public:
        /**
         * @brief Tries to connect a remote device and waits for a certain MDIB change.

         * @param client The client used to establish a connection.
         * @param waitTime The maximum wait time.
         * @param deviceEpr The remote device to connect to (or re-used already established connection).
         * @param mdibPredicate The predicate to match in order to leave the waitFor.
         * @return \c true if mdibPredicate matched within waitTime, or \c false mdibPredicate did not match or
         *         waitTime exceeded.
         */
        static bool waitFor(S31::Sdc::Client& client,
                            std::chrono::milliseconds waitTime,
                            const S31::Sdc::EndpointReference& deviceEpr,
                            const std::function<bool(const DFL::Mdib::Mdib&)>& mdibPredicate);

        /**
         * @brief Tries to connect a remote device and returns a \ref DFL::Mdib::Test::WaitingMdibChangesObserver.
         *
         * @param client The client used to establish a connection.
         * @param deviceEpr The remote device to connect to (or re-used already established connection).
         */
        static DFL::NotNull<std::shared_ptr<DFL::Mdib::Test::WaitingMdibChangesObserver>> createWaitingMdibChangesObserver(
                S31::Sdc::Client& client,
                const S31::Sdc::EndpointReference& deviceEpr);

        /**
         * @brief Tries to connect a remote device and returns a \ref DFL::Mdib::Test::WaitingMdibObserver.
         *
         * @param client The client used to establish a connection.
         * @param deviceEpr The remote device to connect to (or re-used already established connection).
         */
        static DFL::NotNull<std::shared_ptr<DFL::Mdib::Test::WaitingMdibObserver>> createWaitingMdibObserver(
                S31::Sdc::Client& client,
                const S31::Sdc::EndpointReference& deviceEpr);

        /**
         * @brief Tries to connect a remote device.
         *
         * @param client The client used to establish a connection.
         * @param deviceEpr The remote device to connect to (or re-used already established connection).
         * @throws an \c std::runtime_error if no device could be connected.
         */
        static DFL::NotNull<std::shared_ptr<RemoteDevice>> connectRemoteDevice(S31::Sdc::Client& client,
                                                                               const S31::Sdc::EndpointReference& deviceEpr);
};

}
}
