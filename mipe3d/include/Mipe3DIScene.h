#pragma once

#include "apidef.h"

namespace mipe3d
{

class IScene
{
public:
    MIPE3D_API virtual ~IScene() {};

    MIPE3D_API virtual bool startUp() = 0;
    MIPE3D_API virtual bool shutDown() = 0;
    MIPE3D_API virtual void update() = 0;
};

} // namespace mipe3d