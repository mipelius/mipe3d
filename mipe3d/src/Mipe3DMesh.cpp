#include "Mipe3DMesh.h"
#include "Mipe3DJsonUtil.h"
#include "Mipe3DLog.h"

#include <GL/glew.h>
#include <vec3.hpp>
#include <vec2.hpp>

#include <fstream>
#include <nlohmann/json.hpp>

namespace mipe3d
{

Mesh::Mesh(const std::string& filePath) : Resource(filePath) { }

Mesh::~Mesh()
{
}

bool Mesh::loadInternal(const nlohmann::json& metaDefinition)
{
	// parse source path
	JsonValueParserStatus status;

	auto sourcePath = parseStringFromJson(metaDefinition, "source", status);

	if (status.error != JsonValueParserError::NONE)
	{
		MIPE3D_LOG_ERROR(getFilePath() + ", " + status.errorMessage);
		return false;
	}

	// parse obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	bool objWasLoadedSuccessfully = parseObjFile(
		sourcePath,
		vertices,		
		normals,
		uvs
	);

	if (!objWasLoadedSuccessfully)
	{
		return false;
	}

	// generate gl buffers and make data bindings
	m_bufferSize = static_cast<GLsizei>(vertices.size());

	glGenVertexArrays(1, &m_vertexArrayId);
	glBindVertexArray(m_vertexArrayId);

	glGenBuffers(1, &m_vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_normalBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_normalBufferId);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_uvBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvBufferId);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	return true;
}

void Mesh::unloadInternal()
{
	glDeleteBuffers(1, &m_vertexBufferId);
	glDeleteBuffers(1, &m_normalBufferId);
	glDeleteBuffers(1, &m_uvBufferId);
	
	glDeleteVertexArrays(1, &m_vertexArrayId);
}

void Mesh::glBindBuffers()
{
	glEnableVertexAttribArray(GL_ATTRIBUTE_VERTEX);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glVertexAttribPointer(GL_ATTRIBUTE_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(GL_ATTRIBUTE_NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, m_normalBufferId);
	glVertexAttribPointer(GL_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(GL_ATTRIBUTE_UV);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvBufferId);
	glVertexAttribPointer(GL_ATTRIBUTE_UV,	2, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void Mesh::glUnbindBuffers()
{
	glDisableVertexAttribArray(GL_ATTRIBUTE_VERTEX);
	glDisableVertexAttribArray(GL_ATTRIBUTE_NORMAL);
	glDisableVertexAttribArray(GL_ATTRIBUTE_UV);
}

void Mesh::glDrawTriangles()
{
	glDrawArrays(GL_TRIANGLES, 0, m_bufferSize);
}

bool Mesh::parseObjFile(
	const std::string path,
	std::vector<glm::vec3> & outVertices,
	std::vector<glm::vec3> & outNormals,
	std::vector<glm::vec2> & outUvs)
{
	// NOTE: this is just a dummy implementation for now
	outVertices = {
		{ -1.0f, -1.0f, 0.0f },
		{ 1.0f, -1.0f, 0.0f },
		{ 0.0f,  1.0f, 0.0f },
	};
	outNormals = {
		{ 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f },
	};
	outUvs = {
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 0.0f, 1.0f },
	};
	return true;
}

} // namespace mipe3d