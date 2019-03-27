#include "Mipe3DMesh.h"

#include <GL/glew.h>

#include <fstream>

namespace mipe3d
{

Mesh::Mesh(const std::string& filePath) : Resource(filePath) { }

Mesh::~Mesh()
{

}

bool Mesh::loadInternal(const nlohmann::json& metaDefinition)
{
	// ...
	return true;
}

void Mesh::unloadInternal()
{
	// ...
}

} // namespace mipe3d