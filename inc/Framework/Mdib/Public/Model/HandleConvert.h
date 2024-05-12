#pragma once

#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Private/ExpImp.h>

#include <string>

namespace DFL
{
namespace Mdib
{
namespace Convert
{

/**
 * @brief Converts a string list of handles (white spaces separated) into the \ref DFL::Mdib::Handles type.
 * @param handleList A string with white space separated (valid) handles.
 * @return Filled container.
 * @throws std::runtime_error in case of invalid string (e.g., contains an invalid handle).
 * @ingroup Mdib
 */
template <typename T_Handles>
DFL_MDIB_EXPIMP T_Handles toHandles(const std::string& handleList);

/**
 * @brief Converts a handle container to space separated string.
 * @param handles Container with valid handles.
 * @return String containing space separated handles.
 * @throws std::runtime_error in case of invalid handles.
 * @ingroup Mdib
 */
template<typename T_HandleContainer>
DFL_MDIB_EXPIMP std::string internalToString(const T_HandleContainer& handles);

/**
 * @brief Converts handles to a space separated string.
 * @param handles Container with valid handles.
 * @return String containing space separated handles.
 * @throws std::runtime_error in case of invalid handles.
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP std::string toString(const Handles& handles);

/**
 * @brief Converts s handleset to a space separated string.
 * @param handles Container with valid handles.
 * @return String containing space separated handles.
 * @throws std::runtime_error in case of invalid handles.
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP std::string toString(const HandleSet& handles);

}
}
}
