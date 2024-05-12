#pragma once

#include <S31/Safety/Public/Requirements.h>
#include <S31/Sdc/Public/Common/MdibSmartPtrTypes.h>

#include <Framework/Mdib/Public/MdibSmartPtrTypes.h>

#include <utility>

namespace S31::Sdc
{

/**
 * @brief Provides the BICEPS Participant Model related \ref DFL::Mdib::Mdib "MDIB" and transport specific SDC data.
 * @ingroup S31SdcCommon
 */
class Mdib
{
    public:
        /**
         * @brief Constructor.
         */
        Mdib(DFL::NotNull<DFL::Mdib::MdibSharedPtr> mdib,
             DFL::NotNull<std::shared_ptr<const Safety::Requirements>> safetyRequirements);

        /**
         * @brief Returns the \ref DFL::Mdib::Mdib object.
         */
        DFL::NotNull<DFL::Mdib::MdibSharedPtr> mdib() const;

        /**
         * @brief Returns the safety requirements.
         */
        DFL::NotNull<std::shared_ptr<const Safety::Requirements>> safetyRequirements() const;

    private:
        DFL::NotNull<DFL::Mdib::MdibSharedPtr> m_mdib;
        DFL::NotNull<std::shared_ptr<const Safety::Requirements>> m_safetyRequirements;
};

inline Mdib::Mdib(DFL::NotNull<DFL::Mdib::MdibSharedPtr> mdib,
                  DFL::NotNull<std::shared_ptr<const Safety::Requirements>> safetyRequirements) :
        m_mdib(std::move(mdib)),
        m_safetyRequirements(std::move(safetyRequirements))
{
}

inline DFL::NotNull<DFL::Mdib::MdibSharedPtr> Mdib::mdib() const
{
    return m_mdib;
}

inline DFL::NotNull<std::shared_ptr<const Safety::Requirements>> Mdib::safetyRequirements() const
{
    return m_safetyRequirements;
}

}
