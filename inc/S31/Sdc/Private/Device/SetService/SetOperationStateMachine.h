#pragma once

#include <S31/SetService/Public/Common/InvocationState.h>

#include <boost/optional/optional.hpp>

namespace S31::Sdc::Impl
{

/**
 * @brief State machine that allows for correct \ref S31::SetService::InvocationState traversal.
 * @ingroup S31SdcDevice
 */
class SetOperationStateMachine
{
    public:
        /**
         * @brief Resets the state machine to the entry point.
         */
        void reset();

        /**
         * @brief Tries to traverse to the state given by the \c invState argument.
         * @details If the next state is valid, the state machine state is invState.
         * @param next The state to traverse to.
         * @return \c true if the state has been reached successfully, otherwise false.
         */
        bool traverseTo(SetService::InvocationState next);

        /**
         * @brief Returns \c true if the state machine has reached the final state, otherwise false.
         */
        bool isFinalState() const;

        /**
         * @brief Returns \c true if the state machine has left the state machine's entry point.
         */
        bool isStarted() const;

        /**
         * @brief Returns the current state or \c boost::none if the state is reseted.
         */
        boost::optional<SetService::InvocationState> getCurrent() const;

    private:
        boost::optional<SetService::InvocationState> m_optionalCurrentState;

        void setCurrent(SetService::InvocationState current);
};

}
