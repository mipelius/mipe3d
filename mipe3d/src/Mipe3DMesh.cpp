#include "Mipe3DMesh.h"
#include "Mipe3DJsonUtil.h"
#include "Mipe3DLog.h"

#include <GL/glew.h>
#include <vec3.hpp>
#include <vec2.hpp>

#include <fstream>
#include <sstream>
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
    // [1] --- open file stream
    std::ifstream filestream(path, std::ios::in);
    
    if (!filestream.is_open())
    {
        MIPE3D_LOG_ERROR(
            getFilePath() +
            ", Could not read file \"" +
            path +
            "\"");
        
        return false;
    }

    // [2] --- read mesh data into temporary vectors
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> tempVertices;
    std::vector<glm::vec2> tempUvs;
    std::vector<glm::vec3> tempNormals;

    std::string line;
    while (std::getline(filestream, line))
    {
        std::stringstream linestream(line);

        std::string lineHeader;
        linestream >> lineHeader;

        if (lineHeader.empty())
        {
            continue;
        }
        else if (lineHeader == "v")
        {
            glm::vec3 vertex;
            linestream >> vertex.x >> vertex.y >> vertex.z;

            tempVertices.push_back(vertex);
        }
        else if (lineHeader == "vn")
        {
            glm::vec3 normal;
            linestream >> normal.x >> normal.y >> normal.z;

            tempNormals.push_back(normal);
        }
        else if (lineHeader == "vt")
        {
            glm::vec2 uv;
            linestream >> uv.x >> uv.y;

            tempUvs.push_back(uv);
        }
        else if (lineHeader == "f")
        {
            std::string indexString;
            std::array<std::string, 3> faceTokens;
            std::array<unsigned int, 3> indices;

            linestream >> faceTokens[0] >> faceTokens[1] >> faceTokens[2];

            // for each faceToken, read slash separated indices
            for (const auto& faceToken : faceTokens)
            {
                std::stringstream faceTokenStream(faceToken);
                 
                for (auto& index : indices)
                {
                    std::getline(faceTokenStream, indexString, '/');
                    index = std::stoul(indexString);
                }

                vertexIndices.push_back(indices[0]);
                uvIndices.push_back(indices[1]);
                normalIndices.push_back(indices[2]);
            }
        }
    }

    // [3] --- extract temporary data into out-vectors
    for (unsigned int i = 0; i < vertexIndices.size(); i++)
    {
        unsigned int vertexIndex = vertexIndices[i] - 1;
        unsigned int uvIndex = uvIndices[i] - 1;
        unsigned int normalIndex = normalIndices[i] - 1;

        glm::vec3 vertex = tempVertices[vertexIndex];
        glm::vec2 uv = tempUvs[uvIndex];
        glm::vec3 normal = tempNormals[normalIndex];

        outVertices.push_back(vertex);
        outUvs.push_back(uv);
        outNormals.push_back(normal);
    }

    return true;
}

} // namespace mipe3d