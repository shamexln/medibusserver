#pragma once

#include <Framework/Config/Public/Config.h>

#if defined(DFL_CONFIG_OS_WIN32)
#include <Framework/Config/Public/WindowsProxy.h>
// uncomment this line to check if the includes listed
// underneath cause a compile error
// #include <Windows.h>

// list header files here which are known to not compile
// in conjunction with windows.h
#include <WinSock2.h>
#include <WS2tcpip.h>

#endif
