#include "Mipe3DShaderProgram.h"
#include "Mipe3DJsonUtil.h"
#include "Mipe3DLog.h"
#include "Mipe3DTexture.h"

#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <nlohmann/json.hpp>

namespace mipe3d
{

ShaderProgram::ShaderProgram(const std::string& filePath) : Resource(filePath) 
{ 
}

ShaderProgram::~ShaderProgram() 
{ 
}

bool ShaderProgram::loadInternal(const nlohmann::json& metaDefinition)
{
    // parse vertex shader source path
    JsonValueParserStatus status;

    auto vertexShaderSourcePath = 
        parseStringFromJson(metaDefinition, "vertex_shader_source", status);

    if (status.error != JsonValueParserError::NONE)
    {
        MIPE3D_LOG_ERROR(getFilePath() + ", " + status.errorMessage);
        return false;
    }

    // parse fragment shader source path
    auto fragmentShaderSourcePath =
        parseStringFromJson(metaDefinition, "fragment_shader_source", status);

    if (status.error != JsonValueParserError::NONE)
    {
        MIPE3D_LOG_ERROR(getFilePath() + ", " + status.errorMessage);
        return false;
    }

    // compile and link
    GLuint vertexShaderId;
    if (!compileShader(
        vertexShaderSourcePath,
        GL_VERTEX_SHADER,
        vertexShaderId))
    {
        return false;
    }
    
    GLuint fragmentShaderId;
    if (!compileShader(
        fragmentShaderSourcePath,
        GL_FRAGMENT_SHADER,
        fragmentShaderId))
    {
        return false;
    }

    GLuint programId;
    if (!linkProgram(fragmentShaderId, vertexShaderId, programId))
    {
        return false;
    }

    // success -> store program id 
    //            and set uniform locations
    m_programId = programId;
    m_uniformModelMatrixId = glGetUniformLocation(
        m_programId, UNIFORM_MODEL_MATRIX.c_str());
    m_uniformViewMatrixId = glGetUniformLocation(
        m_programId, UNIFORM_VIEW_MATRIX.c_str());
    m_uniformProjectionMatrixId = glGetUniformLocation(
        m_programId, UNIFORM_PROJECTION_MATRIX.c_str());
    m_uniformTextureId = glGetUniformLocation(
        m_programId, UNIFORM_TEXTURE.c_str());
    m_uniformTimeId = glGetUniformLocation(
        m_programId, UNIFORM_TIME.c_str());

    // clean up
    glDetachShader(programId, vertexShaderId);
    glDetachShader(programId, fragmentShaderId);
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return true;
}

void ShaderProgram::unloadInternal()
{
    glDeleteProgram(m_programId);
}

void ShaderProgram::glUse()
{
    glUseProgram(m_programId);
}

void ShaderProgram::bindModelMatrix(const glm::mat4x4& modelMatrix)
{
    glUniformMatrix4fv(
        m_uniformModelMatrixId, 1, GL_FALSE, &modelMatrix[0][0]);
}

void ShaderProgram::bindViewMatrix(const glm::mat4x4& viewMatrix)
{
    glUniformMatrix4fv(
        m_uniformViewMatrixId, 1, GL_FALSE, &viewMatrix[0][0]);
}

void ShaderProgram::bindProjectionMatrix(const glm::mat4x4& projectionMatrix)
{
    glUniformMatrix4fv(
        m_uniformProjectionMatrixId, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void ShaderProgram::bindTexture(const Texture& texture)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.m_textureId);
    glUniform1i(m_uniformTextureId, 0);
}

void ShaderProgram::bindTime(float time)
{
    glUniform1f(m_uniformTimeId, time);
}

void ShaderProgram::glUnuse()
{
    glUseProgram(0);
}

bool ShaderProgram::compileShader(
    const std::string& filePath,
    GLenum shaderType,
    GLuint& shaderIdOut)
{
    // read shader code from file
    std::string shaderCode;
    std::ifstream filestream(filePath, std::ios::in);

    if (filestream.is_open()) 
    {
        std::stringstream sstr;
        sstr << filestream.rdbuf();
        shaderCode = sstr.str();
        filestream.close();
    }
    else 
    {
        MIPE3D_LOG_ERROR(
            getFilePath() + 
            ", Could not read file \"" +
            filePath + 
            "\"");
        return false;
    }

    // create and compile shader
    shaderIdOut = glCreateShader(shaderType);
    const char* shaderCodeCString = shaderCode.c_str();
    glShaderSource(shaderIdOut, 1, &shaderCodeCString, NULL);
    glCompileShader(shaderIdOut);

    // check errors
    GLint success = GL_FALSE;
    int infoLogLength;
    glGetShaderiv(shaderIdOut, GL_COMPILE_STATUS, &success);
    glGetShaderiv(shaderIdOut, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (success != GL_TRUE) {
        std::vector<char> shaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(
            shaderIdOut, infoLogLength, NULL, &shaderErrorMessage[0]);
        MIPE3D_LOG_ERROR(
            filePath + ", shader compilation failed: " + 
            &shaderErrorMessage[0]);
        glDeleteShader(shaderIdOut);
        return false;
    }

    return true;
}

bool ShaderProgram::linkProgram(
    GLuint vertexShaderId,
    GLuint fragmentShaderId,
    GLuint& programIdOut)
{
    // link
    programIdOut = glCreateProgram();
    glAttachShader(programIdOut, vertexShaderId);
    glAttachShader(programIdOut, fragmentShaderId);
    glLinkProgram(programIdOut);

    // check errors
    GLint success = GL_FALSE;
    int infoLogLength;
    glGetProgramiv(programIdOut, GL_LINK_STATUS, &success);
    glGetProgramiv(programIdOut, GL_INFO_LOG_LENGTH, &infoLogLength);
    
    if (success != GL_TRUE)
    {
        std::vector<char> programErrorMessage(infoLogLength + 1);
        glGetProgramInfoLog(
            programIdOut, infoLogLength, NULL, &programErrorMessage[0]);
        MIPE3D_LOG_ERROR(
            getFilePath() + ", shader program linking failed: " + 
            &programErrorMessage[0]);
        glDeleteProgram(programIdOut);
        return false;
    }

    return true;
}

} // namespace mipe3d