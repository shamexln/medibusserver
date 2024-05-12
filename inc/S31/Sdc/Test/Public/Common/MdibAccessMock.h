#pragma once

#include <S31/Sdc/Public/Common/MdibAccess.h>
#include <S31/Sdc/Public/Device/LocalMdibAccess.h>
#include <S31/Sdc/Public/Device/MdibFactory.h>

#include <Framework/Mdib/Public/MdibConstraints.h>
#include <Framework/Mdib/Test/Public/MdibWriter.h>

namespace S31::Sdc::Test
{
/**
 * @brief Mock implementation for \ref S31::Sdc::MdibAccess.
 * @ingroup S31SdcCommon
 */
class MdibAccessMock: public S31::Sdc::MdibAccess
{
    public:
        MdibAccessMock();

        explicit MdibAccessMock(const DFL::Mdib::MdibChangeSet& mdibChangeSet);

        DFL::NotNull<S31::Sdc::MdibSharedPtr> latestSdcMdib() const override;

        DFL::NotNull<DFL::Mdib::MdibSharedPtr> latestMdib() const override;

        void registerObserver(const std::weak_ptr<DFL::Mdib::MdibObserver>& observer) override;

        void unregisterObserver(const std::weak_ptr<DFL::Mdib::MdibObserver>& observer) override;

        void registerSubdividedObserver(const std::weak_ptr<DFL::Mdib::SubdividedMdibObserver>& observer) override;

        void unregisterSubdividedObserver(const std::weak_ptr<DFL::Mdib::SubdividedMdibObserver>& observer) override;

        DFL::NotNull<S31::Sdc::MdibAccessSharedPtr> underlyingMdibAccess();

    private:
        DFL::NotNull<S31::Sdc::MdibAccessSharedPtr> m_mdibAccess;
};

inline MdibAccessMock::MdibAccessMock() :
        m_mdibAccess(S31::Sdc::MdibFactory::createLocalSdcMdibAccess(DFL::Mdib::MdibConstraints::allConstraints()))
{
}

inline MdibAccessMock::MdibAccessMock(const DFL::Mdib::MdibChangeSet& mdibChangeSet) :
        m_mdibAccess(S31::Sdc::MdibFactory::createLocalSdcMdibAccess(DFL::Mdib::MdibConstraints::allConstraints()))
{
    auto localMdibAccess = std::dynamic_pointer_cast<DFL::Mdib::LocalMdibAccess>(underlyingMdibAccess().get());
    THROW_ON_MDIB_WRITE_FAIL(localMdibAccess->writeDescription(mdibChangeSet));
}

inline DFL::NotNull<S31::Sdc::MdibSharedPtr> MdibAccessMock::latestSdcMdib() const
{
    return m_mdibAccess->latestSdcMdib();
}

inline DFL::NotNull<DFL::Mdib::MdibSharedPtr> MdibAccessMock::latestMdib() const
{
    return m_mdibAccess->latestMdib();
}

inline void MdibAccessMock::registerObserver(const std::weak_ptr<DFL::Mdib::MdibObserver>& observer)
{
    m_mdibAccess->registerObserver(observer);
}

inline void MdibAccessMock::unregisterObserver(const std::weak_ptr<DFL::Mdib::MdibObserver>& observer)
{
    m_mdibAccess->unregisterObserver(observer);
}

inline void MdibAccessMock::registerSubdividedObserver(const std::weak_ptr<DFL::Mdib::SubdividedMdibObserver>& /* observer */)
{
}

inline void MdibAccessMock::unregisterSubdividedObserver(const std::weak_ptr<DFL::Mdib::SubdividedMdibObserver>& /* observer */)
{
}

inline DFL::NotNull<MdibAccessSharedPtr> MdibAccessMock::underlyingMdibAccess()
{
    return m_mdibAccess;
}

}
