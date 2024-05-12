#pragma once

#include <Framework/Log/Private/ExpImp.h>

/**
 * @ingroup Log
 * @{
 */
namespace DFL
{
namespace Log
{

class Message;

/**
 * @brief Colorizes the Text attribute of Message according to Severity.
 *
 * SeverityColorizer colorizes the text attribute of Message using ANSI control sequences.
 * These sequences are interpreted by certain terminal applications resulting in colorized text
 * as can be seen in the picture below.
 * @image html Log/Doc/SeverityColorizerMsys2.PNG
 * @warning This features does not work with Windows 7 CMD-Promts.
 * @note This feature works with msys2 terminal windows.
 * @note This feature works with Windows 10 CMD-promts when setting/creating the Windows registry entry "VirtualTerminalLevel" to "1" as depicted in the image below.
 * @image html Log/Doc/SeverityColorizerWindows10Regedit.png
 */
class DFL_LOG_EXPIMP SeverityColorizer
{
public:
    /**
     * @brief Colorizes text attribute of message using ANSI control sequences.
     * @param m message whose text attribute is colorized.
     * @return The message with colorized text attribute
     */
    Message operator()(Message const& m) const;
};

}
}
/** @} */
