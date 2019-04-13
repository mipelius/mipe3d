// Copyright (c) Miika Pelkonen. All rights reserved.
// Licensed under the MIT License.

#pragma once

#ifdef MIPE3D_EXPORTS
#define MIPE3D_API __declspec(dllexport)
#else
#define MIPE3D_API __declspec(dllimport)
#endif