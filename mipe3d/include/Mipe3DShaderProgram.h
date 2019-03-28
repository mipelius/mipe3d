#pragma once

#include "apidef.h"
#include "Mipe3DResource.h"

typedef unsigned int GLuint;

namespace mipe3d
{

class MIPE3D_API ShaderProgram : public Resource
{
friend class Renderable;

public:
	ShaderProgram(const std::string& filePath);
	~ShaderProgram() override;
	
protected:
	bool loadInternal(const nlohmann::json& metaDefinition) override;
	void unloadInternal() override;

private:
	void glUse();
	void glUnuse();

	GLuint m_programId = 0;
};

} // namespace mipe3d