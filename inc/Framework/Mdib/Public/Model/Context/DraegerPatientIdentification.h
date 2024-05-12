#pragma once

#include <boost/optional/optional.hpp>
#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>
#include <Framework/Mdib/Private/ExpImp.h>

namespace DFL::Mdib
{
/**
 * @brief Generates a Draeger patient identification.
 * @details
 * The root is "urn:oid:1.3.6.1.4.1.3592.2.51", extension is a random UUID and
 * the type is MDC_IDT_PATIENT_AUTO_GENERATED.
 * @ingroup Mdib
 */

DFL_MDIB_EXPIMP InstanceIdentifier generateDraegerPatientIdentification();
/**
 * @brief Returns true if \p id contains a Draeger Patient Id root with an
 * invalid extension.
 * @details Due to Modular Requirement PTSR_31233: "An SDC Provider shall not
 * use an empty extension when using the Root 1.3.6.1.4.1.3592.2.51. There is no
 * null flavor for this root."
 *
 * The extension shall be a random UUID according to PTSR_21784: "When an SDC
 * Provider conveys a patient context with ContextAssociation == Assoc then the
 * SDC Provider shall provide at least one PatientContextState/Identification,
 * where the Root is 1.3.6.1.4.1.3592.2.51 and the Extension is a randomly
 * generated UUID acc. to ITU-T Rec. X.667 | ISO/IEC 9834-8:2005."
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP bool isDraegerPatientIdRootWithInvalidExtension(const InstanceIdentifier& id);

/**
 * @brief Returns true if \p id meets the criteria for a Draeger patient identification.
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP bool isDraegerPatientIdentification(const InstanceIdentifier& id);
/**
 * @brief Returns true if one id meets the criteria for a Draeger patient identification.
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP bool hasDraegerPatientIdentification(const InstanceIdentifiers& id);
/**
 * @brief Returns Draeger patient identification if one exists.
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP boost::optional<InstanceIdentifier> draegerPatientIdentification(const InstanceIdentifiers& id);
/**
 * @brief Returns NonDraeger patient identification if one exists.
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP boost::optional<InstanceIdentifier> nonDraegerPatientIdentification(const InstanceIdentifiers& id);
}
