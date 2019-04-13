// Copyright (c) Miika Pelkonen. All rights reserved.
// Licensed under the MIT License.

#include "Mipe3DRenderable.h"

#include "Mipe3DMesh.h"
#include "Mipe3DMaterial.h"
#include "Mipe3DShaderProgram.h"
#include "Mipe3DCamera.h"
#include "Mipe3DTime.h"

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

Transform& Renderable::getTransform()
{
    return m_transform;
}

Renderable::Renderable()
{

}

void Renderable::render()
{
    if (!m_mesh || !m_material || !m_material->m_shaderProgram)
    {
        return;
    }
    
    // NOTE: viewMatrix and projectionMatrix
    //       are calculated for every renderable, which
    //       is not very efficient
    auto modelMatrix = m_transform.getMatrix();
    auto viewMatrix = camera().getViewMatrix();
    auto projectionMatrix = camera().getProjectionMatrix();

    m_material->m_shaderProgram->glUse();
    m_material->m_shaderProgram->bindModelMatrix(modelMatrix);
    m_material->m_shaderProgram->bindViewMatrix(viewMatrix);
    m_material->m_shaderProgram->bindProjectionMatrix(projectionMatrix);
    m_material->m_shaderProgram->bindTime(time().getTime());

    if (m_material->m_texture)
    {
        m_material->m_shaderProgram->bindTexture(*m_material->m_texture);
    }

    m_mesh->glBindBuffers();
    m_mesh->glDrawTriangles();
    m_mesh->glUnbindBuffers();

    m_material->m_shaderProgram->glUnuse();
}

} // namespace mipe3d