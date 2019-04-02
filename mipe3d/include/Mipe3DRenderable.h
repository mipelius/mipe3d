#pragma once

#include "apidef.h"

namespace mipe3d
{
class Mesh;
class Material;

class Renderable
{
friend class RenderSystem;

public:
    MIPE3D_API void setMesh(Mesh* mesh);
    MIPE3D_API void setMaterial(Material* material);

private:
    Renderable();
    virtual ~Renderable() {}

    void render();

    Mesh* m_mesh = nullptr;
    Material* m_material = nullptr;
};

} // namespace mipe3d