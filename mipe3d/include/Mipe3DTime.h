// Copyright (c) Miika Pelkonen. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "apidef.h"

typedef unsigned __int32 Uint32;

namespace mipe3d
{

class Time
{
    friend class Engine;
public:
    MIPE3D_API float getTime() const;
    MIPE3D_API float getDeltaTime() const;

private:
    bool startUp();
    bool shutDown();
    void update();

    float m_deltaTime = 0.0f;
    Uint32 m_timeStampOnLastUpdate = 0;
};

// ---- singleton accessor ----

MIPE3D_API const Time& time();

} // namespace mipe3d