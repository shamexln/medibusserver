#pragma once

#include <boost/config.hpp>

#if defined(BOOST_MSVC)
#include <Framework/Config/Private/Compiler/Msvc.h>
// has to be done before gnu
// since clang also defines __GNUC__
#elif defined(__clang__)
#include <Framework/Config/Private/Compiler/Clang.h>
#elif defined(__GNUC__)
#include <Framework/Config/Private/Compiler/Gcc.h>
#else
#error "unknown compiler"
#endif

/**
 * @ingroup Config
 * @{
 *
 * @file
 * @brief Do not include this file use Config.h
 */

/** @} */
