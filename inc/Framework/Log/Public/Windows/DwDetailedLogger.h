#pragma once

#include <Framework/Config/Public/Config.h>
#if defined(DFL_CONFIG_OS_WIN32)

#include <Framework/Log/Private/ExpImp.h>
#include <Framework/Log/Private/Windows/BasicDwLogger.h>

namespace DFL
{
namespace Log
{
namespace Windows
{
/**
 * @brief Puts received messages into the "DW-Detailed" Windows Event Logbook.
 *
 * Messages are formatted according to IN9880.
 *
 * @pre Ensure that the according logbook is installed on your windows machine.
 * Otherwise messages appear in the Application Logbook.
 * For installation execute S32/Framework/Log/Tools/WinEvtLog/InstallDwLogs.ps1
 * with admin rights.
 *
 * @ingroup Log
 */
class DFL_LOG_EXPIMP DwDetailedLogger : public Impl::Windows::BasicDwLogger
{
public:
    DwDetailedLogger();
};
}
}
}

#endif
