#pragma once

#include <S31/Error/Public/GeneratedRemosErrorCodes.h>
#include <S31/Log/Public/Logger.h>

/// Log "General software error" to service stream
#define S31_SERVICE_STREAM_GENERAL_SW_ERROR S31_SERVICE_STREAM_ERROR_LIMITED(\
    S31::Error::RemosCodes::REMOS_ERR_GENERAL_SOFTWARE_ERROR, "General software error")
