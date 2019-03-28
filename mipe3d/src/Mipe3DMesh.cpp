#include "Mipe3DMesh.h"

#include <GL/glew.h>
#include <vec3.hpp>
#include <vec2.hpp>

#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

namespace mipe3d
{

Mesh::Mesh(const std::string& filePath) : Resource(filePath) { }

Mesh::~Mesh()
{

}

bool Mesh::loadInternal(const nlohmann::json& metaDefinition)
{
	const char* SOURCE_FIELD = "source";

	if (metaDefinition.find(SOURCE_FIELD) == metaDefinition.end())
	{
		std::cout << 
			"Loading mesh failed, no \"source\" specified." << 
			std::endl;
		
		return false;
	}
	
	auto jsonSource = metaDefinition[SOURCE_FIELD];

	if (!jsonSource.is_string())
	{
		std::cout <<
			"Loading mesh failed, source must be a string value." <<
			std::endl;

		return false;
	}

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	bool objWasLoadedSuccessfully = parseObjFile(
		jsonSource.get<std::string>(),
		vertices,		
		normals,
		uvs
	);

	if (!objWasLoadedSuccessfully)
	{
		return false;
	}

	m_bufferSize = vertices.size();

	glGenVertexArrays(1, &m_vertexArrayId);
	glBindVertexArray(m_vertexArrayId);

	// Bind data to buffers
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