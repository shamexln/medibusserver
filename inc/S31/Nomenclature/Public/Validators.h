#pragma once

#include <Framework/Mdib/Public/Model/CodedValueFactory.h>
#include <Framework/Mdib/Public/Model/Uri.h>

namespace S31::Nomenclature
{

/**
 * \brief Constant root of all Draeger specific validating actor elements.
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::Uri DraegerValidatorRoot = DFL::Mdib::Uri{"urn:oid:1.3.6.1.4.1.3592.2.73"};

/**
 * \brief \ref DFL::Mdib::CodedValue for 11073 code MDC_CTX_USR_VALIDATED (user validated context).
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodedValue MDC_CTX_USR_VALIDATED = DFL::Mdib::CodedValueFactory::create11073cfCode("532640");

/**
 * \brief \ref DFL::Mdib::CodedValue for 11073 code MDC_CTX_CSUSR_VALIDATED (clinical super user validated context).
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodedValue MDC_CTX_CSUSR_VALIDATED = DFL::Mdib::CodedValueFactory::create11073cfCode("532641");

/**
 * \brief \ref DFL::Mdib::CodedValue for 11073 code MDC_CTX_RO_VALIDATED (responsible organization/BioMed validated context).
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodedValue MDC_CTX_RO_VALIDATED = DFL::Mdib::CodedValueFactory::create11073cfCode("532642");

/**
 * \brief \ref DFL::Mdib::CodedValue for 11073 code MDC_CTX_SP_VALIDATED (service personnel validated context).
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodedValue MDC_CTX_SP_VALIDATED = DFL::Mdib::CodedValueFactory::create11073cfCode("532643");

/**
 * \brief \ref DFL::Mdib::CodedValue for 11073 code MDC_CTX_XC_VALIDATED (SDC external control/remote operation validated context).
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodedValue MDC_CTX_XC_VALIDATED = DFL::Mdib::CodedValueFactory::create11073cfCode("532644");

/**
 * \brief Constant representing the Validator element with technical means as being the validating actor.
 * \details It is used to infer context states.
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::Uri TechnicalValidator = DFL::Mdib::Uri("urn:oid:1.3.6.1.4.1.3592.2.73.5");

/**
 * \brief \ref DFL::Mdib::CodedValue for 11073 code MDC_CTX_PROV_VALIDATED (technical-means validated context).
 * \ingroup S31Nomenclature
 */
static const DFL::Mdib::CodedValue MDC_CTX_PROV_VALIDATED = DFL::Mdib::CodedValueFactory::create11073cfCode("532645");

}
