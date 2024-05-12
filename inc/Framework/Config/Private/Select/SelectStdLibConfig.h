#pragma once

#include <boost/config.hpp>

#if defined(BOOST_GNU_STDLIB)
#define DFL_CONFIG_STDLIB_GNU
#elif defined(BOOST_DINKUMWARE_STDLIB)
#define DFL_CONFIG_STDLIB_DINKUMWARE
#else
#error "unknown std lib"
#endif

/**
 * @ingroup Config
 * @{
 *
 * @file
 * @brief Do not include this file use Config.h
 */

/** @} */
