#pragma once

#include "apidef.h"
#include "Mipe3DResource.h"

typedef unsigned int GLuint;
typedef unsigned int GLenum;

namespace mipe3d
{

class ShaderProgram : public Resource
{
friend class Renderable;

public:
	MIPE3D_API ShaderProgram(const std::string& filePath);
	MIPE3D_API ~ShaderProgram() override;
	
protected:
	bool loadInternal(const nlohmann::json& metaDefinition) override;
	void unloadInternal() override;

private:
	bool compileShader(
		const std::string& filePath,
		GLenum shaderType,
		GLuint& shaderIdOut);
	bool linkProgram(
		GLuint vertexShaderId, 
		GLuint fragmentShaderId, 
		GLuint& idOut);

	void glUse();
	void glUnuse();
	
	GLuint m_programId = 0;
};

} // namespace mipe3d