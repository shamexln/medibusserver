#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Defines the usage for a medical object in the MDIB.
 * @details Enumeration values prefixed with "Medical" indicate the maximum acceptable "severity" the information is suitable to support.
 *
 * \note The severity levels refer to the levels given in IEC 62304.
 * \note The risk assessment of the manufacturer has to consider for each information the effects of erroneous information on third party devices,
 * especially the severity of the resulting harm, which may be limited to the severity stated by this flag.
 * E.g., a manufacturer flags an information as suitable to contribute to hazards with severity "No injury or damage to health is possible".
 * Within his risk assessment the manufacturer may assume that erroneous information will not lead to harm and the associated risk is acceptable.
 * @ingroup Mdib
 */
enum class SafetyClassification
{
    /// The descriptor and the related state information shall be used for information purposes only. They are not intended to be used in medical-grade algorithms or applications.
    Informational,
    /// Class A indicates that no injury or damage to health is possible if the descriptor and/or related state information is somehow erroneous.
    MedicalClassA,
    /// Class B indicates that non-serious injury is possible if the descriptor and/or related state information is somehow erroneous.
    MedicalClassB,
    /// Class C indicates that death or serious injury is possible if the descriptor and/or related state information is somehow erroneous.
    MedicalClassC
};
DFL_ENUM_CLASS_STREAM_OPERATOR(SafetyClassification, (Informational)(MedicalClassA)(MedicalClassB)(MedicalClassC))

} /* namespace Mdib */
} /* namespace DFL */
