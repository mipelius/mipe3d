#pragma once

#include "apidef.h"
#include "Mipe3DResource.h"

namespace mipe3d
{

class ShaderProgram;
class Texture;

class Material : public Resource
{
friend class Renderable;

public:
	MIPE3D_API Material(const std::string& filePath);
	MIPE3D_API ~Material() override;
	
protected:
	bool loadInternal(const nlohmann::json& metaDefinition) override;
	void unloadInternal() override;

private:
	bool parseShaderProgram(const nlohmann::json& metaDefinition);
	bool parseTexture(const nlohmann::json& metaDefinition);

	ShaderProgram* m_shaderProgram = nullptr;
	Texture* m_texture = nullptr;
};

} // namespace mipe3d