#pragma once

#include <S31/Safety/Public/Requirement.h>
#include <S31/Safety/Public/Requirements.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Visitor to retrieve safety requirement definition from an operation handle.
 * @ingroup S31SdcDevice
 */
class GetSafetyRequirementVisitor
{
    public:
        explicit GetSafetyRequirementVisitor(const Safety::Requirements& safetyRequirements);
        template<class T_OperationHandle>
        Safety::Requirement operator ()(const T_OperationHandle& handle) const;

    private:
        // NOLINTNEXTLINE(clang-diagnostic-unused-private-field)
        const Safety::Requirements& m_safetyRequirements;
};

inline GetSafetyRequirementVisitor::GetSafetyRequirementVisitor(const Safety::Requirements& safetyRequirements) :
        m_safetyRequirements(safetyRequirements)
{
}

template<class T_OperationHandle>
inline Safety::Requirement GetSafetyRequirementVisitor::operator ()(const T_OperationHandle& handle) const
{
    return m_safetyRequirements.get(handle);
}

}
