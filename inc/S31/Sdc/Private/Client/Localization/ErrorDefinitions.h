#pragma once

#include <S31/Utils/Public/Errors.h>

namespace S31::Sdc::Impl::LocalizationImpl::Errors
{

/**
 * @brief Received (positive) outcome, but no job information available
 * @ingroup S31LocalizationCommon
 */
struct OutcomeNotAssignableToJob: Utils::SpecificError
{
};

/**
 * @brief Received (positive) outcome, but no transaction information available
 * @ingroup S31LocalizationCommon
 */
struct OutcomeNotAssignableToTransaction: Utils::SpecificError
{
};

/**
 * @brief %Job cannot be sliced into smaller jobs.
 * @ingroup S31LocalizationCommon
 */
struct JobNotSliceable: Utils::SpecificError
{
};

/**
 * @brief @ref S31::Sdc::LocalizationClient::setActiveLanguage() was not called before fetch.
 * @ingroup S31LocalizationCommon
 */
struct NoActiveLanguage: Utils::SpecificError
{
};

}
