#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Model/Operation/ActivateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetAlertStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetComponentStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetContextStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetMetricStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetStringOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetValueOperation.h>

namespace S31::Safety
{

class Requirement;

/**
 * @brief Result after setting a requirement in \ref S31::Safety::Requirements.
 * @ingroup S31Safety
 */
enum class RequirementsSetStatus
{
    Success, //!< %Operation succeed.
    DuplicatedId //!< %Operation failed as there was a duplicated identifier detected while setting a \ref S31::Safety::Requirement.
};
DFL_ENUM_CLASS_STREAM_OPERATOR(RequirementsSetStatus, (Success)(DuplicatedId))

/**
 * @brief Container to manage safety requirements for set operations.
 * @ingroup S31Safety
 */
class S31_CORE_EXPIMP Requirements
{
    public:
        /**
         * @brief Constructor.
         */
        Requirements();

        /**
         * @brief Destructor.
         */
        ~Requirements();

        /**
         * @name Safety requirements access for SetString operations
         */
        ///@{
        Requirement get(const DFL::Mdib::MdsSetStringOperationHandle& operationHandle) const;
        RequirementsSetStatus set(const DFL::Mdib::MdsSetStringOperationHandle& operationHandle, const Requirement& safetyRequirement) const;

        Requirement get(const DFL::Mdib::VmdSetStringOperationHandle& operationHandle) const;
        RequirementsSetStatus set(const DFL::Mdib::VmdSetStringOperationHandle& operationHandle, const Requirement& safetyRequirement) const;
        ///@}

        /**
         * @name Safety requirements access for SetValue operations
         */
        ///@{
        Requirement get(const DFL::Mdib::MdsSetValueOperationHandle& operationHandle) const;
        RequirementsSetStatus set(const DFL::Mdib::MdsSetValueOperationHandle& operationHandle, const Requirement& safetyRequirement) const;

        Requirement get(const DFL::Mdib::VmdSetValueOperationHandle& operationHandle) const;
        RequirementsSetStatus set(const DFL::Mdib::VmdSetValueOperationHandle& operationHandle, const Requirement& safetyRequirement) const;
        ///@}

        /**
         * @name Safety requirements access for Activate operations
         */
        ///@{
        Requirement get(const DFL::Mdib::MdsActivateOperationHandle& operationHandle) const;
        RequirementsSetStatus set(const DFL::Mdib::MdsActivateOperationHandle& operationHandle, const Requirement& safetyRequirement) const;

        Requirement get(const DFL::Mdib::VmdActivateOperationHandle& operationHandle) const;
        RequirementsSetStatus set(const DFL::Mdib::VmdActivateOperationHandle& operationHandle, const Requirement& safetyRequirement) const;
        ///@}

        /**
         * @name Safety requirements access for SetContext operations
         * @details Defining safety requirements for context data is only sensible on MDS SCO level.
         */
        ///@{
        Requirement get(const DFL::Mdib::MdsSetContextStateOperationHandle& operationHandle) const;
        RequirementsSetStatus set(const DFL::Mdib::MdsSetContextStateOperationHandle& operationHandle, const Requirement& safetyRequirement) const;

        Requirement get(const DFL::Mdib::VmdSetContextStateOperationHandle& operationHandle) const;
        RequirementsSetStatus set(const DFL::Mdib::VmdSetContextStateOperationHandle& operationHandle, const Requirement& safetyRequirement) const;
        ///@}

        /**
         * @name Safety requirements access for SetAlertState operations
         */
        ///@{
        Requirement get(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle) const;
        RequirementsSetStatus set(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle, const Requirement& safetyRequirement) const;

        Requirement get(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle) const;
        RequirementsSetStatus set(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle, const Requirement& safetyRequirement) const;
        ///@}

        /**
         * @name Safety requirements access for SetComponentState operations
         */
        ///@{
        Requirement get(const DFL::Mdib::MdsSetComponentStateOperationHandle& operationHandle) const;
        RequirementsSetStatus set(const DFL::Mdib::MdsSetComponentStateOperationHandle& operationHandle, const Requirement& safetyRequirement) const;

        Requirement get(const DFL::Mdib::VmdSetComponentStateOperationHandle& operationHandle) const;
        RequirementsSetStatus set(const DFL::Mdib::VmdSetComponentStateOperationHandle& operationHandle, const Requirement& safetyRequirement) const;
        ///@}

        /**
         * @name Safety requirements access for SetMetricState operations
         */
        ///@{
        Requirement get(const DFL::Mdib::MdsSetMetricStateOperationHandle& operationHandle) const;
        RequirementsSetStatus set(const DFL::Mdib::MdsSetMetricStateOperationHandle& operationHandle, const Requirement& safetyRequirement) const;

        Requirement get(const DFL::Mdib::VmdSetMetricStateOperationHandle& operationHandle) const;
        RequirementsSetStatus set(const DFL::Mdib::VmdSetMetricStateOperationHandle& operationHandle, const Requirement& safetyRequirement) const;
        ///@}

    private:
        class Impl;
        std::unique_ptr<Impl> m_impl;
};

}
