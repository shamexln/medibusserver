#pragma once

#include <S31/Base/S31Only/PtrHelper.h>
#include <S31/Log/Public/Logger.h>

/**
 * @ingroup S31Utils
 */
#define S31_UTILS_LOCK_OR_RETURN(ptr) S31_BASE_LOCK_OR_RETURN(ptr, S31_STREAM_WARN)

/**
 * @ingroup S31Utils
 */
#define S31_UTILS_LOCK_OR_RETURN_VALUE(ptr, value) S31_BASE_LOCK_OR_RETURN_VALUE(ptr, value, S31_STREAM_WARN)

/**
 * @ingroup S31Utils
 */
#define S31_UTILS_LOCK_OR_RETURN_MSG(ptr, msg) S31_BASE_LOCK_OR_RETURN_MSG(ptr, msg, S31_STREAM_WARN)

/**
 * @ingroup S31Utils
 */
#define S31_UTILS_LOCK_OR_RETURN_VALUE_MSG(ptr, value, msg) S31_BASE_LOCK_OR_RETURN_VALUE_MSG(ptr, value, msg, S31_STREAM_WARN)
