#pragma once

#include "apidef.h"
#include "Mipe3DResource.h"
#include <mat4x4.hpp>

typedef unsigned int GLuint;
typedef unsigned int GLenum;

namespace mipe3d
{

class Texture;

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
    
    void bindModelMatrix(const glm::mat4x4& modelMatrix);
    void bindViewMatrix(const glm::mat4x4& viewMatrix);
    void bindProjectionMatrix(const glm::mat4x4& projectionMatrix);
    void bindTexture(const Texture& texture);

    GLuint m_programId = 0;
    GLuint m_uniformModelMatrixId = 0;
    GLuint m_uniformViewMatrixId = 0;
    GLuint m_uniformProjectionMatrixId = 0;
    GLuint m_uniformTextureId = 0;

    const std::string UNIFORM_MODEL_MATRIX = "u_modelMatrix";
    const std::string UNIFORM_VIEW_MATRIX = "u_viewMatrix";
    const std::string UNIFORM_PROJECTION_MATRIX = "u_projectionMatrix";
    const std::string UNIFORM_TEXTURE = "u_texture";
};

} // namespace mipe3d