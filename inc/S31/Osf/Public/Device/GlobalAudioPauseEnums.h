#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace S31::Osf
{

/**
 * @brief Indicates whether the audio pause button was pressed to set or cancel audio pause
 * @ingroup S31OsfDevice
 */
enum class AudioPauseStatus
{
    /// audio pause is set
    AudioPauseSet,
    /// audio pause is cancelled
    AudioPauseCancel
};
DFL_ENUM_CLASS_STREAM_OPERATOR(AudioPauseStatus, (AudioPauseSet)(AudioPauseCancel))

}
