#pragma once

#include <S31/Error/Public/EventCode.h>
#include <S31/Error/S31Only/EventCodeObserver.h>
#include <S31/S31CoreExImp.h>
#include <S31/Utils/Public/ObservableSubject.h>

#include <memory>
#include <vector>

namespace S31::Error
{
namespace Impl
{
class EventCodeRegistryImpl;
}
/*!
 * \brief Provides access to module events at runtime.
 *
 * @details This static/Singleton class handles events (errors and states) that
 * are notified to the product.
 *
 * \ingroup S31ErrorGroup
 */
class S31_CORE_EXPIMP EventCodeRegistry: public Utils::ObservableSubject<EventCodeObserver>
{
    public:
        EventCodeRegistry();
        ///
        /// \brief Creates a static instance.
        ///
        static std::shared_ptr<EventCodeRegistry> instance();
        ///
        /// \brief Adds the error state to the set of active error state if there is not a state with this id already.
        ///
        /// If the the error state is active already then nothing is done. The listener is notified only if the error
        /// state was not active already.
        ///
        /// \param id event id
        ///
        void addEvent(EventCode id);

        ///
        /// \brief Removes an active error state.
        ///
        /// If the error was not active the call is ignored. The listener is notified only if the error was
        /// active.
        ///
        /// \param id event id
        ///
        void removeEvent(EventCode id);

        ///
        /// \brief Register an observer.
        /// \param observer The weak_ptr to EventCodeObserver.
        ///
        void registerObserver(const std::weak_ptr<EventCodeObserver>& observer) override;

        ///
        /// \brief Unregister an observer.
        /// \param observer The weak_ptr to EventCodeObserver.
        ///
        void unregisterObserver(const std::weak_ptr<EventCodeObserver>& observer) override;

        ///
        /// \brief Returns the set of currently active error states.
        ///
        std::vector<EventCode> getActiveEvents();

        ///
        /// \brief Returns true or false based on whether the error code already exists
        ///
        bool isActiveEvent(EventCode isEvent);

    private:
        std::shared_ptr<Impl::EventCodeRegistryImpl> m_impl;
};

}
