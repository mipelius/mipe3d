// Copyright (c) Miika Pelkonen. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "apidef.h"
#include "Mipe3DTransform.h"

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
    MIPE3D_API Transform& getTransform();

private:
    Renderable();
    virtual ~Renderable() {}

    void render();

    Transform m_transform;
    Mesh* m_mesh = nullptr;
    Material* m_material = nullptr;
};

} // namespace mipe3d