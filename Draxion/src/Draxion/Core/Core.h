#pragma once

#ifdef DRX_BUILD_DLL
	#define DRX_API __declspec(dllexport)
#else
	#define DRX_API __declspec(dllimport)
#endif
