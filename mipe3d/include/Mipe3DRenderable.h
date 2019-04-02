#pragma once

#include "apidef.h"

namespace mipe3d
{
class Mesh;

class Renderable
{
friend class RenderSystem;

public:
    MIPE3D_API void setMesh(Mesh* mesh);

private:
    Renderable();
    virtual ~Renderable() {}

    void render();

    Mesh* m_mesh = nullptr;
};

} // namespace mipe3d