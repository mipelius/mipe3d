#pragma once

#ifdef MIPE3D_EXPORTS
#define MIPE3D_API __declspec(dllexport)
#else
#define MIPE3D_API __declspec(dllimport)
#endif