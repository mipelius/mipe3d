#include "Mipe3DRenderable.h"

#include "Mipe3DMesh.h"
#include "Mipe3DMaterial.h"
#include "Mipe3DShaderProgram.h"

namespace mipe3d
{

void Renderable::setMesh(Mesh* mesh)
{
    m_mesh = mesh;
}

void Renderable::setMaterial(Material* material)
{
    m_material = material;
}

Renderable::Renderable()
{

}

void Renderable::render()
{
    // NOTE: missing shader program and uniform bindings
    if (!m_mesh || !m_material)
    {
        return;
    }
   
    m_material->m_shaderProgram->glUse();

    m_mesh->glBindBuffers();
    m_mesh->glDrawTriangles();
    m_mesh->glUnbindBuffers();

    m_material->m_shaderProgram->glUnuse();
}

} // namespace mipe3d