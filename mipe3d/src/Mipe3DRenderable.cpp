#include "Mipe3DRenderable.h"
#include "Mipe3DMesh.h"

namespace mipe3d
{

void Renderable::setMesh(Mesh* mesh)
{
    m_mesh = mesh;
}

Renderable::Renderable()
{

}

void Renderable::render()
{
    // NOTE: missing shader program and uniform bindings
    if (!m_mesh)
    {
        return;
    }

    m_mesh->glBindBuffers();
    m_mesh->glDrawTriangles();
    m_mesh->glUnbindBuffers();
}

} // namespace mipe3d