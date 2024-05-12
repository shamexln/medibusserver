#pragma once

#include <S31/Safety/Public/Requirements.h>
#include <S31/Sdc/Public/Common/Mdib.h>
#include <S31/Sdc/Public/Common/MdibSmartPtrTypes.h>
#include <S31/Utils/Public/ObservableSubject.h>

#include <Framework/Mdib/Public/MdibAccess.h>
#include <Framework/Mdib/Public/MdibObserver.h>
#include <Framework/Mdib/Public/SubdividedMdibObserver.h>

#include <memory>

namespace S31::Sdc::Impl
{

/**
 * @brief Common part for S31's wrapping of local and remote MdibAccess.
 * @ingroup S31SdcClient
 */
template<class MdibAccessPtr>
class MdibAccessImplCommon :
      public DFL::Mdib::MdibObserver,
        public DFL::Mdib::SubdividedMdibObserver,
        public DFL::Mdib::MdibAccess
{
    public:
        MdibAccessImplCommon(DFL::NotNull<MdibAccessPtr> mdibAccess,
                             DFL::NotNull<std::unique_ptr<Safety::Requirements>> safetyRequirements) :

            m_safetyRequirements(std::move(safetyRequirements)),
            m_mdibAccess(std::move(mdibAccess)),
            m_latestSdcMdib(DFL::asNotNull(std::make_shared<Mdib>(m_mdibAccess->latestMdib(), m_safetyRequirements)))
        {}

        explicit MdibAccessImplCommon(DFL::NotNull<MdibAccessPtr> mdibAccess) :
            m_safetyRequirements(DFL::asNotNull(std::make_shared<Safety::Requirements>())),
            m_mdibAccess(std::move(mdibAccess)),
            m_latestSdcMdib(DFL::asNotNull(std::make_shared<Mdib>(m_mdibAccess->latestMdib(), m_safetyRequirements)))
        {}

        void registerThisAsObserver(const std::shared_ptr<MdibAccessImplCommon>& sharedThisOfDerivedClass);

        DFL::NotNull<MdibSharedPtr> latestSdcMdib() const;

        // MdibAccess interface
        DFL::NotNull<DFL::Mdib::MdibSharedPtr> latestMdib() const override;
        void registerObserver(const std::weak_ptr<DFL::Mdib::MdibObserver>& observer) override;
        void unregisterObserver(const std::weak_ptr<DFL::Mdib::MdibObserver>& observer) override;
        void registerSubdividedObserver(const std::weak_ptr<DFL::Mdib::SubdividedMdibObserver>& observer) override;
        void unregisterSubdividedObserver(const std::weak_ptr<DFL::Mdib::SubdividedMdibObserver>& observer) override;


        // SubdividedMdibObserver interface
        void onDescriptionChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;
        void onAlertChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;
        void onComponentChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;
        void onContextChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;
        void onMetricChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;
        void onOperationChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;
        void onSampleArrayMetricChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;

        // MdibObserver interface
        void onChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes, DFL::Mdib::MdibChangeType changeType) override;

    protected:
        DFL::NotNull<MdibAccessPtr>& mdibAccess();
        const DFL::NotNull<MdibAccessPtr>& mdibAccess() const;
        void injectSafetyRequirements(DFL::NotNull<std::unique_ptr<S31::Safety::Requirements>> safetyRequirements);

    private:
        void updateLatestSdcMdib(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib);

        template<class T_Observer>
        void updateSdcMdibAndNotifyObservers(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib,
                                                    Utils::ObservableSubjectDelegate<T_Observer>& subject,
                                                    std::function<void(T_Observer&)> observerCall);

        mutable std::mutex m_latestSdcMdibMutex;
        DFL::NotNull<std::shared_ptr<Safety::Requirements>> m_safetyRequirements;
        DFL::NotNull<MdibAccessPtr> m_mdibAccess;
        DFL::NotNull<MdibSharedPtr> m_latestSdcMdib;

        Utils::ObservableSubjectDelegate<DFL::Mdib::MdibObserver> m_mdibObserverSubject;
        Utils::ObservableSubjectDelegate<DFL::Mdib::SubdividedMdibObserver> m_subdividedMdibObserverSubject;

};

template<class MdibAccessPtr>
inline void MdibAccessImplCommon<MdibAccessPtr>::registerThisAsObserver(const std::shared_ptr<MdibAccessImplCommon>& sharedThisOfDerivedClass)
{
    m_mdibAccess->registerObserver(std::static_pointer_cast<DFL::Mdib::MdibObserver>(sharedThisOfDerivedClass));
    m_mdibAccess->registerSubdividedObserver(std::static_pointer_cast<DFL::Mdib::SubdividedMdibObserver>(sharedThisOfDerivedClass));
}

template<class MdibAccessPtr>
inline DFL::NotNull<MdibSharedPtr> MdibAccessImplCommon<MdibAccessPtr>::latestSdcMdib() const
{
    return m_latestSdcMdib;
}

template<class MdibAccessPtr>
inline DFL::NotNull<DFL::Mdib::MdibSharedPtr> MdibAccessImplCommon<MdibAccessPtr>::latestMdib() const
{
    return m_mdibAccess->latestMdib();
}

template<class MdibAccessPtr>
inline void MdibAccessImplCommon<MdibAccessPtr>::registerObserver(const std::weak_ptr<DFL::Mdib::MdibObserver>& observer)
{
    m_mdibObserverSubject.registerObserver(observer);
}

template<class MdibAccessPtr>
inline void MdibAccessImplCommon<MdibAccessPtr>::unregisterObserver(const std::weak_ptr<DFL::Mdib::MdibObserver>& observer)
{
    m_mdibObserverSubject.unregisterObserver(observer);
}

template<class MdibAccessPtr>
inline void MdibAccessImplCommon<MdibAccessPtr>::registerSubdividedObserver(const std::weak_ptr<DFL::Mdib::SubdividedMdibObserver>& observer)
{
    m_subdividedMdibObserverSubject.registerObserver(observer);
}

template<class MdibAccessPtr>
inline void MdibAccessImplCommon<MdibAccessPtr>::unregisterSubdividedObserver(const std::weak_ptr<DFL::Mdib::SubdividedMdibObserver>& observer)
{
    m_subdividedMdibObserverSubject.unregisterObserver(observer);
}

template<class MdibAccessPtr>
inline void MdibAccessImplCommon<MdibAccessPtr>::onDescriptionChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes)
{
    updateSdcMdibAndNotifyObservers<DFL::Mdib::SubdividedMdibObserver>(mdib, m_subdividedMdibObserverSubject, [&](DFL::Mdib::SubdividedMdibObserver& observer)
    {
        observer.onDescriptionChange(mdib, changes);
    });
}

template<class MdibAccessPtr>
inline void MdibAccessImplCommon<MdibAccessPtr>::onAlertChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes)
{
    updateSdcMdibAndNotifyObservers<DFL::Mdib::SubdividedMdibObserver>(mdib, m_subdividedMdibObserverSubject, [&](DFL::Mdib::SubdividedMdibObserver& observer)
    {
        observer.onAlertChange(mdib, changes);
    });
}

template<class MdibAccessPtr>
inline void MdibAccessImplCommon<MdibAccessPtr>::onComponentChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes)
{
    updateSdcMdibAndNotifyObservers<DFL::Mdib::SubdividedMdibObserver>(mdib, m_subdividedMdibObserverSubject, [&](DFL::Mdib::SubdividedMdibObserver& observer)
    {
        observer.onComponentChange(mdib, changes);
    });
}

template<class MdibAccessPtr>
inline void MdibAccessImplCommon<MdibAccessPtr>::onContextChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes)
{
    updateSdcMdibAndNotifyObservers<DFL::Mdib::SubdividedMdibObserver>(mdib, m_subdividedMdibObserverSubject, [&](DFL::Mdib::SubdividedMdibObserver& observer)
    {
        observer.onContextChange(mdib, changes);
    });
}

template<class MdibAccessPtr>
inline void MdibAccessImplCommon<MdibAccessPtr>::onMetricChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes)
{
    updateSdcMdibAndNotifyObservers<DFL::Mdib::SubdividedMdibObserver>(mdib, m_subdividedMdibObserverSubject, [&](DFL::Mdib::SubdividedMdibObserver& observer)
    {
        observer.onMetricChange(mdib, changes);
    });
}

template<class MdibAccessPtr>
inline void MdibAccessImplCommon<MdibAccessPtr>::onOperationChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes)
{
    updateSdcMdibAndNotifyObservers<DFL::Mdib::SubdividedMdibObserver>(mdib, m_subdividedMdibObserverSubject, [&](DFL::Mdib::SubdividedMdibObserver& observer)
    {
        observer.onOperationChange(mdib, changes);
    });
}

template<class MdibAccessPtr>
inline void MdibAccessImplCommon<MdibAccessPtr>::onSampleArrayMetricChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes)
{
    updateSdcMdibAndNotifyObservers<DFL::Mdib::SubdividedMdibObserver>(mdib, m_subdividedMdibObserverSubject, [&](DFL::Mdib::SubdividedMdibObserver& observer)
    {
        observer.onSampleArrayMetricChange(mdib, changes);
    });
}

template<class MdibAccessPtr>
DFL::NotNull<MdibAccessPtr>& MdibAccessImplCommon<MdibAccessPtr>::mdibAccess()
{
    return m_mdibAccess;
}

template<class MdibAccessPtr>
const DFL::NotNull<MdibAccessPtr>& MdibAccessImplCommon<MdibAccessPtr>::mdibAccess() const
{
    return m_mdibAccess;
}

template<class MdibAccessPtr>
inline void MdibAccessImplCommon<MdibAccessPtr>::injectSafetyRequirements(DFL::NotNull<std::unique_ptr<S31::Safety::Requirements>> safetyRequirements)
{
    std::lock_guard<std::mutex> const lock(m_latestSdcMdibMutex);
    m_safetyRequirements = std::move(safetyRequirements);
}

template<class MdibAccessPtr>
inline void MdibAccessImplCommon<MdibAccessPtr>::onChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes, DFL::Mdib::MdibChangeType changeType)
{
    updateSdcMdibAndNotifyObservers<DFL::Mdib::MdibObserver>(mdib, m_mdibObserverSubject, [&](DFL::Mdib::MdibObserver& observer)
    {
        observer.onChange(mdib, changes, changeType);
    });
}

template<class MdibAccessPtr>
inline void MdibAccessImplCommon<MdibAccessPtr>::updateLatestSdcMdib(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib)
{
    std::lock_guard<std::mutex> const lock(m_latestSdcMdibMutex);
    m_latestSdcMdib = DFL::asNotNull(std::make_shared<Mdib>(mdib, m_safetyRequirements));
}

template<class MdibAccessPtr>
template<class T_Observer>
inline void MdibAccessImplCommon<MdibAccessPtr>::updateSdcMdibAndNotifyObservers(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib,
                                                                       Utils::ObservableSubjectDelegate<T_Observer>& subject,
                                                                       std::function<void(T_Observer&)> observerCall)
{
    updateLatestSdcMdib(mdib);
    subject.notify(observerCall);
}

}
