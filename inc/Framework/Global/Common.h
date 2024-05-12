#pragma once

#if defined(WIN32) && !defined(PLATFORM_DO_STATIC_LINKAGE)
#define DLL_IMPORT __declspec(dllimport)
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_IMPORT
#define DLL_EXPORT

#endif
