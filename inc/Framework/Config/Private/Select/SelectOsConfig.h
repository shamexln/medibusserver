#pragma once

#include <boost/config.hpp>

#if defined(BOOST_WINDOWS)
#include <Framework/Config/Private/Os/Win32.h>
#elif defined(__VXWORKS__)
#include <Framework/Config/Private/Os/VxWorks.h>
#elif defined(__unix__)
#include <Framework/Config/Private/Os/Unix.h>
#else
#error "unknown os"
#endif

/**
 * @ingroup Config
 * @{
 *
 * @file
 * @brief Do not include this file use Config.h
 */

/** @} */
