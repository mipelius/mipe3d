#pragma once

#include "apidef.h"

namespace mipe3d
{
class Mesh;

class MIPE3D_API Renderable
{
friend class RenderSystem;

public:
	void setMesh(Mesh* mesh);

private:
	Renderable();
	virtual ~Renderable() {}

	void render();

	Mesh* m_mesh = nullptr;
};

} // namespace mipe3d