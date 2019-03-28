#include "Mipe3DShaderProgram.h"

#include <GL/glew.h>

#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

namespace mipe3d
{

ShaderProgram::ShaderProgram(const std::string& filePath) : Resource(filePath) { }

ShaderProgram::~ShaderProgram() { }

bool ShaderProgram::loadInternal(const nlohmann::json& metaDefinition)
{
	const char* VERTEX_SHADER_SOURCE_FIELD = "vertex_shader_source";
	const char* FRAGMENT_SHADER_SOURCE_FIELD = "fragment_shader_source";
	
	return true;
}

void ShaderProgram::unloadInternal()
{

}

void ShaderProgram::glUse()
{
	// glUseProgram(m_programId);
}

void ShaderProgram::glUnuse()
{
	glUseProgram(0);
}

} // namespace mipe3d