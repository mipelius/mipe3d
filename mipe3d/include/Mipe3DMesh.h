#pragma once

#include "apidef.h"
#include "Mipe3DResource.h"
#include <vec3.hpp>
#include <vec2.hpp>

typedef unsigned int GLuint;

namespace mipe3d
{

class MIPE3D_API Mesh : public Resource
{
public:
	Mesh(const std::string& filePath);
	~Mesh() override;
	
protected:
	bool loadInternal(const nlohmann::json& metaDefinition) override;
	void unloadInternal() override;

private:
	GLuint m_vertexArrayId;
	GLuint m_vertexBufferId;
	GLuint m_normalBufferId;
	GLuint m_uvBufferId;

	bool parseObjFile(
		const std::string path,
		std::vector<glm::vec3>& outVertices,
		std::vector<glm::vec3>& outNormals,
		std::vector<glm::vec2>& outUvs);
};

} // namespace mipe3d