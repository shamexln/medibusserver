#pragma once

#include <S31/Error/Public/EventCode.h>
#include <S31/Utils/Public/ObservableSubject.h>

#include <Framework/Utils/Public/NotNull.h>

#include <mutex>
#include <vector>

namespace S31::Error
{
class EventCodeObserver;

namespace Impl
{
using EventCodeRegistrySubject = Utils::ObservableSubjectDelegate<Error::EventCodeObserver>;
/*!
 * \brief Module event registry implementation.
 *
 * \see EventCodeRegistry should be used as public access interface for module errors.
 *
 * \ingroup S31ErrorGroup
 */
class EventCodeRegistryImpl
{
public:
    EventCodeRegistryImpl();
    void addEvent(EventCode id);

    void removeEvent(EventCode id);

    void registerObserver(const DFL::NotNull<std::shared_ptr<EventCodeObserver>>& observer);

    void unregisterObserver(const DFL::NotNull<std::shared_ptr<EventCodeObserver>>& observer);

    std::vector<EventCode> getActiveEvents();
private:
    bool stateExistsNoLock(EventCode id);
    std::vector<EventCode> m_activeErrorStates;
    std::shared_ptr<EventCodeRegistrySubject> m_remosCodeLogSubject;
    std::mutex m_stateMutex;
};

}
}
