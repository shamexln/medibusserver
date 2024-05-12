#pragma once

/**
 * @ingroup Config
 * @{
 *
 * @file
 * @brief Do not include this file use Config.h
 */

/**
 * @brief Identifies the operating system vxworks.
 */
#define DFL_CONFIG_OS_VXWORKS

#if defined(__RTP__)
/**
 * @brief Software runs in user space.
 */
#define DFL_CONFIG_USER_SPACE

#elif defined(_WRS_KERNEL)
/**
 * @brief Software runs in kernel space.
 */
#define DFL_CONFIG_KERNEL_SPACE

#else
#error "unknown runtime space"
#endif

/** @} */
